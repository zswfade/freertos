/* Kernel includes. */
#include "FreeRTOS.h" /* Must come first. */
#include "queue.h"    /* RTOS queue related API prototypes. */
#include "semphr.h"   /* Semaphore related API prototypes. */
#include "task.h"     /* RTOS task related API prototypes. */
#include "timers.h"   /* Software timer related API prototypes. */

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bsl.h"
#include "unity.h" /* unit testing support functions */

/* Priorities at which the tasks are created.  The max priority can be specified
as ( configMAX_PRIORITIES - 1 ). */
#define mainTASK_A_PRIORITY (tskIDLE_PRIORITY + 1)
#define mainTASK_B_PRIORITY (tskIDLE_PRIORITY + 2)

#define mainSOFTWARE_TIMER_PERIOD_MS pdMS_TO_TICKS(10)

static void prvTaskA(void *pvParameters);
static void prvTaskB(void *pvParameters);

#if configNUM_CORES != 2
#error Require two cores be configured for FreeRTOS
#endif

TaskHandle_t taskAHandle, taskBHandle;

void setup_test_fr7_001(void) {
  xTaskCreate(prvTaskA, "TaskA", configMINIMAL_STACK_SIZE, NULL,
              mainTASK_A_PRIORITY, &taskAHandle);

  xTaskCreate(prvTaskB, "TaskB", configMINIMAL_STACK_SIZE, NULL,
              mainTASK_B_PRIORITY, &taskBHandle);
}

void setUp(void) {} /* Is run before every test, put unit init calls here. */
void tearDown(void) {
} /* Is run after every test, put unit clean-up calls here. */

int main(void) {
  initTestEnvironment();

  UNITY_BEGIN();

  RUN_TEST(setup_test_fr7_001);

  vTaskStartScheduler();
  // AMPLaunchOnCore(1, vTaskStartScheduler);

  /* should never reach here */
  panic_unsupported();

  return 0; // UNITY_END is unreachable via this path. a state machine and
            // counter is used so that just one child task will call it
            // instead.
}

static uint32_t taskAState = 0;

static void prvTaskA(void *pvParameters) {
  setPin(LED_PIN);

  vTaskDelay(pdMS_TO_TICKS(5000));

  clearPin(LED_PIN);

  taskAState++;

  // idle the task
  for (;;) {
    vTaskDelay(mainSOFTWARE_TIMER_PERIOD_MS);
  }
}

static void prvTaskB(void *pvParameters) {
  int iter = 1;
  int numIters = 10;
  char strbuf[] = "task B enter critical section";
  size_t strbuf_len = sizeof(strbuf) / sizeof(char);
  HeapStats_t heapStats;
  size_t bytesAvailBefore, bytesAvailDelta;

  while(taskAState < 1) {
    vTaskDelay(mainSOFTWARE_TIMER_PERIOD_MS);
  }

  vPortGetHeapState(&heapStats);
  bytesAvailBefore = heapStats.xAvailableHeapSpaceInBytes;

  vTaskDelete(taskAHandle);
  vTaskDelay(pdMS_TO_TICKS(1000));

  setPin(LED_PIN);

  vPortGetHeapState(&heapStats);
  // XXXADS assert that before - current isn't negative. That would indicate
  // test failure.
  bytesAvailDelta = bytesAvailBefore - heapStats.xAvailableHeapSpaceInBytes;

  // idle the task
  for (;;) {
    vTaskDelay(mainSOFTWARE_TIMER_PERIOD_MS);
  }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
  (void)pcTaskName;
  (void)xTask;

  /* Run time stack overflow checking is performed if
  configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
  function is called if a stack overflow is detected.  pxCurrentTCB can be
  inspected in the debugger if the task name passed into this function is
  corrupt. */
  for (;;)
    ;
}

void vApplicationTickHook(void) {
  static uint32_t ulCount = 0;
  ulCount++;
}

void vApplicationMallocFailedHook(void) {
  char strbuf[] = "Malloc Failed";
  size_t strbuf_len = sizeof(strbuf) / sizeof(char);

  sendReport(strbuf, strbuf_len);
}
