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

WINDOW *map_window;
WINDOW *info_window;

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
    info_window = newwin(INFO_HEIGHT + 2, INFO_WIDTH + 2, 0, MAP_WIDTH + 4); // + 2 because of border
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
        players[i].start_y = 2;
        players[i].number = i + 1;
        players[i].coins_carried = 0;
        players[i].coins_brought = 0;
        players[i].deaths = 0;
    }
}

void print_players(){
    for(int i = 0; i < NUMBER_OF_PLAYERS; i++)
        mvwaddch(map_window, players[i].y, players[i].x, players[i].number + '0');
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
    for(int i = 0; i < 50; i++){
        if(coins[i].status == 1){
            switch(mvwinch(map_window, coins[i].y, coins[i].x)){
                case '1':
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

    for(int i = 0; i < 3; i++){
        if(treasures[i].status == 1){
            switch(mvwinch(map_window, treasures[i].y, treasures[i].x)){
                case '1':
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

    for(int i = 0; i < 2; i++){
        if(l_treasures[i].status == 1){
            switch(mvwinch(map_window, l_treasures[i].y, l_treasures[i].x)){
                case '1':
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

void print_info(){
    int y_offset = 0;

    mvwprintw(info_window, ++y_offset, 1, "Server's PID: %d", getpid());
    mvwprintw(info_window, ++y_offset, 1, " Campsite X/Y: %d/%d", CAMPSITE_X, CAMPSITE_Y);
    mvwprintw(info_window, ++y_offset, 1, " Round number: ");

    y_offset += 3;

    mvwprintw(info_window, ++y_offset, 1, "Parameter:   Player 1    Player 2    Player 3    Player 4");
    mvwprintw(info_window, ++y_offset, 1, " PID         %d           %d           -           -", 1, 1);
    mvwprintw(info_window, ++y_offset, 1, " TYPE        HUMAN       HUMAN       -           -");
    mvwprintw(info_window, ++y_offset, 1, " Curr X/Y    %d/%d         %d/%d         --/--       --/--", players[0].x, players[0].y, players[1].x, players[1].y);
    mvwprintw(info_window, ++y_offset, 1, " Deaths      %d           %d           -           -", 0, 0);

    y_offset += 3;

    mvwprintw(info_window, ++y_offset, 1, "Coins");
    mvwprintw(info_window, ++y_offset, 1, " Carried     %d          %d", players[0].coins_carried, players[1].coins_carried);
    mvwprintw(info_window, ++y_offset, 1, " Brought     %d          %d", players[0].coins_brought, players[1].coins_brought);

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

void handle_signal(int signum, siginfo_t *info, void *ucontext){
    int key = (int)info->si_value.sival_int;

    switch(key){
        case 65: // up
            if(mvwinch(map_window, players[1].y - 1, players[1].x) != (' ' | A_REVERSE))
                players[1].y--;
        break;
        case 66: // down
            if(mvwinch(map_window, players[1].y + 1, players[1].x) != (' ' | A_REVERSE))
                players[1].y++;
        break;
        case 67: // right
            if(mvwinch(map_window, players[1].y, players[1].x + 1) != (' ' | A_REVERSE))
                players[1].x++;
        break;
        case 68: // left
            if(mvwinch(map_window, players[1].y, players[1].x - 1) != (' ' | A_REVERSE))
                players[1].x--;
        break;
    }
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
