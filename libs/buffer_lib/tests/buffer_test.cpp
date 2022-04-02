// Copyright 2022 zenehu

#include <gtest/gtest.h>

extern "C" {
#include "buffer.h"
}

TEST(BufferTest, InitializeTest) {
  size_t size = 1024;

  t_buffer buffer;
  ASSERT_TRUE(buffer_init(&buffer, size));
  ASSERT_EQ(buffer.size, size);
  ASSERT_EQ(buffer.length, 0);

  t_buffer *buffer1 = NULL;
  EXPECT_FALSE(buffer_init(buffer1, size));

  free_buffer(&buffer);
}

TEST(BufferTest, PushBackTest) {
  t_buffer buffer;

  buffer_init(&buffer, 1);

  ASSERT_TRUE(push_back(&buffer, 5));
  EXPECT_EQ(buffer.buffer[0], 5);

  ASSERT_TRUE(push_back(&buffer, 10));
  EXPECT_EQ(buffer.buffer[1], 10);
  free_buffer(&buffer);
}

TEST(BufferTest, PosMaxTest) {
  t_buffer buffer;

  buffer_init(&buffer, 1);

  push_back(&buffer, 5);
  push_back(&buffer, 10);
  push_back(&buffer, 3);
  push_back(&buffer, 6);
  push_back(&buffer, -11);

  EXPECT_EQ(positive_max(&buffer), 10);
  free_buffer(&buffer);
}
