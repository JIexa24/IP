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
  if (n_players < 3) printf("%s[SYSTEM]%s\tAmount of players are less than 3. Debug is ON\n", YELLOW, RESET);
  unsigned long int general_p;
  generate_prime_number(1000, MAXINT, &general_p);
  if(n_players < 3) printf("%s[DEBUG]%s\tGeneral P was generated:\t%lu\n", BLUE, RESET, general_p);

  unsigned long int c[n_players], d[n_players], euclid_res[3];
  for (int i = 0; i < n_players; ++i) {
    do {
      c[i] = generate_mutually_prime_number(general_p - 1, 1, general_p - 1);
      euclid(general_p - 1, c[i], euclid_res);
      d[i] = euclid_res[1];
    } while (d[i] > 0xFFFFFF);

    if (n_players < 3) printf("%s[DEBUG]%s\tFor Player %d generated:\t%lu\t%lu\n", BLUE, RESET, i, c[i], d[i]);
  }

  FILE *deck_file = fopen("deck", "r");
  if (deck_file == NULL) {
      fprintf(stderr, "%s[ERROR]%s\tFile doesn't exist!\n", RED, RESET);
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

  unsigned long int curr_card = NUMBER_CARDS;
  struct deck player_hand[n_players][2];
  for (int i = 0; i < n_players; ++i) {
    int rand_card;
    for(int j = 0; j < 2; j++) {
      rand_card = rand() % curr_card;
      for(int k = 0; k < n_players; k++)
        if (i != k) expmod_func(encoded_deck[rand_card], d[k], general_p, &encoded_deck[rand_card]);
      expmod_func(encoded_deck[rand_card], d[i], general_p, &encoded_deck[rand_card]);
      for(int k = 0; k < NUMBER_CARDS; k++) {
        if (game_deck[k].start_card == encoded_deck[rand_card]) {
          player_hand[i][j] = game_deck[k];
          encoded_deck[rand_card] = encoded_deck[curr_card - 1];
          curr_card--;
          k = NUMBER_CARDS;
        }
      }
    }
    for(int j = 0; j < curr_card; j++) {
      rand_card = rand() % curr_card;
      swap_card(&encoded_deck[j], &encoded_deck[rand_card]);
    }
  }


  printf("\n%s[SYSTEM]%s Cards on the board:\n", YELLOW, RESET);
  for(int j = 0, rand_card; j < 5; j++) {
    rand_card = rand() % curr_card;
    for(int k = 0; k < n_players; k++) {
      expmod_func(encoded_deck[rand_card], d[k], general_p, &encoded_deck[rand_card]);
    }
    for(int k = 0; k < NUMBER_CARDS; k++) {
      if (game_deck[k].start_card == encoded_deck[rand_card]) {
        if (!strcmp(game_deck[k].name, "jack")) {
          printf("J ");
        } else if (!strcmp(game_deck[k].name, "queen")) {
          printf("Q ");
        } else if (!strcmp(game_deck[k].name, "king")) {
          printf("K ");
        } else if (!strcmp(game_deck[k].name, "ace")) {
          printf("A ");
        } else printf("%s ", game_deck[k].name);
        if (!strcmp(game_deck[k].suit, "clubs")) {
          printf("%s\n", CLUB);
        } else if (!strcmp(game_deck[k].suit, "spades")) {
          printf("%s\n", SPADE);
        } else if (!strcmp(game_deck[k].suit, "diamonds")) {
          printf("%s\n", DIAMOND);
        } else if (!strcmp(game_deck[k].suit, "hearts")) {
          printf("%s\n", HEART);
        }
        encoded_deck[rand_card] = encoded_deck[curr_card - 1];
        curr_card--;
        k = NUMBER_CARDS;
      }
    }
  }
  printf("\n");
  for(int i = 0; i < n_players; i++) {
    printf("%s[SYSTEM]%s Player %d:\n", YELLOW, RESET, i + 1);
    if (!strcmp(player_hand[i][0].name, "jack")) {
      printf("J ");
    } else if (!strcmp(player_hand[i][0].name, "queen")) {
      printf("Q ");
    } else if (!strcmp(player_hand[i][0].name, "king")) {
      printf("K ");
    } else if (!strcmp(player_hand[i][0].name, "ace")) {
      printf("A ");
    } else printf("%s ", player_hand[i][0].name);
    if (!strcmp(player_hand[i][0].suit, "clubs")) {
      printf("%s\n", CLUB);
    } else if (!strcmp(player_hand[i][0].suit, "spades")) {
      printf("%s\n", SPADE);
    } else if (!strcmp(player_hand[i][0].suit, "diamonds")) {
      printf("%s\n", DIAMOND);
    } else if (!strcmp(player_hand[i][0].suit, "hearts")) {
      printf("%s\n", HEART);
    }
    if (!strcmp(player_hand[i][1].name, "jack")) {
      printf("J ");
    } else if (!strcmp(player_hand[i][1].name, "queen")) {
      printf("Q ");
    } else if (!strcmp(player_hand[i][1].name, "king")) {
      printf("K ");
    } else if (!strcmp(player_hand[i][1].name, "ace")) {
      printf("A ");
    } else printf("%s ", player_hand[i][1].name);
    if (!strcmp(player_hand[i][1].suit, "clubs")) {
      printf("%s\n", CLUB);
    } else if (!strcmp(player_hand[i][1].suit, "spades")) {
      printf("%s\n", SPADE);
    } else if (!strcmp(player_hand[i][1].suit, "diamonds")) {
      printf("%s\n", DIAMOND);
    } else if (!strcmp(player_hand[i][1].suit, "hearts")) {
      printf("%s\n", HEART);
    }
    printf("\n");
  }
  printf("%s[SYSTEM]%s Widow: %lu cards\n", YELLOW, RESET, curr_card);
}
