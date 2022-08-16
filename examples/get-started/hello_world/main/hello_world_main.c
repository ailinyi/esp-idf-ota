
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp32/rom/spi_flash.h"
#include "esp_flash_partitions.h"
#include "esp_partition.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_flash_partitions.h"
#include "esp_partition.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "errno.h"
void app_main()
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    const esp_partition_t *configured = esp_ota_get_boot_partition();
    //const esp_partition_t *running = esp_ota_get_running_partition();

        printf( "Configured OTA boot partition at offset 0x%08x",configured->address);
        printf( "(This can happen if either the OTA boot data or preferred boot image become corrupted somehow.)");
    

    uint32_t address = 0x40000;
    char data[4] = {0};
    spi_flash_read(0x7C0000 , data,sizeof(data));

    for (int i = 0; i < sizeof(data); i++) {
        printf("data[%d]%d\n",i,data[i]);
    }

    for (int i = 0; i < sizeof(data); i++) {
        data[i] ++;
    }   
    
    esp_rom_spiflash_erase_sector(0x7C0000 /1024/4);


    esp_rom_spiflash_write(0x7C0000 ,(uint8_t *)&configured->address,4);

    spi_flash_read(0x7C0000 , data,sizeof(data));

    for (int i = 0; i < sizeof(data); i++) {
        printf("data[%d]%d\n",i,data[i]);
    }

    for (int i = 3; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
