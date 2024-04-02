#ifndef _GPS_H
#define _GPS_H

#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>
#include<string.h>

#define NMEA_MAX_SENTENCE_LENGTH 82
#define PMTK_SET_GPGGA "PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0"
#define PMTK_SET_FAST_UPDATE "PMTK220,100"
#define PMTK_RESET "PMTK104"

void GPS_init();
void GPS_startup();
uint8_t GPS_getSats();
int32_t GPS_getLat();
int32_t GPS_getLon();
uint8_t GPS_getFix();
int32_t GPS_getAlt();
uint32_t GPS_parse_lat(char *input);
uint32_t GPS_parse_lon(char *input);
int32_t GPS_parse_sign(char *input, uint32_t latlon);
bool GPS_parse(char c);
bool GPS_getStatus();
uint16_t GPS_crc_calc(char *message);
void GPS_sendCmd(char *message);

#endif
