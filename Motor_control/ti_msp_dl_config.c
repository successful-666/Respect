/*
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_TIMER_0_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_UART_1_init();
    SYSCFG_DL_UART_2_init();
    SYSCFG_DL_SYSTICK_init();
}



SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerG_reset(TIMER_0_INST);
    DL_UART_Main_reset(UART_0_INST);
    DL_UART_Main_reset(UART_1_INST);
    DL_UART_Main_reset(UART_2_INST);


    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerG_enablePower(TIMER_0_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_UART_Main_enablePower(UART_1_INST);
    DL_UART_Main_enablePower(UART_2_INST);

    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_1_IOMUX_TX, GPIO_UART_1_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_1_IOMUX_RX, GPIO_UART_1_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_2_IOMUX_TX, GPIO_UART_2_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_2_IOMUX_RX, GPIO_UART_2_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalOutputFeatures(LED_PIN0_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);

    DL_GPIO_initDigitalOutput(OLED_SCL_IOMUX);

    DL_GPIO_initDigitalOutput(OLED_SDA_IOMUX);

    DL_GPIO_clearPins(GPIOA, LED_PIN0_PIN);
    DL_GPIO_setPins(GPIOA, OLED_SCL_PIN |
		OLED_SDA_PIN);
    DL_GPIO_enableOutput(GPIOA, LED_PIN0_PIN |
		OLED_SCL_PIN |
		OLED_SDA_PIN);

}



SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_enableMFCLK();

}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   40000 Hz = 4000000 Hz / (8 * (99 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_0ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 99U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_0_INST_LOAD_VALUE = (100ms * 40000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_0TimerConfig = {
    .period     = TIMER_0_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_0_init(void) {

    DL_TimerG_setClockConfig(TIMER_0_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_0ClockConfig);

    DL_TimerG_initTimerMode(TIMER_0_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_0TimerConfig);
    DL_TimerG_enableInterrupt(TIMER_0_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
    DL_TimerG_enableClock(TIMER_0_INST);




}



static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_MFCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115107.91
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_4_MHZ_115200_BAUD, UART_0_FBRD_4_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_0_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);


    DL_UART_Main_enable(UART_0_INST);
}

static const DL_UART_Main_ClockConfig gUART_1ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_MFCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_1Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_1_init(void)
{
    DL_UART_Main_setClockConfig(UART_1_INST, (DL_UART_Main_ClockConfig *) &gUART_1ClockConfig);

    DL_UART_Main_init(UART_1_INST, (DL_UART_Main_Config *) &gUART_1Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115107.91
     */
    DL_UART_Main_setOversampling(UART_1_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_1_INST, UART_1_IBRD_4_MHZ_115200_BAUD, UART_1_FBRD_4_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_1_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);


    DL_UART_Main_enable(UART_1_INST);
}

static const DL_UART_Main_ClockConfig gUART_2ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_MFCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_2Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_2_init(void)
{
    DL_UART_Main_setClockConfig(UART_2_INST, (DL_UART_Main_ClockConfig *) &gUART_2ClockConfig);

    DL_UART_Main_init(UART_2_INST, (DL_UART_Main_Config *) &gUART_2Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115107.91
     */
    DL_UART_Main_setOversampling(UART_2_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_2_INST, UART_2_IBRD_4_MHZ_115200_BAUD, UART_2_FBRD_4_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_2_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);


    DL_UART_Main_enable(UART_2_INST);
}

SYSCONFIG_WEAK void SYSCFG_DL_SYSTICK_init(void)
{
    /* Initialize the period to 1.00 μs */
    DL_SYSTICK_init(32);
    /* Enable the SysTick and start counting */
    DL_SYSTICK_enable();
}

