#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define allitems 4
#define alldefenseitems 2

struct magic
{
	char* equiped;
	int damage;
	int randommagic;
	int rangey;
	int rangex;
	int cost;
};

struct character
{
	char* character;
	char* sign;
	int hitpoints;
	int attack;
	int defense;
	int randomcharacter;
	int magicresist;
};

struct shieldsdamage
{
	char *item;
	int damage[alldefenseitems];
};

struct shields
{
	char* equiped;
	char* item[alldefenseitems];
	int damage;
	int numberitems;
};

struct weaponsdamage
{
	char* item;
	int damage[allitems];
	int rangey[allitems];
	int rangex[allitems];
};

struct weapons
{
	char* equiped;
	char* item[allitems];
	int damage;
	int rangey;
	int rangex;
	int numberitems;
};

struct hitpointspos
{
	int y;
	int x;
	int ay;
	int ax;
};

struct player
{
	int y;
	int x;
	int hitpoints;
	int magicpoints;
	int defensepoints;
	char* weapon;
	char* shield;
	char* charactersign;
	int prevy;
	int prevx;
	int magicattack;
	int count;
	int replayer;
	int playerturn;
	struct weapons weapontype;
	struct weaponsdamage weaponsdamage1;
	int randomitem;
	struct shields shieldstype;
	struct shieldsdamage shieldsdamage1;
	int shieldsrandomitem;
	struct character character1;
	struct magic magic1;
};

struct aicharacter
{
	int y;
	int x;
	int hitpoints;
	int magicpoints;
	int defensepoints;
	char* weapon;
	char* shield;
	char* charactersign;
	int prevy;
	int prevx;
	int magicattack;
	int count;
	int replayer;
	int playerturn;
	struct weapons weapontype;
	struct weaponsdamage weaponsdamage1;
	int randomitem;
	struct shields shieldstype;
	struct shieldsdamage shieldsdamage1;
	int shieldsrandomitem;
	struct character character1;
	struct magic magic1;
};

