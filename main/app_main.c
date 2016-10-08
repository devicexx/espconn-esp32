/*
 * Copyright (C) 2016, Device++. All rights reserved.
 * Copyright (C) 2016, Vankia Inc. All rights reserved.
 *
 * Created at 2016-09-21, Huang Rui <vowstar@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY DEVICE++. OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "nghttp2/nghttp2.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "wifi_utils.h"
#include "httpclient.h"

#include "espconn.h"




void httpTask(void *pvParameters)
{
    static uint32_t count = 0;
    // http_request();
    char data[10] = "lasjd";
    // http_post("http://www.devicexx.com", NULL, data, http_callback_example);
    while (1) {
        vTaskDelay(10 / portTICK_PERIOD_MS);
        count ++;
        if (0 == count % (100 * 3))
        {
            printf("http\n");
            // http_post("http://www.baidu.com", NULL, data, http_callback_example);
            http_post("http://www.devicexx.com", NULL, data, http_callback_example);

        }
    }
}

void pingTask(void *pvParameters)
{
    // wifi_setup_sta();
    // vTaskDelay(10 / portTICK_PERIOD_MS);
    // wifi_setup_ap();
    // vTaskDelay(10 / portTICK_PERIOD_MS);
    // wifi_connect();
    while (1) {
        vTaskDelay(1000 * 10 / portTICK_PERIOD_MS);
        printf("ping\n");
    }
}

void app_main()
{
    // Init nvs flash
    nvs_flash_init();
    // Init system
    system_init();
    // Init LWIP
    tcpip_adapter_init();
    // Init Wi-Fi subsystem
    wifi_subsystem_init();
    // Create Task
    // xTaskCreatePinnedToCore(&pingTask, "pingTask", 2048, NULL, 5, NULL, 0);
    // xTaskCreatePinnedToCore(&httpTask, "httpTask", 4096, NULL, 5, NULL, 0);
    espconn_init();
}
