#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
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

#define SHM_NAME "Project"

enum move {UP, DOWN, LEFT, RIGHT, NONE};

struct player_t{
    int x, y;
    int start_x, start_y;
    int number;
    int coins_carried;
    int coins_brought;
    int deaths;
    int PID;
    enum move next_move;
} players[NUMBER_OF_PLAYERS];

struct beast_t{
    int x, y;
} beast;

struct coin_t{
    int x, y;
    int status; // 1 - on map, 2 - picked
} coins[MAXIMUM_AMOUNT_OF_COINS], treasures[MAXIMUM_AMOUNT_OF_TREASURES], l_treasures[MAXIMUM_AMOUNT_OF_LARGE_TREASURES];

struct player_map_data{
    sem_t sem;
    struct player_t player;
    wchar_t map[PLAYER_VISIBILITY_Y][PLAYER_VISIBILITY_X];
    int round_number;
};

void init_ncurses();
void refresh_all();
void print_map();
int scan_surrounding_area();
int can_see_the_player();
void move_to_players_coordinates();
void *beast_behaviour();
void init_beast();
void print_beast();
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
void handle_signal(int signum, siginfo_t *info, void *oldact);
void handle_bad_exit(int signum, siginfo_t *info, void *oldact);
void move_players();
void send_map();
void *game_logic();

#endif //FUNCTIONS_H
