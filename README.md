# ESP32_GYROSCOPE 
ESP-IDF

Description:
  - ESP32
  - Two I2C slaves 
      - RTC 1307 module
      - MPU 6050 module
  - FreeRTOS
  - SPIFFS

RTC and MPU Tasks run in the same core and share I2C bus.Access to the I2C bus is controlled by a binary semaphore.
When values of acceleration and rotation are collected by MPU Task, these values + time collected by the RTC Task are registered in a SPIFFS file.
 
 Connections:
    
    VCC(ESP32)    	   	    -> Powered by USB 
  
    VCC(MPU Module)             -> ESP32 Vin pin
    
    VCC(RTC Module)             -> ESP32 Vin pin
    
    SDA(MPU Module/RTC Module)  -> ESP32 21 pin
    
    SCL(MPU Module/RTC Module)  -> ESP32 22 pin
    
    AD0(MPU Module pin)         -> ESP32 3V3/Vin pin

Used Components(ESP-IDF):
  
  - I2Cbus(MPU Module) : https://github.com/natanaeljr/esp32-I2Cbus.git
  
  - RTC1307(RTC Module): https://github.com/UncleRus/esp-idf-lib/tree/master/components/ds1307
  
  - MPU Driver: https://github.com/natanaeljr/esp32-MPU-driver.git
  
  - I2CDev: https://github.com/UncleRus/esp-idf-lib/tree/master/components/i2cdev
  
  - ESP_IDF_LIB_HELPERS: https://github.com/UncleRus/esp-idf-lib/tree/master/components/esp_idf_lib_helpers

Used Modules
  
  - RTC 1307: https://www.baudaeletronica.com.br/real-time-clock-rtc-ds1307-sem-bateria.html
  
  - MPU 6050 Module: https://www.robocore.net/sensor-robo/acelerometro-e-giroscopio-mpu6050
  
  - ESP32 DOIT WROOM 32 Module: https://www.curtocircuito.com.br/placa-doit-esp32-esp32-wroom-32d-wifi-bluetooth.html?utm_term=&utm_campaign=&utm_source=adwords&utm_medium=ppc&hsa_acc=7016354091&hsa_cam=16195286552&hsa_grp=131151020817&hsa_ad=581803262557&hsa_src=g&hsa_tgt=pla-490064249712&hsa_kw=&hsa_mt=&hsa_net=adwords&hsa_ver=3
  
