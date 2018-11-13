#include "../include/encryptolib.h"
#include "../include/cryptolib.h"
#include "../include/extralib.h"
#include "../include/hashtab.h"
#include "../include/pokerlib.h"

void swap_card(unsigned long int *card_a, unsigned long int *card_b)
{
  unsigned long int tmp;
  tmp = *card_a;
  *card_a = *card_b;
  *card_b = tmp;
}

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

  // P1 encode whole deck, shuffle it and send it to P2     for each player repeat step 4
  FILE *deck_file = fopen("deck", "r");
  if (deck_file == NULL) {
      fprintf(stderr, "[ERROR]\tFile doesn't exist!\n");
      exit(EXIT_FAILURE);
  }
  struct deck game_deck[NUMBER_CARDS];
  unsigned long int encoded_deck[NUMBER_CARDS];
  for(int i = 0; i < NUMBER_CARDS; ++i) {
      fscanf(deck_file, "%s", game_deck[i].suit);
      fscanf(deck_file, "%s", game_deck[i].name);
      game_deck[i].start_card = i + 1;
      encoded_deck[i] = i + 1;
  }
  fclose(deck_file);

  for(int i = 0; i < n_players; ++i){
    for (int j = 0; j < NUMBER_CARDS; ++j) {
      expmod_func(encoded_deck[j], c[i], general_p, &encoded_deck[j]);
    }
    int rand_card;
    for(int j = 0; j < NUMBER_CARDS; ++j) {
      rand_card = rand() % NUMBER_CARDS;
      swap_card(&encoded_deck[j], &encoded_deck[rand_card]);
    }
  }
}
