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

typedef struct Position
{
	int x;
	int y;
} Position;

typedef struct Room
{
	Position position;
	int height;
	int width;
	//	Monster ** monsters;
	//	Item ** items;
} Room;

typedef struct Player
{
	Position position;
	int health;
} Player;

int screenSetUp();
Room **mapSetUp();

Player *playerSetUp();

int handleInput(int input, Player *player);
int checkPosition(int newY, int newX, Player *player);

int playerMove(int y, int x, Player *player);
Room *createRoom(int y, int x, int height, int width);
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

Room **mapSetUp()
{
	Room **rooms;
	rooms = malloc(sizeof(Room) * 6);

	rooms[0] = createRoom(13, 13, 6, 8);
	drawRoom(rooms[0]);

	rooms[1] = createRoom(40, 2, 6, 8);
	drawRoom(rooms[1]);

	rooms[2] = createRoom(40, 10, 6, 12);
	drawRoom(rooms[2]);
	return rooms;
}

Room *createRoom(int x, int y, int height, int width)
{
	Room *newRoom;
	newRoom = malloc(sizeof(Room));
	newRoom->position.x = x;
	newRoom->position.y = y;
	newRoom->height = height;
	newRoom->width = width;

	return newRoom;
}
int drawRoom(Room *room)
{
	int x;
	int y;
	// draw top and bottom
	for (x = room->position.x; x < room->position.x + room->width; x++)
	{
		mvprintw(room->position.y, x, "-");
		mvprintw(room->position.y + room->height - 1, x, "-");
	}

	// draw floors
	for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++)
	{
		mvprintw(y, room->position.x, "|");
		mvprintw(y, room->position.x + room->width - 1, "|");
		for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
		{
			mvprintw(y, x, ".");
		}
	}
}
Player *playerSetUp()
{
	Player *newPlayer;
	newPlayer = malloc(sizeof(Player));
	newPlayer->position.x = 14;
	newPlayer->position.y = 14;
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
		newY = player->position.y - 1;
		newX = player->position.x;
		break;
	case 'S':
	case 's':
		newY = player->position.y + 1;
		newX = player->position.x;
		break;
	case 'A':
	case 'a':
		newY = player->position.y;
		newX = player->position.x - 1;
		break;
	case 'D':
	case 'd':
		newY = player->position.y;
		newX = player->position.x + 1;
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
		move(player->position.y, player->position.x);
		break;
	}
}

int playerMove(int y, int x, Player *player)
{
	mvprintw(player->position.y, player->position.x, ".");
	player->position.y = y;
	player->position.x = x;
	mvprintw(player->position.y, player->position.x, "@");
	move(player->position.y, player->position.x);
}
