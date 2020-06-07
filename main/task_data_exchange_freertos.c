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

#define TASK_LOOP 1

//All task data here
OSHANDLES taskSystem;

//TODO Interrupt must be add the system

void SystemInit()
{
    taskSystem.queue = xQueueCreate(5, sizeof(uint32_t));
    taskSystem.lock = xSemaphoreCreateMutex();
}

void parameterInit()
{
    //other system parameter init here
    taskSystem.init = SystemInit;
}
#define MAX_MESSAGE_LEN 20
//shared data must be global or static
struct Message_t
{
    uint8_t messageType;
    char data[MAX_MESSAGE_LEN];
} message;

//Sourse may be spi or i2c etc....
void importantSourse()
{
    printf("important resource\n");
}

void taskA(void *p)
{
    OSHANDLES *osHandles = (*OSHANDLES)p;
    while (TASK_LOOP)
    {
        printf("taskA\n");
        if (xSemaphoreTake(osHandles->lock, 1000))
        {
            printf("TaskA running here and take semaphore\n");
            importantSourse();
            if (xQueueSend(osHandles->queue, &message, (TickType_t)10) != pdPASS)
            {
                /**! Failed to post the message, even after 10 ticks. */
            }
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
            printf("taskA dont take semaphore\n");
        }
    }
}

void taskB(void *p)
{
    //TODO: Task init here
    OSHANDLES *osHandles = (OSHANDLES *)p;
    struct message receiveMessage;
    while (TASK_LOOP)
    {
        printf("taskB\n");
        if (xSemaphoreTake(osHandles->lock, 1000))
        {
            if (xQueueReceive(osHandles->queue, &(receiveMessage), (TickType_t)10) == pdPASS)
            {
                /* xRxedStructure now contains a copy of xMessage. */
            }
            printf("TaskB running here and take semaphore\n");
            osHandles->queue

            importantSourse();
            xSemaphoreGive(osHandles->lock);
        }
        else
        {
            printf("taskB dont take semaphore\n");
        }
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

//! and this can generally be replase with

void app_main()
{
    parameterInit(void);
    taskSystem.init();
    // TODO: return value must be handle here, heap must be watching by programers
    xTaskCreate(taskA, "taskA", 2048, &taskSystem, 10, &taskSystem.task.StateMachineTask);
    xTaskCreate(taskB, "taskB", 2048, &taskSystem, 10, &taskSystem.task.LoggingTask);
}