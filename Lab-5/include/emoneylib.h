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

#include "../include/encryptolib.h"
#include "../include/cryptolib.h"
#include "../include/extralib.h"
#include "../include/hashtab.h"

#define MAXINT 512000

struct data_BANK {
    //секретные ключи
    unsigned long int P;
    unsigned long int Q;
    unsigned long int c[5];

    //открытые ключи
    unsigned long int N;
    unsigned long int d[5];
} BANK;

long int generation_simple_number_in_limit(long int MAX_LIMIT);
long int inversion(long int a_euclid, long int b_euclid);
void initialization_data_key_BANK();
long int hash_calculation(long int m);
void operation_customer(long int n);
void list_many(long int amount_customer);

#endif
