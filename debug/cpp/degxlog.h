// Author: Alexey Kasyanchuk <degitx@gmail.com>

#pragma once

#include <iostream>
#include <string.h>
#include <sys/time.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define DX_PRINTF(out, color, type, msg, ...) {\
  timeval curTime;\
  char timebuffer[28];\
  gettimeofday(&curTime, NULL);\
  strftime(timebuffer, 28, "%H:%M:%S", localtime((time_t*)&curTime.tv_sec));\
\
  fprintf(out, "[%s:%03ld] [%s] %s:%d: %s: " msg "\n", timebuffer, curTime.tv_usec / 1000, "\x1B[" color "m" type "\033[0m", __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__);\
}

#define DX_ERROR(...) DX_PRINTF(stderr, "31", "E", ##__VA_ARGS__)
#define DX_WARN(...) DX_PRINTF(stdout, "33", "W", ##__VA_ARGS__)
#define DX_INFO(...) DX_PRINTF(stdout, "32", "I", ##__VA_ARGS__)
#define DX_DEBUG(...) DX_PRINTF(stdout, "36", "D", ##__VA_ARGS__)

static uint64_t DXGetSystemNanoTime()
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    uint64_t currentSystemTime = now.tv_sec * 1000000000LL + now.tv_nsec;
 
    return currentSystemTime;
}
 
// содержит timestamp!
static uint64_t DXGetMicroTime()
{
	struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * 1000000LL + currentTime.tv_usec;
}

// содержит timestamp!
static uint64_t DXGetMiliTime()
{
	return DXGetMicroTime() / 1000;
}

#define DX_START_NANO_TIMER(dx_nano_timer_tag) uint64_t start_##dx_nano_timer_tag = DXGetSystemNanoTime();
#define DX_STOP_NANO_TIMER(dx_nano_timer_tag) uint64_t diff_##dx_nano_timer_tag = DXGetSystemNanoTime() - start_##dx_nano_timer_tag;
#define DX_STOP_NANO_TIMER_PRINT(dx_nano_timer_tag) DX_INFO("%ld ns ["#dx_nano_timer_tag"]", DXGetSystemNanoTime() - start_##dx_nano_timer_tag);
#define DX_GET_NANO_TIMER(dx_nano_timer_tag) diff_##dx_nano_timer_tag

#define DX_START_MICRO_TIMER(dx_micro_timer_tag) uint64_t start_##dx_micro_timer_tag = DXGetMicroTime();
#define DX_STOP_MICRO_TIMER(dx_micro_timer_tag) uint64_t diff_##dx_micro_timer_tag = DXGetMicroTime() - start_##dx_micro_timer_tag;
#define DX_STOP_MICRO_TIMER_PRINT(dx_micro_timer_tag) DX_INFO("%ld qs ["#dx_micro_timer_tag"]", DXGetMicroTime() - start_##dx_micro_timer_tag);
#define DX_GET_MICRO_TIMER(dx_micro_timer_tag) diff_##dx_micro_timer_tag

#define DX_START_MILI_TIMER(dx_mili_timer_tag) uint64_t start_##dx_mili_timer_tag = DXGetMiliTime();
#define DX_STOP_MILI_TIMER(dx_mili_timer_tag) uint64_t diff_##dx_mili_timer_tag = DXGetMiliTime() - start_##dx_mili_timer_tag;
#define DX_STOP_MILI_TIMER_PRINT(dx_mili_timer_tag) DX_INFO("%ld ms ["#dx_mili_timer_tag"]", DXGetMiliTime() - start_##dx_mili_timer_tag);
#define DX_GET_MILI_TIMER(dx_mili_timer_tag) diff_##dx_mili_timer_tag

#define DX_START_HU_TIMER(dx_nano_timer_tag) uint64_t start_##dx_nano_timer_tag = DXGetSystemNanoTime();
#define DX_STOP_HU_TIMER_PRINT(dx_nano_timer_tag) \
  uint64_t diff_##dx_nano_timer_tag = DXGetSystemNanoTime() - start_##dx_nano_timer_tag; \
  if (diff_##dx_nano_timer_tag >= 1000 * 1000) { \
    DX_INFO("%f ms ["#dx_nano_timer_tag"]", (double)diff_##dx_nano_timer_tag / 1000000); \
  } else if(diff_##dx_nano_timer_tag >= 1000) { \
    DX_INFO("%f qs ["#dx_nano_timer_tag"]", (double)diff_##dx_nano_timer_tag / 1000); \
  } else { \
    DX_INFO("%f ns ["#dx_nano_timer_tag"]", diff_##dx_nano_timer_tag); \
  }



