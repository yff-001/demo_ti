#include "gpio.h"
#include "driver/gpio.h"

#include "ti_msp_dl_config.h"

/*
    DL_GPIO_clearPins(gpioPort, gpioPins);
    DL_GPIO_setPins(gpioPort, gpioPins);
    DL_GPIO_togglePins(gpioPort, gpioPins);
*/

void gpio_init() {
    /* set PA0 as output, clear pin */
    DL_GPIO_initDigitalOutput(IOMUX_PINCM1);
    DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_0);
    DL_GPIO_enableOutput(GPIOA, DL_GPIO_PIN_0);
}