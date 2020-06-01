#ifndef OSHANDLES_H
#define OSHANDLES_H

/**
 * @file os_Handles.h
 * @author Ömer Çaylan (omer-ceylan17@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-05-29
 * 
 * @copyright Copyright (c) 2020
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

typedef void (*FunctionFunc)();

typedef struct
{

    struct
    {
        //TODO: All control data here
    } fligt_control;

    struct
    {
        //TODO: All control data here
    } fligt_control;

    struct
    {
        //TODO: All control data here
    } Vtool_Setting;

    struct
    {

        //TODO: queue data here
        QueueHandle_t xQueue;
    } queue;

    struct
    {
        xSemaphoreHandle SPI; // spi lock
    } lock;

    struct
    {
        xTaskHandle fligtTask;
        xTaskHandle LoggingTask;
        xTaskHandle StateMachineTask;
    } task;

    void (*init)(void);

} OSHANDLES;

#endif /* COMMONDEFS_H_ */
