#include <ncurses.h>
#include <stdlib.h>

typedef struct
{
	int xPosition;
	int yPosition;
	int health;
} Player;

int screenSetUp();
int mapSetUp();

Player *playerSetUp();

int handleInput(int input, Player *player);
int checkPosition(int newY, int newX, Player *player);

int playerMove(int y, int x, Player *player);

int main()
{
	Player *player;
	int ch;
	screenSetUp();
	mapSetUp();

	player = playerSetUp();

	while ((ch = getch()) != 'q')
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

Player *playerSetUp()
{
	Player *newPlayer;
	newPlayer = malloc(sizeof(Player));
	newPlayer->xPosition = 14;
	newPlayer->yPosition = 14;
	newPlayer->health = 20;
	playerMove(14, 14, newPlayer);

	return newPlayer;
}

int handleInput(int input, Player *player)
{
	int newY;
	int newX;
	switch (input)
	{
	case 'W':
	case 'w':
		newY = player->yPosition - 1;
		newX = player->xPosition;
		break;
	case 'S':
	case 's':
		newY = player->yPosition + 1;
		newX = player->xPosition;
		break;
	case 'A':
	case 'a':
		newY = player->yPosition;
		newX = player->xPosition - 1;
		break;
	case 'D':
	case 'd':
		newY = player->yPosition;
		newX = player->xPosition + 1;
		break;
	default:
		break;
	}
	checkPosition(newY, newX, player);
}

int checkPosition(int newY, int newX, Player *player)
{
	int space;
	switch (mvinch(newY, newX))
	{
	case '.':
		playerMove(newY, newX, player);
		break;
	default:
		move(player->yPosition, player->xPosition);
		break;
	}
}

int playerMove(int y, int x, Player *player)
{
	mvprintw(player->yPosition, player->xPosition, ".");
	player->yPosition = y;
	player->xPosition = x;
	mvprintw(player->yPosition, player->xPosition, "@");
	move(player->yPosition, player->xPosition);
}
