//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//               佛祖保佑         永無BUG
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <ncurses.h>
#include <stdlib.h>

typedef struct Room
{
	int xPosition;
	int yPosition;
	int height;
	int width;
//	Monster ** monsters;
//	Item ** items;
} Room;

typedef struct Player
{
	int xPosition;
	int yPosition;
	int health;
} Player;

int screenSetUp();
Room ** mapSetUp();

Player *playerSetUp();

int handleInput(int input, Player *player);
int checkPosition(int newY, int newX, Player *player);

int playerMove(int y, int x, Player *player);
Room * createRoom(int y, int x, int height, int width);
int drawRoom(Room *room);

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

Room ** mapSetUp()
{
	Room ** rooms;
	rooms = malloc(sizeof(Room) *6);
	
	rooms[0] = createRoom(13,13,6,8);
	drawRoom(rooms[0]);
	
	rooms[1] = createRoom(40,2,6,8);
	drawRoom(rooms[1]);
	
	rooms[2] = createRoom(40,10,6,12);
	drawRoom(rooms[2]);
	return rooms;
}

Room * createRoom(int x, int y, int height, int width)
{
	Room * newRoom;
	newRoom = malloc(sizeof(Room));
	newRoom->xPosition = x;
	newRoom->yPosition = y;
	newRoom->height = height;
	newRoom->width =width;

	return newRoom;
}
int drawRoom(Room *room)
{
	int x;
	int y;
	// draw top and bottom
	for(x = room->xPosition; x < room->xPosition + room->width; x++)
	{
		mvprintw(room->yPosition, x, "-");
		mvprintw(room->yPosition + room->height - 1, x, "-"); 
	}


	// draw floors
	for (y = room->yPosition + 1; y < room->yPosition + room->height -1; y++)
	{
		mvprintw(y, room->xPosition, "|"); 
		mvprintw(y, room->xPosition + room->width - 1, "|"); 
		for (x = room->xPosition + 1; x < room->xPosition + room->width - 1; x++)
		{
			mvprintw(y,x,".");
		}

	}
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
