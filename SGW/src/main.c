#include "../include/main.h"

int main(int argc, char const *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "%s[ERROR]%s Not enough arguments!\n", RED, RESET);
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
