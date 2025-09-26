#include "trackerHw.h"
#include "gps.h"

//#define DEBUG_PRINTF(x...) printf(x)
#define DEBUG_PRINTF(x...);


uint32_t GPS_lat_unsigned = 0;
uint32_t GPS_lon_unsigned = 0;
int32_t  GPS_lat = 0;
int32_t  GPS_lon = 0;
int32_t  GPS_alt = 0;
uint8_t  GPS_sat_count = 0;
uint8_t  GPS_fix = 0;
char     GPS_sentence[NMEA_MAX_SENTENCE_LENGTH];
uint8_t  GPS_msg_id = 0;
bool     GPS_msg_started = 0;
char txMessageBuffer[64];

void GPS_init(){
	GPS_sendCmd(PMTK_RESET);
	GPS_sendCmd(PMTK_SET_GPGGA);
	GPS_sendCmd(PMTK_SET_FAST_UPDATE);
}

void GPS_startup() {
	while(GPS_getSats() < 5) {
		HW_writeLED(1);
		HW_DelayMs(500);
		HW_writeLED(0);
		HW_DelayMs(500);

		for(int i=0; i<GPS_getSats(); i++) {
			HW_writeLED(1);
			HW_DelayMs(50);
			HW_writeLED(0);
			HW_DelayMs(300);
		}
		HW_DelayMs(1000);
	}
}

uint8_t GPS_getSats(){
	return GPS_sat_count;
}

int32_t GPS_getLat(){
	return GPS_lat;
}

int32_t GPS_getLon(){
	return GPS_lon;
}

uint8_t GPS_getFix(){
	return GPS_fix;
}

int32_t GPS_getAlt(){
	return GPS_alt;
}

uint32_t GPS_parse_lat(char *input) {
    if (!*input) return 0;
    double val = atof(input);
    if (val == 0.0) return 0;
    int deg = (int)(val / 100.0);
    double mins = val - deg * 100.0;
    double decimal = deg + mins / 60.0;

    return (uint32_t)(decimal * 10000000.0 + 0.5);
}

uint32_t GPS_parse_lon(char *input) {
    if (!*input) return 0;
    double val = atof(input);
    if (val == 0.0) return 0;
    int deg = (int)(val / 100.0);
    double mins = val - deg * 100.0;
    double decimal = deg + mins / 60.0;

    return (uint32_t)(decimal * 10000000.0 + 0.5);
}

int32_t GPS_parse_sign(char *input, uint32_t latlon) {
	int32_t result = (int32_t)latlon;
	if (*input == 'S' || *input == 'W') {
		result = -result;
	}

	return result;
}

bool validate_checksum(char *sentence) {
    char *star = strchr(sentence, '*');
    if (!star) return false;
    uint8_t crc = 0;
    for (char *p = sentence; p < star; ++p) {
        crc ^= *p;
    }

    int expected = (int)strtol(star + 1, NULL, 16);
    return crc == expected;
}

uint16_t GPS_crc_calc(char *message) {
	uint8_t crc = 0;
	uint16_t len = strlen(message);

	if(len > 100)
		return 0;

	for (size_t i = 0; i < len; ++i) {
		crc ^= message[i];
	}

	return crc;
}

bool GPS_parse(char c) {
	if(c == '$') {
		GPS_msg_id = 0;
		GPS_msg_started = true;
	}
	else if(c == '\r' && GPS_msg_started) {
		GPS_sentence[GPS_msg_id] = '\0';
		GPS_msg_id = 0;
		GPS_msg_started = false;

		char *star = strchr(GPS_sentence, '*');
		if (!star) {
			DEBUG_PRINTF("Debug: No * found in sentence\n");
		} else {
			uint8_t crc = 0;
			for (char *p = GPS_sentence; p < star; ++p) {
				crc ^= *p;
			}

			DEBUG_PRINTF("Debug: Calculated crc: 0x%02X\n", crc);
			int expected = (int)strtol(star + 1, NULL, 16);
			DEBUG_PRINTF("Debug: Expected crc: 0x%02X\n", expected);
			bool valid = (crc == expected);
			DEBUG_PRINTF("Debug: Checksum valid: %s\n", valid ? "true" : "false");

			if (valid && (GPS_sentence[2] == 'G') && (GPS_sentence[3] == 'G') && (GPS_sentence[4] == 'A')) {
				// Reset values to avoid keeping old data
//				GPS_lat_unsigned = 0;
//				GPS_lon_unsigned = 0;
//				GPS_lat = 0;
//				GPS_lon = 0;
//				GPS_alt = 0;
				GPS_sat_count = 0;
				GPS_fix = 0;

				// Manual field extraction to handle empty fields properly
				char fields[15][64];
				memset(fields, 0, sizeof(fields));
				char *s = strchr(GPS_sentence, ',');  // Skip $xxGGA
				if (s) s++;  // Move to first field (time)
				int fc = 1;  // field 1: time
				while (*s && fc < 15) {
					char *comma = strchr(s, ',');
					if (!comma) comma = s + strlen(s);
					int len = comma - s;
					if (len >= sizeof(fields[0])) len = sizeof(fields[0]) - 1;
					strncpy(fields[fc], s, len);
					fields[fc][len] = '\0';
					s = comma + 1;
					fc++;
				}

				// Print fields for debug
				for (int i = 1; i < 15; ++i) {
					DEBUG_PRINTF("Debug: Field %d: '%s'\n", i, fields[i]);
				}

				// Parse relevant fields
				GPS_lat_unsigned = GPS_parse_lat(fields[2]);
				GPS_lat = GPS_parse_sign(fields[3], GPS_lat_unsigned);
				GPS_lon_unsigned = GPS_parse_lon(fields[4]);
				GPS_lon = GPS_parse_sign(fields[5], GPS_lon_unsigned);
				GPS_fix = atoi(fields[6]);
				GPS_sat_count = atoi(fields[7]);
				if (*fields[9]) {
					double alt_d = atof(fields[9]);
					GPS_alt = (int32_t)(alt_d + 0.5);
				}

				// Print parsed values
				DEBUG_PRINTF("Debug: Parsed GPS_lat: %ld\n", (long)GPS_lat);
				DEBUG_PRINTF("Debug: Parsed GPS_lon: %ld\n", (long)GPS_lon);
				DEBUG_PRINTF("Debug: Parsed GPS_fix: %u\n", GPS_fix);
				DEBUG_PRINTF("Debug: Parsed GPS_sat_count: %u\n", GPS_sat_count);
				DEBUG_PRINTF("Debug: Parsed GPS_alt: %ld\n", (long)GPS_alt);
			} else if (valid) {
				DEBUG_PRINTF("Debug: Valid checksum but not GGA\n");
			}
		}
	} else if(GPS_msg_started && GPS_msg_id < NMEA_MAX_SENTENCE_LENGTH) {
		GPS_sentence[GPS_msg_id] = c;
		GPS_msg_id++;
	}
	return false;
}

bool GPS_getStatus() {
	return GPS_msg_started;
}

void GPS_sendCmd(char *message) {
	int len = sprintf(txMessageBuffer, "$%s*%02X\r\n", message, GPS_crc_calc(message));
	HW_send_UART(txMessageBuffer, len);
}
