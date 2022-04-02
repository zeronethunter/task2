// Copyright 2022 zenehu

#include <getopt.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "temperature.h"

int main(int argc, char *argv[]) {
  opterr = 0;
  int l_temp = 0, r_temp = 0, size = 0;
  int c;
  static struct option long_options[] = {{"low_temp", no_argument, 0, 'l'},
                                         {"high_temp", no_argument, 0, 'h'},
                                         {"size_in_bytes", no_argument, 0, 's'},
                                         {0, 0, 0, 0}};
  int option_index = 0;
  while ((c = getopt_long(argc, argv, "l:h:s:", long_options, &option_index)) !=
         -1) {
    switch (c) {
      case 'l':
        l_temp = atoi(optarg);
        printf("lowest_temp: %d\n", l_temp);
        break;
      case 'h':
        r_temp = atoi(optarg);
        printf("highest_temp: %d\n", r_temp);
        break;
      case 's':
        size = atoi(optarg);
        printf("size_in_bytes: %d\n", size);
        break;
      case '?':
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        break;
      case 1:
        fprintf(stderr, "Non-option argument %s\n", optarg);
        break;
      default:
        break;
    }
  }

  ssize_t err;

  clock_t start, end;
  double time;
  start = clock();
  temperature *_temperature = temperature_init(size, l_temp, r_temp);

  err = temperature_search(_temperature);

  if (err == -1) {
    return -1;
  }
  end = clock();

  temperature_print(_temperature);

  temperature_free(_temperature);

  time = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Found for %f seconds\n", time);

  return 0;
}
