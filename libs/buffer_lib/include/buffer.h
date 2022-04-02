// Copyright 2022 zenehu

#include <stdbool.h>
#include <stdlib.h>

#ifndef INCLUDE_BUFFER_H_
#define INCLUDE_BUFFER_H_

typedef struct {
  int *buffer;    // buffer
  size_t size;    // size of buffer
  size_t length;  // length of buffer
} t_buffer;

bool buffer_init(t_buffer *_buffer, size_t _size);

bool expansion(t_buffer *_buffer);

bool push_back(t_buffer *_buffer, int value);

int positive_max(t_buffer *_buffer);

void free_buffer(t_buffer *buffer);

#endif  // INCLUDE_BUFFER_H_
