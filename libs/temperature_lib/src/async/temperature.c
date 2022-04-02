// Copyright 2022 zenehu

#include "temperature.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "buffer.h"

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

  new_temp->process_count = sysconf(_SC_NPROCESSORS_ONLN);

  buffer_init(&new_temp->indexes, 1);

  new_temp->l_temp = _l_temp;
  new_temp->r_temp = _r_temp;

  new_temp->fd = (int *)malloc(sizeof(int) * new_temp->process_count * 2);
  if (!new_temp->fd) {
    return NULL;
  }

  temperature_pipes_init(new_temp);

  return new_temp;
}

ssize_t temperature_pipes_init(temperature *_temperature) {
  int exit_code = -1;
  for (size_t i = 0; i < _temperature->process_count; ++i) {
    exit_code = pipe(
        &_temperature->fd[2 * i]);  // filling every 2 places for each process
    if (exit_code) {
      return exit_code;  // if not null
    }
  }
  return exit_code;
}

ssize_t temperature_search(temperature *_temperature) {
  if (!_temperature) {
    return -1;
  }
  for (size_t i = 0; i < _temperature->process_count; ++i) {
    pid_t pid = fork();
    if (pid == -1) {
      return -1;
    }
    if (pid) {                                  // parent process
      close(_temperature->fd[2 * i + 1]);       // close on reading
    } else {                                    // child process
      temperature_sub_search(_temperature, i);  // start search in sub buffer
    }
  }

  wait(NULL);  // wait for all the kids to stop working

  size_t process_count = _temperature->process_count;

  for (size_t i = 0; i < process_count; ++i) {
    int maximum_index;
    while (read(_temperature->fd[2 * i], &maximum_index, sizeof(int)) > 0) {
      push_back(
          &_temperature->indexes,
          maximum_index + _temperature->_buffer.length * i / process_count);
    }

    close(_temperature->fd[2 * i]);  // close on read
  }

  return 0;
}

void temperature_sub_search(temperature *temp_sub_buffer, size_t index) {
  close(temp_sub_buffer->fd[2 * index]);  // close on read

  int result = 0;
  size_t result_index = 0;
  size_t step =
      temp_sub_buffer->_buffer.length / temp_sub_buffer->process_count;

  for (size_t i = 0; i < step; ++i) {
    int difference = temp_sub_buffer->_buffer.buffer[index * step + i + 1] -
                     temp_sub_buffer->_buffer.buffer[index * step + i];
    if (difference > result) {
      result = difference;
      result_index = i;
    }
  }
  write(temp_sub_buffer->fd[2 * index + 1], &result_index, sizeof(size_t));

  close(temp_sub_buffer->fd[2 * index + 1]);  // close on write

  exit(0);  // disable process
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
  free(_temperature->fd);
  free(_temperature);
}
