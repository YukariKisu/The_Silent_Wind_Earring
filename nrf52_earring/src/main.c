#include "nrf_gpio.h"
#include "nrf.h"

#define LED_PIN 24
#define RX_PIN 8

void simple_uart_init(void) {
    NRF_UART0->PSELTXD = 6;        // TX pin
    NRF_UART0->PSELRXD = RX_PIN;   // RX pin
    NRF_UART0->BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud115200;
    NRF_UART0->ENABLE = 4;
    NRF_UART0->TASKS_STARTRX = 1;
}

uint8_t simple_uart_get(void) {
    while (NRF_UART0->EVENTS_RXDRDY == 0) {
        
    }
    NRF_UART0->EVENTS_RXDRDY = 0;
    return NRF_UART0->RXD;
}

int main(void) {
    // preparation for GPIO
    nrf_gpio_cfg_output(LED_PIN);
    nrf_gpio_pin_clear(LED_PIN); // off-board LED
    //nrf_gpio_pin_set(LED_PIN);     // on-board LED

    // Initialize UART
    simple_uart_init();

    while (1) {
        uint8_t c = simple_uart_get();  
        if (c == '1') {
            nrf_gpio_pin_set(LED_PIN); // off-board LED
            //nrf_gpio_pin_clear(LED_PIN); // on-board LED
        } else {
            nrf_gpio_pin_clear(LED_PIN); //  off-board LED
            //nrf_gpio_pin_set(LED_PIN);    //  on-board LED
        }
    }
}

