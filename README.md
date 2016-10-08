# READ ME 
## TOOL USED 
* esp32 IDF from [https://github.com/espressif/esp-idf](https://github.com/espressif/esp-idf)
* develop on docker image
## THE FUNCTION    
     this project achieve the funtion of espconn base on lwip and freertos,and use the espconn achieve httpclient.    
     
## HOW TO USE
1. modify the flowing parameter on esp_wifi.c  
  * SSID_STA and PASSWORD_STA, the station which you want to connect to 
  * SSID_AP and PASSWORD_AP, the AP which you want to set
2. make the project and flash the bin file to esp32 then run it

