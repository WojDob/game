#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define WIDTH 20
#define HEIGHT 10

typedef struct{
    int x, y;
    int hp;
}Player;
int getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
char map[HEIGHT][WIDTH] = {
    "####################",
    "#@.................#",
    "#..................#",
    "#.......~..........#",
    "#..................#",
    "#...........#......#",
    "#..................#",
    "#....<......#......#",
    "#..................#",
    "####################"};

void render_map(char map[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            putchar(map[i][j]);
        }
        putchar('\n');
    }
}
void move_player(Player *player,char direction)
{
    switch (direction)
    {
    case 'w':
        if (map[player->y - 1][player->x] == '.')
        {
            map[player->y][player->x] = '.';
            player->y--;
            map[player->y][player->x] = '@';
        }
        break;
    case 's':
        if (map[player->y + 1][player->x] == '.')
        {
            map[player->y][player->x] = '.';
            player->y++;
            map[player->y][player->x] = '@';
        }
        break;
    case 'a':
    if (map[player->y][player->x-1] == '.')
    {
        map[player->y][player->x] = '.';
        player->x--;
        map[player->y][player->x] = '@';
    }
    break;
    case 'd':
        if (map[player->y][player->x + 1] == '.')
        {
            map[player->y][player->x] = '.';
            player->x++;
            map[player->y][player->x] = '@';
        }
        break;
    }
}

Player* new_player() {
    Player* player = (Player*)malloc(sizeof(Player));
    player->x = 1;
    player->y = 1;
    player->hp = 100;
    return player;
}

int main()
{
    Player* player = new_player();

    char input;
    while (1)
    {
        system("clear");

        render_map(map);
        printf("Player: [%d, %d]\n", player->x,player->y);

        input = getch();
        move_player(player, input);
    }

    return 0;
}
