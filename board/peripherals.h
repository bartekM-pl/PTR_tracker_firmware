/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_adc16.h"
#include "fsl_lpuart.h"
#include "fsl_clock.h"
#include "fsl_spi.h"
#include "fsl_vref.h"
#include "fsl_tpm.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* Alias for ADC0 peripheral */
#define ADC0_PERIPHERAL ADC0
/* ADC0 interrupt vector ID (number). */
#define ADC0_IRQN ADC0_IRQn
/* ADC0 interrupt handler identifier. */
#define ADC0_IRQHANDLER ADC0_IRQHandler
/* Channel 0 (SE.15) conversion control group. */
#define ADC0_CH0_CONTROL_GROUP 0
/* Channel 1 (SE.23) conversion control group. */
#define ADC0_CH1_CONTROL_GROUP 1
/* Definition of peripheral ID */
#define LPUART1_PERIPHERAL LPUART1
/* Definition of the clock source frequency */
#define LPUART1_CLOCK_SOURCE 8000000UL
/* LPUART1 interrupt vector ID (number). */
#define LPUART1_SERIAL_RX_TX_IRQN LPUART1_IRQn
/* LPUART1 interrupt handler identifier. */
#define LPUART1_SERIAL_RX_TX_IRQHANDLER LPUART1_IRQHandler
/* BOARD_InitPeripherals defines for SPI0 */
/* Definition of peripheral ID */
#define SPI0_PERIPHERAL SPI0
/* Definition of the clock source */
#define SPI0_CLOCK_SOURCE SPI0_CLK_SRC
/* Definition of the clock source frequency */
#define SPI0_CLK_FREQ CLOCK_GetFreq(SPI0_CLOCK_SOURCE)
/* Alias for VREF peripheral */
#define VREF_PERIPHERAL VREF
/* Alias for VREF initial trim value */
#define VREF_INITIAL_TRIM 0U
/* Definition of peripheral ID */
#define TPM0_PERIPHERAL TPM0
/* Definition of the clock source frequency */
#define TPM0_CLOCK_SOURCE 8000000UL
/* TPM0 interrupt vector ID (number). */
#define TPM0_IRQN TPM0_IRQn
/* TPM0 interrupt handler identifier. */
#define TPM0_IRQHANDLER TPM0_IRQHandler

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern adc16_channel_config_t ADC0_channelsConfig[2];
extern const adc16_config_t ADC0_config;
extern const adc16_channel_mux_mode_t ADC0_muxMode;
extern const adc16_hardware_average_mode_t ADC0_hardwareAverageMode;
extern const lpuart_config_t LPUART1_config;
extern const spi_master_config_t SPI0_config;
extern const vref_config_t VREF_config;
extern const tpm_config_t TPM0_config;

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/

void BOARD_InitPeripherals(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
