/*
 * Copyright (c) 2021, Texas Instruments Incorporated
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

#include "ti_msp_dl_config.h"


int main(void)
{
    SYSCFG_DL_init();
    // soft_timer_init();

    /*
     * Initializes the SysTick period to 500.00 ms,
     * enables the interrupt, and starts the SysTick Timer
     */
    // DL_SYSTICK_config(16000000);

    NVIC_EnableIRQ(TIMG0_INT_IRQn);
    // DL_TimerG_startCounter(TIMG0);

    /* set PA0 as output, clear pin */
    DL_GPIO_initDigitalOutput(IOMUX_PINCM1);
    DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_0);
    DL_GPIO_enableOutput(GPIOA, DL_GPIO_PIN_0);

    while (1) {
        __WFI();
    }
}

// void SysTick_Handler(void)
// {
//     DL_GPIO_togglePins(GPIOA, DL_GPIO_PIN_0);
// }

/*  this function gets its name from the paramter passed to NVIC_EnableIRQ()
    mystery sovled!
    beware of mistach!
*/
void TIMG0_IRQHandler(void)
{
    DL_GPIO_togglePins(GPIOA, DL_GPIO_PIN_0);
    // static uint32_t count = TIMER_500_MILLISECONDS_TICKS;
    // switch (DL_TimerG_getPendingInterrupt(TIMG0)) {
    //     case DL_TIMER_IIDX_ZERO:
    //         DL_GPIO_togglePins(GPIOA, DL_GPIO_PIN_0);
    //         break;
    //     default:
    //         break;
    // }
}

/*
    DL_GPIO_clearPins(gpioPort, gpioPins);
    DL_GPIO_setPins(gpioPort, gpioPins);
    DL_GPIO_togglePins(gpioPort, gpioPins);
*/