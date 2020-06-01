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
#include "os_Handles.h"

#define LOOP 1

OSHANDLES taskSystem;

void SystemInit()
{
    taskSystem.queue = xQueueCreate(5, sizeof(uint32_t));
    taskSystem.lock = xSemaphoreCreateMutex();
}

void parameterInit()
{
    taskSystem.FunctionFunc = SystemInit;
}

void kaynak()
{
    printf("important resource\n");
}

void taskA(void *p)
{
    OSHANDLES *osHandles = (*OSHANDLES)p;

    while (LOOP)
    {
        printf("taskA\n");
        if (xSemaphoreTake(osHandles->lock, 1000))
        {
            printf("TaskA running here\n");
            kaynak();
            for (size_t i = 0; i < 10; i++)
            {
                printf("i = %d\n", i);
                vTaskDelay(1000 / portTICK_RATE_MS);
                if (i == 9)
                {
                    xSemaphoreGive(osHandles->lock);
                }
            }
        }
        else
        {
            printf("taskA failed\n");
        }
    }
}

void taskB(void *p)
{
    //TODO: Task init here
    OSHANDLES *osHandles = (OSHANDLES *)p;

    while (LOOP)
    {
        printf("taskB\n");
        if (xSemaphoreTake(osHandles->lock, 1000))
        {
            printf("TaskB running here\n");
            kaynak();
            xSemaphoreGive(osHandles->lock);
        }
        else
        {
            printf("taskB failed\n");
        }
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

//! and this can generally be replase with

void app_main()
{
    parameterInit(void);
    xTaskCreate(taskA, "taskA", 2048, &taskSystem, 10, &taskSystem.task.StateMachineTask);
    xTaskCreate(taskB, "taskB", 2048, &taskSystem, 10, &taskSystem.task.LoggingTask);
}