#include "functions.h"

#define MAP_WIDTH 61
#define MAP_HEIGHT 41
#define INFO_WIDTH 61
#define INFO_HEIGHT 30

#define COIN_SIGN 'c'
#define COIN_VALUE 1
#define TREASURE_SIGN 't'
#define TREASURE_VALUE 10
#define LARGE_TREASURE_SIGN 'T'
#define LARGE_TREASURE_VALUE 50

#define CAMPSITE_SIGN 'A'
#define CAMPSITE_X 3
#define CAMPSITE_Y 4

#define BUSH_SIGN '#'

#define BEAST_SIGN '*'

#define LOOT_SIGN 'D'

WINDOW *map_window;
WINDOW *info_window;

pthread_mutex_t beast_mutex = PTHREAD_MUTEX_INITIALIZER;

const wchar_t map[41][62] = {
        {' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' | A_REVERSE},
        {' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE,' ' | A_REVERSE}
};

void init_ncurses(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    timeout(200);

    map_window = newwin(MAP_HEIGHT + 2, MAP_WIDTH + 2, 0, 0);
    box(map_window, 0, 0);
    info_window = newwin(INFO_HEIGHT + 2, INFO_WIDTH + 2, 0, MAP_WIDTH + 2 + 2); // + 2 because of border
    box(info_window, 0, 0);
}

void refresh_all(){
    refresh(); // refresh display
    wrefresh(map_window); // refresh window
    wrefresh(info_window);
}

void print_map(){
    for(int y = 0; y < MAP_HEIGHT; y++)
        for(int x = 0; x < MAP_WIDTH; x++)
            mvwaddch(map_window, y + 1, x + 1, map[y][x]);
}

void init_players(){
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
        players[i].x = i + 2;
        players[i].start_x = i + 2;
        players[i].y = 2;
        players[i].type = 0;
        players[i].start_y = 2;
        players[i].number = i + 1;
        players[i].coins_carried = 0;
        players[i].coins_brought = 0;
        players[i].PID = 0;
        players[i].campsite_spotted = 1;
        players[i].deaths = 0;
        players[i].on_bush = 1;
    }
}

void is_near_campsite(){
    if((players[1].x - 2 <= CAMPSITE_X && players[1].x + 2 >= CAMPSITE_X)
    && (players[1].y - 2 <= CAMPSITE_Y && players[1].y + 2 >= CAMPSITE_Y))
        players[1].campsite_spotted = 2;
}

void print_players(){
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
        if(players[i].type != 0)
            mvwaddch(map_window, players[i].y, players[i].x, players[i].number + '0');
}

void init_beast(){
    beast.x = 5;
    beast.y = 10;
}

void print_beast(){
    mvwaddch(map_window, beast.y, beast.x, BEAST_SIGN);
}

