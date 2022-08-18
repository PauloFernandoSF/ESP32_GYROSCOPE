/*
 Name:		    ESP32_RTC_GYROSCOPE.ino
 Created:	    18/08/2022
 Author:	    Paulo Fernando <pfsf07@gmail.com>
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
    VCC(ESP32)    			    -> Powered by USB 
	VCC(MPU Module)             -> ESP32 Vin pin
    VCC(RTC Module)             -> ESP32 Vin pin
    SDA(MPU Module/RTC Module)  -> ESP32 21 pin
    SCL(MPU Module/RTC Module)  -> ESP32 22 pin
    AD0(MPU Module pin)         -> ESP32 3V3/Vin pin
*/
//General
#include "stdio.h"
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include "esp_log.h"
#include "sys/unistd.h"
#include "sys/stat.h"
#include "esp_spiffs.h"
//MPU
#include "I2Cbus.hpp"
#include "MPU.hpp"
#include "mpu/math.hpp"
#include "mpu/types.hpp"
//RTC
#include "ds1307.h"
//I2C Bus pins
#define SDA_PIN 21
#define SCL_PIN 22
//Semaphore handle
SemaphoreHandle_t xSemaphore = NULL;
//Variable to set RTC time data configuration
bool first_operation = true;
static const char* TAG = "example";
static constexpr gpio_num_t SDA = GPIO_NUM_21;
static constexpr gpio_num_t SCL = GPIO_NUM_22;
//I2C bus speed
static constexpr uint32_t CLOCK_SPEED = 400000;  
//RTC task
void ds1307_Update(void *pvParameters);
//MPU task
void mpu_Update(void *pvParameters);
//Write SPIFFS file
void write_file(const char* file_name,float,float,float,float,float,float);
//Global variable to print in the file
struct tm time_global;

