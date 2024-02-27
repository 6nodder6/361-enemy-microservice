#include "enemysharelib.h"

int main(int argc, char const *argv[])
{
    int floorNum = -1, difficultyNum = -1;
    
    cout << "Enter a test floor number: ";
    cin >> floorNum;

    cout << "\nEnter a test difficulty (1, 2, 3): ";
    cin >> difficultyNum;


    struct enemy* new_enemy = generate_enemy(floorNum, difficultyNum);

    _print_enemy(new_enemy);
    return 0;
}