int can_see_the_player(){
    //int a = 1, b = 1;
    wchar_t c = 0;
    
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++){
        if(beast.x == players[i].x){
            if(beast.y < players[i].y){
                /*while((beast.y + a) != players[i].y){
                    pthread_mutex_lock(&beast_mutex);
                    c = mvwinch(map_window, beast.y + a, beast.x);
                    pthread_mutex_unlock(&beast_mutex);
                    if(c == (' ' | A_REVERSE))
                        return 0;
                    a++;
                }*/
                
                pthread_mutex_lock(&beast_mutex);
                c = mvwinch(map_window, beast.y + 1, beast.x);
                pthread_mutex_unlock(&beast_mutex);
                if(c == (' ' | A_REVERSE))
                    return 0;
            }
            else if(beast.y > players[i].y){
                /*while((beast.y - a) != players[i].y){
                    pthread_mutex_lock(&beast_mutex);
                    c = mvwinch(map_window, beast.y - a, beast.x);
                    pthread_mutex_unlock(&beast_mutex);
                    if(c == (' ' | A_REVERSE))
                        return 0;
                    a++;
                }*/
                
                pthread_mutex_lock(&beast_mutex);
                c = mvwinch(map_window, beast.y - 1, beast.x);
                pthread_mutex_unlock(&beast_mutex);
                if(c == (' ' | A_REVERSE))
                    return 0;
            }
        }
        else if(beast.y == players[i].y){
            if(beast.x < players[i].x){
                /*while((beast.x + b) != players[i].x){
                    pthread_mutex_lock(&beast_mutex);
                    c = mvwinch(map_window, beast.y, beast.x + b);
                    pthread_mutex_unlock(&beast_mutex);
                    if(c == (' ' | A_REVERSE))
                        return 0;
                    b++;
                }*/
                
                pthread_mutex_lock(&beast_mutex);
                c = mvwinch(map_window, beast.y, beast.x + 1);
                pthread_mutex_unlock(&beast_mutex);
                if(c == (' ' | A_REVERSE))
                    return 0;
            }
            else if(beast.x > players[i].x){
                /*while((beast.x - b) != players[i].x){
                    pthread_mutex_lock(&beast_mutex);
                    c = mvwinch(map_window, beast.y, beast.x - b);
                    pthread_mutex_unlock(&beast_mutex);
                    if(c == (' ' | A_REVERSE))
                        return 0;
                    b++;
                }*/
                
                pthread_mutex_lock(&beast_mutex);
                c = mvwinch(map_window, beast.y, beast.x - 1);
                pthread_mutex_unlock(&beast_mutex);
                if(c == (' ' | A_REVERSE))
                    return 0;
            }
            else{
                if(players[i].x == (beast.x - 2) && players[i].y == (beast.y - 2)){
                    pthread_mutex_lock(&beast_mutex);
                    c = mvwinch(map_window, beast.y - 1, beast.x - 1);
                    pthread_mutex_unlock(&beast_mutex);
                    if(c == (' ' | A_REVERSE))
                        return 0;
                }
                else if(players[i].x == (beast.x + 2) && players[i].y == (beast.y - 2)){
                    pthread_mutex_lock(&beast_mutex);
                    c = mvwinch(map_window, beast.y - 1, beast.x + 1);
                    pthread_mutex_unlock(&beast_mutex);
                    if(c == (' ' | A_REVERSE))
                        return 0;
                }
                else if(players[i].x == (beast.x - 2) && players[i].y == (beast.y + 2)){
                    pthread_mutex_lock(&beast_mutex);
                    c = mvwinch(map_window, beast.y + 1, beast.x - 1);
                    pthread_mutex_unlock(&beast_mutex);
                    if(c == (' ' | A_REVERSE))
                        return 0;
                }
                else if(players[i].x == (beast.x + 2) && players[i].y == (beast.y + 2)){
                    pthread_mutex_lock(&beast_mutex);
                    c = mvwinch(map_window, beast.y + 1, beast.x + 1);
                    pthread_mutex_unlock(&beast_mutex);
                    if(c == (' ' | A_REVERSE))
                        return 0;
                }
                
                /*if(beast.x > players[i].x && beast.y > players[i].y){
                    while((beast.x - a) > players[i].x && (beast.y - b) > players[i].y){
                        c = mvwinch(map_window, beast.y - b, beast.x - a);
                        if(c == (' ' | A_REVERSE))
                            return 0;
                        a++, b++;
                    }
                }
                else if(beast.x < players[i].x && beast.y > players[i].y){
                    while((beast.x + a) < players[i].x && (beast.y - b) > players[i].y){
                        c = mvwinch(map_window, beast.y - b, beast.x + a);
                        if(c == (' ' | A_REVERSE))
                            return 0;
                        a++, b++;
                    }
                }
                else if(beast.x < players[i].x && beast.y < players[i].y){
                    while((beast.x + a) < players[i].x && (beast.y + b) < players[i].y){
                        c = mvwinch(map_window, beast.y + b, beast.x + a);
                        if(c == (' ' | A_REVERSE))
                            return 0;
                        a++, b++;
                    }
                }
                else{
                    while((beast.x - a) > players[i].x && (beast.y + b) < players[i].y){
                        c = mvwinch(map_window, beast.y + b, beast.x - a);
                        if(c == (' ' | A_REVERSE))
                            return 0;
                        a++, b++;
                    }
                }*/
            }
        }
    }

    return 1;
}

int scan_surrounding_area(){
    int player_found = 0;
    
    for(int y = beast.y - 2; y <= beast.y + 2; y++){
        for(int x = beast.x - 2; x <= beast.x + 2; x++){
            if((x == players[0].x && y == players[0].y) || (x == players[1].x && y == players[1].y)){
                player_found = 1;
                break;
            }
        }
    }
    
    return player_found;
}

