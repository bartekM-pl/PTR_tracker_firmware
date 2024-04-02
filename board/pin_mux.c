/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v14.0
processor: MKL27Z256xxx4
package_id: MKL27Z256VFM4
mcu_data: ksdk2_0
processor_version: 13.0.1
external_user_signals:
  routingDetailsColumns: ['#', Peripheral, Signal, Arrow]
  signals:
  - id: '1'
    pin_connections: ['28']
  - id: '2'
    pin_connections: ['9']
  - id: '3'
    pin_connections: ['17']
  - id: '4'
    pin_connections: ['18']
  - id: '5'
    pin_connections: ['20']
  - id: '6'
    pin_connections: ['21']
  - id: '7'
    pin_connections: ['22']
  - id: '8'
    pin_connections: ['23']
  - id: '9'
    pin_connections: ['24']
  - id: '10'
    pin_connections: ['25']
  - id: '11'
    pin_connections: ['26']
  - id: '12'
    pin_connections: ['27']
  - id: '13'
    pin_connections: ['29']
  - id: '14'
    pin_connections: ['30']
pin_labels:
- {pin_num: '9', pin_signal: DAC0_OUT/ADC0_SE23/CMP0_IN4/PTE30/TPM0_CH3/TPM_CLKIN1/LPUART1_TX/LPTMR0_ALT1, label: SEL_SW, identifier: SEL_SW}
- {pin_num: '17', pin_signal: EXTAL0/PTA18/LPUART1_RX/TPM_CLKIN0, label: GPS_IN, identifier: GPS_IN}
- {pin_num: '18', pin_signal: XTAL0/PTA19/LPUART1_TX/TPM_CLKIN1/LPTMR0_ALT1, label: GPS_OUT, identifier: GPS_OUT}
- {pin_num: '22', pin_signal: ADC0_SE15/PTC1/LLWU_P6/RTC_CLKIN/I2C1_SCL/TPM0_CH0/I2S0_TXD0, label: VBAT, identifier: VBAT}
- {pin_num: '23', pin_signal: ADC0_SE11/PTC2/I2C1_SDA/TPM0_CH1/I2S0_TX_FS, label: JUMPER_SW, identifier: JUMPER_SW}
- {pin_num: '24', pin_signal: PTC3/LLWU_P7/SPI1_SCK/LPUART1_RX/TPM0_CH2/CLKOUT/I2S0_TX_BCLK, label: LED, identifier: LED}
- {pin_num: '29', pin_signal: PTD4/LLWU_P14/SPI1_SS/UART2_RX/TPM0_CH4/FXIO0_D4, label: LORA_BUSY, identifier: LORA_BUSY}
- {pin_num: '30', pin_signal: ADC0_SE6b/PTD5/SPI1_SCK/UART2_TX/TPM0_CH5/FXIO0_D5, label: LORA_DIO1, identifier: LORA_DIO1}
- {pin_num: '25', pin_signal: PTC4/LLWU_P8/SPI0_SS/LPUART1_TX/TPM0_CH3/I2S0_MCLK, label: LORA_CS, identifier: LORA_CS}
- {pin_num: '26', pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/I2S0_RXD0/CMP0_OUT, label: LORA_SCK, identifier: LORA_SCK}
- {pin_num: '27', pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_MOSI/EXTRG_IN/I2S0_RX_BCLK/SPI0_MISO/I2S0_MCLK, label: LORA_MOSI, identifier: LORA_MOSI}
- {pin_num: '28', pin_signal: CMP0_IN1/PTC7/SPI0_MISO/USB_SOF_OUT/I2S0_RX_FS/SPI0_MOSI, label: LORA_MISO, identifier: LORA_MISO}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '9', peripheral: ADC0, signal: 'SE, 23', pin_signal: DAC0_OUT/ADC0_SE23/CMP0_IN4/PTE30/TPM0_CH3/TPM_CLKIN1/LPUART1_TX/LPTMR0_ALT1}
  - {pin_num: '18', peripheral: LPUART1, signal: TX, pin_signal: XTAL0/PTA19/LPUART1_TX/TPM_CLKIN1/LPTMR0_ALT1, direction: OUTPUT}
  - {pin_num: '17', peripheral: LPUART1, signal: RX, pin_signal: EXTAL0/PTA18/LPUART1_RX/TPM_CLKIN0}
  - {pin_num: '20', peripheral: I2C0, signal: SCL, pin_signal: ADC0_SE8/PTB0/LLWU_P5/I2C0_SCL/TPM1_CH0}
  - {pin_num: '21', peripheral: I2C0, signal: SDA, pin_signal: ADC0_SE9/PTB1/I2C0_SDA/TPM1_CH1}
  - {pin_num: '22', peripheral: ADC0, signal: 'SE, 15', pin_signal: ADC0_SE15/PTC1/LLWU_P6/RTC_CLKIN/I2C1_SCL/TPM0_CH0/I2S0_TXD0}
  - {pin_num: '23', peripheral: GPIOC, signal: 'GPIO, 2', pin_signal: ADC0_SE11/PTC2/I2C1_SDA/TPM0_CH1/I2S0_TX_FS, direction: INPUT}
  - {pin_num: '24', peripheral: GPIOC, signal: 'GPIO, 3', pin_signal: PTC3/LLWU_P7/SPI1_SCK/LPUART1_RX/TPM0_CH2/CLKOUT/I2S0_TX_BCLK, direction: OUTPUT, gpio_init_state: 'true',
    slew_rate: slow, drive_strength: high}
  - {pin_num: '26', peripheral: SPI0, signal: SCK, pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/I2S0_RXD0/CMP0_OUT}
  - {pin_num: '27', peripheral: SPI0, signal: MOSI, pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_MOSI/EXTRG_IN/I2S0_RX_BCLK/SPI0_MISO/I2S0_MCLK}
  - {pin_num: '28', peripheral: SPI0, signal: MISO, pin_signal: CMP0_IN1/PTC7/SPI0_MISO/USB_SOF_OUT/I2S0_RX_FS/SPI0_MOSI}
  - {pin_num: '29', peripheral: GPIOD, signal: 'GPIO, 4', pin_signal: PTD4/LLWU_P14/SPI1_SS/UART2_RX/TPM0_CH4/FXIO0_D4, direction: INPUT}
  - {pin_num: '30', peripheral: GPIOD, signal: 'GPIO, 5', pin_signal: ADC0_SE6b/PTD5/SPI1_SCK/UART2_TX/TPM0_CH5/FXIO0_D5, direction: INPUT}
  - {pin_num: '25', peripheral: GPIOC, signal: 'GPIO, 4', pin_signal: PTC4/LLWU_P8/SPI0_SS/LPUART1_TX/TPM0_CH3/I2S0_MCLK, direction: OUTPUT, gpio_init_state: 'true'}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t JUMPER_SW_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC2 (pin 23)  */
    GPIO_PinInit(BOARD_INITPINS_JUMPER_SW_GPIO, BOARD_INITPINS_JUMPER_SW_PIN, &JUMPER_SW_config);

    gpio_pin_config_t LED_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTC3 (pin 24)  */
    GPIO_PinInit(BOARD_INITPINS_LED_GPIO, BOARD_INITPINS_LED_PIN, &LED_config);

    gpio_pin_config_t LORA_CS_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTC4 (pin 25)  */
    GPIO_PinInit(BOARD_INITPINS_LORA_CS_GPIO, BOARD_INITPINS_LORA_CS_PIN, &LORA_CS_config);

    gpio_pin_config_t LORA_BUSY_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTD4 (pin 29)  */
    GPIO_PinInit(BOARD_INITPINS_LORA_BUSY_GPIO, BOARD_INITPINS_LORA_BUSY_PIN, &LORA_BUSY_config);

    gpio_pin_config_t LORA_DIO1_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTD5 (pin 30)  */
    GPIO_PinInit(BOARD_INITPINS_LORA_DIO1_GPIO, BOARD_INITPINS_LORA_DIO1_PIN, &LORA_DIO1_config);

    /* PORTA18 (pin 17) is configured as LPUART1_RX */
    PORT_SetPinMux(BOARD_INITPINS_GPS_IN_PORT, BOARD_INITPINS_GPS_IN_PIN, kPORT_MuxAlt3);

    /* PORTA19 (pin 18) is configured as LPUART1_TX */
    PORT_SetPinMux(BOARD_INITPINS_GPS_OUT_PORT, BOARD_INITPINS_GPS_OUT_PIN, kPORT_MuxAlt3);

    /* PORTB0 (pin 20) is configured as I2C0_SCL */
    PORT_SetPinMux(PORTB, 0U, kPORT_MuxAlt2);

    /* PORTB1 (pin 21) is configured as I2C0_SDA */
    PORT_SetPinMux(PORTB, 1U, kPORT_MuxAlt2);

    /* PORTC1 (pin 22) is configured as ADC0_SE15 */
    PORT_SetPinMux(BOARD_INITPINS_VBAT_PORT, BOARD_INITPINS_VBAT_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTC2 (pin 23) is configured as PTC2 */
    PORT_SetPinMux(BOARD_INITPINS_JUMPER_SW_PORT, BOARD_INITPINS_JUMPER_SW_PIN, kPORT_MuxAsGpio);

    /* PORTC3 (pin 24) is configured as PTC3 */
    PORT_SetPinMux(BOARD_INITPINS_LED_PORT, BOARD_INITPINS_LED_PIN, kPORT_MuxAsGpio);

    PORTC->PCR[3] = ((PORTC->PCR[3] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_SRE_MASK | PORT_PCR_DSE_MASK | PORT_PCR_ISF_MASK)))

                     /* Slew Rate Enable: Slow slew rate is configured on the corresponding pin, if the pin is
                      * configured as a digital output. */
                     | PORT_PCR_SRE(kPORT_SlowSlewRate)

                     /* Drive Strength Enable: High drive strength is configured on the corresponding pin, if pin
                      * is configured as a digital output. */
                     | PORT_PCR_DSE(kPORT_HighDriveStrength));

    /* PORTC4 (pin 25) is configured as PTC4 */
    PORT_SetPinMux(BOARD_INITPINS_LORA_CS_PORT, BOARD_INITPINS_LORA_CS_PIN, kPORT_MuxAsGpio);

    /* PORTC5 (pin 26) is configured as SPI0_SCK */
    PORT_SetPinMux(BOARD_INITPINS_LORA_SCK_PORT, BOARD_INITPINS_LORA_SCK_PIN, kPORT_MuxAlt2);

    /* PORTC6 (pin 27) is configured as SPI0_MOSI */
    PORT_SetPinMux(BOARD_INITPINS_LORA_MOSI_PORT, BOARD_INITPINS_LORA_MOSI_PIN, kPORT_MuxAlt2);

    /* PORTC7 (pin 28) is configured as SPI0_MISO */
    PORT_SetPinMux(BOARD_INITPINS_LORA_MISO_PORT, BOARD_INITPINS_LORA_MISO_PIN, kPORT_MuxAlt2);

    /* PORTD4 (pin 29) is configured as PTD4 */
    PORT_SetPinMux(BOARD_INITPINS_LORA_BUSY_PORT, BOARD_INITPINS_LORA_BUSY_PIN, kPORT_MuxAsGpio);

    /* PORTD5 (pin 30) is configured as PTD5 */
    PORT_SetPinMux(BOARD_INITPINS_LORA_DIO1_PORT, BOARD_INITPINS_LORA_DIO1_PIN, kPORT_MuxAsGpio);

    /* PORTE30 (pin 9) is configured as ADC0_SE23 */
    PORT_SetPinMux(BOARD_INITPINS_SEL_SW_PORT, BOARD_INITPINS_SEL_SW_PIN, kPORT_PinDisabledOrAnalog);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_LPUART1TXSRC_MASK | SIM_SOPT5_LPUART1RXSRC_MASK)))

                  /* LPUART1 Transmit Data Source Select: LPUART1_TX pin. */
                  | SIM_SOPT5_LPUART1TXSRC(SOPT5_LPUART1TXSRC_LPUART_TX)

                  /* LPUART1 Receive Data Source Select: LPUART1_RX pin. */
                  | SIM_SOPT5_LPUART1RXSRC(SOPT5_LPUART1RXSRC_LPUART_RX));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/