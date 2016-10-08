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
#include <string.h>

#include "esp_err.h"
#include "esp_wifi.h"
// #include "esp_event.h"
#include "esp_event_loop.h"

#ifndef SSID_STA
#define SSID_STA "vankia"
#endif

#ifndef PASSWORD_STA
#define PASSWORD_STA "diligentsuccess"
#endif

#ifndef SSID_AP
#define SSID_AP "Vankia_ESP32"
#endif

#ifndef PASSWORD_AP
#define PASSWORD_AP "diligentsuccess"
#endif

static system_event_cb_t upstream_event_callback_handle = NULL;
uint8_t gStaStatus=0;
void wifi_station_set_connect_status(uint8_t status)
{
    gStaStatus = status;
}
uint8_t wifi_station_get_connect_status(void)
{
    // printf("status %d\n", gStaStatus);
    return gStaStatus;
}


esp_err_t wifi_event_callback(void *ctx, system_event_t *event) {
    if (NULL != event)
    {
        switch (event->event_id) {
        case SYSTEM_EVENT_WIFI_READY:               /**< ESP32 WiFi ready */
            printf("%s: SYSTEM_EVENT_WIFI_READY\n", __func__);
            break;
        case SYSTEM_EVENT_SCAN_DONE:                /**< ESP32 finish scanning AP */
            printf("%s: SYSTEM_EVENT_SCAN_DONE\n", __func__);
            break;
        case SYSTEM_EVENT_STA_START:                /**< ESP32 station start */
            printf("%s: SYSTEM_EVENT_STA_START\n", __func__);
            break;
        case SYSTEM_EVENT_STA_STOP:                 /**< ESP32 station stop */
            printf("%s: SYSTEM_EVENT_STA_STOP\n", __func__);
            break;
        case SYSTEM_EVENT_STA_CONNECTED:            /**< ESP32 station connected to AP */
            printf("%s: SYSTEM_EVENT_STA_CONNECTED\n", __func__);
            wifi_station_set_connect_status(SYSTEM_EVENT_STA_CONNECTED);
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:         /**< ESP32 station disconnected from AP */
            printf("%s: SYSTEM_EVENT_STA_DISCONNECTED\n", __func__);
            wifi_station_set_connect_status(SYSTEM_EVENT_STA_DISCONNECTED);
            break;
        case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:      /**< the auth mode of AP connected by ESP32 station changed */
            printf("%s: SYSTEM_EVENT_STA_AUTHMODE_CHANGE\n", __func__);
            break;
        case SYSTEM_EVENT_STA_GOT_IP:               /**< ESP32 station got IP from connected AP */
            printf("%s: SYSTEM_EVENT_STA_GOT_IP\n", __func__);
            wifi_station_set_connect_status(SYSTEM_EVENT_STA_GOT_IP);
extern void httpTask(void *pvParameters);

            // xTaskCreate(&httpTask, "httpTask", 4096, NULL, 5, NULL);
            xTaskCreatePinnedToCore(&httpTask, "httpTask", 4096, NULL, 5, NULL, 0);
            break;
        case SYSTEM_EVENT_AP_START:                 /**< ESP32 soft-AP start */
            printf("%s: SYSTEM_EVENT_AP_START\n", __func__);
            break;
        case SYSTEM_EVENT_AP_STOP:                  /**< ESP32 soft-AP stop */
            printf("%s: SYSTEM_EVENT_AP_STOP\n", __func__);
            break;
        case SYSTEM_EVENT_AP_STACONNECTED:          /**< a station connected to ESP32 soft-AP */
            printf("%s: SYSTEM_EVENT_AP_STACONNECTED\n", __func__);
            break;
        case SYSTEM_EVENT_AP_STADISCONNECTED:       /**< a station disconnected from ESP32 soft-AP */
            printf("%s: SYSTEM_EVENT_AP_STADISCONNECTED\n", __func__);
            break;
        case SYSTEM_EVENT_AP_PROBEREQRECVED:        /**< Receive probe request packet in soft-AP interface */
            printf("%s: SYSTEM_EVENT_AP_PROBEREQRECVED\n", __func__);
            break;
        default:
            break;
        }
        if (NULL != upstream_event_callback_handle)
            return upstream_event_callback_handle(ctx, event);
        else
            return ESP_OK;
    }
    else
    {
        return ESP_FAIL;
    }
}

