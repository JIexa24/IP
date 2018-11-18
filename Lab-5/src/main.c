#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

#include "../include/emoneylib.h"

int main(int argc, char const *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "[ERROR] Not enough arguments!\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
