#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <sys/ioctl.h>

#ifdef OPENBSD
#define rand() arc4random()
#elif LINUX
#include <bsd/stdlib.h>
#define rand() arc4random()
#endif

#define allitems 5
#define allitemsenemies 6

#define alldefenseitems 5
#define alldefenseitemsenemies 5

#define allmagics 5
#define allmagicsenemies 5

ssize_t getline(char **restrict lineptr, size_t *restrict n, FILE *restrict stream);

typedef enum {
    STR2INT_SUCCESS,
    STR2INT_OVERFLOW,
    STR2INT_UNDERFLOW,
    STR2INT_INCONVERTIBLE
} str2int_errno;

str2int_errno str2int(int *out, char *s, int base);

struct magic
{
	char* equiped;
	int damage;
	int randommagic;
	int rangey;
	int rangex;
	int cost;
	char* magicitems[allmagics];
	int nextrandommagic;
	int nextrandommagic2;
	int magiccount;
};

struct magicenemies
{
	char* equiped;
	int damage;
	int randommagic;
	int rangey;
	int rangex;
	int cost;
	char* magicitems[allmagicsenemies];
	int nextrandommagic;
	int nextrandommagic2;
	int magiccount;
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
	char* item;
	int damage[alldefenseitems];
};

struct shieldsdamageenemies
{
	char* item;
	int damage[alldefenseitemsenemies];
};

struct shields
{
	char* equiped;
	char* item[alldefenseitems];
	int damage;
	int numberitems;
	int randomshield;
	int nextrandomshield;
	int nextrandomshield2;
	int shieldcount;
};

struct shieldsenemies
{
	char* equiped;
	char* item[alldefenseitemsenemies];
	int damage;
	int numberitems;
	int randomshield;
	int nextrandomshield;
	int nextrandomshield2;
	int shieldcount;
};

struct weaponsdamage
{
	char* item;
	int damage[allitems];
	int rangey[allitems];
	int rangex[allitems];
};

struct weaponsdamageenemies
{
	char* item;
	int damage[allitemsenemies];
	int rangey[allitemsenemies];
	int rangex[allitemsenemies];
};

struct weapons
{
	char* equiped;
	char* item[allitems];
	int damage;
	int rangey;
	int rangex;
	int numberitems;
	int randomweapon;
	int nextrandomweapon;
	int nextrandomweapon2;
	int weaponcount;
};

struct weaponsenemies
{
	char* equiped;
	char* item[allitemsenemies];
	int damage;
	int rangey;
	int rangex;
	int numberitems;
	int randomweapon;
	int nextrandomweapon;
	int nextrandomweapon2;
	int weaponcount;
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
	struct weaponsenemies weapontype;
	struct weaponsdamageenemies weaponsdamage1;
	int randomitem;
	struct shieldsenemies shieldstype;
	struct shieldsdamageenemies shieldsdamage1;
	int shieldsrandomitem;
	struct character character1;
	struct magicenemies magic1;
};

