// Copyright 2022 zenehu

#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>

#include "buffer.h"

#ifndef INCLUDE_TEMPERATURE_H_
#define INCLUDE_TEMPERATURE_H_

typedef struct {
  int l_temp;  // lowest temperature
  int r_temp;  // highest temperature

  t_buffer _buffer;

  size_t process_count;  // max count of processes
  int *fd;               // fd dynamic array

  t_buffer indexes;  // indexes of maximum elements in sub_buffers
} temperature;

temperature *temperature_init(size_t _size, int _l_temp, int _r_temp);

ssize_t temperature_pipes_init(temperature *_temperature);

ssize_t temperature_search(temperature *_temperature);

void temperature_sub_search(temperature *temp_sub_buffer, size_t index);

void temperature_free(temperature *_temperature);

void temperature_print(temperature *_temperature);

#endif  // INCLUDE_TEMPERATURE_H_
