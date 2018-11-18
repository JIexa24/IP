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
  int account_state = atoi(argv[1]);
  int payment_amount;
  while (account_state > 0) {
    printf("[BANK] Enter the payment amount:\n");
    scanf("%d", &payment_amount);
    if (payment_amount == 0) {
      printf("[BANK] Recieved zero payment! Exiting now...\n");
      break;
    }
    printf("[BANK] Starting transaction...\n");
    if(!initialization_transaction(&account_state, payment_amount)) {
      printf("[SHOP] Item was successfully purchased!\n");
    } else {
      printf("[SHOP] Payment rejected!\n");
      break;
    }
    printf("[CUSTOMER] Current account state:\t%d\n\n", account_state);
  }

  return EXIT_SUCCESS;
}
