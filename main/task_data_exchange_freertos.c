/**
 * @file task_data_exchange_freertos.c
 * @author your omer (omer-ceylan17@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-03-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "freertos/semphr.h"
#include "freertos/timers.h"
xSemaphoreHandle semaphore = NULL;
void kaynak(){
    printf("important resource\n");
}
void taskA(void *p)
{
    while(1){
        if(xSemaphoreTake(semaphore,1000)){
            printf("TaskA running here\n");
            kaynak();
        }else{
            printf("taskA failed\n");
        }
    }
    
}

void taskB(void *p) 
{
    while(1){
        if(xSemaphoreTake(semaphore,1000)){
            printf("TaskA running here\n");
            kaynak();
        }else{
            printf("taskA failed\n");
        }

    }
    
}

//! and this can generally be replase with

void app_main(){
    semaphore = xSemaphoreCreateMutex();
    xTaskCreate(taskA,"taskA",2048,NULL,10,NULL);
    xTaskCreate(taskB,"taskB",2048,NULL,10,NULL);
}