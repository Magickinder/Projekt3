#include "functions.h"

#define SHM_NAME "Project"

int main(void){
    int pid, result = 0;

    result = shm_open(SHM_NAME, O_RDWR, 0606);
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

    int res = 0;
    printf("Podaj PID: ");
    do{
        res = scanf("%d", &pid);
        if(!res)
            printf("Prosze podac poprawny PID: ");
        while(getchar() != '\n');
    }while(res != 1);

    init_ncurses();
    
    pdata->player.PID = getpid();

    char c;
    while(1){
        refresh_all();
        print_map(pdata);
        print_info(pdata, pid);
        c = getch();
        if(c != -1){
            if(c == 'q' || c == 'Q')
                break;
            if(c == 27){
                getch();
                c = getch();
            }
            sigqueue(pid, SIGUSR1, (union sigval){.sival_int = c});
        }
    }
    //end:

    sem_close(&(pdata->sem));
    close(result);
    shm_unlink(SHM_NAME);
    endwin();
    
    return 0;
}
