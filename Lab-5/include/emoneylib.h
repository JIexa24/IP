#ifndef EMONEYLIB_H
#define EMONEYLIB_H

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

#define MAXINT 512000

struct data_BANK {
    unsigned long int P;
    unsigned long int Q;
    unsigned long int c[3];
    unsigned long int N;
    unsigned long int d[3];
} BANK;

struct electronic_money {
  unsigned long int banknote;
  unsigned long int enc_hash;
} EMONEY;

void bank_startup();
void oneside_encryption();
int initialization_transaction(int *account_state, int payment_amount);

#endif
