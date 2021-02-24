#include "functions.h"

int main(void){
    srand(time(0));

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

    struct sigaction sigusrSignal;
    memset(&sigusrSignal, 0, sizeof(struct sigaction));
    sigusrSignal.sa_flags = SA_SIGINFO;
    sigusrSignal.sa_sigaction = handle_signal;
    assert(!sigaction(SIGUSR1, &sigusrSignal, NULL));
    
    struct sigaction sigIntSignal;
    memset(&sigIntSignal, 0, sizeof(struct sigaction));
    sigIntSignal.sa_flags = SA_SIGINFO;
    sigIntSignal.sa_sigaction = handle_bad_exit;
    assert(!sigaction(SIGINT, &sigIntSignal, NULL));

    sem_init(&(pdata->sem), 1, 0);
    
    pthread_t th1, th2;

    init_ncurses();
    init_players();
    init_beast();
    players[0].type = 1;
    players[0].PID = getpid();
    
    print_map();
    print_players();
    print_beast();
    print_campsite();
    print_bushes();
    init_objects();
    
    pthread_create(&th2, NULL, game_logic, (void *)pdata);
    pthread_create(&th1, NULL, beast_behaviour, NULL);

    char c = 0;
    while(1){
        c = getch();
        if(c != -1){
            switch(c){
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
                    if(c == 27){
                        getch();
                        c = getch();
                    }
                    handleKey(c);
                break;
            }
        }
    }
    end:

    sem_close(&(pdata->sem));
    close(result);
    shm_unlink(SHM_NAME);
    endwin();
    return 0;
}
