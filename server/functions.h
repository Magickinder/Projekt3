#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <ncurses.h>
#include <wchar.h>

#define NUMBER_OF_PLAYERS 2
#define MAXIMUM_AMOUNT_OF_COINS 100
#define MAXIMUM_AMOUNT_OF_TREASURES 5
#define MAXIMUM_AMOUNT_OF_LARGE_TREASURES 3
#define PLAYER_VISIBILITY_X 5
#define PLAYER_VISIBILITY_Y 5

struct player_t{
    int x, y;
    int start_x, start_y;
    int number;
    int coins_carried;
    int coins_brought;
    int deaths;
} players[NUMBER_OF_PLAYERS];

struct coin_t{
    int x, y;
    int status; // 1 - on map, 2 - picked
} coins[MAXIMUM_AMOUNT_OF_COINS], treasures[MAXIMUM_AMOUNT_OF_TREASURES], l_treasures[MAXIMUM_AMOUNT_OF_LARGE_TREASURES];

struct player_map_data{
    sem_t sem;
    struct player_t player;
    wchar_t map[PLAYER_VISIBILITY_Y][PLAYER_VISIBILITY_X];
};

void init_ncurses();
void refresh_all();
void print_map();
void init_players();
void init_objects();
void generate_coin();
void generate_treasure();
void generate_l_treasure();
void print_players();
void print_coins();
void print_campsite();
void print_bushes();
void print_info();
void handle_signal();
void send_map();

#endif //FUNCTIONS_H
