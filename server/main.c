#include "functions.h"

#define SHM_NAME "Project"

int main(void){
    srand(time(0));

    //shm_unlink(SHM_NAME);
    int result = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0606);
    if(result == -1){
        printf("Error\n");
        return -1;
    }

    if(ftruncate(result, sizeof(struct player_map_data)) == -1){
        printf("Failed to truncate\n");
        close(result);
        shm_unlink(SHM_NAME);
        return -2;
    }

    struct player_map_data *pdata = mmap(NULL, sizeof(struct player_map_data), PROT_READ | PROT_WRITE, MAP_SHARED, result, 0);
    if(pdata == NULL){
        printf("MMAP ERROR\n");
        close(result);
        shm_unlink(SHM_NAME);
        return -3;
    }

    {
        struct sigaction sigusrSignal;
        sigusrSignal.sa_flags = SA_SIGINFO;
        sigusrSignal.sa_sigaction = handle_signal;
        assert(!sigaction(SIGUSR1, &sigusrSignal, NULL));
    }

    sem_init(&(pdata->sem), 1, 0);

    init_ncurses();
    init_players();
    print_map();
    print_players();
    print_campsite();
    init_objects();

    while(1){
        //Do oddzielnego watku
        print_map();
        print_players();
        print_coins();
        print_campsite();
        print_bushes();
        print_info();
        refresh_all();
        send_map(pdata);

        switch(getch()){
            case 'c':
                generate_coin();
                break;
            break;
            case 't':
                generate_treasure();
                break;
            break;
            case 'T':
                generate_l_treasure();
                break;
            break;
            case 'q':
            case 'Q':
                goto end;
            default:
            break;
        }
    }
    end:

    sem_close(&(pdata->sem));
    close(result);
    shm_unlink(SHM_NAME);
    endwin();
    return 0;
}
