#ifndef POKERLIB_H
#define POKERLIB_H

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

#define NUMBER_CARDS 52
#define MAXINT 512000

struct card {
    char mast[10]; // Масть карты
    char name[10];  // Ранг карты
    unsigned long int start_card;
};

void gen_cd(unsigned long int *c, unsigned long int *d, unsigned long int p);
void swap_card(unsigned long int *a, unsigned long int *b);
void mental_poker(unsigned long int number_players);

#endif