int main(int argc, char *argv[])
{
	#define maxenemies 5
	#define maxplayers 3
	#define allitemsenemies 4
	#define alldefenseitemsenemies 2
	#define playercharacters 4
	#define aicharacters 4
	#define playermagiclist 5
	#define aimagiclist 5

	srand(time(NULL));

	struct player myplayer[maxplayers];
	struct aicharacter myai[maxenemies];

	char* item[allitems];
	item[0] = "Knife";
	item[1] = "Gun";
	item[2] = "Pistol";
	item[3] = "Shotgun";

	char* itemdamage[alldefenseitems];
	itemdamage[0] = "Short_Shield";
	itemdamage[1] = "Long_Shield";

	char* itemenemies[allitemsenemies];
	itemenemies[0] = "Knife";
	itemenemies[1] = "Gun";
	itemenemies[2] = "Pistol";
	itemenemies[3] = "Shotgun";

	char* itemdamageenemies[alldefenseitemsenemies];
	itemdamageenemies[0] = "Short_Shield";
	itemdamageenemies[1] = "Long_Shield";

	int damage[allitems] = { 40, 60, 50, 80 };
	int rangey[allitems] = { 1, 2, 3, 4 };
	int rangex[allitems] = { 1, 2, 3, 4 };

	int damageenemies[allitemsenemies] = { 40, 60, 50, 80 };
	int rangeyenemies[allitemsenemies] = { 1, 2, 3, 4 };
	int rangexenemies[allitemsenemies] = { 1, 2, 3, 4 };

	int shielddamage[alldefenseitems] = { 2, 4 };

	int shielddamageenemies[alldefenseitemsenemies] = { 2, 4 };

	char* playercharacter1[playercharacters];
	playercharacter1[0] = "Human";
	playercharacter1[1] = "Orc";
	playercharacter1[2] = "Elf";
	playercharacter1[3] = "Dwarf";

	char* aicharacter1[aicharacters];
	aicharacter1[0] = "Human";
	aicharacter1[1] = "Orc";
	aicharacter1[2] = "Elf";
	aicharacter1[3] = "Dwarf";

	char* playersigns[playercharacters];
	playersigns[0] = "H";
	playersigns[1] = "O";
	playersigns[2] = "E";
	playersigns[3] = "D";

	char* aisigns[aicharacters];
	aisigns[0] = "h";
	aisigns[1] = "o";
	aisigns[2] = "e";
	aisigns[3] = "d";

	int playerhitpoints[playercharacters];
	playerhitpoints[0] = 1500;
	playerhitpoints[1] = 2000;
	playerhitpoints[2] = 1000;
	playerhitpoints[3] = 800;

	int aihitpoints[aicharacters];
	aihitpoints[0] = 1500;
	aihitpoints[1] = 2000;
	aihitpoints[2] = 1000;
	aihitpoints[3] = 800;

	int playerdefense[playercharacters];
	playerdefense[0] = 10;
	playerdefense[1] = 30;
	playerdefense[2] = 3;
	playerdefense[3] = 20;

	int aidefense[aicharacters];
	aidefense[0] = 10;
	aidefense[1] = 30;
	aidefense[2] = 3;
	aidefense[3] = 20;

	int playerattack[playercharacters];
	playerattack[0] = 10;
	playerattack[1] = 20;
	playerattack[2] = 8;
	playerattack[3] = 15;

	int aiattack[aicharacters];
	aiattack[0] = 10;
	aiattack[1] = 20;
	aiattack[2] = 8;
	aiattack[3] = 15;


	char* playermagicitems[playermagiclist];
	playermagicitems[0] = "Fire";
	playermagicitems[1] = "Wind";
	playermagicitems[2] = "Ice";
	playermagicitems[3] = "Water";
	playermagicitems[4] = "Lightning";

	char* aimagicitems[aimagiclist];
	aimagicitems[0] = "Fire";
	aimagicitems[1] = "Wind";
	aimagicitems[2] = "Ice";
	aimagicitems[3] = "Water";
	aimagicitems[4] = "Lightning";

	int playermagicdamage[playermagiclist];
	playermagicdamage[0] = 80;
	playermagicdamage[1] = 80;
	playermagicdamage[2] = 80;
	playermagicdamage[3] = 80;
	playermagicdamage[4] = 80;

	int aimagicdamage[aimagiclist];
	aimagicdamage[0] = 40;
	aimagicdamage[1] = 40;
	aimagicdamage[2] = 40;
	aimagicdamage[3] = 40;
	aimagicdamage[4] = 40;

	int playermagicdistance[playermagiclist];
	playermagicdistance[0] = 8;
	playermagicdistance[1] = 8;
	playermagicdistance[2] = 8;
	playermagicdistance[3] = 8;
	playermagicdistance[4] = 8;

	int aimagicdistance[aimagiclist];
	aimagicdistance[0] = 8;
	aimagicdistance[1] = 8;
	aimagicdistance[2] = 8;
	aimagicdistance[3] = 8;
	aimagicdistance[4] = 8;

	int playermagicresist[playercharacters];
	playermagicresist[0] = 20;
	playermagicresist[1] = 5;
	playermagicresist[2] = 40;
	playermagicresist[3] = 10;

	int aimagicresist[aicharacters];
	aimagicresist[0] = 20;
	aimagicresist[1] = 5;
	aimagicresist[2] = 40;
	aimagicresist[3] = 10;

	int playermagicpoints[playercharacters];
	playermagicpoints[0] = 400;
	playermagicpoints[1] = 200;
	playermagicpoints[2] = 500;
	playermagicpoints[3] = 100;

	int aimagicpoints[aicharacters];
	aimagicpoints[0] = 400;
	aimagicpoints[1] = 200;
	aimagicpoints[2] = 500;
	aimagicpoints[3] = 100;

	int playermagiccost[playermagiclist];
	playermagiccost[0] = 40;
	playermagiccost[1] = 40;
	playermagiccost[2] = 40;
	playermagiccost[3] = 40;
	playermagiccost[4] = 40;

	int aimagiccost[aimagiclist];
	aimagiccost[0] = 40;
	aimagiccost[1] = 40;
	aimagiccost[2] = 40;
	aimagiccost[3] = 40;
	aimagiccost[4] = 40;
	
	for(int i = 0; i < maxplayers; i++)
	{
		myplayer[i].randomitem = rand() % allitems;
	}
	
	for(int i = 0; i < maxenemies; i++)
	{
		myai[i].randomitem = rand() % allitems;
	}

	for(int i = 0; i < maxplayers; i++)
	{
		myplayer[i].shieldsrandomitem = rand() % alldefenseitems;
	}

	for(int i = 0; i < maxenemies; i++)
	{
		myai[i].shieldsrandomitem = rand() % alldefenseitems;
	}

	for(int i = 0; i < maxplayers; i++)
	{
		myplayer[i].character1.randomcharacter = rand() % playercharacters;
	}

	for(int i = 0; i < maxenemies; i++)
	{
		myai[i].character1.randomcharacter = rand() % aicharacters;
	}

	for(int i = 0; i < maxplayers; i++)
	{
		myplayer[i].magic1.randommagic = rand() % playermagiclist;
	}

	for(int i = 0; i < maxenemies; i++)
	{
		myai[i].magic1.randommagic = rand() % aimagiclist;
	}

	for(int i = 0; i < maxplayers; i++)
	{
		myplayer[i].y = 10;
		myplayer[i].x = 12;
		myplayer[i].hitpoints = 1000;
		myplayer[i].magicpoints = 1000;
		myplayer[i].defensepoints = 20;
		myplayer[i].weapon = "Knife";
		myplayer[i].shield = "LargeShield";
		myplayer[i].charactersign = "@";
		myplayer[i].prevy = 10;
		myplayer[i].prevx = 12;
		myplayer[i].magicattack = 100;
		myplayer[i].count = i+1;
		myplayer[i].replayer =  0;
		myplayer[i].playerturn = 0;
		myplayer[i].weapontype.equiped = "NULL";

		myplayer[i].character1.character = playercharacter1[myplayer[i].character1.randomcharacter];
		myplayer[i].character1.sign = playersigns[myplayer[i].character1.randomcharacter];
		myplayer[i].character1.hitpoints = playerhitpoints[myplayer[i].character1.randomcharacter];
		myplayer[i].character1.defense = playerdefense[myplayer[i].character1.randomcharacter];
		myplayer[i].character1.attack = playerattack[myplayer[i].character1.randomcharacter];

		myplayer[i].weaponsdamage1.item = item[myplayer[i].randomitem];

		myplayer[i].charactersign = myplayer[i].character1.sign;
		myplayer[i].defensepoints = myplayer[i].character1.defense;
		myplayer[i].hitpoints = myplayer[i].character1.hitpoints;

		for(int j = 0; j < allitems; j++)
		{
			myplayer[i].weapontype.item[j] = item[j];
		}

		myplayer[i].weapontype.damage = damage[myplayer[i].randomitem];
		myplayer[i].weapontype.rangey = rangey[myplayer[i].randomitem];
		myplayer[i].weapontype.rangex = rangex[myplayer[i].randomitem];
		myplayer[i].weapontype.numberitems = allitems;

		for(int j = 0; j < allitems; j++)
		{
			myplayer[i].weaponsdamage1.damage[j] = damage[j];
			myplayer[i].weaponsdamage1.rangey[j] = rangey[j];
			myplayer[i].weaponsdamage1.rangex[j] = rangex[j];
		}

		for(int j = 0; j < alldefenseitems; j++)
		{
			myplayer[i].shieldstype.item[j] = itemdamage[j];
		}

		myplayer[i].shieldstype.equiped = itemdamage[myplayer[i].shieldsrandomitem];

		myplayer[i].shieldstype.damage = shielddamage[myplayer[i].shieldsrandomitem];
		myplayer[i].shieldstype.numberitems = alldefenseitems;

		myplayer[i].shieldsdamage1.item = itemdamage[myplayer[i].shieldsrandomitem];

		for(int j = 0; j < alldefenseitems; j++)
		{
			myplayer[i].shieldsdamage1.damage[j] = shielddamage[j];
		}

		myplayer[i].magic1.equiped = playermagicitems[myplayer[i].magic1.randommagic];
		myplayer[i].magic1.rangey = playermagicdistance[myplayer[i].magic1.randommagic];
		myplayer[i].magic1.rangex = playermagicdistance[myplayer[i].magic1.randommagic];
		myplayer[i].magic1.damage = playermagicdamage[myplayer[i].magic1.randommagic];

		myplayer[i].magicattack = myplayer[i].magic1.damage;

		myplayer[i].character1.magicresist = playermagicresist[myplayer[i].character1.randomcharacter];

		myplayer[i].magicpoints = playermagicpoints[myplayer[i].character1.randomcharacter];

		myplayer[i].magic1.cost = playermagiccost[myplayer[i].magic1.randommagic];
	}

	for(int i = 0; i < maxplayers; i++)
	{
		for(int j = 1; j < maxplayers; j++)
		{
			if(i != j && myplayer[i].y == myplayer[j].y && myplayer[i].x == myplayer[j].x)
			{
				myplayer[j].y = rand() % (24 - (maxplayers + maxenemies));
				myplayer[j].x = rand() % 80;

				myplayer[j].prevy = myplayer[j].y;
				myplayer[j].prevx = myplayer[j].x;
				
				i = -1;
				j = j - 1;

				break;
			}
		}
	}

	for(int i = 0; i < maxenemies; i++)
	{
		myai[i].y = 10;
		myai[i].x = 70;
		myai[i].hitpoints = 500;
		myai[i].magicpoints = 500;
		myai[i].defensepoints = 20;
		myai[i].weapon = "Gun";
		myai[i].shield = "SmallShield";
		myai[i].charactersign = "a";
		myai[i].prevy = 10;
		myai[i].prevx = 70;
		myai[i].magicattack = 40;
		myai[i].count = i+1;
		myai[i].replayer =  0;
		myai[i].playerturn = 0;
		myai[i].weapontype.equiped = "NULL";

		myai[i].character1.character = aicharacter1[myai[i].character1.randomcharacter];
		myai[i].character1.sign = aisigns[myai[i].character1.randomcharacter];
		myai[i].character1.hitpoints = aihitpoints[myai[i].character1.randomcharacter];
		myai[i].character1.defense = aidefense[myai[i].character1.randomcharacter];
		myai[i].character1.attack = aiattack[myai[i].character1.randomcharacter];

		myai[i].weaponsdamage1.item = itemenemies[myai[i].randomitem];

		myai[i].charactersign = myai[i].character1.sign;
		myai[i].defensepoints = myai[i].character1.defense;
		myai[i].hitpoints = myai[i].character1.hitpoints;

		for(int j = 0; j < allitemsenemies; j++)
		{
			myai[i].weapontype.item[j] = itemenemies[j];
		}

		myai[i].weapontype.damage = damageenemies[myai[i].randomitem];
		myai[i].weapontype.rangey = rangeyenemies[myai[i].randomitem];
		myai[i].weapontype.rangex = rangexenemies[myai[i].randomitem];
		myai[i].weapontype.numberitems = allitemsenemies;

		for(int j = 0; j < allitemsenemies; j++)
		{
			myai[i].weaponsdamage1.damage[j] = damageenemies[j];
			myai[i].weaponsdamage1.rangey[j] = rangeyenemies[j];
			myai[i].weaponsdamage1.rangex[j] = rangexenemies[j];
		}

		for(int j = 0; j < alldefenseitemsenemies; j++)
		{
			myai[i].shieldstype.item[j] = itemdamageenemies[j];
		}

		myai[i].shieldstype.equiped = itemdamageenemies[myai[i].shieldsrandomitem];

		myai[i].shieldstype.damage = shielddamageenemies[myai[i].shieldsrandomitem];
		myai[i].shieldstype.numberitems = alldefenseitemsenemies;

		myai[i].shieldsdamage1.item = itemdamageenemies[myai[i].shieldsrandomitem];

		for(int j = 0; j < alldefenseitemsenemies; j++)
		{
			myai[i].shieldsdamage1.damage[j] = shielddamageenemies[j];
		}

		myai[i].magic1.equiped = aimagicitems[myai[i].magic1.randommagic];
		myai[i].magic1.rangey = aimagicdistance[myai[i].magic1.randommagic];
		myai[i].magic1.rangex = aimagicdistance[myai[i].magic1.randommagic];
		myai[i].magic1.damage = aimagicdamage[myai[i].magic1.randommagic];

		myai[i].magicattack = myai[i].magic1.damage;

		myai[i].character1.magicresist = aimagicresist[myai[i].character1.randomcharacter];

		myai[i].magicpoints = aimagicpoints[myai[i].character1.randomcharacter];

		myai[i].magic1.cost = aimagiccost[myai[i].magic1.randommagic];
	}
	
	for(int i = 0; i < maxenemies; i++)
	{
		for(int j = 1; j < maxenemies; j++)
		{
			if(i != j && myai[i].y == myai[j].y && myai[i].x == myai[j].x)
			{
				myai[j].y = rand() % (24 - (maxplayers + maxenemies));
				myai[j].x = rand() % 80;
				
				myai[j].prevy = myai[j].y;
				myai[j].prevx = myai[j].x;
				
				i = -1;
				j = j - 1;

				break;
			}
		}

		for(int j = 0; j < maxplayers; j++)
		{
			if(myai[i].y == myplayer[j].y && myai[i].x == myplayer[j].x)
			{
				myai[i].y = rand() % (24 - (maxplayers + maxenemies));
				myai[i].x = rand() % 80;

				myai[i].prevy = myai[i].y;
				myai[i].prevx = myai[i].x;
				
				i = -1;
				j = -1;

				break;
			}
		}
	}

	for(int i = 0; i < maxplayers; i++)
	{
		myplayer[i].weapontype.numberitems = allitems;
	}

	for(int i = 0; i < maxplayers; i++)
	{
		myplayer[i].weapontype.equiped = myplayer[i].weapontype.item[myplayer[i].randomitem];
	}

	for(int i = 0; i < maxenemies; i++)
	{
		myai[i].weapontype.equiped = myai[i].weapontype.item[myai[i].randomitem];
	}
	
	for(int i = 0; i < maxplayers; i++)
	{
		if(myplayer[i].y >= (24 - (maxplayers + maxenemies)))
		{
			printf("The player initialization code isn't correct.\n");

			return 1;
		}
	}

	for(int i = 0; i < maxenemies; i++)
	{
		if(myai[i].y >= (24 - (maxplayers + maxenemies)))
		{
			printf("The ai initialization code isn't correct.\n");

			return 1;
		}
	}
	
	int ch;
	
	char* winner = "ai";
	
	int replayer = 0;
	
	int positionxdiff;
	
	int positionydiff;
	
	struct hitpointspos hitpointspos1 = { 24 - (maxplayers + maxenemies), 0, 24 - (maxenemies), 0 };
	
	initscr();
	
	noecho();
	
	cbreak();
	
	for(int i = 0; i < maxplayers; i++)
	{
		mvprintw(myplayer[i].y, myplayer[i].x, myplayer[i].charactersign);
	}
	
	for(int i = 0; i < maxenemies; i++)
	{
		mvprintw(myai[i].y, myai[i].x, myai[i].charactersign);
	}
	
	for(int i = 0; i < maxplayers; i++)
	{
	   mvprintw(hitpointspos1.y + i, hitpointspos1.x, "Player %d is %s hitpoints: %d mp: %d attack: %d magic: %s %d defense: %d weapon: %s shield: %s", myplayer[i].count, myplayer[i].character1.character, myplayer[i].hitpoints, myplayer[i].magicpoints, myplayer[i].weapontype.damage + myplayer[i].character1.attack, myplayer[i].magic1.equiped, myplayer[i].magic1.damage, myplayer[i].defensepoints + myplayer[i].shieldstype.damage, myplayer[i].weapontype.equiped, myplayer[i].shieldstype.equiped);
	}
	
	for(int i = 0; i < maxenemies; i++)
	{
	   mvprintw(hitpointspos1.ay + i, hitpointspos1.ax, "AI %d is %s hitpoints: %d mp: %d attack: %d magic: %s %d defense: %d weapon: %s shield: %s", myai[i].count, myai[i].character1.character, myai[i].hitpoints, myai[i].magicpoints, myai[i].weapontype.damage + myai[i].character1.attack, myai[i].magic1.equiped, myai[i].magic1.damage, myai[i].defensepoints + myai[i].shieldstype.damage, myai[i].weapontype.equiped, myai[i].shieldstype.equiped);
	}
	
	move(myplayer[0].y, myplayer[0].x);

	refresh();
	
	int i = 0;
	
	while((ch = getch()) != 'q')
	{	
		if(ch == 'h')
		{
			clear();

			mvprintw(0, 0, "Press a to move left");
			mvprintw(1, 0, "Press d to move right");
			mvprintw(2, 0, "Press w to move up");
			mvprintw(3, 0, "Press s to move down");
			mvprintw(4, 0, "Press m to use magic");
			mvprintw(5, 0, "Press n to cycle through player characters forward");
			mvprintw(6, 0, "Press p to cycle through player characters backward");
			mvprintw(7, 0, "Press h to display this during game to see this screen");
			mvprintw(8, 0, "The H is a player human and the h is a ai human");
			mvprintw(9, 0, "The O is a player orc and the o is a ai orc");
			mvprintw(10, 0, "The E is a player elf and the e is a ai elf");
			mvprintw(11, 0, "The D is a player dwarf and the d is a ai elf");
			mvprintw(12, 0, "Press key to quit help");

			refresh();

			getch();

			move(myplayer[i].y, myplayer[i].x);

			refresh();
		}
		
		clear();

		if(ch == 'p')
		{
			i--;

			if(i < 0)
			{
				i = maxplayers - 1;
			}

			for(int j = 0; j < maxplayers; j++)
			{	
				for(int j = 0; j < maxplayers; j++)
				{
					myplayer[j].playerturn--;
				}
			
				if(i < 0)
				{
					i = maxplayers - 1;
				}
			
				if(myplayer[0].playerturn < 0)
				{
					for(int i = 0; i < maxplayers; i++)
					{
						myplayer[i].playerturn = maxplayers - 1;
					}
				}

				if(myplayer[i].hitpoints > 0)
				{
					break;
				}
				
				if(myplayer[i].hitpoints <= 0)
				{
					i--;
					
					if(i < 0)
					{
						i = maxplayers - 1;
					}
				}
			}
		}
		
		if(ch == 'n')
		{
			i++;
			
			if(i >= maxplayers)
			{
				i = 0;
			}
			
			for(int j = 0; j < maxplayers; j++)
			{	
				for(int j = 0; j < maxplayers; j++)
				{
					myplayer[j].playerturn++;
				}
			
				if(i == maxplayers)
				{
					i = 0;
				}
			
				if(myplayer[0].playerturn == maxplayers)
				{
					for(int i = 0; i < maxplayers; i++)
					{
						myplayer[i].playerturn = 0;
					}
				}

				if(myplayer[i].hitpoints > 0)
				{
					break;
				}
				
				if(myplayer[i].hitpoints <= 0)
				{
					i++;
					
					if(i >= maxplayers)
					{
						i = 0;
					}
				}
			}
		}
		
		if(ch == 'a')
		{
			myplayer[i].x = myplayer[i].x - 1;
			
			if(myplayer[i].x < 0)
			{
				myplayer[i].x = 0;
			}
		}
		
		if(ch == 'd')
		{
			myplayer[i].x = myplayer[i].x + 1;
			
			if(myplayer[i].x > 79)
			{
				myplayer[i].x = 79;
			}
		}
		
		if(ch == 'w')
		{
			myplayer[i].y = myplayer[i].y - 1;
			
			if(myplayer[i].y < 0)
			{
				myplayer[i].y = 0;
			}
		}
		
		if(ch == 's')
		{
			myplayer[i].y = myplayer[i].y + 1;
			
			if(myplayer[i].y > (hitpointspos1.y - 1))
			{
				myplayer[i].y = (hitpointspos1.y - 1);
			}
		}
		
		for(int p = 0; p < maxenemies; p++)
		{
			for(int j = 0; j < maxplayers; j++)
			{
				if((myai[p].magicpoints >= myai[p].magic1.cost) && (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myai[p].magic1.rangey && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myai[p].magic1.rangex && ch == 'm' && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0)
				{
					myplayer[j].hitpoints = myplayer[j].hitpoints - myai[p].magicattack + myplayer[j].character1.magicresist;

					myai[p].magicpoints = myai[p].magicpoints - myai[p].magic1.cost;

					for(int k = 0; k < maxplayers; k++)
					{
						if(myplayer[k].hitpoints > 0)
						{
							break;
						}

						if(k == maxplayers - 1)
						{
							winner = "ai";

							goto ended;
						}
					}
				}
			}
		}

		for(int p = 0; p < maxenemies; p++)
		{ 
			for(int j = 0; j < maxplayers; j++)
			{
				if((myplayer[j].magicpoints >= myplayer[j].magic1.cost) && (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myplayer[j].magic1.rangey  && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myplayer[j].magic1.rangex && ch == 'm' && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0)
				{
					if(j == i)
					{
						myai[p].hitpoints = myai[p].hitpoints - myplayer[j].magicattack + myai[p].character1.magicresist;
						
						myplayer[j].magicpoints = myplayer[j].magicpoints - myplayer[j].magic1.cost;
					}
					
					for(int k = 0; k < maxenemies; k++)
					{
						if(myai[k].hitpoints > 0)
						{
							break;
						}
						
						if(k == maxenemies - 1)
						{
							winner = "player";
						
							goto ended;
						}
					}
					
				}
			}
		}
		
		for(int p = 0; p < maxenemies; p++)
		{
			for(int j = 0; j < maxplayers; j++)
			{
				if( (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myplayer[j].weapontype.rangey  && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myplayer[j].weapontype.rangex && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0 && j == i && (ch == 'a' || ch == 'd' || ch == 'w' || ch == 's'))
				{	
					myai[p].hitpoints = myai[p].hitpoints - myplayer[j].weapontype.damage - myplayer[j].character1.attack + myai[p].shieldstype.damage + myai[p].defensepoints;
					
					for(int k = 0; k < maxenemies; k++)
					{
						if(myai[k].hitpoints > 0)
						{
							break;
						}
						
						if(k == maxenemies - 1)
						{
							winner = "player";
				
							goto ended;
						}
					}
				}

				if( (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myai[p].weapontype.rangey  && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myai[p].weapontype.rangex && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0 && j == i && (ch == 'a' || ch == 'd' || ch == 'w' || ch == 's'))
				{	
					myplayer[j].hitpoints = myplayer[j].hitpoints - myai[p].weapontype.damage - myai[p].character1.attack + myplayer[j].shieldstype.damage + myplayer[j].defensepoints;

					for(int k = 0; k < maxplayers; k++)
					{
						if(myplayer[k].hitpoints > 0)
						{
							break;
						}

						if(k == maxenemies - 1)
						{
							winner = "ai";

							goto ended;
						}
					}
				}
			}

		}

		for(int j = 0; j < maxplayers; j++)
		{
			if(myplayer[i].hitpoints <= 0)
			{
				i++;
			}
			
			if(i >= maxplayers)
			{
				i = 0;
			}
			
			if(myplayer[i].hitpoints > 0)
			{
				break;
			}
		}
		
		for(int j = 0; j < maxenemies; j++)
		{
			if(myplayer[i].y == myai[j].y && myplayer[i].x == myai[j].x && myai[j].hitpoints > 0)
			{
				myplayer[i].y = myplayer[i].prevy;
				myplayer[i].x = myplayer[i].prevx;
			
				myplayer[i].replayer = 1;
			}
				
			for(int l = 0; l < maxplayers; l++)
			{
				if(i != l)
				{
					if(myplayer[l].y == myplayer[i].y && myplayer[l].x == myplayer[i].x && myplayer[l].hitpoints > 0)
					{
						myplayer[i].y = myplayer[i].prevy;
						myplayer[i].x = myplayer[i].prevx;
							
						myplayer[i].replayer = 1;
					}
				}
			}
		}
		
		if(myplayer[i].replayer == 0)
		{
			myplayer[i].prevy = myplayer[i].y;
			myplayer[i].prevx = myplayer[i].x;
		}
		
		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].replayer = 0;
		}
		
		for(int i = 0; i < maxplayers; i++)
		{
			if(myplayer[i].hitpoints > 0)
			{
				mvprintw(myplayer[i].y, myplayer[i].x, myplayer[i].charactersign);
			}
		}
		
		for(int i = 0; i < maxenemies; i++)
		{
			if(myai[i].hitpoints > 0)
			{
		   	mvprintw(myai[i].y, myai[i].x, myai[i].charactersign);
		   }
		}
		
		for(int i = 0; i < maxplayers; i++)
		{
		   mvprintw(hitpointspos1.y + i, hitpointspos1.x, "Player %d is %s hitpoints: %d mp: %d attack: %d magic: %s %d defense: %d weapon: %s shield: %s", myplayer[i].count, myplayer[i].character1.character, myplayer[i].hitpoints, myplayer[i].magicpoints, myplayer[i].weapontype.damage + myplayer[i].character1.attack, myplayer[i].magic1.equiped, myplayer[i].magic1.damage, myplayer[i].defensepoints + myplayer[i].shieldstype.damage, myplayer[i].weapontype.equiped, myplayer[i].shieldstype.equiped);
		}
		
		for(int i = 0; i < maxenemies; i++)
		{
		   mvprintw(hitpointspos1.ay + i, hitpointspos1.ax, "AI %d is %s hitpoints: %d mp: %d attack: %d magic: %s %d defense: %d weapon: %s shield: %s", myai[i].count, myai[i].character1.character, myai[i].hitpoints, myai[i].magicpoints, myai[i].weapontype.damage + myai[i].character1.attack, myai[i].magic1.equiped, myai[i].magic1.damage, myai[i].defensepoints + myai[i].shieldstype.damage, myai[i].weapontype.equiped, myai[i].shieldstype.equiped);
		}

		for(int i = 0; i < maxplayers; i++)
		{
			if(myplayer[i].hitpoints > 0)
			{
				break;
			}

			if(i == maxplayers - 1)
			{
				goto ended;
			}
		}

		move(myplayer[i].y, myplayer[i].x);
		
		refresh();
	}
ended:
	clear();
	
	mvprintw(0, 0, "The game is over and the winner is %s.  Press q to end the game.\n", winner); 
	
	refresh();
	
	while((ch = getch()) != 'q')
	{
	}
	
	endwin();
	
	return 0;
}
