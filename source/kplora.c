//This file contains functions specific to the KP-LORA protocol
#include <string.h>
#include "kplora.h"

kppacket_t KPLORA_selfTelemetryPacket;
kppacket_t KPLORA_relayBuffer[KPLORA_RELAYBUFFER_SIZE];
kppacket_t KPLORA_receivedPacket;
KPLORA_ProtocolTier KPLORA_protocolTier;
int KPLORA_LBTCounter;
uint16_t KPLORA_packetCounter = 0;

void KPLORA_pack_data_standard(int _state, uint32_t time_ms, uint8_t _vbat, uint32_t _lat, uint32_t _lon, uint32_t _alt, uint8_t _fix, uint8_t _sats) {

	kppacket_header_t header = {
		.packet_id.msg_type = PACKET_TRACKER,
		.packet_id.msg_ver = 0,
		.packet_id.retransmit = 0,
		.packet_id.encoded = 0,
		.packet_id.redu = 0,
		.sender_id = TRACKER_ID,
		.dest_id = 0,
		.packet_no = KPLORA_packetCounter++,
		.timestamp_ms = time_ms,
		.CRC16 = 0
	};

	kppacket_payload_rocket_tracker_t payload = {
		.retransmission_cnt = 0,
		.vbat_10 = _vbat,
		.lat = _lat,
		.lon = _lon,
		.alti_gps = _alt,
		.sats_fix = ((_fix & 3) << 6) | (_sats & 0x3F)
	};

	KPLORA_selfTelemetryPacket.packet_len = sizeof(kppacket_header_t) + sizeof(kppacket_payload_rocket_tracker_t);
	memcpy(&(KPLORA_selfTelemetryPacket.header), &header, sizeof(kppacket_header_t));
	memcpy(&(KPLORA_selfTelemetryPacket.payload), &payload, sizeof(kppacket_payload_rocket_tracker_t));
}

void KPLORA_send_data_lora() {
	HW_writeLED(1);
	RADIO_sendPacketLoRa((uint8_t*)&(KPLORA_selfTelemetryPacket.header), KPLORA_selfTelemetryPacket.packet_len, 500);
	HW_writeLED(0);
	RADIO_clearIrqStatus();
	HW_DelayMs(5);
}

void KPLORA_fillRelayBuffer(kppacket_t newData, kppacket_t* buffer) {
	for(int i = 0;i<KPLORA_RELAYBUFFER_SIZE;i++) {
		if(buffer[i].header.packet_id.ID == 0) {
			buffer[i] = newData;
			return;
		}
	}
}

void KPLORA_listenForPackets() {
	RADIO_clearIrqStatus();
	HW_DelayMs(5);

	RADIO_setRxSingle();
	HW_DelayMs(5);

	uint32_t time_now = HW_getTimeMs();
	while((HW_getTimeMs() - time_now) < TRACKER_TRANSMISSION_SPACING) {
		if((RADIO_readIrqStatus() & 0x2) == 0x2) {
			if(RADIO_getCRC() == 0) {
				if(RADIO_getRxPayloadSize() == sizeof(KPLORA_selfTelemetryPacket)) {
					RADIO_getRxPayload((uint8_t*)&KPLORA_receivedPacket);
					if(KPLORA_receivedPacket.header.packet_id.ID == KPLORA_PACKET_ID_FULL) {
						KPLORA_fillRelayBuffer(KPLORA_receivedPacket, KPLORA_relayBuffer);
					}
				}
			}
			RADIO_setBufferBaseAddress(0, 100);
			RADIO_clearIrqStatus();
			HW_DelayMs(5);
		}
	}
}

int KPLORA_listenBeforeTalk() {
	uint32_t time_now = HW_getTimeMs();

	while((HW_getTimeMs() - time_now) < KPLORA_LBT1_TIMEOUT) { //If the interference doesn't stop after 5s, transmit anyway
		HW_DelayMs((uint8_t)(RADIO_getRandInt(1)));
		int flag = 1;
		int i;
		for(i=0;i<10;i++) {
			if((RADIO_get_CAD()) || (RADIO_get_rssi() > -90)) {
				flag = 0;
				break;
			}
		}
		if(flag == 1) {
			break;
		}
	}
	return 1;
}

void KPLORA_transmitRelayBuffer() {
	for(int i=0;i<KPLORA_RELAYBUFFER_SIZE;i++) {
		if(KPLORA_relayBuffer[i].header.packet_id.ID == KPLORA_PACKET_ID_FULL) {
			KPLORA_relayBuffer[i].header.packet_id.ID = KPLORA_PACKET_ID_FULL_RETRANSMIT;
			KPLORA_listenBeforeTalk();
			HW_writeLED(1);
			RADIO_sendPacketLoRa((uint8_t*)&KPLORA_relayBuffer[i], sizeof(DataPackageRF_t), 500);
			HW_writeLED(0);
			RADIO_clearIrqStatus();
			HW_DelayMs(5);
		}
	}

	for(int i=0;i<KPLORA_RELAYBUFFER_SIZE;i++) {
		KPLORA_relayBuffer[i].header.packet_id.ID = 0;
	}
}