void move_to_players_coordinates(){
    if(beast.x == players[1].x){
        if(beast.y < players[1].y){
            while(beast.y != players[1].y){
                if(mvwinch(map_window, players[0].y - 1, players[0].x) != (' ' | A_REVERSE))
                    beast.y++;
            }
        }
        else if(beast.y > players[1].y){
            while(beast.y != players[1].y){
                if(mvwinch(map_window, players[0].y - 1, players[0].x) != (' ' | A_REVERSE))
                    beast.y--;
            }
        }
    }
    else if(beast.y == players[1].y){
        if(beast.x < players[1].x){
            while(beast.x != players[1].x){
                if(mvwinch(map_window, players[0].y - 1, players[0].x) != (' ' | A_REVERSE))
                    beast.x++;
            }
        }
        else if(beast.x > players[1].x){
            while(beast.x != players[1].x){
                if(mvwinch(map_window, players[0].y - 1, players[0].x) != (' ' | A_REVERSE))
                    beast.x--;
            }
        }
    }
    else{
        if(beast.x > players[1].x && beast.y > players[1].y){
            while(beast.x > players[1].x && beast.y > players[1].y){
                if(mvwinch(map_window, players[0].y - 1, players[0].x) != (' ' | A_REVERSE)){
                    beast.x--;
                    beast.y--;
                }
            }
        }
        else if(beast.x < players[1].x && beast.y > players[1].y){
            while(beast.x < players[1].x && beast.y > players[1].y){
                if(mvwinch(map_window, players[0].y - 1, players[0].x) != (' ' | A_REVERSE)){
                    beast.x--;
                    beast.y--;
                }
            }
        }
        else if(beast.x < players[1].x && beast.y < players[1].y){
            while(beast.x < players[1].x && beast.y < players[1].y){
                if(mvwinch(map_window, players[0].y - 1, players[0].x) != (' ' | A_REVERSE)){
                    beast.x++;
                    beast.y++;
                }
            }
        }
        else{
            while(beast.x > players[1].x && beast.y < players[1].y){
                if(mvwinch(map_window, players[0].y - 1, players[0].x) != (' ' | A_REVERSE)){
                    beast.x--;
                    beast.y++;
                }
            }
        }
    }
}

void beast_random_movement(){
    beast.next_move = rand() % 4 + 1;
}

void *beast_behaviour(){
    while(1){
        if((scan_surrounding_area()) && (can_see_the_player())){
                beast_random_movement();
                //move_to_players_coordinates();
                //beast.x--;
        }
        else{
            beast.next_move = NONE;
        }
    }
    
    return NULL;
}

void player_beast_collision(){
    int i = 0;
    for(int j = 0; j < NUMBER_OF_PLAYERS; j++){
        if(players[j].x == beast.x && players[j].y == beast.y && players[j].type != 0){
            if(players[j].coins_carried > 0){
                for(; i < MAXIMUM_AMOUNT_OF_LOOTS; i++){
                    if(loots[i].status != 1){
                        loots[i].x = players[j].x;
                        loots[i].y = players[j].y;
                        loots[i].value = players[j].coins_carried;
                        loots[i].status = 1;
                        players[j].coins_carried = 0;
                        break;
                    }
                }
            }
            players[j].deaths++;
            players[j].x = players[j].start_x;
            players[j].y = players[j].start_y;
        }
    }
}

void players_collision(){
    int i = 0;
    if(players[0].x == players[1].x && players[0].y == players[1].y && players[0].type != 0 && players[1].type != 0){
        if(players[0].coins_carried > 0 || players[1].coins_carried > 0){
            for(; i < MAXIMUM_AMOUNT_OF_LOOTS; i++){
                if(loots[i].status != 1){
                    loots[i].x = players[0].x;
                    loots[i].y = players[0].y;
                    loots[i].value = players[0].coins_carried + players[1].coins_carried;
                    loots[i].status = 1;
                    players[0].coins_carried = 0;
                    players[1].coins_carried = 0;
                    break;
                }
            }
        }
        
        players[0].x = players[0].start_x;
        players[0].y = players[0].start_y;
        players[0].deaths++;
        players[1].x = players[1].start_x;
        players[1].y = players[1].start_y;
        players[1].deaths++;
    }
}

