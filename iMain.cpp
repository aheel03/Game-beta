#include "iGraphics.h"
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include<vector>
#include<math.h>

void drawHomePage();
void drawStartPage();
void drawnamepage();
void StartButtonClickHandler();
void drawInstPage();
void InstButtonClickHandler();
void BackButtonClickHandler();
void coordinates();
void location_change();
void drawwinpage();
void drawgamepage();
void check_pic();
void drawscorepage();

bool homepage=1;
bool startpage=0;
bool gamepage=0;
bool instpage=0;
bool winpage=0;
bool namepage=0;
bool musicon=1;

int mode =1; //easy mode 
int moves =0;
char arr[100], str[10];
int index = 0, run = 1;
clock_t start;

struct pic{
	int x;
	int y;
};

struct correct_pic{
	int x;
	int y;
};

struct pic pic[25];
struct correct_pic correct_pic[25];

int openx = 0, openy = 480;
int x = 300, y = 300, r = 20;
bool correct = true;


char picture[25][20] = { "25.bmp", "24.bmp", "23.bmp", "22.bmp", "21.bmp", "20.bmp",
"19.bmp", "18.bmp", "17.bmp", "16.bmp", "15.bmp",
"14.bmp", "13.bmp", "12.bmp", "11.bmp", "10.bmp",
"09.bmp", "08.bmp", "07.bmp", "06.bmp", "05.bmp",
"04.bmp", "03.bmp", "02.bmp", "01.bmp"};

char alt[25][20];



void iDraw() {
	iClear();
	if(homepage){
		drawHomePage();
	}
	else if(startpage){
		drawStartPage();
	}
	else if(gamepage)
	{
		iSetColor(144, 238, 144);
		clock_t end = clock();
		double time_diff = (start - end) / CLOCKS_PER_SEC;
		char str2[10];
		sprintf(str2, "%.2lf", time_diff);
		if (time_diff < 1)
		{
			homepage=0;
			startpage=0;
			gamepage=0;
			instpage=0;
			winpage=1;
			namepage=0;
		}
		iText(730, 450, "TIME :", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(810, 450, str2, GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(149, 33, 246);
		//iFilledRectangle(0, 0, 700, 700);
		iSetColor(255, 255, 255);
		iText(740, 330, "MOVES ->", GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf(str, "%i", moves);
		iSetColor(255, 0, 0);
		iText(780, 300, str, GLUT_BITMAP_TIMES_ROMAN_24);
		int count = 1;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == 0 && j == 0) continue;
				else{
					iShowBMP(pic[count].x, pic[count].y, picture[count]);
					count++;
				}
			}
		}
		check_pic();
		if (correct == true)
		{
			printf("BROOOOO\n");
			homepage = 0;
			gamepage=0;
			startpage = 0;
			instpage = 0;
			winpage = 1;
		}
		
	}else if(namepage){
		drawnamepage();
	}
	else if(instpage){
		drawInstPage();
	}else if(winpage){
		drawwinpage();
	}
}

void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
}

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		printf("x = %d, y= %d\n",mx,my);
		if(homepage && (mx>=400 && mx<=600) && (my>=450 && my<=530 )){
			homepage=0;
			startpage=1;
		}else if(homepage && (mx>=400 && mx<=600) && (my>=150 && my<=230 )){
			homepage=0;
			startpage=0;
			instpage=1;
		}
		else if(startpage && (mx>=400 && mx<=600) && (my>=450 && my<=530 )){
			homepage = 0;
			startpage = 0;
			instpage = 0;
			winpage = 0;
			gamepage=0;
			namepage=1;
			mode = 1;
		}
		else if(startpage && (mx>=400 && mx<=600) && (my>=150 && my<=230 )){
			homepage = 0;
			startpage = 0;
			instpage = 0;
			winpage = 0;
			gamepage=0;
			namepage=1;
			mode = 2;
		}else if(namepage && (mx>=400 && mx<=600) && (my>=150 && my<=230 )){
			homepage = 0;
			startpage = 0;
			instpage = 0;
			winpage = 0;
			gamepage=1;
			namepage=0;
			coordinates();
               location_change();
        		openx = 0, openy = 480;
        		moves = 0;
        		//PlaySound(0, 0, 0);
        		start = clock() + 31000;
		}
		else if(gamepage && mode==1){
			PlaySoundA("click.wav", NULL,SND_ASYNC);
			//PlaySound("click.wav", NULL, SND_ASYNC);
               moves++;
			int tempx = (mx / 120) * 120;
			int tempy = (my / 120) * 120;
			for (int i = 1; i < 25; i++)
			{
				if (pic[i].x == tempx && pic[i].y == tempy)
				{
					pic[i].x = openx;
					pic[i].y = openy;
					openx = tempx;
					openy = tempy;
					break;
				}
			}
		}
		else if(gamepage && mode==2){
			int tempx = (mx / 120) * 120;
			int tempy = (my / 120) * 120;
			if((tempx==openx && abs(tempy-openy)==120) 
			|| (tempy==openy && abs(tempx-openx)==120)){
				for (int i = 1; i < 25; i++)
				{
					if (pic[i].x == tempx && pic[i].y == tempy)
					{
						pic[i].x = openx;
						pic[i].y = openy;
						openx = tempx;
						openy = tempy;
						break;
					}
				}
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		
	}
}

