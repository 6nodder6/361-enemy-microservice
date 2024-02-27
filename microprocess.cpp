#include <iostream>
#include <string>
#include <time.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Linux only
#include <unistd.h>

using namespace std;

#define EASY 1;
#define MEDIUM 2;
#define HARD 3;

struct enemy
{
    int health;
    int attack;
    int rarity;
    string name;

};

void _print_enemy(struct enemy* toprint){
    // cout << "Name: " << toprint->name;
    cout << "\nHealth: " << toprint->health;
    cout << "\nAttack: " << toprint->attack;
    cout << "\nRarity: " << toprint->rarity << "\n";
}


int main(int argc, char const *argv[])
{
    srand(time(NULL));
    key_t key_send_floor = ftok("accesskey.txt", 45);
    key_t key_send_difficulty = ftok("accesskey.txt", 50);
    key_t key_switch = ftok("accesskey.txt", 55);
    key_t key_getenemy = ftok("accesskey.txt", 65);

    size_t key_floorsize = sizeof(int);
    size_t key_diffsize = sizeof(int);
    size_t key_switchsize = (sizeof(bool)); 
    size_t key_enemysize = (sizeof(enemy));

    int floor_id = shmget(key_send_floor, key_floorsize, 0666 | IPC_CREAT);
    int diff_id = shmget(key_send_difficulty,key_diffsize, 0666 | IPC_CREAT);
    int switch_id = shmget(key_switch, key_switchsize, 0666 | IPC_CREAT);
    int enemy_id = shmget(key_getenemy, key_enemysize, 0666 | IPC_CREAT);

    int* floor_pipe = (int*)shmat(floor_id, NULL, 0);
    int* diff_pipe = (int*)shmat(diff_id, NULL, 0);
    int* switch_pipe = (int*)shmat(switch_id, NULL, 0);   
    struct enemy* enemy_pipe = (enemy*)shmat(enemy_id, NULL, 0);

    *switch_pipe = false;

    // Loop forever until killed
    while(1){
        // cout << "Waiting for signal\n";
        // cout << "Switch_pipe = " << *switch_pipe << "\n";
        while(*switch_pipe == false){
            sleep(0.5);
        }
        // cout << "Signal received\n";

        int floor = *floor_pipe;
        int difficulty = *diff_pipe;

        // Initializations
        int hp_max = 999;
        int hp_min = -1;

        int atk_max = 999;
        int atk_min = -1;

        switch (difficulty) {
            case 1:
                hp_min = 10 + floor;
                hp_max = 30 + floor - hp_min;

                atk_min = 1 + (5 * ((int)floor / 5));
                atk_max = 5 + (5 * ((int)floor / 5)) - atk_min;
                break;
            case 2:
                hp_min = 10 + (floor * 2);
                hp_max = 50 + (floor * 2) - hp_min;

                atk_min = 1 + (5 * ((int)floor / 3));
                atk_max = 5 + (5 * ((int)floor / 3)) - atk_min;
                break;
            case 3:
                hp_min = 10 + (floor * 3);
                hp_max = 100 + (floor * 3) - hp_min;

                atk_min = 1 + (5 * floor);
                atk_max = 5 + (5 * floor) - atk_min;
                break;
            default:
                cout << "error: Got " << difficulty << "\n";
                return -1;
                break;
        }
        // cout << "\n\nhp_max: " << hp_max
        //     << "\nhp_min: " << hp_min
        //     << "\natk_max: " << atk_max
        //     << "\natk_min: " << atk_min 
        //     << "\n\n";
        

        enemy_pipe->health = (rand() % hp_max) + hp_min;
        enemy_pipe->attack = (rand() % atk_max) + atk_min;
        float temp_rarity = (float)((float)(enemy_pipe->health + enemy_pipe->attack)/(float)(hp_max + atk_max + hp_min + atk_min)) * 100;
        enemy_pipe->rarity = temp_rarity;
        // enemy_pipe->name = "Generic Enemy";

        if(enemy_pipe->rarity > 100){
            cout << "\n\nERROR, RARITY = " << enemy_pipe->rarity << "\n";
            return -1;
        }
        // _print_enemy(enemy_pipe);
        // Reset everything
        *floor_pipe = -1;
        *diff_pipe = -1;
        *switch_pipe = false;
    }

    
    
    return 0;
}