void init_objects(){
    int flag = 0;

    for(int i = 0; i < 50; i++){
        if(coins[i].status != 1){
            coins[i].x = rand() % (MAP_WIDTH - 3) + 2;
            coins[i].y = rand() % (MAP_HEIGHT - 3) + 2;
            coins[i].status = 1;

            while(!flag){
                switch(mvwinch(map_window, coins[i].y, coins[i].x)){
                    case '1':
                    case '2':
                    case COIN_SIGN:
                    case TREASURE_SIGN:
                    case LARGE_TREASURE_SIGN:
                    case ' ' | A_REVERSE:
                    case CAMPSITE_SIGN:
                    case BUSH_SIGN:
                    case BEAST_SIGN:
                    case LOOT_SIGN:
                        coins[i].x = rand() % (MAP_WIDTH - 3) + 2;
                        coins[i].y = rand() % (MAP_HEIGHT - 3) + 2;
                    break;
                    default:
                        flag = 1;
                    break;
                }
            }

            flag = 0;
        }
    }

    for(int i = 0; i < 3; i++){
        if(treasures[i].status != 1){
            treasures[i].x = rand() % (MAP_WIDTH - 3) + 2;
            treasures[i].y = rand() % (MAP_HEIGHT - 3) + 2;
            treasures[i].status = 1;

            while(!flag){
                switch(mvwinch(map_window, treasures[i].y, treasures[i].x)){
                    case '1':
                    case '2':
                    case COIN_SIGN:
                    case TREASURE_SIGN:
                    case LARGE_TREASURE_SIGN:
                    case ' ' | A_REVERSE:
                    case CAMPSITE_SIGN:
                    case BUSH_SIGN:
                    case BEAST_SIGN:
                    case LOOT_SIGN:
                        treasures[i].x = rand() % (MAP_WIDTH - 3) + 2;
                        treasures[i].y = rand() % (MAP_HEIGHT - 3) + 2;
                        break;
                    default:
                        flag = 1;
                        break;
                }
            }

            flag = 0;
        }
    }

    for(int i = 0; i < 2; i++){
        if(l_treasures[i].status != 1){
            l_treasures[i].x = rand() % (MAP_WIDTH - 3) + 2;
            l_treasures[i].y = rand() % (MAP_HEIGHT - 3) + 2;
            l_treasures[i].status = 1;

            while(!flag){
                switch(mvwinch(map_window, l_treasures[i].y, l_treasures[i].x)){
                    case '1':
                    case '2':
                    case COIN_SIGN:
                    case TREASURE_SIGN:
                    case LARGE_TREASURE_SIGN:
                    case ' ' | A_REVERSE:
                    case CAMPSITE_SIGN:
                    case BUSH_SIGN:
                    case BEAST_SIGN:
                    case LOOT_SIGN:
                        l_treasures[i].x = rand() % (MAP_WIDTH - 3) + 2;
                        l_treasures[i].y = rand() % (MAP_HEIGHT - 3) + 2;
                        break;
                    default:
                        flag = 1;
                        break;
                }
            }

            flag = 0;
        }
    }
}

void generate_coin(){
    int flag = 0;
    
    for(int i = 0; i < MAXIMUM_AMOUNT_OF_COINS; i++){
        if(coins[i].status != 1){
            coins[i].x = rand() % (MAP_WIDTH - 3) + 2;
            coins[i].y = rand() % (MAP_HEIGHT - 3) + 2;
            coins[i].status = 1;

            while(!flag){
                switch(mvwinch(map_window, coins[i].y, coins[i].x)){
                    case '1':
                    case '2':
                    case COIN_SIGN:
                    case TREASURE_SIGN:
                    case LARGE_TREASURE_SIGN:
                    case ' ' | A_REVERSE:
                    case CAMPSITE_SIGN:
                    case BUSH_SIGN:
                    case BEAST_SIGN:
                    case LOOT_SIGN:
                        coins[i].x = rand() % (MAP_WIDTH - 3) + 2;
                        coins[i].y = rand() % (MAP_HEIGHT - 3) + 2;
                    break;
                    default:
                        flag = 1;
                    break;
                }
            }

            flag = 0;
            break;
        }
    }
}

void generate_treasure(){
    int flag = 0;
    
    for(int i = 0; i < MAXIMUM_AMOUNT_OF_TREASURES; i++){
        if(treasures[i].status != 1){
            treasures[i].x = rand() % (MAP_WIDTH - 3) + 2;
            treasures[i].y = rand() % (MAP_HEIGHT - 3) + 2;
            treasures[i].status = 1;

            while(!flag){
                switch(mvwinch(map_window, treasures[i].y, treasures[i].x)){
                    case '1':
                    case '2':
                    case COIN_SIGN:
                    case TREASURE_SIGN:
                    case LARGE_TREASURE_SIGN:
                    case ' ' | A_REVERSE:
                    case CAMPSITE_SIGN:
                    case BUSH_SIGN:
                    case BEAST_SIGN:
                    case LOOT_SIGN:
                        treasures[i].x = rand() % (MAP_WIDTH - 3) + 2;
                        treasures[i].y = rand() % (MAP_HEIGHT - 3) + 2;
                        break;
                    default:
                        flag = 1;
                        break;
                }
            }

            flag = 0;
            break;
        }
    }
}