void iKeyboard(unsigned char key) {
	if (key == 'q') {
		exit(0);
	}
	if(namepage) // ENTRY
	{
		if (key != '\b')
		{
			arr[index] = key;
			index++;
			arr[index] = '\0';
		}
		else
		{
			if (index > 0)
			{
				index--;
				arr[index] = '\0';
			}
			else
			{
				index = 0;
			}
		}
	}

	/* if(key == 'k'){
		if(musicon){
			musicon=false;
			PlaySound(0,0,0);
		}else{
			musicon=true;
			PlaySound("bg_music.wav", NULL, SND_ASYNC);
		}
	} */
}

void iSpecialKeyboard(unsigned char key) {
	if (key == GLUT_KEY_END) {
		exit(0);
	}
}

void drawnamepage(){
	iSetColor(20, 200, 200);
	iFilledRectangle(400,150,200,80);

	iSetColor(0, 0, 0);

	iText(420, 190, "START GAME",GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(255, 255, 255);
     iFilledRectangle(300, 500, 300, 60);

     iSetColor(0, 255, 0);

     iText(375, 450, "YOUR NAME", GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(0, 0, 0);
     iText(395, 520, arr, GLUT_BITMAP_TIMES_ROMAN_24);
     iText(395 + 11 * index, 520, "_", GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawStartPage(){
	iSetColor(20, 200, 0);
	iFilledRectangle(400,450,200,80);

	iSetColor(20, 200, 200);
	iFilledRectangle(400,150,200,80);

	iSetColor(0, 0, 0);

	iText(420, 190, "Hard mode",GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(0, 0, 0);

	iText(420, 490, "Easy MOde",GLUT_BITMAP_TIMES_ROMAN_24);
}

void drawInstPage(){
	/* iSetColor(200, 200, 200);
	iText(320, 490, "***EKHANE GAME ER INSTRUCTIONS THAKBE***",GLUT_BITMAP_TIMES_ROMAN_24); */
	iSetColor(128,128,128);
	//iFilledRectangle(0,0,1000,600);
	iShowBMP2(300,50,"image\\inst.bmp",0);
	iShowBMP2(5,500,"image\\back.bmp",0);
}

void drawwinpage(){
	/* iSetColor(200, 200, 200);
	iText(320, 490, "***YOU WON***",GLUT_BITMAP_TIMES_ROMAN_24); */
	int y_co = 240;
	iText(350, 250, "NAME", GLUT_BITMAP_TIMES_ROMAN_24);
	iLine(350, y_co, 420, y_co);
	iText(500, 250, "MOVES", GLUT_BITMAP_TIMES_ROMAN_24);
	iLine(500, y_co, 590, y_co);
	iSetColor(255, 192, 203);

	FILE *ifp = fopen("score.txt", "r");
	if (ifp == NULL)
		printf("Cant open ifp");
	else
	{
		for (int i = 0; i < 3; i++)
		{
			char name[150];
			char point[10];
			int v;
			fgets(name, 200, ifp);
			fgets(point, 8, ifp);

			iText(350, 200 - i * 50, name, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(520, 200 - i * 50, point, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		fclose(ifp);
	}
}



void BackButtonClickHandler(){
	homepage=true;
	startpage=false;
	instpage=false;
}


void drawHomePage(){
	iSetColor(128,128,128);
	iFilledRectangle(0,0,1000,600);
	iShowBMP2(0,0,"image\\start.bmp",0);

	iSetColor(20, 200, 0);
	iFilledRectangle(400,450,200,80);

	iSetColor(20, 200, 200);
	iFilledRectangle(400,150,200,80);

	iSetColor(0, 0, 0);

	iText(420, 190, "INSTRUCTIONS",GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(0, 0, 0);

	iText(420, 490, "START GAME",GLUT_BITMAP_TIMES_ROMAN_24);
}

void location_change()
{
	int a = 2, b = 25;
	int box[6];
	srand(time(NULL));

	for (int i = 0; i < 6; i++)
	{
		box[i] = rand() % (b - a) + a;
	label:
		for (int j = 0; j < i; j++)
		{
			if (box[i] == box[j])
			{
				box[i] = rand() % (b - a) + a;
				goto label;
			}
		}
		printf("%d\n", box[i]);
	}
	for (int i = 0; i < 6; i = i + 2)
	{
		pic[box[i]].x = correct_pic[box[i + 1]].x;
		pic[box[i]].y = correct_pic[box[i + 1]].y;
		printf("%d got %d's coordinates\n",box[i],box[i+1]);
		pic[box[i + 1]].x = correct_pic[box[i]].x;
		pic[box[i + 1]].y = correct_pic[box[i]].y;
	}
}

void coordinates()
{
	int n = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			pic[n].x = 0 + j * 120; // storing real addresses
			pic[n].y = 480 - i * 120;
			correct_pic[n].x = pic[n].x; // storing real addresses
			correct_pic[n].y = pic[n].y;
			n++;
		}
	}
}

void check_pic()
{
	int n = 1;
	correct = true;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 0 && j == 0)
				continue;
			else
			{
				if (pic[n].x != correct_pic[n].x)
				{
					correct = false;
					break;
				}
				if (pic[n].y != correct_pic[n].y)
				{
					correct = false;
					break;
				}
				n++;
			}
		}
	}
}

void musicplay(int music){
	if(music){
		PlaySoundA("The_Painful_Way.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}else{
		PlaySoundA( NULL,NULL,NULL);
	}
}

int main() {
	musicplay(musicon);
	//coordinates();
	//location_change();
	iInitialize(1000, 600, "Page title");
	return 0;
}
