/*
    IoT Controller
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "freertos/queue.h"

// #include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_log.h"
// #include "esp_system.h"

#include "RCSwitch.h"

#define LEVEL_HIGH  1
#define LEVEL_LOW   0
#define TRANSMITTER_IO_NUM  5
#define LED_IO_NUM          2 // WeMos D1 Mini compatible
#define LED_IO_PIN_MASK     ((1ULL << LED_IO_NUM))
#define LED_ON LEVEL_LOW
#define LED_OFF LEVEL_HIGH

// Message length bits
#define MESSAGE_LENGTH 32
/** 32bit message format: 0xXXXXYYZZ
 * XXXX - 16bit preamble
 * YY   - 8bit receiver address
 * ZZ   - 8bit data
 */
#define MESSAGE_ON  0x3C300303
#define MESSAGE_OFF 0x3C300305

static const char* TAG = "main";
RCSwitch transmitter = RCSwitch();

static void configure_transmitter() {
    ESP_LOGI(TAG, "Configure transmitter GPIO");
    transmitter.enableTransmit(TRANSMITTER_IO_NUM);

    // Optional: set protocol (default is 1, will work for most outlets)
    // transmitter.setProtocol(1);

    // Optional: set pulse length. 350 for the protocol 1
    // transmitter.setPulseLength(320);

    // Optional: set number of transmission repetitions.
    // transmitter.setRepeatTransmit(10);
}

static void configure_led() {
    ESP_LOGI(TAG, "Configure LED GPIO");
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = LED_IO_PIN_MASK;
    io_conf.pull_down_en = (gpio_pulldown_t)0;
    io_conf.pull_up_en = (gpio_pullup_t)0;
    gpio_config(&io_conf);
}

extern "C" void app_main(void) {

    ESP_LOGI(TAG, "\n\nDevice is up. Hey there!");

    uart_set_baudrate((uart_port_t)0, 115200);
    configure_transmitter();
    configure_led();

    while (1) {

        ESP_LOGI(TAG, "Sending: %#X", MESSAGE_ON);
        transmitter.send(MESSAGE_ON, MESSAGE_LENGTH);
        gpio_set_level((gpio_num_t)LED_IO_NUM, LED_ON);
        // vTaskDelay(3000 / portTICK_RATE_MS);
        vTaskDelay(pdMS_TO_TICKS(3000));

        ESP_LOGI(TAG, "Sending: %#X", MESSAGE_OFF);
        transmitter.send(MESSAGE_OFF, MESSAGE_LENGTH);
        gpio_set_level((gpio_num_t)LED_IO_NUM, LED_OFF);
        // vTaskDelay(3000 / portTICK_RATE_MS);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
