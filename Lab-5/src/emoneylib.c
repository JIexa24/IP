#include "../include/encryptolib.h"
#include "../include/extralib.h"
#include "../include/cryptolib.h"
#include "../include/hashtab.h"
#include "../include/emoneylib.h"
#include "../include/md5.h"

void bank_startup()
{
  unsigned long int Phi;

  generate_prime_number(1, MAXINT, &BANK.P);
  generate_prime_number(1, MAXINT, &BANK.Q);
  BANK.N = BANK.P * BANK.Q;
  Phi = (BANK.P - 1) * (BANK.Q - 1);

  for (int i = 0; i < 3; ++i)
    do {
      BANK.c[i] = generate_mutually_prime_number(Phi, 1, Phi - 1);
      expmod_func(BANK.c[i], -1, Phi, &BANK.d[i]);
    } while(BANK.d[i] > 0xFFFFFF);

  // printf("[DEBUG]\tGenerated next values:\n");
  // printf("P = %lu\tQ = %lu\tN = %lu\nC = %lu\tD = %lu\nC = %lu\tD = %lu\nC = %lu\tD = %lu\t\n",
  // BANK.P, BANK.Q, BANK.N, BANK.c[0], BANK.d[0], BANK.c[1], BANK.d[1], BANK.c[2], BANK.d[2]);
}

void oneside_encryption()
{
  uint8_t res[16];
  uint8_t arr[1];
  long int hash = 0;
  md5(arr, 1, res);
  for (int i = 0; i < 16; ++i)
    hash += res[i] << 4;
  EMONEY.enc_hash = hash;
}

int initialization_transaction(int *account_state, int payment_amount)
{
  generate_prime_number(2, BANK.N - 1, &EMONEY.banknote);
  oneside_encryption();
  //printf("[DEBUG] Generated next banknote:\t%lu\t%lu\n", EMONEY.banknote, EMONEY.enc_hash);
  *account_state -= payment_amount;
  if (*account_state >= 0) {
    return 0;
  } else return 1;
}