void wifi_setup_sta(void)
{
    // Create Station Wi-Fi configure data
    wifi_config_t config = {
        .sta = {
            // SSID of target AP
            .ssid = SSID_STA,
            // password of target AP
            .password = PASSWORD_STA,
            // whether set MAC address of target AP or not. Generally, station_config.bssid_set needs to be 0; and it needs to be 1 only when users need to check the MAC address of the AP.
            .bssid_set = 0,
            // MAC address of target AP
            .bssid = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00,},
        },
    };

    // Set Wi-Fi mode into Station mode
    esp_wifi_set_mode(WIFI_MODE_APSTA);
    // Set Station config. This API can be called only when specified interface is enabled, otherwise, API fail
    esp_wifi_set_config(WIFI_IF_STA, &config);
    
}

void wifi_setup_ap(void)
{
    // Create AP Wi-Fi configure data
    wifi_config_t config = {
        .ap = {
            // SSID of ESP32 soft-AP
            .ssid = SSID_AP,
            // Password of ESP32 soft-AP
            .password = PASSWORD_AP,
            // Length of SSID. If softap_config.ssid_len==0, check the SSID until there is a termination character; otherwise, set the SSID length according to softap_config.ssid_len.
            .ssid_len = strlen(SSID_AP),
            // Channel of ESP32 soft-AP
            .channel = 0,
            // Auth mode of ESP32 soft-AP. Do not support AUTH_WEP in soft-AP mode
            .authmode = WIFI_AUTH_WPA_PSK,
            // Broadcast SSID or not, default 0, broadcast the SSID
            .ssid_hidden = 0,
            // Max number of stations allowed to connect in, default 4, max 4
            .max_connection = 4,
            // Beacon interval, 100 ~ 60000 ms, default 100 ms
            .beacon_interval = 100,
        },
    };
    // Set AP name with MAC address
    uint8_t mac[6];
    esp_wifi_get_mac(WIFI_IF_AP, mac);
    // Reset AP SSID
    //sprintf(config.ap.ssid, strlen(SSID_AP "_" "123456") + 1, SSID_AP "_%02X%02X%02X", mac[3], mac[4], mac[5]);
    sprintf(config.ap.ssid, SSID_AP "_%02X%02X%02X", mac[3], mac[4], mac[5]);

    config.ap.ssid_len = strlen(config.ap.ssid);

    printf("%s: config.ap.ssid = %s\n", __func__, config.ap.ssid);
    printf("%s: config.ap.password = %s\n", __func__, config.ap.password);
    // Set Wi-Fi mode into Station mode
    esp_wifi_set_mode(WIFI_MODE_APSTA);
    // Set AP config. This API can be called only when specified interface is enabled, otherwise, API fail
    esp_wifi_set_config(WIFI_IF_AP, & config);
}



void wifi_subsystem_init(void)
{
    // Init Wi-Fi sub-system
    ESP_ERROR_CHECK( esp_event_loop_init(wifi_event_callback, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_FLASH) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    // Set Wi-Fi event callback
    //upstream_event_callback_handle = esp_event_loop_set_cb(wifi_event_callback, NULL);
    // Set Wi-Fi mode into AP & Station mode
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    // Set STA config
    wifi_setup_sta();
    // Set AP config
    wifi_setup_ap();
    // Set auto config
    ESP_ERROR_CHECK( esp_wifi_set_auto_connect(true));
    // Start
    ESP_ERROR_CHECK( esp_wifi_start() );
    ESP_ERROR_CHECK( esp_wifi_connect() );
}