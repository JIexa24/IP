#include "../include/encryptolib.h"
#include "../include/extralib.h"
#include "../include/cryptolib.h"
#include "../include/hashtab.h"
#include "../include/emoneylib.h"
#include "../include/md5.h"

long int inversion(long int a_euclid, long int b_euclid)
{
  unsigned long int inversion_number, res[3];
  if(a_euclid > b_euclid)
    euclid(a_euclid, b_euclid, res);
  else
    euclid(b_euclid, a_euclid, res);
  if(res[0] == 1){
    if(res[2] < 0){
      inversion_number = res[2] + b_euclid;
    } else {
      inversion_number = res[2];
    }
  } else {
    return -1;
  }
  return inversion_number;
}

void initialization_data_key_BANK()
{
    generate_prime_number(1000, MAXINT, &BANK.P);
    generate_prime_number(1000, MAXINT, &BANK.Q);
    BANK.N = BANK.P * BANK.Q;

    long int phi = (BANK.P - 1) * (BANK.Q - 1);
    for (int i = 1, j = 1; i <= 1000; i *= 10, j++) {
        do {
            generate_prime_number(1, phi, &BANK.d[j]);
            BANK.c[j] = inversion(BANK.d[j], phi);
        } while (BANK.c[j] == (-1));
    }
}

long int hash_calculation(long int m)
{
    uint8_t res[16];
    uint8_t arr[1];
    long int hash = 0;
    md5(arr, 1, res);
    for (int i = 0; i < 16; ++i) {
        hash += res[i] << 4;
    }
    return hash;
}

// n = amount_customer
// n_home_f - это переменная найденная от f(n) по слепой подпеси (f(n) * r^d) mod N
// s_home_f - это переменная найденная от n_home_f по слепой подпеси n_home_f^c mod N
// s == f(n)^c mod N calculation as (s_home_f * r^(-1)) mod N)
// банкнота определяется как {n, s_home_f}
void operation_customer(long int n)
{
    printf("n=%ld\n", n);
    int position_domination = 0;
    for (int i = n; i > 0; i /= 10) {
        position_domination++;
    }
    //printf("position_domination=%ld\n", position_domination);
    unsigned long int f_n, r, r_inversion;
    f_n = hash_calculation(n);
    do {
        generate_prime_number(1, BANK.N, &r);
        r_inversion = inversion(r, BANK.N);
    } while (r_inversion == (-1));

    unsigned long int n_home_f, s_home_f, s;
    unsigned long int expmod_res = 1;
    expmod_func(r, BANK.d[position_domination], BANK.N, &expmod_res);
    n_home_f = (f_n * expmod_res) % BANK.N;

    // s_home_f this code_BANK
    expmod_func(n_home_f, BANK.c[position_domination], BANK.N, &s_home_f);

    //{n, s}
    s = (r_inversion * s_home_f) % BANK.N;

    f_n = hash_calculation(n);
    expmod_func(s, BANK.d[position_domination], BANK.N, &expmod_res);
    if (expmod_res == f_n) {
        printf("[SUCCESS]\n\n");
    } else {
        printf("[FAILURE]\n\n");
    }
}

void list_many(long int amount_customer)
{
    long int begin_domination = 1000;
    do {
        if ((amount_customer / begin_domination) > 0) {
            amount_customer -= begin_domination;
            operation_customer(begin_domination);
        } else {
            begin_domination /= 10;
        }
    } while (amount_customer > 0);
}
