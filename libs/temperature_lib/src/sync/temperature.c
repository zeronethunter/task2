// Copyright 2022 zenehu

#include "temperature.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

temperature *temperature_init(size_t _size, int _l_temp, int _r_temp) {
  if (!_size || (_size % sizeof(int) != 0)) {
    return NULL;
  }
  temperature *new_temp = (temperature *)malloc(sizeof(temperature));
  if (!new_temp) {
    return NULL;
  }
  buffer_init(&new_temp->_buffer, _size / sizeof(int));

  srand(time(NULL));
  for (size_t i = 0; i < _size / sizeof(int); ++i) {
    push_back(&new_temp->_buffer, rand() % (_r_temp - _l_temp) +
                                      _l_temp);  // fill with random temperature
  }

  buffer_init(&new_temp->indexes, 1);

  new_temp->l_temp = _l_temp;
  new_temp->r_temp = _r_temp;

  return new_temp;
}

ssize_t temperature_search(temperature *_temperature) {
  if (!_temperature) {
    return -1;
  }
  int max_diff = 0;
  int max_index = 0;
  for (size_t i = 0; i < _temperature->_buffer.length; ++i) {
    int difference =
        _temperature->_buffer.buffer[i + 1] - _temperature->_buffer.buffer[i];
    if (difference > max_diff) {
      max_diff = difference;
      max_index = i;
    }
  }
  push_back(&_temperature->indexes, max_index);

  return 0;
}

void temperature_print(temperature *_temperature) {
  if (!_temperature) {
    return;
  }
  if (!_temperature->indexes.buffer) {
    return;
  }
  int max_index = positive_max(&_temperature->indexes);
  if (max_index == -1) {
    return;
  }
  int max_diff = _temperature->_buffer.buffer[max_index + 1] -
                 _temperature->_buffer.buffer[max_index];
  printf("The maximum difference is %d, at %d index\n", max_diff,
         max_index);
}

void temperature_free(temperature *_temperature) {
  if (!_temperature) {
    return;
  }
  free_buffer(&_temperature->_buffer);
  free_buffer(&_temperature->indexes);
  free(_temperature);
}