void generate_l_treasure(){
    int flag = 0;
    
    for(int i = 0; i < MAXIMUM_AMOUNT_OF_LARGE_TREASURES; i++){
        if(l_treasures[i].status != 1){
            l_treasures[i].x = rand() % (MAP_WIDTH - 3) + 2;
            l_treasures[i].y = rand() % (MAP_HEIGHT - 3) + 2;
            l_treasures[i].status = 1;

            while(!flag){
                switch(mvwinch(map_window, l_treasures[i].y, l_treasures[i].x)){
                    case '1':
                    case '2':
                    case COIN_SIGN:
                    case TREASURE_SIGN:
                    case LARGE_TREASURE_SIGN:
                    case ' ' | A_REVERSE:
                    case CAMPSITE_SIGN:
                    case BUSH_SIGN:
                    case BEAST_SIGN:
                    case LOOT_SIGN:
                        l_treasures[i].x = rand() % (MAP_WIDTH - 3) + 2;
                        l_treasures[i].y = rand() % (MAP_HEIGHT - 3) + 2;
                        break;
                    default:
                        flag = 1;
                        break;
                }
            }

            flag = 0;
            break;
        }
    }
}

void print_coins(){
    for(int i = 0; i < MAXIMUM_AMOUNT_OF_COINS; i++){
        if(coins[i].status == 1){
            switch(mvwinch(map_window, coins[i].y, coins[i].x)){
                case '1':
                    players[0].coins_carried += COIN_VALUE;
                    coins[i].status = 2;
                break;
                case '2':
                    players[1].coins_carried += COIN_VALUE;
                    coins[i].status = 2;
                break;
                default:
                    mvwaddch(map_window, coins[i].y, coins[i].x, COIN_SIGN);
                break;
            }
        }
    }

    for(int i = 0; i < MAXIMUM_AMOUNT_OF_TREASURES; i++){
        if(treasures[i].status == 1){
            switch(mvwinch(map_window, treasures[i].y, treasures[i].x)){
                case '1':
                    players[0].coins_carried += TREASURE_VALUE;
                    treasures[i].status = 2;
                break;
                case '2':
                    players[1].coins_carried += TREASURE_VALUE;
                    treasures[i].status = 2;
                    break;
                default:
                    mvwaddch(map_window, treasures[i].y, treasures[i].x, TREASURE_SIGN);
                    break;
            }
        }
    }

    for(int i = 0; i < MAXIMUM_AMOUNT_OF_LARGE_TREASURES; i++){
        if(l_treasures[i].status == 1){
            switch(mvwinch(map_window, l_treasures[i].y, l_treasures[i].x)){
                case '1':
                    players[0].coins_carried += LARGE_TREASURE_VALUE;
                    l_treasures[i].status = 2;
                break;
                case '2':
                    players[1].coins_carried += LARGE_TREASURE_VALUE;
                    l_treasures[i].status = 2;
                    break;
                default:
                    mvwaddch(map_window, l_treasures[i].y, l_treasures[i].x, LARGE_TREASURE_SIGN);
                    break;
            }
        }
    }
    
    for(int i = 0; i < MAXIMUM_AMOUNT_OF_LOOTS; i++){
        if(loots[i].status == 1){
            switch(mvwinch(map_window, loots[i].y, loots[i].x)){
                case '1':
                    players[0].coins_carried += loots[i].value;
                    loots[i].status = 2;
                break;
                case '2':
                    players[1].coins_carried += loots[i].value;
                    loots[i].status = 2;
                    break;
                default:
                    mvwaddch(map_window, loots[i].y, loots[i].x, LOOT_SIGN);
                    break;
            }
        }
    }
}

void print_campsite(){
    switch(mvwinch(map_window, CAMPSITE_Y, CAMPSITE_X)){
        case '1':
            players[0].coins_brought += players[0].coins_carried;
            players[0].coins_carried = 0;
        break;
        case '2':
            players[1].coins_brought += players[1].coins_carried;
            players[1].coins_carried = 0;
        break;
        default:
            mvwaddch(map_window, CAMPSITE_Y, CAMPSITE_X, CAMPSITE_SIGN);
        break;
    }
}

