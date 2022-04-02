// Copyright 2022 zenehu

#include "buffer.h"

bool buffer_init(t_buffer *_buffer, size_t _size) {
  if (!_buffer) {
    return false;
  }
  _buffer->buffer = (int *)malloc(sizeof(int) * _size * 2);
  if (!_buffer->buffer) {
    return false;
  }
  _buffer->size = _size;
  _buffer->length = 0;

  return true;
}

bool expansion(t_buffer *_buffer) {
  if (!_buffer) {
    return false;
  }
  if (!_buffer->buffer) {
    _buffer->buffer = (int *)malloc(sizeof(int));
    _buffer->size = 1;
    _buffer->length = 0;
    return true;
  }

  int *new_buffer = (int *)malloc(sizeof(int) * _buffer->size * 2);
  if (!new_buffer) {
    return false;
  }
  for (size_t i = 0; i < _buffer->size; ++i) {
    new_buffer[i] = _buffer->buffer[i];
  }

  free(_buffer->buffer);

  _buffer->buffer = new_buffer;
  _buffer->size *= 2;

  return true;
}

bool push_back(t_buffer *_buffer, int value) {
  if (_buffer->size == _buffer->length || !_buffer->buffer) {
    if (!expansion(_buffer)) {
      return false;
    }
  }
  _buffer->buffer[_buffer->length++] = value;
  return true;
}

int positive_max(t_buffer *_buffer) {
  if (!_buffer) {
    return -1;
  }
  int result = -1;

  for (size_t i = 0; i < _buffer->length; ++i) {
    int tmp = _buffer->buffer[i];
    if (tmp > result) {
      result = tmp;
    }
  }

  if (result < 0) {
    return -1;
  }
  return result;
}

void free_buffer(t_buffer *buffer) {
  if (!buffer) {
    return;
  }
  free(buffer->buffer);
}
