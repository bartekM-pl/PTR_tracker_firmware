#ifndef _TRACKERHW_H
#define _TRACKERHW_H

#include<stdint.h>
#include<stdbool.h>
#include "MKL27Z4.h"

void SysTick_tickHandler(void);
void HW_DelayMs(uint32_t _ms);
uint32_t HW_getTimeMs();

void HW_trackerHwInit(void);
void HW_writeLED(bool _value);
void HW_write_LORACS(bool _value);
void HW_send_UART(char* _txbuffer, uint8_t _size);
void HW_SPI_WriteBuffer(uint8_t *data, uint32_t size);
void HW_SPI_ReadBuffer(uint8_t *data, uint32_t size);
uint32_t HW_readADC(uint8_t _ch);
uint8_t HW_getVbat();
uint8_t HW_getSW();
uint8_t HW_readDIO1();
uint8_t HW_readJMP();

#endif
