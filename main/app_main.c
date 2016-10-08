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
    char data[10] = "lasjd";
    while (1) {
        if (0 == count % (10 * 3))
        {
            printf("http\n");
            // http_post("http://www.baidu.com", NULL, data, http_callback_example);
            http_post("http://www.devicexx.com", NULL, data, http_callback_example);

        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
        count ++;
    }
}

void pingTask(void *pvParameters)
{
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
    espconn_init();
}
