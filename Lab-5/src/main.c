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
  long int my_amount_many, amount_customer;
  initialization_data_key_BANK();
  printf("Введите сумму в банке\n");
  scanf("%ld", &my_amount_many);
  while (1) {
    printf("Сумма платежа\n");
    scanf("%ld", &amount_customer);
    if (amount_customer <= my_amount_many && amount_customer > 0 ) {
      my_amount_many -= amount_customer;
      list_many(amount_customer);
    } else break;
  }

  return EXIT_SUCCESS;
}
