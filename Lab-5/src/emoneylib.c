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

  do {
    BANK.c = generate_mutually_prime_number(Phi, 1, Phi - 1);
    expmod_func(BANK.c, -1, Phi, &BANK.d);
  } while(BANK.d > 0xFFFFFF);

  printf("[DEBUG]\tGenerated next values:\n");
  printf("P = %lu\tQ = %lu\tN = %lu\nC = %lu\tD = %lu\n", BANK.P, BANK.Q, BANK.N, BANK.c, BANK.d);
}

int oneside_encryption()
{
  uint8_t res[16];
  uint8_t arr[1];
  unsigned long int hash = 0;
  md5(arr, 1, res);
  for (int i = 0; i < 16; ++i)
    hash += res[i] << 4;
  return hash;
}

int initialization_transaction(int *account_state, int payment_amount)
{
  unsigned long int pseudo_banknote, banknote_hash, result;

  generate_prime_number(2, BANK.N - 1, &EMONEY.banknote);

  unsigned long int r = generate_mutually_prime_number(BANK.N, 1, BANK.N - 1);
  expmod_func(r, BANK.d, BANK.N, &banknote_hash);
  pseudo_banknote = (EMONEY.banknote * banknote_hash) % BANK.N;

  expmod_func(pseudo_banknote, BANK.c, BANK.N, &EMONEY.banksign);
  expmod_func(r, -1, BANK.N, &r);

  EMONEY.banksign = (EMONEY.banksign * r) % BANK.N;
  expmod_func(EMONEY.banknote, BANK.d, BANK.N, &result);

  if (result == EMONEY.banksign) {
    *account_state -= payment_amount;
    if (*account_state >= 0) {
      return 0;
    } else return 1;
  } else {
    printf("[BANK] Wrong banknote sign!\n");
    return 1;
  }
}
