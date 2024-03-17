#include "timer.h"
#include "ti_msp_dl_config.h"

/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                           (127U)

void timer_init() {
    DL_TimerG_reset(TIMER_0_INST);
    DL_TimerG_enablePower(TIMER_0_INST);
    SYSCFG_DL_TIMER_0_init();
}

/*
 * Timer clock configuration to be sourced by LFCLK /  (32768 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   128 Hz = 32768 Hz / (1 * (255 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_0ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_LFCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 255U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_0_INST_LOAD_VALUE = (1000 ms * 128 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_0TimerConfig = {
    .period     = TIMER_0_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_0_init(void) {
    DL_TimerG_setClockConfig(TIMER_0_INST, (DL_TimerG_ClockConfig *) &gTIMER_0ClockConfig);
    DL_TimerG_initTimerMode(TIMER_0_INST, (DL_TimerG_TimerConfig *) &gTIMER_0TimerConfig);
    DL_TimerG_enableInterrupt(TIMER_0_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
    DL_TimerG_enableClock(TIMER_0_INST);
}

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