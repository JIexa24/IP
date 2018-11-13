#include "../include/encryptolib.h"
#include "../include/cryptolib.h"
#include "../include/extralib.h"
#include "../include/hashtab.h"
#include "../include/pokerlib.h"

void mental_poker(int n_players)
{
  if (n_players < 3) printf("[SYSTEM]\tAmount of players are less than 3. Debug is ON\n");
  // generate general p
  unsigned long int general_p;
  generate_prime_number(1000, MAXINT, &general_p);
  if(n_players < 3) printf("[DEBUG]\tGeneral P was generated:\t%lu\n", general_p);

  // generate secret c & d      for each player repeat step 2
  unsigned long int c[n_players], d[n_players], euclid_res[3];
  for (int i = 0; i < n_players; ++i) {
    do {
      c[i] = generate_mutually_prime_number(general_p - 1, 1, general_p - 1);
      euclid(general_p - 1, c[i], euclid_res);
      d[i] = euclid_res[1];
    } while (d[i] > 0xFFFFFF);

    if (n_players < 3) printf("[DEBUG]\tFor Player %d generated:\t%lu\t%lu\n", i, c[i], d[i]);
  }
  // P1 encode whole deck, shuffle it and send it to P2
  // for each player repeat step 4
  // PN

}
