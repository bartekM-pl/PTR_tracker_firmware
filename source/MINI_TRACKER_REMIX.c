/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    MINI_TRACKER_REMIX.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "MKL27Z4.h"
#include "trackerState.h"
#include "trackerHw.h"
#include "gps.h"
#include "config.h"
#include "kplora.h"

trackerState state = STARTUP;
uint8_t repeater_enabled = 0;
uint8_t channel = 0;
uint8_t txPower = TRACKER_TXPOWER_LOW;
uint32_t freq_list [4] = {TRACKER_FREQUENCY_0, TRACKER_FREQUENCY_1, TRACKER_FREQUENCY_2, TRACKER_FREQUENCY_3};

void Tracker_setup(uint8_t params) {
	channel = params & 0b11;
	repeater_enabled = params & 0b100;

	if(HW_readJMP()) {
		txPower = TRACKER_TXPOWER_HIGH;
	}
}

int main(void) {
    state = STARTUP;
	HW_trackerHwInit();
	Tracker_setup(HW_getSW());
	RADIO_init();
	RADIO_modeLORA(freq_list[channel], txPower);
	GPS_init();

	state = WAIT_FOR_FIX;
	GPS_startup();

	state = OPERATION;
    while(1) {
    	KPLORA_pack_data_standard(state, HW_getTimeMs(), HW_getVbat(), GPS_getLat(), GPS_getLon(), GPS_getAlt(), GPS_getFix(), GPS_getSats());
		KPLORA_listenBeforeTalk();
		KPLORA_send_data_lora();

		if(repeater_enabled) {
			KPLORA_listenForPackets();
			KPLORA_transmitRelayBuffer();
		} else {
			HW_DelayMs(TRACKER_TRANSMISSION_SPACING);
		}
    }

    return 0 ;
}
