#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_gpio.h"
#include "fsl_uart.h"

#include "gps.h"
#include "trackerHw.h"


static volatile uint32_t systick_msCounter = 0;
static volatile uint32_t TimingDelay = 0;


void SysTick_tickHandler(void) {
	if (TimingDelay != 0x00) {
		TimingDelay--;
	}

	systick_msCounter++;
}

void HW_DelayMs(uint32_t _ms) {
	TimingDelay = _ms;

	while(TimingDelay != 0);
}

uint32_t HW_getTimeMs(){
	return systick_msCounter;
}

void HW_trackerHwInit(void) {
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	SysTick_Config(CLOCK_GetFreq(kCLOCK_CoreSysClk) / 1000U);
	HW_DelayMs(10); // ADC startup
}

void HW_writeLED(bool _value) {
	GPIO_PinWrite(BOARD_INITPINS_LED_GPIO, BOARD_INITPINS_LED_PIN, _value==1);
}

void HW_write_LORACS(bool _value) {
	GPIO_PinWrite(GPIOC, BOARD_INITPINS_LORA_CS_PIN, _value==1);
}

void HW_send_UART(char* _txbuffer, uint8_t _size) {
	LPUART_WriteBlocking(LPUART1_PERIPHERAL, (uint8_t *)_txbuffer, _size);
}

void HW_SPI_WriteBuffer(uint8_t *data, uint32_t size) {
	spi_transfer_t xfer  = {0};

	xfer.txData   = data;
	xfer.rxData   = NULL;
	xfer.dataSize = size;
	SPI_MasterTransferBlocking(SPI0_PERIPHERAL, &xfer);
}

void HW_SPI_ReadBuffer(uint8_t *data, uint32_t size) {
	spi_transfer_t xfer  = {0};

	xfer.txData   = NULL;
	xfer.rxData   = data;
	xfer.dataSize = size;
	SPI_MasterTransferBlocking(SPI0_PERIPHERAL, &xfer);
}

uint32_t HW_readADC(uint8_t _ch) {
    return ADC16_GetChannelConversionValue(ADC0, _ch);
}

uint8_t HW_getVbat(){
	uint32_t raw = HW_readADC(0);
	float tmp = 10.0f * 10.7f * (float)raw * 3.3f / 65536.0f;	//11x bo dzielnik 1:11,   3.3f bo 3.3V Vref,    65536.0f bo 16bit
	return (uint8_t)tmp;
}

uint8_t HW_getSW(){
	uint32_t raw = 0;

	for(int i=0;i<32;i++) {
		raw += HW_readADC(0);
	}
	uint32_t adcValue = raw / 32;

	// Change ADC channel from SW to VBAT
	ADC16_SetChannelConfig(ADC0_PERIPHERAL, ADC0_CH0_CONTROL_GROUP, &ADC0_channelsConfig[1]);

	if(adcValue < 52000)
		return 0;
	else if(adcValue < 56943)
		return 1;
	else if(adcValue < 60591)
		return 2;
	else if(adcValue < 62860)
		return 3;
	else if(adcValue < 64310)
		return 4;
	else if(adcValue < 64425)
		return 5;
	else if(adcValue < 64522)
		return 6;
	else if(adcValue < 65000)
		return 7;
	else
		return 0;
}

uint8_t HW_readDIO1() {
	return GPIO_PinRead(BOARD_INITPINS_LORA_DIO1_GPIO, BOARD_INITPINS_LORA_DIO1_PIN);
}

uint8_t HW_readJMP() {
	return GPIO_PinRead(BOARD_INITPINS_JUMPER_SW_GPIO, BOARD_INITPINS_JUMPER_SW_PIN);
}

void SysTick_Handler() {
	SysTick_tickHandler();
}

void LPUART1_IRQHandler(void) {
	uint32_t intStatus;
	/* Reading all interrupt flags of status registers */
	intStatus = LPUART_GetStatusFlags(LPUART1_PERIPHERAL);

	if(intStatus & kLPUART_RxDataRegFullFlag){
		GPS_parse(LPUART1->DATA);
		LPUART_ClearStatusFlags(LPUART1_PERIPHERAL, kLPUART_RxDataRegFullFlag);
	} else {
		(void)(LPUART1->DATA);
		LPUART_ClearStatusFlags(LPUART1_PERIPHERAL, 0xFFFFFFFF);
	}
}
