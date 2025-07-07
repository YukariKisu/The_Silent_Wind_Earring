#include "nrf.h"
#include "nrf_gpio.h"

#define LED1 17
#define Button1 13

int main(void)
{
    // Set LED pin as output
    nrf_gpio_cfg_output(LED1);
    nrf_gpio_pin_clear(LED1);

    // Turn on LED
    nrf_gpio_cfg_input(Button1, NRF_GPIO_PIN_PULLUP);  // Active low (0 = ON)

    while (1)
    {
        if(nrf_gpio_pin_read(Button1)==1){
            nrf_gpio_pin_set(LED1);
        }else{
            nrf_gpio_pin_clear(LED1);
        }
        for(volatile int i = 0; i < 10000; i++);
    }
}