void print_bushes(){
    mvwaddch(map_window, 3, 2, BUSH_SIGN);
    mvwaddch(map_window, 4, 2, BUSH_SIGN);
    mvwaddch(map_window, 11, 29, BUSH_SIGN);
    mvwaddch(map_window, 11, 30, BUSH_SIGN);
    mvwaddch(map_window, 10, 29, BUSH_SIGN);
    mvwaddch(map_window, 10, 30, BUSH_SIGN);
    mvwaddch(map_window, 26, 31, BUSH_SIGN);
    mvwaddch(map_window, 25, 30, BUSH_SIGN);
    mvwaddch(map_window, 25, 29, BUSH_SIGN);
    mvwaddch(map_window, 31, 23, BUSH_SIGN);
    mvwaddch(map_window, 31, 24, BUSH_SIGN);
    mvwaddch(map_window, 35, 8, BUSH_SIGN);
    mvwaddch(map_window, 36, 9, BUSH_SIGN);
}

void print_info(struct player_map_data *pdata){
    int y_offset = 0;
    
    werase(info_window);
    box(info_window, 0, 0);

    mvwprintw(info_window, ++y_offset, 1, "Server's PID: %d", getpid());
    mvwprintw(info_window, ++y_offset, 1, " Campsite X/Y: %d/%d", CAMPSITE_X, CAMPSITE_Y);
    mvwprintw(info_window, ++y_offset, 1, " Round number: %d", pdata->round_number);

    y_offset += 3;

    //Players info
    mvwprintw(info_window, ++y_offset, 1, "Parameter:   Player 1    Player 2    Player 3    Player 4");
        
    if(players[1].type == 0){
        mvwprintw(info_window, ++y_offset, 1, " PID         %04d", players[0].PID);
        mvwprintw(info_window, y_offset, 26, "-");
        mvwprintw(info_window, y_offset, 38, "-");
        mvwprintw(info_window, y_offset, 50, "-");
        mvwprintw(info_window, ++y_offset, 1, " TYPE        %s", "HUMAN");
        mvwprintw(info_window, y_offset, 26, "%s", "-");
        mvwprintw(info_window, y_offset, 38, "-");
        mvwprintw(info_window, y_offset, 50, "-");
        mvwprintw(info_window, ++y_offset, 1, " Curr X/Y    %02d/%02d", players[0].x, players[0].y);
        mvwprintw(info_window, y_offset, 26, "-/-");
        mvwprintw(info_window, y_offset, 38, "-/-");
        mvwprintw(info_window, y_offset, 50, "-/-");
        mvwprintw(info_window, ++y_offset, 1, " Deaths      %d", players[0].deaths);
        mvwprintw(info_window, y_offset, 26, "-");
        mvwprintw(info_window, y_offset, 38, "-");
        mvwprintw(info_window, y_offset, 50, "-");
        
        y_offset += 3;

        mvwprintw(info_window, ++y_offset, 1, "Coins");
        mvwprintw(info_window, ++y_offset, 1, " Carried     %04d", players[0].coins_carried);
        mvwprintw(info_window, y_offset, 26, "-");
        mvwprintw(info_window, y_offset, 38, "-");
        mvwprintw(info_window, y_offset, 50, "-");
        mvwprintw(info_window, ++y_offset, 1, " Brought     %04d", players[0].coins_brought);
        mvwprintw(info_window, y_offset, 26, "-");
        mvwprintw(info_window, y_offset, 38, "-");
        mvwprintw(info_window, y_offset, 50, "-");
    }
    else{
        mvwprintw(info_window, ++y_offset, 1, " PID         %04d", players[0].PID);
        mvwprintw(info_window, y_offset, 26, "%04d", players[1].PID);
        mvwprintw(info_window, y_offset, 38, "-");
        mvwprintw(info_window, y_offset, 50, "-");
        mvwprintw(info_window, ++y_offset, 1, " TYPE        %s", "HUMAN");
        mvwprintw(info_window, y_offset, 26, "%s", players[1].type == 1 ? "HUMAN" : "CPU");
        mvwprintw(info_window, y_offset, 38, "-");
        mvwprintw(info_window, y_offset, 50, "-");
        mvwprintw(info_window, ++y_offset, 1, " Curr X/Y    %02d/%02d", players[0].x, players[0].y);
        mvwprintw(info_window, y_offset, 26, "%02d/%02d", players[1].x, players[1].y);
        mvwprintw(info_window, y_offset, 38, "-/-");
        mvwprintw(info_window, y_offset, 50, "-/-");
        mvwprintw(info_window, ++y_offset, 1, " Deaths      %d", players[0].deaths);
        mvwprintw(info_window, y_offset, 26, "%d", players[1].deaths);
        mvwprintw(info_window, y_offset, 38, "-");
        mvwprintw(info_window, y_offset, 50, "-");
        
        y_offset += 3;

        mvwprintw(info_window, ++y_offset, 1, "Coins");
        mvwprintw(info_window, ++y_offset, 1, " Carried     %04d", players[0].coins_carried);
        mvwprintw(info_window, y_offset, 26, "%04d", players[1].coins_carried);
        mvwprintw(info_window, y_offset, 38, "-");
        mvwprintw(info_window, y_offset, 50, "-");
        mvwprintw(info_window, ++y_offset, 1, " Brought     %04d", players[0].coins_brought);
        mvwprintw(info_window, y_offset, 26, "%04d", players[1].coins_brought);
        mvwprintw(info_window, y_offset, 38, "-");
        mvwprintw(info_window, y_offset, 50, "-");
    }
    
    y_offset += 3;

    mvwprintw(info_window, ++y_offset, 1, "Legend:");
    mvwprintw(info_window, ++y_offset, 1, " 1234 - players");
    mvwaddch(info_window, ++y_offset, 2, ' ' | A_REVERSE);
    mvwprintw(info_window, y_offset, 3, "    - wall");
    mvwprintw(info_window, ++y_offset, 1, " #    - bush");
    mvwprintw(info_window, ++y_offset, 1, " *    - wild beast");
    mvwprintw(info_window, ++y_offset, 1, " %c    - one coin", COIN_SIGN);
    mvwprintw(info_window, ++y_offset, 1, " %c    - treasure (10 coins)", TREASURE_SIGN);
    mvwprintw(info_window, ++y_offset, 1, " %c    - large treasure (50 coins)", LARGE_TREASURE_SIGN);
    mvwprintw(info_window, ++y_offset, 1, " A    - campsite");
    mvwprintw(info_window, ++y_offset, 1, " D    - dropped treasure");
}

