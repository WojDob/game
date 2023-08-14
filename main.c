#include <ncurses.h>
#include <stdlib.h>

typedef struct{
	int xPosition;
	int yPosition;
	int health;
} Player;

int screenSetUp();
int mapSetUp(); 

Player * playerSetUp();

int handleInput(int input, Player * player);
int playerMove(int y, int x, Player * player);

int main()
{
	Player * player;
	int ch;
	screenSetUp();
   	mapSetUp(); 

	player = playerSetUp();

	while((ch =getch()) != 'q')
	{
		handleInput(ch, player);	
	}

    	endwin();
    	return 0;
}

int screenSetUp()
{
    	initscr();
    	printw("Hello world!");
    	noecho();
    	refresh();

    	return 1;
}

int mapSetUp()
{
	mvprintw(13, 13, "--------");
	mvprintw(14, 13, "|......|");
	mvprintw(15, 13, "|......|");
	mvprintw(16, 13, "|......|");
	mvprintw(17, 13, "|......|");
	mvprintw(18, 13, "--------");
	
	mvprintw(2, 40, "--------");
	mvprintw(3, 40, "|......|");
	mvprintw(4, 40, "|......|");
	mvprintw(5, 40, "|......|");
	mvprintw(6, 40, "|......|");
	mvprintw(7, 40, "--------");
}


Player * playerSetUp()
{
	Player * newPlayer;
	newPlayer = malloc(sizeof(Player));
	newPlayer->xPosition = 14;
	newPlayer->yPosition = 14;
	newPlayer->health= 20;
	mvprintw(newPlayer->yPosition,newPlayer->xPosition, "@");  
	move(newPlayer->yPosition,newPlayer->xPosition);  
	return newPlayer;
}


int handleInput(int input, Player * player)
{
	switch(input)
	{
		case 'w':
			playerMove(player->yPosition-1,player->xPosition,player);
			break;
		case 's':
			playerMove(player->yPosition+1,player->xPosition,player);
			break;
		case 'a':
			playerMove(player->yPosition,player->xPosition-1,player);
			break;
		case 'd':
			playerMove(player->yPosition,player->xPosition+1,player);
			break;
		default:
			break;
	}
}

int playerMove(int y, int x, Player * player)
{
	mvprintw(player->yPosition,player->xPosition, ".");  
	player->yPosition = y;
	player->xPosition = x;
	mvprintw(player->yPosition,player->xPosition, "@");  
	move(player->yPosition,player->xPosition);  
}