extern "C" void app_main() {
    xSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphore);
    xTaskCreate(ds1307_Update, "ds1307_update", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL);
    xTaskCreate(mpu_Update,    "mpu_update",    configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL);   
    //write_file("/spiffs/mpu_alarm.txt",123.45,123.45,123.45,123.45,123.45,123.45);
}
//RTC Task
void ds1307_Update(void *pvParameters){
    printf("Initiating RTC Task\n");
    fflush(stdout);
    struct tm time;
    //
    while(1){
        //Check availability of the semaphore.
        if(xSemaphoreTake(xSemaphore, portMAX_DELAY)){
            printf("Semaphore - RTC\n");
            //I2C bus config
            ESP_ERROR_CHECK(i2cdev_init());            
            i2c_dev_t dev;
            memset(&dev, 0, sizeof(i2c_dev_t));
            ESP_ERROR_CHECK(ds1307_init_desc(&dev, 0, SDA, SCL));
            /*Set RTC for the first time
            if(first_operation){
                printf("Primeira operação,setando horário\n");
                fflush(stdout);
                first_operation = false;
                // setup datetime: 2018-04-11 00:52:10
                time.tm_sec  = 0;
                time.tm_min  = 46;
                time.tm_hour = 17;
                time.tm_wday = 5;
                time.tm_mday = 18;
                time.tm_mon  = 8;
                time.tm_year = 122;
                ESP_ERROR_CHECK(ds1307_set_time(&dev, &time));
                ds1307_start(&dev, true);
            }
            */
            //Get RTC time
            ds1307_get_time(&dev, &time);
            //Debug time
            printf("%04d-%02d-%02d %02d:%02d:%02d\n", time.tm_year + 1900 /*Add 1900 for better readability*/, time.tm_mon,
            time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);
            //Update global variable
            time_global.tm_sec  = time.tm_sec;
            time_global.tm_min  = time.tm_min;
            time_global.tm_hour = time.tm_hour;
            time_global.tm_wday = time.tm_wday;
            time_global.tm_mday = time.tm_mday;
            time_global.tm_mon  = time.tm_mon;
            time_global.tm_year = time.tm_year;
            //Disable I2C bus
            i2c_driver_delete(0);
            //Give Demaphore
            xSemaphoreGive(xSemaphore);
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    vTaskDelete(NULL);
}
//MPU Task
void mpu_Update(void *pvParameters){
    while(1){
        if(xSemaphoreTake(xSemaphore, portMAX_DELAY)){
            printf("Semaphore - MPU\n");
            //Initialize I2C on port 0 using I2Cbus interface
            i2c0.begin(SDA, SCL, CLOCK_SPEED);
            //MPU object
            MPU_t MPU;  
            //Set bus port
            MPU.setBus(i2c0);  
            //Set address, default is AD0_LOW.Address is 0x39.
            MPU.setAddr(mpud::MPU_I2CADDRESS_AD0_HIGH);  
            //Verify the communication
            //(this also check if the connected MPU supports the implementation of chip selected in the component menu)
            while(esp_err_t err = MPU.testConnection()) {
                ESP_LOGE(TAG, "Failed to connect to the MPU, error=%#X", err);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
            ESP_LOGI(TAG, "MPU connection successful!");
            //Initialize with default configurations
            ESP_ERROR_CHECK(MPU.initialize());  
            //Setup with your configurations
            //ESP_ERROR_CHECK(MPU.setSampleRate(50));  
            //ESP_ERROR_CHECK(MPU.setGyroFullScale(mpud::GYRO_FS_250DPS));
            //ESP_ERROR_CHECK(MPU.setAccelFullScale(mpud::ACCEL_FS_2G));
            //Reading sensor data
            printf("Reading sensor data:\n");
            mpud::raw_axes_t accelRaw;   // x, y, z axes as int16
            mpud::raw_axes_t gyroRaw;    // x, y, z axes as int16
            mpud::float_axes_t accelG;   // accel axes in (g) gravity format
            mpud::float_axes_t gyroDPS;  // gyro axes in (DPS) º/s format
            //Read
            MPU.acceleration(&accelRaw);  // fetch raw data from the registers
            MPU.rotation(&gyroRaw);       // fetch raw data from the registers
            //MPU.motion(&accelRaw, &gyroRaw);  // read both in one shot
            //Convert
            accelG = mpud::accelGravity(accelRaw, mpud::ACCEL_FS_4G);
            gyroDPS = mpud::gyroDegPerSec(gyroRaw, mpud::GYRO_FS_500DPS);
            //Debug
            printf("accel: [%+6.2f %+6.2f %+6.2f ] (G) \t", accelG.x, accelG.y, accelG.z);
            printf("gyro: [%+7.2f %+7.2f %+7.2f ] (º/s)\n", gyroDPS[0], gyroDPS[1], gyroDPS[2]);
            //Update file
            write_file("/spiffs/mpu_alarm.txt",accelG.x,accelG.y,accelG.z,gyroDPS[0],gyroDPS[1],gyroDPS[2]);
            //Disable I2C bus
            i2c_driver_delete(0);
            //Give Semaphore
            xSemaphoreGive(xSemaphore);
        }
        vTaskDelay(1000);
    }
    vTaskDelete(NULL);
}
//Register MPU values in a file
void write_file(const char* file_name,float acc_x,float acc_y,float acc_z,float gyr_x,float gyr_y,float gyr_z){
    ESP_LOGI(TAG, "Initializing SPIFFS");
    esp_vfs_spiffs_conf_t conf = {
      .base_path              = "/spiffs",
      .partition_label        = NULL,
      .max_files              = 5,
      .format_if_mount_failed = true
    };
    //Use settings defined above to initialize and mount SPIFFS filesystem.
    //Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if(ret != ESP_OK){
        if(ret == ESP_FAIL){
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } 
        else if(ret == ESP_ERR_NOT_FOUND){
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } 
        else{
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }
    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if(ret != ESP_OK){
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s). Formatting...", esp_err_to_name(ret));
        esp_spiffs_format(conf.partition_label);
        return;
    } 
    else{
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }
    //Use POSIX and C standard library functions to work with files.
    //First create a file.
    ESP_LOGI(TAG, "Opening file");
    FILE* f = fopen(file_name, "w");
    if(f == NULL){
        ESP_LOGE(TAG, "Failed to open file for writing");
        return;
    }
    fprintf(f, "%d %s %d %s %d %s %d %s %d %s %d %s %6.2f %s %6.2f %s %6.2f %s %6.2f %s %6.2f %s %6.2f",time_global.tm_mday,";",time_global.tm_mon,";",time_global.tm_year + 1900,";",time_global.tm_hour,";",time_global.tm_min,";",time_global.tm_sec,";",acc_x,";",acc_y,";",acc_z,";",gyr_x,";",gyr_y,";",gyr_z);
    fclose(f);
    ESP_LOGI(TAG, "File written");
    //Read file to debug
    ESP_LOGI(TAG, "Reading file");
    f = fopen(file_name, "r");
    if(f == NULL){
        ESP_LOGE(TAG, "Failed to open file for reading");
        return;
    }
    char line[128];
    fgets(line, sizeof(line), f);
    fclose(f);
    //Strip newline
    char* pos = strchr(line, '\n');
    if(pos){
        *pos = '\0';
    }
    ESP_LOGI(TAG, "Read from file: '%s'", line);
    //All done, unmount partition and disable SPIFFS
    esp_vfs_spiffs_unregister(conf.partition_label);
    ESP_LOGI(TAG, "SPIFFS unmounted");
}