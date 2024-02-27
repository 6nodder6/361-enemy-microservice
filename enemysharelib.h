#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>

// Linux only
#include <unistd.h>

using namespace std;

struct enemy
{
    int health;
    int attack;
    int rarity;
    string name;
};

void _print_enemy(struct enemy* toprint);


struct enemy* generate_enemy(int floor, int difficulty);