void handle_signal(int signum, siginfo_t *info, void *oldact){
    int key = (int)info->si_value.sival_int;
    if(players[1].PID == 0)
        players[1].PID = (int)info->si_pid;

    switch(key){
        case 0:
        case 1:
        case 2:
            players[1].type = key;
            if(key == 0)
                players[1].PID = 0;
        break;
        case 65: // up
            players[1].next_move = UP;
        break;
        case 66: // down
            players[1].next_move = DOWN;
        break;
        case 67: // right
            players[1].next_move = RIGHT;
        break;
        case 68: // left
            players[1].next_move = LEFT;
        break;
        default:
        break;
    }
}

void handle_bad_exit(int signum, siginfo_t *info, void *oldact){
    shm_unlink(SHM_NAME);
    endwin();
}

void handleKey(int key){
    switch(key){
        case 65: // up
            players[0].next_move = UP;
        break;
        case 66: // down
            players[0].next_move = DOWN;
        break;
        case 67: // right
            players[0].next_move = RIGHT;
        break;
        case 68: // left
            players[0].next_move = LEFT;
        break;
        default:
        break;
    }
}

void move_players(){
    switch(players[0].next_move){
        case UP:
            if(mvwinch(map_window, players[0].y - 1, players[0].x) == BUSH_SIGN){
                if(players[0].on_bush != 2){
                    players[0].y--;
                    players[0].on_bush = 2;
                    break;
                }
            }
            
            if(players[0].on_bush == 2){
                players[0].on_bush = 1;
                break;
            }
                    
            if(mvwinch(map_window, players[0].y - 1, players[0].x) != (' ' | A_REVERSE))
                players[0].y--;
        break;
        case DOWN:
            if(mvwinch(map_window, players[0].y + 1, players[0].x) == BUSH_SIGN){
                if(players[0].on_bush != 2){
                    players[0].y++;
                    players[0].on_bush = 2;
                    break;
                }
            }
            
            if(players[0].on_bush == 2){
                players[0].on_bush = 1;
                break;
            }
        
            if(mvwinch(map_window, players[0].y + 1, players[0].x) != (' ' | A_REVERSE))
                players[0].y++;
        break;
        case RIGHT:
            if(mvwinch(map_window, players[0].y, players[0].x + 1) == BUSH_SIGN){
                if(players[0].on_bush != 2){
                    players[0].x++;
                    players[0].on_bush = 2;
                    break;
                }
            }
            
            if(players[0].on_bush == 2){
                players[0].on_bush = 1;
                break;
            }
        
            if(mvwinch(map_window, players[0].y, players[0].x + 1) != (' ' | A_REVERSE))
                players[0].x++;
        break;
        case LEFT:
            if(mvwinch(map_window, players[0].y, players[0].x - 1) == BUSH_SIGN){
                if(players[0].on_bush != 2){
                    players[0].x--;
                    players[0].on_bush = 2;
                    break;
                }
            }
            
            if(players[0].on_bush == 2){
                players[0].on_bush = 1;
                break;
            }
        
            if(mvwinch(map_window, players[0].y, players[0].x - 1) != (' ' | A_REVERSE))
                players[0].x--;
        break;
        default:
        break;
    }
    
    switch(players[1].next_move){
        case UP:
            if(mvwinch(map_window, players[1].y - 1, players[1].x) == BUSH_SIGN){
                if(players[1].on_bush != 2){
                    players[1].y--;
                    players[1].on_bush = 2;
                    break;
                }
            }
            
            if(players[1].on_bush == 2){
                players[1].on_bush = 1;
                break;
            }
                    
            if(mvwinch(map_window, players[1].y - 1, players[1].x) != (' ' | A_REVERSE))
                players[1].y--;
        break;
        case DOWN:
            if(mvwinch(map_window, players[1].y + 1, players[1].x) == BUSH_SIGN){
                if(players[1].on_bush != 2){
                    players[1].y++;
                    players[1].on_bush = 2;
                    break;
                }
            }
            
            if(players[1].on_bush == 2){
                players[1].on_bush = 1;
                break;
            }
        
            if(mvwinch(map_window, players[1].y + 1, players[1].x) != (' ' | A_REVERSE))
                players[1].y++;
        break;
        case RIGHT:
            if(mvwinch(map_window, players[1].y, players[1].x + 1) == BUSH_SIGN){
                if(players[1].on_bush != 2){
                    players[1].x++;
                    players[1].on_bush = 2;
                    break;
                }
            }
            
            if(players[1].on_bush == 2){
                players[1].on_bush = 1;
                break;
            }
        
            if(mvwinch(map_window, players[1].y, players[1].x + 1) != (' ' | A_REVERSE))
                players[1].x++;
        break;
        case LEFT:
            if(mvwinch(map_window, players[1].y, players[1].x - 1) == BUSH_SIGN){
                if(players[1].on_bush != 2){
                    players[1].x--;
                    players[1].on_bush = 2;
                    break;
                }
            }
            
            if(players[1].on_bush == 2){
                players[1].on_bush = 1;
                break;
            }
        
            if(mvwinch(map_window, players[1].y, players[1].x - 1) != (' ' | A_REVERSE))
                players[1].x--;
        break;
        default:
        break;
    }
    
    switch(beast.next_move){
        case UP:
            if(mvwinch(map_window, beast.y - 1, beast.x) != (' ' | A_REVERSE))
                beast.y--;
        break;
        case DOWN:
            if(mvwinch(map_window, beast.y + 1, beast.x) != (' ' | A_REVERSE))
                beast.y++;
        break;
        case RIGHT:
            if(mvwinch(map_window, beast.y, beast.x + 1) != (' ' | A_REVERSE))
                beast.x++;
        break;
        case LEFT:
            if(mvwinch(map_window, beast.y, beast.x - 1) != (' ' | A_REVERSE))
                beast.x--;
        break;
        default:
        break;
    }
    
    players[0].next_move = NONE;
    players[1].next_move = NONE;
}

void send_map(struct player_map_data *pdata){
    if(pdata == NULL)
        return;

    pdata->player = players[1];

    for(int y = 0; y < PLAYER_VISIBILITY_Y; y++)
        for(int x = 0; x < PLAYER_VISIBILITY_X; x++)
            pdata->map[y][x] = mvwinch(map_window, players[1].y + (y - 2), players[1].x + (x - 2));

    sem_post(&(pdata->sem));
}

void *game_logic(struct player_map_data *pdata){
    struct player_map_data *data = (struct player_map_data *)pdata;
    data->round_number = 0;
    
    while(1){
        pthread_mutex_lock(&beast_mutex);
        print_map();
        print_players();
        print_beast();
        print_coins();
        print_campsite();
        print_bushes();
        print_info(data);
        move_players();
        is_near_campsite();
        players_collision();
        player_beast_collision();
        refresh_all();
        send_map(data);
        pthread_mutex_unlock(&beast_mutex);
        usleep(600000);
        pdata->round_number++;
    }
    
    return NULL;
}