int main(int argc, char *argv[])
{
	#define maxenemies 10
	#define maxplayers 8
	#define playercharacters 4
	#define aicharacters 4
	#define playermagiclist allmagics
	#define aimagiclist allmagicsenemies
	#define rounds 50
	#define lineamount 128
	int terminalend = maxenemies + maxplayers + 50;

	int hitpointsy = 24;
	int hitpointsx = 95;
	int positiony = 0;
	int aiopponent = 0;

	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	if(maxenemies < 1)
	{
		printf("You need maxenemies set to 1 or greater\n");
		
		return 1;
	}
	
	if(maxplayers < 1)
	{
		printf("You need maxplayers set to 1 or greater\n");
		
		return 1;
	}
	
	if(w.ws_row < hitpointsy)
	{
		printf("Change your terminal row to %d or greater\n", hitpointsy);

		return 1;
	}

	if(w.ws_col < hitpointsx)
	{
		printf("Change your terminal col to %d or greater\n", hitpointsx);

		return 1;
	}
	
	if((argc == 2) && strcmp(argv[1], "ai") == 0)
	{
		aiopponent = 1;
	}

	FILE *fp1;

	char lineBuffer[lineamount];
	ssize_t len = 0;

	for(int j = 0; j < lineamount; j++)
	{
		lineBuffer[j] = '\0';
	}

	int roundssofar = 1;

	int ch;

	ch = 'l';

#ifndef OPENBSD
#elif LINUX
#else
	srand(time(NULL));
#endif

beginning:

	while(roundssofar <= rounds && ch != 'y')
	{
		struct player myplayer[maxplayers];
		struct aicharacter myai[maxenemies];

		char* item[allitems];
		item[0] = "Knife";
		item[1] = "Gun";
		item[2] = "Pistol";
		item[3] = "Shotgun";
		item[4] = "Machine Gun";

		char* itemdamage[alldefenseitems];
		itemdamage[0] = "Short_Shield";
		itemdamage[1] = "Long_Shield";
		itemdamage[2] = "Metal_Shield";
		itemdamage[3] = "Iron_Shield";
		itemdamage[4] = "Steel_Shield";

		char* itemenemies[allitemsenemies];
		itemenemies[0] = "Knife";
		itemenemies[1] = "Gun";
		itemenemies[2] = "Pistol";
		itemenemies[3] = "Shotgun";
		itemenemies[4] = "Machine Gun";
		itemenemies[5] = "Weak Hammer";

		char* itemdamageenemies[alldefenseitemsenemies];
		itemdamageenemies[0] = "Short_Shield";
		itemdamageenemies[1] = "Long_Shield";
		itemdamageenemies[2] = "Metal_Shield";
		itemdamageenemies[3] = "Iron_Shield";
		itemdamageenemies[4] = "Steel_Shield";

		int damage[allitems] = { 40, 60, 50, 80, 120 };
		int rangey[allitems] = { 1, 2, 3, 4, 2 };
		int rangex[allitems] = { 1, 2, 3, 4, 2 };

		int damageenemies[allitemsenemies] = { 40, 60, 50, 80, 120, 20 };
		int rangeyenemies[allitemsenemies] = { 1, 2, 3, 4, 2, 1 };
		int rangexenemies[allitemsenemies] = { 1, 2, 3, 4, 2, 1 };

		int shielddamage[alldefenseitems] = { 2, 4, 6, 8, 10 };

		int shielddamageenemies[alldefenseitemsenemies] = { 2, 4, 6, 8, 10};

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
		playermagicdamage[1] = 70;
		playermagicdamage[2] = 60;
		playermagicdamage[3] = 50;
		playermagicdamage[4] = 40;

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
		playermagiccost[0] = 50;
		playermagiccost[1] = 40;
		playermagiccost[2] = 30;
		playermagiccost[3] = 20;
		playermagiccost[4] = 10;

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
			myai[i].randomitem = rand() % allitemsenemies;
		}

		for(int i = 0; i < maxplayers; i++)
		{
			myplayer[i].shieldsrandomitem = rand() % alldefenseitems;
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].shieldsrandomitem = rand() % alldefenseitemsenemies;
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
			for(int j = 0; j < allmagics; j++)
			{
				myplayer[i].magic1.magicitems[j] = "Empty";
			}

			for(int j = 0; j < allitems; j++)
			{
				myplayer[i].weapontype.item[j] = "Empty";
			}

			for(int j = 0; j < alldefenseitems; j++)
			{
				myplayer[i].shieldstype.item[j] = "Empty";
			}

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

			myplayer[i].magic1.magiccount = 0;

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

			myplayer[i].shieldstype.equiped = itemdamage[myplayer[i].shieldsrandomitem];

			myplayer[i].shield = myplayer[i].shieldstype.equiped;

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

			myplayer[i].weapontype.numberitems = allitems;

			myplayer[i].magic1.magicitems[myplayer[i].magic1.magiccount] = playermagicitems[myplayer[i].magic1.randommagic];
			
			myplayer[i].magic1.magiccount++;

			myplayer[i].magic1.nextrandommagic = myplayer[i].magic1.randommagic;

			while(myplayer[i].magic1.nextrandommagic == myplayer[i].magic1.randommagic)
			{
				myplayer[i].magic1.nextrandommagic = rand() % playermagiclist;
			}

			myplayer[i].magic1.magicitems[myplayer[i].magic1.magiccount] = playermagicitems[myplayer[i].magic1.nextrandommagic];

			myplayer[i].magic1.magiccount++;

			myplayer[i].magic1.nextrandommagic2 = myplayer[i].magic1.randommagic;

			while(myplayer[i].magic1.nextrandommagic2 == myplayer[i].magic1.randommagic || myplayer[i].magic1.nextrandommagic2 == myplayer[i].magic1.nextrandommagic)
			{
				myplayer[i].magic1.nextrandommagic2 = rand() % playermagiclist;
			}

			myplayer[i].magic1.magicitems[myplayer[i].magic1.magiccount] = playermagicitems[myplayer[i].magic1.nextrandommagic2];

			myplayer[i].magic1.magiccount++;

			myplayer[i].weapontype.weaponcount = 0;

			myplayer[i].weapontype.randomweapon = myplayer[i].randomitem;

			myplayer[i].weapontype.item[myplayer[i].weapontype.weaponcount] = item[myplayer[i].weapontype.randomweapon];

			myplayer[i].weapontype.weaponcount++;

			myplayer[i].weapontype.nextrandomweapon = myplayer[i].weapontype.randomweapon;

			while(myplayer[i].weapontype.nextrandomweapon == myplayer[i].weapontype.randomweapon)
			{
				myplayer[i].weapontype.nextrandomweapon = rand() % allitems;
			}

			myplayer[i].weapontype.item[myplayer[i].weapontype.weaponcount] = item[myplayer[i].weapontype.nextrandomweapon];

			myplayer[i].weapontype.equiped = item[myplayer[i].weapontype.randomweapon];

			myplayer[i].weapon = myplayer[i].weapontype.equiped;

			myplayer[i].weapontype.weaponcount++;

			myplayer[i].weapontype.nextrandomweapon2 = myplayer[i].weapontype.randomweapon;

			while(myplayer[i].weapontype.nextrandomweapon2 == myplayer[i].weapontype.nextrandomweapon || myplayer[i].weapontype.nextrandomweapon2 == myplayer[i].weapontype.randomweapon)
			{
				myplayer[i].weapontype.nextrandomweapon2 = rand() % allitems;
			}

			myplayer[i].weapontype.item[myplayer[i].weapontype.weaponcount] = item[myplayer[i].weapontype.nextrandomweapon2];

			myplayer[i].weapontype.weaponcount++;

			myplayer[i].shieldstype.shieldcount = 0;

			myplayer[i].shieldstype.randomshield = myplayer[i].shieldsrandomitem;

			myplayer[i].shieldstype.item[myplayer[i].shieldstype.shieldcount] = itemdamage[myplayer[i].shieldstype.randomshield];

			myplayer[i].shieldstype.equiped = myplayer[i].shieldstype.item[0];

			myplayer[i].shieldstype.shieldcount++;

			myplayer[i].shieldstype.nextrandomshield = myplayer[i].shieldstype.randomshield;

			while(myplayer[i].shieldstype.nextrandomshield == myplayer[i].shieldstype.randomshield)
			{
				myplayer[i].shieldstype.nextrandomshield = rand() % alldefenseitems;
			}

			myplayer[i].shieldstype.item[myplayer[i].shieldstype.shieldcount] = itemdamage[myplayer[i].shieldstype.nextrandomshield];

			myplayer[i].shieldstype.shieldcount++;

			myplayer[i].shieldstype.nextrandomshield2 = myplayer[i].shieldstype.randomshield;

			while(myplayer[i].shieldstype.nextrandomshield2 == myplayer[i].shieldstype.nextrandomshield || myplayer[i].shieldstype.nextrandomshield2 == myplayer[i].shieldstype.randomshield)
			{
				myplayer[i].shieldstype.nextrandomshield2 = rand() % alldefenseitems;
			}

			myplayer[i].shieldstype.item[myplayer[i].shieldstype.shieldcount] = itemdamage[myplayer[i].shieldstype.nextrandomshield2];

			myplayer[i].shieldstype.shieldcount++;
		}

		for(int i = 0; i < maxplayers; i++)
		{
			for(int j = 1; j < maxplayers; j++)
			{
				if(i != j && myplayer[i].y == myplayer[j].y && myplayer[i].x == myplayer[j].x)
				{
					myplayer[j].y = rand() % (terminalend - (maxplayers + maxenemies));
					myplayer[j].x = rand() % (hitpointsx - 1);

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

			myai[i].shield = myai[i].shieldstype.equiped;

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

			myai[i].weapontype.numberitems = allitemsenemies;
		}

		for(int i = 0; i < maxenemies; i++)
		{
			for(int j = 1; j < maxenemies; j++)
			{
				if(i != j && myai[i].y == myai[j].y && myai[i].x == myai[j].x)
				{
					myai[j].y = rand() % (terminalend - (maxplayers + maxenemies));
					myai[j].x = rand() % (hitpointsx - 1);
				
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
					myai[i].y = rand() % (terminalend - (maxplayers + maxenemies));
					myai[i].x = rand() % (hitpointsx - 1);

					myai[i].prevy = myai[i].y;
					myai[i].prevx = myai[i].x;
				
					i = -1;
					j = -1;

					break;
				}
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			myai[i].weapontype.equiped = myai[i].weapontype.item[myai[i].randomitem];
		}

		if(access("SaveFile.txt", F_OK ) != -1)
		{
			int c;
			int j = 0;
		
			fp1 = fopen("SaveFile.txt", "r");
			
			for(int i = 0; i < maxplayers; i++)
			{
				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].randomitem), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
		
					j++;
				}

				str2int(&(myplayer[i].shieldsrandomitem), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
		
					j++;
				}

				str2int(&(myplayer[i].character1.randomcharacter), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].magic1.randommagic), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
		
					j++;
				}
		
				str2int(&(myplayer[i].y), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
		
				j = 0;
		
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
		
					j++;
				}
		
				str2int(&(myplayer[i].x), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
		
				j = 0;
		
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
		
					j++;
				}
		
				str2int(&(myplayer[i].hitpoints), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
		
				j = 0;
		
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
		
					j++;
				}
		
				str2int(&(myplayer[i].magicpoints), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].defensepoints), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myplayer[i].weapon = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myplayer[i].shield = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;

				}

				myplayer[i].charactersign = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].prevy), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].prevx), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].magicattack), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].count), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].replayer), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].playerturn), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myplayer[i].weapontype.equiped = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				lineBuffer[j] = '\0';

				myplayer[i].character1.character = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myplayer[i].character1.sign = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].character1.hitpoints), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].character1.defense), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].character1.attack), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myplayer[i].weaponsdamage1.item = strdup(lineBuffer);


				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].defensepoints), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].hitpoints), lineBuffer, 10);

				for(int q = 0; q < allitems; q++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}
	
					j = 0;
	
					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;
	
						j++;
					}

					myplayer[i].weapontype.item[q] = strdup(lineBuffer);
				}

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].weapontype.damage), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].weapontype.rangey), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].weapontype.rangex), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].weapontype.numberitems), lineBuffer, 10);

				for(int q = 0; q < allitems; q++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}
	
					j = 0;
	
					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;
	
						j++;
					}

					str2int(&(myplayer[i].weaponsdamage1.damage[q]), lineBuffer, 10);
				}

				for(int q = 0; q < allitems; q++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}
	
					j = 0;
	
					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;
	
						j++;
					}

					str2int(&(myplayer[i].weaponsdamage1.rangey[q]), lineBuffer, 10);
				}

				for(int q = 0; q < allitems; q++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}
	
					j = 0;
	
					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;
	
						j++;
					}

					str2int(&(myplayer[i].weaponsdamage1.rangex[q]), lineBuffer, 10);
				}

				for(int q = 0; q < alldefenseitems; q++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}
	
					j = 0;
	
					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;
	
						j++;
					}

					myplayer[i].shieldstype.item[q] = strdup(lineBuffer);
				}

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myplayer[i].shieldstype.equiped = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].shieldstype.damage), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].shieldstype.numberitems), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myplayer[i].shieldsdamage1.item = strdup(lineBuffer);

				for(int q = 0; q < alldefenseitems; q++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}
	
					j = 0;
	
					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;
	
						j++;
					}
					
					str2int(&(myplayer[i].shieldsdamage1.damage[q]), lineBuffer, 10);
				}

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				myplayer[i].magic1.equiped = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myplayer[i].magic1.rangey), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myplayer[i].magic1.rangex), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myplayer[i].magic1.damage), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myplayer[i].magicattack), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myplayer[i].character1.magicresist), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myplayer[i].magicpoints), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myplayer[i].magic1.cost), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myplayer[i].weapontype.numberitems), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				myplayer[i].weapontype.equiped = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].magic1.magiccount), lineBuffer, 10);
			
				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].magic1.nextrandommagic), lineBuffer, 10);

				for(int l = 0; l < allmagics; l++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}

					j = 0;

					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;

						j++;
					}

					myplayer[i].magic1.magicitems[l] = strdup(lineBuffer);
				}

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].magic1.nextrandommagic2), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].weapontype.randomweapon), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].weapontype.nextrandomweapon), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].weapontype.nextrandomweapon2), lineBuffer, 10);

				for(int l = 0; l < allitems; l++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}

					j = 0;

					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;

						j++;
					}

					myplayer[i].weapontype.item[l] = strdup(lineBuffer);
				}

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].shieldstype.randomshield), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].shieldstype.nextrandomshield), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myplayer[i].shieldstype.nextrandomshield2), lineBuffer, 10);

				for(int l = 0; l < alldefenseitems; l++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}

					j = 0;

					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;

						j++;
					}

					myplayer[i].shieldstype.item[l] = strdup(lineBuffer);
				}
			}
		
			for(int i = 0; i < maxenemies; i++)
			{
				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].randomitem), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
		
					j++;
				}

				str2int(&(myai[i].shieldsrandomitem), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
		
					j++;
				}

				str2int(&(myai[i].character1.randomcharacter), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].magic1.randommagic), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
		
					j++;
				}
		
				str2int(&(myai[i].y), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
		
				j = 0;
		
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
		
					j++;
				}
		
				str2int(&(myai[i].x), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
		
				j = 0;
		
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
		
					j++;
				}
		
				str2int(&(myai[i].hitpoints), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
		
				j = 0;
		
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
		
					j++;
				}
		
				str2int(&(myai[i].magicpoints), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].defensepoints), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myai[i].weapon = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myai[i].shield = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}
				

				myai[i].charactersign = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].prevy), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].prevx), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].magicattack), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].count), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].replayer), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].playerturn), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myai[i].weapontype.equiped = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myai[i].character1.character = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myai[i].character1.sign = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].character1.hitpoints), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].character1.defense), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].character1.attack), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myai[i].weaponsdamage1.item = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].defensepoints), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].hitpoints), lineBuffer, 10);

				for(int q = 0; q < allitemsenemies; q++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}
	
					j = 0;
	
					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;
	
						j++;
					}

					myai[i].weapontype.item[q] = strdup(lineBuffer);
				}

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].weapontype.damage), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].weapontype.rangey), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].weapontype.rangex), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].weapontype.numberitems), lineBuffer, 10);

				for(int q = 0; q < allitemsenemies; q++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}
	
					j = 0;
	
					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;
	
						j++;
					}

					str2int(&(myai[i].weaponsdamage1.damage[q]), lineBuffer, 10);
				}

				for(int q = 0; q < allitemsenemies; q++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}
	
					j = 0;
	
					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;
	
						j++;
					}

					str2int(&(myai[i].weaponsdamage1.rangey[q]), lineBuffer, 10);
				}

				for(int q = 0; q < allitemsenemies; q++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}
	
					j = 0;
	
					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;
	
						j++;
					}

					str2int(&(myai[i].weaponsdamage1.rangex[q]), lineBuffer, 10);
				}

				for(int q = 0; q < alldefenseitemsenemies; q++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}
	
					j = 0;
	
					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;
	
						j++;
					}

					myai[i].shieldstype.item[q] = strdup(lineBuffer);
				}

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myai[i].shieldstype.equiped = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].shieldstype.damage), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				str2int(&(myai[i].shieldstype.numberitems), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}

				j = 0;

				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;

					j++;
				}

				myai[i].shieldsdamage1.item = strdup(lineBuffer);

				for(int q = 0; q < alldefenseitemsenemies; q++)
				{
					for(int k = 0; k < lineamount; k++)
					{
						lineBuffer[k] = '\0';
					}
	
					j = 0;
	
					while((c = fgetc(fp1)) != '\n')
					{
						lineBuffer[j] = c;
	
						j++;
					}
				
					str2int(&(myai[i].shieldsdamage1.damage[q]), lineBuffer, 10);
				}

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				myai[i].magic1.equiped = strdup(lineBuffer);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myai[i].magic1.rangey), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myai[i].magic1.rangex), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myai[i].magic1.damage), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myai[i].magicattack), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myai[i].character1.magicresist), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myai[i].magicpoints), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myai[i].magic1.cost), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				str2int(&(myai[i].weapontype.numberitems), lineBuffer, 10);

				for(int k = 0; k < lineamount; k++)
				{
					lineBuffer[k] = '\0';
				}
	
				j = 0;
	
				while((c = fgetc(fp1)) != '\n')
				{
					lineBuffer[j] = c;
	
					j++;
				}

				myai[i].weapontype.equiped = strdup(lineBuffer);
			}

			for(int k = 0; k < lineamount; k++)
			{
				lineBuffer[k] = '\0';
			}

			j = 0;

			while((c = fgetc(fp1)) != '\n')
			{
				lineBuffer[j] = c;

				j++;
			}

			str2int(&(roundssofar), lineBuffer, 10);

			for(int k = 0; k < lineamount; k++)
			{
				lineBuffer[k] = '\0';
			}

			j = 0;

			while((c = fgetc(fp1)) != '\n')
			{
				lineBuffer[j] = c;

				j++;
			}

			str2int(&(positiony), lineBuffer, 10);

			for(int k = 0; k < lineamount; k++)
			{
				lineBuffer[k] = '\0';
			}

			j = 0;

			while((c = fgetc(fp1)) != '\n')
			{
				lineBuffer[j] = c;
			
				j++;
			}
	
			str2int(&(aiopponent), lineBuffer, 10);

			fclose(fp1);

			remove("SaveFile.txt");
		}
	
		for(int i = 0; i < maxplayers; i++)
		{
			if(myplayer[i].y >= (terminalend - (maxplayers + maxenemies)))
			{
				printf("The player initialization code isn't correct.\n");

				return 1;
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			if(myai[i].y >= (terminalend - (maxplayers + maxenemies)))
			{
				printf("The ai initialization code isn't correct.\n");

				return 1;
			}
		}

		char* winner = "ai";
	
		int replayer = 0;
	
		int positionxdiff;
	
		int positionydiff;
	
		struct hitpointspos hitpointspos1 = { terminalend - (maxplayers + maxenemies), 0, terminalend - (maxenemies), 0 };
	
		initscr();
		
		resize_term(hitpointsy, hitpointsx);

		noecho();
	
		cbreak();

		positiony = (myplayer[0].y / 24) * 24;

		if(positiony > 0)
		{
			positiony++;
		}
	
		for(int i = 0; i < maxplayers; i++)
		{
			if(myplayer[i].hitpoints > 0 && myplayer[i].y >= (positiony - hitpointsy))
			{
				mvprintw(myplayer[i].y - positiony, myplayer[i].x, myplayer[i].charactersign);
			}
		}
	
		for(int i = 0; i < maxenemies; i++)
		{
			if(myai[i].hitpoints > 0 && myai[i].y >= (positiony - hitpointsy))
			{
				   mvprintw(myai[i].y - positiony, myai[i].x, myai[i].charactersign);
			}
		}
	
		for(int i = 0; i < maxplayers; i++)
		{
			if((hitpointspos1.y + i) > positiony)
			{
				mvprintw(hitpointspos1.y + i - positiony, hitpointspos1.x, "Player %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s", myplayer[i].count, myplayer[i].character1.character, myplayer[i].hitpoints, myplayer[i].magicpoints, myplayer[i].weapontype.damage + myplayer[i].character1.attack, myplayer[i].magic1.equiped, myplayer[i].magic1.damage, myplayer[i].defensepoints + myplayer[i].shieldstype.damage, myplayer[i].weapontype.equiped, myplayer[i].shieldstype.equiped);
		
			}
		}

		for(int i = 0; i < maxenemies; i++)
		{
			if((hitpointspos1.ay + i) >= (positiony) && (positiony > (maxenemies)))
			{
				mvprintw(hitpointspos1.ay + i - positiony, hitpointspos1.ax, "AI %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s", myai[i].count, myai[i].character1.character, myai[i].hitpoints, myai[i].magicpoints, myai[i].weapontype.damage + myai[i].character1.attack, myai[i].magic1.equiped, myai[i].magic1.damage, myai[i].defensepoints + myai[i].shieldstype.damage, myai[i].weapontype.equiped, myai[i].shieldstype.equiped);
		
			}
		}
	
		move(myplayer[0].y - positiony, myplayer[0].x);

		refresh();
	
		int i = 0;
	
		while((ch = getch()) != 'q')
		{	
			if(ch == 'S')
			{
				clear();

				mvprintw(0, 0, "Saving now and then exiting");

				refresh();

				fp1 = fopen("SaveFile.txt", "w");

				for(int i = 0; i < maxplayers; i++)
				{
					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].randomitem);

					int k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].shieldsrandomitem);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].character1.randomcharacter);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);
				
					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].magic1.randommagic);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].y);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].x);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].hitpoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].magicpoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].defensepoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myplayer[i].weapon);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myplayer[i].shield);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myplayer[i].charactersign);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].prevy);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].prevx);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].magicattack);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].count);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].replayer);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].playerturn);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myplayer[i].weapontype.equiped);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myplayer[i].character1.character);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myplayer[i].character1.sign);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].character1.hitpoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].character1.defense);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].character1.attack);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myplayer[i].weaponsdamage1.item);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].defensepoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].hitpoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int q = 0; q < allitems; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						strcpy(lineBuffer, myplayer[i].weapontype.item[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].weapontype.damage);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].weapontype.rangey);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].weapontype.rangex);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].weapontype.numberitems);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int q = 0; q < allitems; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						snprintf(lineBuffer, lineamount, "%d", myplayer[i].weaponsdamage1.damage[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int q = 0; q < allitems; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						snprintf(lineBuffer, lineamount, "%d", myplayer[i].weaponsdamage1.rangey[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int q = 0; q < allitems; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						snprintf(lineBuffer, lineamount, "%d", myplayer[i].weaponsdamage1.rangex[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int q = 0; q < alldefenseitems; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						strcpy(lineBuffer, myplayer[i].shieldstype.item[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myplayer[i].shieldstype.equiped);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].shieldstype.damage);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].shieldstype.numberitems);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myplayer[i].shieldsdamage1.item);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int q = 0; q < alldefenseitems; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						snprintf(lineBuffer, lineamount, "%d", myplayer[i].shieldsdamage1.damage[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myplayer[i].magic1.equiped);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].magic1.rangey);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].magic1.rangex);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].magic1.damage);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].magicattack);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].character1.magicresist);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].magicpoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].magic1.cost);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].weapontype.numberitems);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myplayer[i].weapontype.equiped);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].magic1.magiccount);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);
				
					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}
	
					snprintf(lineBuffer, lineamount, "%d", myplayer[i].magic1.nextrandommagic);
	
					k = 0;
	
					while(lineBuffer[k] != '\0')
					{
						k++;
					}
	
					lineBuffer[k] = '\n';
	
					fwrite(lineBuffer, 1, k+1, fp1);
					
					for(int q = 0; q < allmagics; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						strcpy(lineBuffer, myplayer[i].magic1.magicitems[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].magic1.nextrandommagic2);

					k =  0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].weapontype.randomweapon);

					k =  0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].weapontype.nextrandomweapon);

					k =  0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].weapontype.nextrandomweapon2);

					k =  0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int q = 0; q < allitems; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						strcpy(lineBuffer, myplayer[i].weapontype.item[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}
					
					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].shieldstype.randomshield);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].shieldstype.nextrandomshield);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myplayer[i].shieldstype.nextrandomshield2);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int q = 0; q < alldefenseitems; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						strcpy(lineBuffer, myplayer[i].shieldstype.item[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}
				}

				for(int i = 0; i < maxenemies; i++)
				{
					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].randomitem);

					int k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].shieldsrandomitem);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].character1.randomcharacter);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);
				
					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].magic1.randommagic);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].y);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].x);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].hitpoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].magicpoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].defensepoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myai[i].weapon);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myai[i].shield);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myai[i].charactersign);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].prevy);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].prevx);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].magicattack);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].count);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].replayer);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].playerturn);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myai[i].weapontype.equiped);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myai[i].character1.character);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myai[i].character1.sign);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].character1.hitpoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].character1.defense);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].character1.attack);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myai[i].weaponsdamage1.item);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].defensepoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].hitpoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int q = 0; q < allitemsenemies; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						strcpy(lineBuffer, myai[i].weapontype.item[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].weapontype.damage);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].weapontype.rangey);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].weapontype.rangex);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].weapontype.numberitems);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int q = 0; q < allitemsenemies; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						snprintf(lineBuffer, lineamount, "%d", myai[i].weaponsdamage1.damage[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int q = 0; q < allitemsenemies; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						snprintf(lineBuffer, lineamount, "%d", myai[i].weaponsdamage1.rangey[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int q = 0; q < allitemsenemies; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						snprintf(lineBuffer, lineamount, "%d", myai[i].weaponsdamage1.rangex[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int q = 0; q < alldefenseitemsenemies; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						strcpy(lineBuffer, myai[i].shieldstype.item[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myai[i].shieldstype.equiped);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].shieldstype.damage);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].shieldstype.numberitems);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myai[i].shieldsdamage1.item);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int q = 0; q < alldefenseitemsenemies; q++)
					{
						for(int j = 0; j < lineamount; j++)
						{
							lineBuffer[j] = '\0';
						}
	
						snprintf(lineBuffer, lineamount, "%d", myai[i].shieldsdamage1.damage[q]);
	
						k = 0;
	
						while(lineBuffer[k] != '\0')
						{
							k++;
						}
	
						lineBuffer[k] = '\n';
	
						fwrite(lineBuffer, 1, k+1, fp1);
					}

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myai[i].magic1.equiped);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].magic1.rangey);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].magic1.rangex);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].magic1.damage);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].magicattack);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].character1.magicresist);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].magicpoints);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].magic1.cost);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					snprintf(lineBuffer, lineamount, "%d", myai[i].weapontype.numberitems);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);

					for(int j = 0; j < lineamount; j++)
					{
						lineBuffer[j] = '\0';
					}

					strcpy(lineBuffer, myai[i].weapontype.equiped);

					k = 0;

					while(lineBuffer[k] != '\0')
					{
						k++;
					}

					lineBuffer[k] = '\n';

					fwrite(lineBuffer, 1, k+1, fp1);
					
				}

				for(int j = 0; j < lineamount; j++)
				{
					lineBuffer[j] = '\0';
				}

				snprintf(lineBuffer, lineamount, "%d", roundssofar);

				int k = 0;

				while(lineBuffer[k] != '\0')
				{
					k++;
				}

				lineBuffer[k] = '\n';

				fwrite(lineBuffer, 1, k+1, fp1);
				
				for(int j = 0; j < lineamount; j++)
				{
					lineBuffer[j] = '\0';
				}

				snprintf(lineBuffer, lineamount, "%d", positiony);

				k = 0;

				while(lineBuffer[k] != '\0')
				{
					k++;
				}

				lineBuffer[k] = '\n';

				fwrite(lineBuffer, 1, k+1, fp1);

				for(int j = 0; j < lineamount; j++)
				{
					lineBuffer[j] = '\0';
				}

				snprintf(lineBuffer, lineamount, "%d", aiopponent);

				k = 0;

				while(lineBuffer[k] != '\0')
				{
					k++;
				}

				lineBuffer[k] = '\n';

				fwrite(lineBuffer, 1, k+1, fp1);

				fclose(fp1);

				endwin();

				return 0;
			}

			if(ch == 'h')
			{
				clear();

				mvprintw(0, 0, "Press a to move left");
				mvprintw(1, 0, "Press d to move right");
				mvprintw(2, 0, "Press w to move up");
				mvprintw(3, 0, "Press s to move down");
				mvprintw(4, 0, "Press m to use magic");
				mvprintw(5, 0, "Press M to equip different magic, weapon, and shield");
				mvprintw(6, 0, "Press n to cycle through player characters forward");
				mvprintw(7, 0, "Press p to cycle through player characters backward");
				mvprintw(8, 0, "Press c to see what magics, weapons, and shields you have");
				mvprintw(9, 0, "Press h to display this during game to see this screen");
				mvprintw(10, 0, "The H is a player human and the h is a ai human");
				mvprintw(11, 0, "The O is a player orc and the o is a ai orc");
				mvprintw(12, 0, "The E is a player elf and the e is a ai elf");
				mvprintw(13, 0, "The D is a player dwarf and the d is a ai elf");
				mvprintw(14, 0, "Press q from battle screen to quit game");
				mvprintw(15, 0, "Press S to save and quit");
				mvprintw(16, 0, "Press u to scroll up");
				mvprintw(17, 0, "Press j to scroll down");
				mvprintw(18, 0, "Press key to quit help");

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
						positiony = (myplayer[i].y / 24) * 24;

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
						positiony = ((myplayer[i].y) / 24) * 24;

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
			
				if(myplayer[i].x > hitpointsx - 1)
				{
					myplayer[i].x = hitpointsx - 1;
				}
			}
		
			if(ch == 'w')
			{
				myplayer[i].y = myplayer[i].y - 1;
			
				if(myplayer[i].y < 0)
				{
					myplayer[i].y = 0;
				}

				positiony = ((myplayer[i].y) / 24) * 24;
			}

			if(ch == 'u')
			{
				clear();

				positiony--;
				
				if(positiony < 0)
				{
					positiony = 0;
				}

				move(positiony, 0);

				refresh();
			}

			if(ch == 'j')
			{
				clear();

				positiony++;
				
				if(positiony > (terminalend + 1 - hitpointsy))
				{
					positiony = (terminalend + 1 - hitpointsy);
				}

				move(positiony, 0);

				refresh();
			}
		
			if(ch == 's')
			{
				myplayer[i].y = myplayer[i].y + 1;
			
				if(myplayer[i].y > (hitpointspos1.y - 1))
				{
					myplayer[i].y = (hitpointspos1.y - 1);
				}

				positiony = ((myplayer[i].y) / 24) * 24;
			}

			if(ch == 'c')
			{
				clear();

				int list = 0;
				int l = 0;
				int gotcharacter = '0';

				do
				{
					clear();

					if(gotcharacter == 'd')
					{
						list++;
					}

					if(list > 2)
					{
						list = 0;
					}

					if(list == 0)
					{
						while(strcmp(myplayer[i].magic1.magicitems[l], "Empty") != 0)
						{
							mvprintw(l, 0, "Magic item %d is %s", l + 1, myplayer[i].magic1.magicitems[l]);
							l++;
						}
					}

					if(list == 1)
					{
						while(strcmp(myplayer[i].weapontype.item[l], "Empty") != 0)
						{
							mvprintw(l, 0, "Weapon item %d is %s", l + 1, myplayer[i].weapontype.item[l]);
							l++;
						}
					}

					if(list == 2)
					{
						while(strcmp(myplayer[i].shieldstype.item[l], "Empty") != 0)
						{
							mvprintw(l, 0, "Shield item %d is %s", l + 1, myplayer[i].shieldstype.item[l]);
							l++;
						}
					}

					mvprintw(l, 0, "Press d to move to next category\n");

					l++;

					mvprintw(l, 0, "Press anything else to exit this menu\n");

					l = 0;

					move(0, 0);

					refresh();
				} 
				while((gotcharacter = getch()) == 'd');

				list = 0;
				l = 0;
				
				move(myplayer[i].y, myplayer[i].x);

				clear();

				refresh();
			}

			if(ch == 'M')
			{
				int gotcharacter;
				int keypressed;

				int list = 0;

				clear();
				
				int l = 0;
				
				while(strcmp(myplayer[i].magic1.magicitems[l], "Empty") != 0)
				{
					mvprintw(l, 0, "Magic item %d is %s.\n", l + 1, myplayer[i].magic1.magicitems[l], l+1);
					l++;
				}

				mvprintw(l, 0, "press w to move up\n");
				l++;
				mvprintw(l, 0, "press s to move down\n");
				l++;
				mvprintw(l, 0, "press e to select\n");
				l++;
				mvprintw(l, 0, "press d to move to next category\n");
				l++;
				
				int u = 0;

				move(u, 0);

				refresh();

				while((gotcharacter = getch()) != 'e')
				{
					if(gotcharacter == 'w')
					{
						u--;

						if(u < 0)
						{
							u = 0;
						}
					}

					if(gotcharacter == 's')
					{
						u++;

						if(u > (myplayer[i].magic1.magiccount - 1) && list == 0)
						{
							u = myplayer[i].magic1.magiccount - 1;
						}

						if(u > (myplayer[i].weapontype.weaponcount - 1) && list == 1)
						{
							u = myplayer[i].weapontype.weaponcount - 1;
						}

						if(u > (myplayer[i].shieldstype.shieldcount - 1) && list == 2)
						{
							u = myplayer[i].shieldstype.shieldcount - 1;
						}
					}

					if(gotcharacter == 'd')
					{
						list++;

						if(list > 2)
						{
							list = 0;
						}

						u = 0;

						clear();

						if(list == 0)
						{
							l = 0;
							
							while(strcmp(myplayer[i].magic1.magicitems[l], "Empty") != 0)
							{
								mvprintw(l, 0, "Magic item %d is %s.\n", l + 1, myplayer[i].magic1.magicitems[l], l+1);
								l++;
							}
						}

						if(list == 1)
						{
							l = 0;

							while(strcmp(myplayer[i].weapontype.item[l], "Empty") != 0)
							{
								mvprintw(l, 0, "Weapon item %d is %s.\n", l + 1, myplayer[i].weapontype.item[l], l+1);
								l++;
							}
						}

						if(list == 2)
						{
							l = 0;

							while(strcmp(myplayer[i].shieldstype.item[l], "Empty") != 0)
							{
								mvprintw(l, 0, "Shield item %d is %s.\n", l + 1, myplayer[i].shieldstype.item[l], l+1);
								l++;
							}
						}

						mvprintw(l, 0, "press w to move up\n");
						l++;
						mvprintw(l, 0, "press s to move down\n");
						l++;
						mvprintw(l, 0, "press e to select\n");
						l++;
						mvprintw(l, 0, "press d to move to next category\n");
						l++;
					}

					move(u, 0);

					refresh();
				}

				if(list == 0)
				{
					myplayer[i].magic1.equiped = myplayer[i].magic1.magicitems[u];

					if(u == 0)
					{
						myplayer[i].magic1.rangey = playermagicdistance[myplayer[i].magic1.randommagic];
						myplayer[i].magic1.rangex = playermagicdistance[myplayer[i].magic1.randommagic];
						myplayer[i].magic1.damage = playermagicdamage[myplayer[i].magic1.randommagic];
						myplayer[i].magic1.cost = playermagiccost[myplayer[i].magic1.randommagic];
					}

					if(u == 1)
					{
						myplayer[i].magic1.rangey = playermagicdistance[myplayer[i].magic1.nextrandommagic];
						myplayer[i].magic1.rangex = playermagicdistance[myplayer[i].magic1.nextrandommagic];
						myplayer[i].magic1.damage = playermagicdamage[myplayer[i].magic1.nextrandommagic];
						myplayer[i].magic1.cost = playermagiccost[myplayer[i].magic1.nextrandommagic];
					}

					if(u == 2)
					{
						myplayer[i].magic1.rangey = playermagicdistance[myplayer[i].magic1.nextrandommagic2];
						myplayer[i].magic1.rangex = playermagicdistance[myplayer[i].magic1.nextrandommagic2];
						myplayer[i].magic1.damage = playermagicdamage[myplayer[i].magic1.nextrandommagic2];
						myplayer[i].magic1.cost = playermagiccost[myplayer[i].magic1.nextrandommagic2];
					}

					myplayer[i].magicattack = myplayer[i].magic1.damage;
				}

				if(list == 1)
				{
					if(u == 0)
					{
						myplayer[i].weapontype.equiped = item[myplayer[i].weapontype.randomweapon];
						myplayer[i].weapontype.rangey = rangey[myplayer[i].weapontype.randomweapon];
						myplayer[i].weapontype.rangex = rangex[myplayer[i].weapontype.randomweapon];
						myplayer[i].weapontype.damage = damage[myplayer[i].weapontype.randomweapon];
					}

					if(u == 1)
					{
						myplayer[i].weapontype.equiped = item[myplayer[i].weapontype.nextrandomweapon];
						myplayer[i].weapontype.rangey = rangey[myplayer[i].weapontype.nextrandomweapon];
						myplayer[i].weapontype.rangex = rangex[myplayer[i].weapontype.nextrandomweapon];
						myplayer[i].weapontype.damage = damage[myplayer[i].weapontype.nextrandomweapon];
					}

					if(u == 2)
					{
						myplayer[i].weapontype.equiped = item[myplayer[i].weapontype.nextrandomweapon2];
						myplayer[i].weapontype.rangey = rangey[myplayer[i].weapontype.nextrandomweapon2];
						myplayer[i].weapontype.rangex = rangex[myplayer[i].weapontype.nextrandomweapon2];
						myplayer[i].weapontype.damage = damage[myplayer[i].weapontype.nextrandomweapon2];
					}
				}

				if(list == 2)
				{
					if(u == 0)
					{
						myplayer[i].shieldstype.equiped = itemdamage[myplayer[i].shieldstype.randomshield];
						myplayer[i].shieldstype.damage = shielddamage[myplayer[i].shieldstype.randomshield];
						myplayer[i].shieldsdamage1.item = itemdamage[myplayer[i].shieldstype.randomshield];
					}

					if(u == 1)
					{
						myplayer[i].shieldstype.equiped = itemdamage[myplayer[i].shieldstype.nextrandomshield];
						myplayer[i].shieldstype.damage = shielddamage[myplayer[i].shieldstype.nextrandomshield];
						myplayer[i].shieldsdamage1.item = itemdamage[myplayer[i].shieldstype.nextrandomshield];
					}

					if(u == 2)
					{
						myplayer[i].shieldstype.equiped = itemdamage[myplayer[i].shieldstype.nextrandomshield2];
						myplayer[i].shieldstype.damage = shielddamage[myplayer[i].shieldstype.nextrandomshield2];
						myplayer[i].shieldsdamage1.item = itemdamage[myplayer[i].shieldstype.nextrandomshield2];
					}

					myplayer[i].shield = myplayer[i].shieldstype.equiped;
				}

				l = 0;
				u = 0;

				move(myplayer[i].y, myplayer[i].x);
				
				clear();
				
				refresh();
			}

			if(ch == 'm')
			{
				int t = -1;
				
				for(int j = 0; j < maxenemies; j++)
				{
					if((positionydiff = abs(myplayer[i].y - myai[j].y)) <= myai[j].magic1.rangey && (positionxdiff = abs(myplayer[i].x - myai[j].x)) <= myai[j].magic1.rangex)
					{
						t = j;
						break;
					}
				
				}
				for(int p = 0; p < maxenemies; p++)
				{
					for(int j = 0; j < maxplayers; j++)
					{
						if(t != -1 )
						{
							p = t;

							if((myai[p].magicpoints >= myai[p].magic1.cost) && (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myai[p].magic1.rangey && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myai[p].magic1.rangex && ch == 'm' && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0)
							{
								myplayer[j].hitpoints = myplayer[j].hitpoints - myai[p].magicattack + myplayer[j].character1.magicresist;

								if(i == j)
								{
									myai[p].magicpoints = myai[p].magicpoints - myai[p].magic1.cost;
								}

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

					if(t != -1)
					{
						break;
					}
				}


				for(int p = 0; p < maxenemies; p++)
				{
					
					if(t != -1)
					{
						p = t;
					}

					for(int j = 0; j < maxplayers; j++)
					{
						if((myplayer[j].magicpoints >= myplayer[j].magic1.cost) && (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myplayer[j].magic1.rangey  && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myplayer[j].magic1.rangex && ch == 'm' && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0)
						{
							if(j == i)
							{
								myai[p].hitpoints = myai[p].hitpoints - myplayer[j].magicattack + myai[p].character1.magicresist;
						
							}	myplayer[j].magicpoints = myplayer[j].magicpoints - myplayer[j].magic1.cost;
					
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

					if(t != -1)
					{
						break;
					}
				}
			}

			for(int p = 0; p < maxenemies; p++)
			{
				for(int j = 0; j < maxplayers; j++)
				{
					if( (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myplayer[j].weapontype.rangey  && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myplayer[j].weapontype.rangex && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0 && (ch == 'a' || ch == 'd' || ch == 'w' || ch == 's'))
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

					if( (positionydiff = abs(myplayer[j].y - myai[p].y)) <= myai[p].weapontype.rangey  && (positionxdiff = abs(myplayer[j].x - myai[p].x)) <= myai[p].weapontype.rangex && myai[p].hitpoints > 0 && myplayer[j].hitpoints > 0 && (ch == 'a' || ch == 'd' || ch == 'w' || ch == 's'))
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

			if(aiopponent == 1 && (ch != 'u' || ch != 'j' || ch != 'h'))
			{
				for(int j = 0; j < maxenemies; j++)
				{
					if(myplayer[i].y < myai[j].y)
					{
						myai[j].y = myai[j].y - 1;
					}

					if(myplayer[i].y > myai[j].y)
					{
						myai[j].y = myai[j].y + 1;
					}
				}
			}
		
			for(int j = 0; j < maxenemies; j++)
			{
				if(myplayer[i].y == myai[j].y && myplayer[i].x == myai[j].x && myai[j].hitpoints > 0)
				{
					myplayer[i].y = myplayer[i].prevy;
					myplayer[i].x = myplayer[i].prevx;

					positiony = (myplayer[i].y / 24) * 24;
					
					if(positiony > 0)
					{
						positiony++;
					}
			
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

							positiony = (myplayer[i].y / 24) * 24;
							
							if(positiony > 0)
							{
								positiony++;
							}
							
							myplayer[i].replayer = 1;
						}
					}
				}

				for(int l = 0; l < maxenemies; l++)
				{
					if(j != l)
					{
						if(myai[j].y == myai[l].y && myai[j].x == myai[l].x && myai[j].hitpoints > 0 && myai[l].hitpoints > 0)
						{
							myai[j].y = myai[j].prevy;
							myai[j].x = myai[j].prevx;

							myai[j].replayer = 1;
						}
					}
				}

				for(int k = 0; k < maxplayers; k++)
				{
					if(myplayer[k].y == myai[j].y && myplayer[k].x == myai[j].x && myplayer[k].hitpoints > 0 && myai[j].hitpoints > 0)
					{
						myai[j].y = myai[j].prevy;
						myai[j].x = myai[j].prevx;

						myai[j].replayer = 1;
					}
				}
			}

			if(myplayer[i].replayer == 1)
			{
				for(int j = 0; j < maxenemies; j++)
				{
					if(myai[j].y == myai[j].prevy && myplayer[i].x != myai[j].x && myplayer[i].y == (myai[j].y - 1))
					{
						myai[j].y = myai[j].y - 1;
					}

					if(myai[j].y == myai[j].prevy && myplayer[i].x != myai[j].x && myplayer[i].y == (myai[j].y + 1))
					{
						myai[j].y = myai[j].y + 1;
					}

					if(!(abs(myplayer[i].y - myai[j].y) < 1 && myplayer[i].x != myai[j].x))
					{
						if(myplayer[i].y == myai[j].prevy && myplayer[i].x != myai[j].x && myplayer[i].y != myai[j].y)
						{
							myai[j].y = myai[j].prevy;
						}
					}
				}
			}

			if(myplayer[i].replayer == 0)
			{
				myplayer[i].prevy = myplayer[i].y;
				myplayer[i].prevx = myplayer[i].x;
			}

			for(int j = 0; j < maxenemies; j++)
			{
				if(myai[j].replayer == 0)
				{
					myai[j].prevy = myai[j].y;
					myai[j].prevx = myai[j].x;
				}
			}
		
			for(int i = 0; i < maxplayers; i++)
			{
				myplayer[i].replayer = 0;
			}

			for(int i = 0; i < maxenemies; i++)
			{
				myai[i].replayer = 0;
			}
		
			for(int i = 0; i < maxplayers; i++)
			{
				if(myplayer[i].hitpoints > 0 && myplayer[i].y >= (positiony - hitpointsy))
				{
					mvprintw(myplayer[i].y - positiony, myplayer[i].x, myplayer[i].charactersign);
				}
			}
		
			for(int i = 0; i < maxenemies; i++)
			{
				if(myai[i].hitpoints > 0 && myai[i].y >= (positiony - hitpointsy))
				{
					   mvprintw(myai[i].y - positiony, myai[i].x, myai[i].charactersign);
				}
			}
		
			for(int i = 0; i < maxplayers; i++)
			{
				if((hitpointspos1.y + i) > positiony)
				{
					mvprintw(hitpointspos1.y + i - positiony, hitpointspos1.x, "Player %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s", myplayer[i].count, myplayer[i].character1.character, myplayer[i].hitpoints, myplayer[i].magicpoints, myplayer[i].weapontype.damage + myplayer[i].character1.attack, myplayer[i].magic1.equiped, myplayer[i].magic1.damage, myplayer[i].defensepoints + myplayer[i].shieldstype.damage, myplayer[i].weapontype.equiped, myplayer[i].shieldstype.equiped);
			
				}
			}

			for(int i = 0; i < maxenemies; i++)
			{
				if((hitpointspos1.ay + i) >= (positiony) && (positiony > (maxenemies)))
				{
					mvprintw(hitpointspos1.ay + i - positiony, hitpointspos1.ax, "AI %d is %s hp:%d mp:%d at:%d ma:%s %d def:%d w:%s sh:%s", myai[i].count, myai[i].character1.character, myai[i].hitpoints, myai[i].magicpoints, myai[i].weapontype.damage + myai[i].character1.attack, myai[i].magic1.equiped, myai[i].magic1.damage, myai[i].defensepoints + myai[i].shieldstype.damage, myai[i].weapontype.equiped, myai[i].shieldstype.equiped);
			
				}
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

			move(myplayer[i].y - positiony, myplayer[i].x);

			refresh();
		}

	ended:
		clear();
	
		if(ch == 'q')
		{
			if(access("SaveFile.txt", F_OK ) != -1)
			{
				remove("SaveFile.txt");
			}

			goto endmenow;
		}
	
		if(strcmp(winner, "ai") == 0)
		{
			mvprintw(0, 0, "You lose the ai won the game is over.");
			mvprintw(1, 0, "Press y to end");

			refresh();

			if(access("SaveFile.txt", F_OK ) != -1)
			{
				remove("SaveFile.txt");
			}

			ch = getch();

			if(ch != 'y')
			{
				roundssofar = 1;

				clear();

				refresh();

				goto beginning;
			}
		
			endwin();

			return 0;
		}

		if(roundssofar == rounds)
		{
			mvprintw(0, 0, "You have beat the game. Congratulations.");
			mvprintw(1, 0, "Press y to end");

			refresh();

			if(access("SaveFile.txt", F_OK ) != -1)
			{
				remove("SaveFile.txt");
			}

			ch = getch();

			if(ch != 'y')
			{
				roundssofar = 1;

				clear();

				refresh();

				goto beginning;
			}

			endwin();

			return 0;
		}

		mvprintw(0, 0, "The winner of the %d battle is %s.", roundssofar, winner);
		mvprintw(1, 0, "You have %d battle to go", rounds - roundssofar);
		mvprintw(2, 0, "Press y to end"); 
	
		refresh();
	
		ch = getch();

		if(ch != 'y')
		{
			roundssofar++;

			clear();

			refresh();

			goto beginning;
		}

	endmenow:
		if(access("SaveFile.txt", F_OK ) != -1)
		{
			remove("SaveFile.txt");
		}

		endwin();
	
		return 0;
	}
}

str2int_errno str2int(int *out, char *s, int base) {
    char *end;
    if (s[0] == '\0' || isspace((unsigned char) s[0]))
        return STR2INT_INCONVERTIBLE;
    errno = 0;
    long l = strtol(s, &end, base);
    /* Both checks are needed because INT_MAX == LONG_MAX is possible. */
    if (l > INT_MAX || (errno == ERANGE && l == LONG_MAX))
        return STR2INT_OVERFLOW;
    if (l < INT_MIN || (errno == ERANGE && l == LONG_MIN))
        return STR2INT_UNDERFLOW;
    if (*end != '\0')
        return STR2INT_INCONVERTIBLE;
    *out = l;
    return STR2INT_SUCCESS;
}
