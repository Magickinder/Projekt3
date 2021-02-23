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

#define PLAYER_VISIBILITY_X 5
#define PLAYER_VISIBILITY_Y 5

#define MAP_WIDTH 61
#define MAP_HEIGHT 41
#define INFO_WIDTH 61
#define INFO_HEIGHT 30

#define COIN_SIGN 'c'
#define TREASURE_SIGN 't'
#define LARGE_TREASURE_SIGN 'T'

#define CAMPSITE_X 3
#define CAMPSITE_Y 4

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
};

struct player_map_data{
    sem_t sem;
    struct player_t player;
    wchar_t map[PLAYER_VISIBILITY_Y][PLAYER_VISIBILITY_X];
    int round_number;
};

void init_ncurses();
void print_map();
void print_info(struct player_map_data *pdata, int servers_pid);
void refresh_all();

#endif //FUNCTIONS_H
