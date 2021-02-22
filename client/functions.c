#include "functions.h"

WINDOW *map_window;
WINDOW *info_window;

void init_ncurses(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    timeout(200);
    map_window = newwin(MAP_HEIGHT + 2, MAP_WIDTH + 2, 0, 0);
    info_window = newwin(INFO_HEIGHT + 2, INFO_WIDTH + 2, 0, MAP_WIDTH + 4);
    box(info_window, 0, 0);
}

void refresh_all(){
    refresh(); // refresh display
    wrefresh(map_window);
    wrefresh(info_window);
}

void print_map(struct player_map_data *pdata){
    if(pdata == NULL)
        return;

    sem_wait(&(pdata->sem));

    werase(map_window);
    box(map_window, 0, 0);
    for(int y = 0; y < PLAYER_VISIBILITY_Y; y++)
        for(int x = 0; x < PLAYER_VISIBILITY_X; x++)
            mvwaddch(map_window, pdata->player.y + (y - 2), pdata->player.x + (x - 2), pdata->map[y][x]);
}

void print_info(struct player_map_data *pdata, int servers_pid){
    int y_offset = 0;
    
    mvwprintw(info_window, ++y_offset, 1, "Server's PID: %d", servers_pid);
    mvwprintw(info_window, ++y_offset, 1, " Campsite X/Y: unknown");
    mvwprintw(info_window, ++y_offset, 1, " Round number: ");

    y_offset += 3;

    mvwprintw(info_window, ++y_offset, 1, "Player:");
    mvwprintw(info_window, ++y_offset, 1, " Number:  %d", pdata->player.number);
    mvwprintw(info_window, ++y_offset, 1, " TYPE        HUMAN");
    mvwprintw(info_window, ++y_offset, 1, " Curr X/Y    %d/%d", pdata->player.x, pdata->player.y);
    mvwprintw(info_window, ++y_offset, 1, " Deaths      %d", pdata->player.deaths);

    y_offset += 3;

    mvwprintw(info_window, ++y_offset, 1, "Coins found %d", pdata->player.coins_carried);
    mvwprintw(info_window, ++y_offset, 1, "Coins brought %d", pdata->player.coins_brought);

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
