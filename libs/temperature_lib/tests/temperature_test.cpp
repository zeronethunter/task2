// Copyright 2022 zenehu

#include <gtest/gtest.h>

extern "C" {
#include "temperature.h"
}

TEST(TemperatureTest, InitializeTest) {
  size_t bad_size = 0;
  size_t size = 1024;
  int l_temp = -20;
  int r_temp = 20;

  temperature *_temp = temperature_init(bad_size, l_temp, r_temp);
  ASSERT_FALSE(_temp);

  _temp = temperature_init(size, l_temp, r_temp);
  EXPECT_TRUE(_temp);
  EXPECT_TRUE(_temp->_buffer.buffer);

  temperature_free(_temp);
}

TEST(TemperatureTest, SearchTest) {
  size_t size = 1024;
  int l_temp = -20;
  int r_temp = 20;

  temperature *_temp = temperature_init(size, l_temp, r_temp);

  ssize_t err = temperature_search(_temp);

  EXPECT_TRUE(err >= 0);
  EXPECT_TRUE(_temp);
  EXPECT_TRUE(_temp->_buffer.buffer);

  temperature_free(_temp);
}
