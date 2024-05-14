#include<windows.h>
#include<conio.h>
#include<time.h>
#include<iostream>
#include<cstring>
#include "mylib.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <mmsystem.h>
#define MAX 10000
using namespace std;

//xac dinh ran
int x[MAX], y[MAX];
int xqua = 0;
int yqua = 0;
int x10 = 200, y10 = 100;
int xo = 50, yo = 13;

//chieu dai ran
int dai = 4;

//map
int xm1 = 10;
int ym1 = 1;
int xm2 = 100;
int ym2 = 26;

//diem
long long score = 0;
int checkscore = 0;

//toc do ran
double tocdo = 150;
double vtmp = 150;


//dem so buoc di chuyen cua ran
unsigned long long dem = 0;

//gia toc ran
int giatoc = 0;

int dem10 = 0;
int no10 = 0;
int xoa10 = 0;

//cac gia tri check tuong ung
int check = 2;
int checkmap = 0;
int checkmode = 0;
int mode1 = 0;

//pause game
int cp = 0;

//snake setting
int colors = 2;
char head = 'O';
char mid1 = 'o';
char mid2 = 248;

// menu
void menu();
void huongdan();
void level();
void setting();
void pause(int xqua, int yqua, int x10, int y10, int& cp);
void snakecolor();
void Map();
void spmap(int& xo, int& yo);
void headsnake();
void mid();
void background();
void mode();
void mod1();
void drawsnake();
void highscore(int& checkscore);
void playgame(int& xo, int& yo, int& xqua, int& yqua, int& x10, int& y10, int& giatoc, unsigned long long& dem, long long& score);
void highread();

//ve
void vetuong();
void outgame();
void drawingame();
void drawmutantsnake();

//diem so nguoi choi
void diem();

//ran
void taoran(int x[], int y[]);
void veran(int x[], int y[]);
void xoaran(int x[], int y[]);
void them(int a[], int moi);
void xoa(int a[], int bo);
void xuliran(int x[], int y[], int& xo, int& yo, int& xqua, int& yqua, int& x10, int& y10, int& giatoc);
void dichuyen(int& xo, int& yo);
void tangtoc(double& tocdo, int& giatoc);

//cac loai qua
bool dequa(int x[], int y[], int xqua, int yqua);
void qua(int& xqua, int& yqua, int x[], int y[]);
void qua10(int& x10, int& y10, int x[], int y[], int xqua, int yqua);
void xoadi10(int& x10, int& y10, int& dem10);
bool quadequa(int x10, int y10, int xqua, int yqua);
bool anqua(int x[], int y[], int xqua, int yqua);

//choi xong
bool gameover(int x[], int y[]);
void reset(int x[], int y[], int& xo, int& yo, int& xqua, int& yqua, int& x10, int& y10, int& giatoc, int& dem10, int& no10, int& xoa10, int& check, int& mode1, unsigned long long& dem);
void resetmang();

int main() {
	system("mode con cols=130 lines=30");
	PlaySound(TEXT("soundeffect.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	do {
		ShowCur(false);
		resetmang();
		check = 2;
		menu();
		system("cls");
		vetuong();
		taoran(x, y);
		veran(x, y);
		srand(time(NULL));
		qua(xqua, yqua, x, y);
		int xo = 50, yo = 13;
		playgame(xo, yo, xqua, yqua, x10, y10, giatoc, dem, score);
		if (cp != 0) {
			reset(x, y, xo, yo, xqua, yqua, x10, y10, giatoc, dem10, no10, xoa10, check, mode1, dem);
			system("cls");
			cp = 0;
			continue;
		}
		outgame();
		reset(x, y, xo, yo, xqua, yqua, x10, y10, giatoc, dem10, no10, xoa10, check, mode1, dem);
		system("cls");
	} while (true);
	return 0;
}
void vetuong()
{
	char a = 176;
	int xt = xm1, yt = ym1;
	while (xt <= xm2)
	{
		gotoxy(xt, yt);
		cout << a;
		xt++;
	}
	xt = xm1;
	yt = ym2;
	while (xt <= xm2)
	{
		gotoxy(xt, yt);
		cout << a;
		xt++;
	}
	yt = ym1;
	xt = xm2;
	while (yt <= ym2)
	{
		gotoxy(xt, yt);
		cout << a;
		yt++;
	}
	xt = xm1;
	yt = ym1;
	while (yt <= ym2)
	{
		gotoxy(xt, yt);
		cout << a;
		yt++;
	}
	if (checkmode == 1) {
		gotoxy(105, 3);
		cout << "Hungry point:";
	}
	gotoxy(105, 5);
	cout << "Speed:";
	setcolor(10);
	gotoxy(111, 5);
	cout << 160 - tocdo;
	drawingame();
}
void taoran(int x[], int y[])
{
	int xo = 50, yo = 13;
	for (int i = 0; i < dai; i++)
	{
		x[i] = xo;
		y[i] = yo;
		xo--;
	}
}
void veran(int x[], int y[])
{
	setcolor(colors);
	for (int i = 0; i < dai; i++)
	{
		if (i == 0) {
			gotoxy(x[i], y[i]);
			cout << head;
		}
		else
		{
			gotoxy(x[i], y[i]);
			if (dem % 2 == 0)
			{
				// uon luon ran 
				if (i % 2 == 0)
					cout << mid1;
				else
					cout << mid2;
			}
			else
			{
				if (i % 2 == 1)
					cout << mid1;
				else
					cout << mid2;
			}
		}
	}
}
void xoaran(int x[], int y[])
{
	gotoxy(x[dai - 1], y[dai - 1]);
	cout << " ";
}
void them(int a[], int moi)
{
	//them dau ran
	for (int i = dai; i > 0; i--)
	{
		a[i] = a[i - 1];
	}
	a[0] = moi;
	dai++;
}
void xoa(int a[], int bo) {
	//bo phan duoi ran
	for (int i = bo; i < dai; i++)
	{
		a[i] = a[i + 1];
	}
	dai--;
}
void xuliran(int x[], int y[], int& xo, int& yo, int& xqua, int& yqua, int& x10, int& y10, int& giatoc) {
	them(x, xo);
	them(y, yo);
	mod1();
	if (score % 5 == 0 && score > 0 && dem10 == 0 && no10 == 0)
	{
		qua10(x10, y10, x, y, xqua, yqua);
		dem10++;
		xoa10 = dem;
	}
	xoadi10(x10, y10, dem10);
	/**no10 ngan an qua10 xong k bi tao qua10 tiep
	dem10 ngan k tao qua lien tuc trong moi buoc di chuyen
	xoa10 de xoa qua trong 50 buoc**/
	if (anqua(x, y, xqua, yqua) == false && anqua(x, y, x10, y10) == false)
	{
		xoa(x, dai - 1);
		xoa(y, dai - 1);
	}
	else if (anqua(x, y, xqua, yqua) == true)
	{
		qua(xqua, yqua, x, y);
		score += 1;
		if (checkmode == 2) {
			dai += 2;
		}
		dai--;
		Beep(300, 5);
		no10 = 0;
		giatoc++;
	}
	else
	{
		giatoc++;
		Beep(10000, 5);
		score += 10;
		if (checkmode == 2) {
			dai += 4;
		}
		dem10 = 0;
		no10++;
		gotoxy(105, 1);
		cout << "                 ";
		x10 = 200;
		y10 = 100;
	}
	veran(x, y);
	tangtoc(tocdo, giatoc);
}
void dichuyen(int& xo, int& yo)
{
	//0 : xuong
	//1 : len
	//2 : phai
	//3 : trai
	if (_kbhit())
	{
		//kiem tra nhap
		char k = _getch();
		if (k == 'p')
		{
			pause(xqua, yqua, x10, y10, cp);
		}
		if (k == 'c')
		{
			system("cls");
			system("continue");
		}
		if (k == 'w')
		{
			if (check != 1)
				check = 0;
		}
		else if (k == 's')
		{
			if (check != 0)
				check = 1;
		}
		else if (k == 'd')
		{
			if (check != 3)
				check = 2;
		}
		else if (k == 'a')
		{
			if (check != 2)
				check = 3;
		}
	}
	if (checkmap == 1) {
		spmap(xo, yo);
	}
	if (check == 0)
	{
		yo--;
	}
	else if (check == 1)
	{
		yo++;
	}
	else if (check == 2)
	{
		xo++;
	}
	else if (check == 3)
	{
		xo--;
	}
}
bool gameover(int x[], int y[])
{
	if (checkmode == 1) {
		if (mode1 >= 200) {
			return true;
		}
	}
	if (checkmap == 0 || checkmap == 2) {
		if (x[0] == xm1 || x[0] == xm2 || y[0] == ym1 || y[0] == ym2)
		{
			return true;
		}
	}
	for (int i = 1; i < dai; i++)
	{
		if (x[0] == x[i] && y[0] == y[i])
			return true;
	}
	if (dem < 10) return false;
	return false;
}
bool dequa(int x[], int y[], int xqua, int yqua)
{
	// kiem tra xem qua tao ra co de len ran khong
	for (int i = 0; i < dai; i++)
	{
		if (x[i] == xqua && y[i] == yqua)
			return true;
	}
	return false;
}
void qua(int& xqua, int& yqua, int x[], int y[])
{
	//tao qua
	char a = 15;
	setcolor(14);
	do {
		xqua = rand() % (xm2 - xm1 - 2) + (xm1 + 1);;
		yqua = rand() % (ym2 - ym1 - 2) + (ym1 + 1);;
	} while (dequa(x, y, xqua, yqua) == true);
	gotoxy(xqua, yqua);
	cout << a;
	setcolor(7);
}
bool anqua(int x[], int y[], int xqua, int yqua)
//kiem tra xem ran an qua khong
{
	if (x[0] == xqua && y[0] == yqua) {
		return true;
	}
	return false;
}
void menu()
{
	drawsnake();
	drawmutantsnake();
	char p2 = 17;
	char p1 = 16;
	int xo = 59, yo = 6;
	char k = 0;
	setcolor(10);
	setcolor(3);
	gotoxy(62, 19);
	cout << "MENU";
	setcolor(11);
	gotoxy(62, 20);
	cout << "PLAY";
	gotoxy(59, 21);
	cout << "HOW TO PLAY";
	gotoxy(62, 22);
	cout << "LEVEL";
	gotoxy(61, 23);
	cout << "SETTING";
	gotoxy(60, 24);
	cout << "HIGH SCORE";
	int yd = yo + 14;
	gotoxy(xo - 5, yd);
	cout << p1;
	gotoxy(xo + 15, yd);
	cout << p2;
	do {
		if (_kbhit()) {
			gotoxy(xo - 5, yd);
			cout << " ";
			gotoxy(xo + 15, yd);
			cout << " ";//xoa mui ten cu
			k = _getch();
			if (k == 72) {
				yd--;
			}
			else  if (k == 80) {
				yd++;
			}
			else cout << "";
			if (yd < 20) {
				yd = 24;
			}
			else if (yd > 24) {
				yd = 20;
			}
			gotoxy(xo - 5, yd);//tao mui ten moi
			cout << p1;
			gotoxy(xo + 15, yd);
			cout << p2;
		}
	} while (k != 13);
	Beep(3000, 5);
	k = 1;
	if (yd == 20) {
		return;
	}
	else if (yd == 21) {
		huongdan();
	}
	else if (yd == 22) {
		level();
	}
	else if (yd == 23) {
		setting();
	}
	else if (yd == 24) {
		highread();
	}
}
void huongdan()
{
	system("cls");
	setcolor(3);
	gotoxy(56, 4);
	cout << "HOW TO PLAY?";
	setcolor(11);
	gotoxy(59, 6);
	cout << "NORMAL";
	gotoxy(59, 8);
	cout << "HUNGRY";
	gotoxy(59, 10);
	cout << "GROWTH";
	gotoxy(60, 12);
	cout << "BACK";
	char p2 = 17;
	char p1 = 16;
	int xd = 66, yd = 6;
	gotoxy(xd - 15, yd);
	cout << p1;
	gotoxy(xd + 6, yd);
	cout << p2;
	char phim = 0;
	do {
		if (_kbhit()) {
			gotoxy(xd - 15, yd);
			cout << " ";
			gotoxy(xd + 6, yd);
			cout << " ";
			//xoa mui ten cu
			phim = _getch();
			if (phim == 72) {
				yd -= 2;
			}
			else  if (phim == 80) {
				yd += 2;
			}
			else cout << "";
			if (yd < 6) {
				yd = 12;
			}
			else if (yd > 12) {
				yd = 6;
			}
			gotoxy(xd - 15, yd);
			//tao mui ten moi
			cout << p1;
			gotoxy(xd + 6, yd);
			cout << p2;
		}
	} while (phim != 13);
	Beep(3000, 5);
	system("cls");
	if (yd == 6) {
		setcolor(3);
		gotoxy(45, 5);
		cout << "NORMAL MODE";
		setcolor(11);
		gotoxy(10, 7);
		cout << "Control the snake with the corresponding WASD buttons up, down, left, and right to hunt.";
		gotoxy(10, 8);
		cout << "If the snake bites its tail or hits its head against the wall, the game is over.";
		gotoxy(10, 9);
		cout << "Every time you eat 5 normal baits, a special bait will appear, and when eaten, you will get 10 points.";
		gotoxy(10, 10);
		cout << "The special bait will disappear after 100 moves.";
		gotoxy(10, 11);
		cout << "Press p to pause game.";
		gotoxy(10, 12);
		cout << "Press enter to return." << endl;
		char enter;
		while (1)
		{
			enter = _getch();
			if (enter == 13)
				break;
		}
		Beep(3000, 5);
		system("cls");
		huongdan();
	}
	if (yd == 8) {
		setcolor(3);
		gotoxy(45, 5);
		cout << "HUNGRY MODE";
		setcolor(11);
		gotoxy(10, 7);
		cout << "The game rules are similar to normal mode.";
		gotoxy(10, 8);
		cout << "If the snake does not eat its bait after 100 moves, the game is over.";
		gotoxy(10, 9);
		cout << "Press enter to return.";
		char enter;
		while (1)
		{
			enter = _getch();
			if (enter == 13)
				break;
		}
		Beep(3000, 5);
		system("cls");
		huongdan();
	}
	if (yd == 10) {
		setcolor(3);
		gotoxy(45, 5);
		cout << "GROWTH MODE";
		setcolor(11);
		gotoxy(10, 7);
		cout << "Snakes will grow stronger than normal mode.";
		gotoxy(10, 8);
		cout << "After the snake eats normal bait, 3 more segments will be added.";
		gotoxy(10, 9);
		cout << "After the snake eats special bait, 5 more segments will be added.";
		gotoxy(10, 10);
		cout << "Press enter to return." << endl;
		char enter;
		while (1)
		{
			enter = _getch();
			if (enter == 13)
				break;
		}
		Beep(3000, 5);
		system("cls");
		huongdan();
	}
	if (yd == 12) menu();
	system("cls");
}
void diem()
{
	setcolor(14);//in ra man hinh diem 
	gotoxy(0, 0);
	cout << "Your score is:" << score;
	setcolor(7);
	mod1();
}
void tangtoc(double& tocdo, int& giatoc) {
	if (tocdo >= 20 && giatoc % 5 == 0 && giatoc > 0) {
		tocdo -= 5;
		giatoc = 0;
		setcolor(10);
		gotoxy(111, 5);
		cout << 160 - tocdo;
	}
}
void level()
{
	char p2 = 17;
	char p1 = 16;
	system("cls");
	setcolor(3);
	gotoxy(60, 4);
	cout << "LEVEL" << endl;
	setcolor(11);
	gotoxy(60, 7);
	cout << "EASY";
	gotoxy(59, 9);
	cout << "NORMAL" << endl;
	gotoxy(60, 11);
	cout << "HARD" << endl;
	int xd = 66, yd = 7;
	gotoxy(xd - 15, yd);
	cout << p1;
	gotoxy(xd + 6, yd);
	cout << p2;
	char phim = 0;
	do {
		if (_kbhit()) {
			gotoxy(xd - 15, yd);
			cout << " ";
			gotoxy(xd + 6, yd);
			cout << " ";
			//xoa mui ten cu
			phim = _getch();
			if (phim == 72) {
				yd-=2;
			}
			else  if (phim == 80) {
				yd+=2;
			}
			else cout << "";
			if (yd < 7) {
				yd = 11;
			}
			else if (yd > 11) {
				yd = 7;
			}
			gotoxy(xd - 15, yd);
			//tao mui ten moi
			cout << p1;
			gotoxy(xd + 6, yd);
			cout << p2;
		}
	} while (phim != 13);
	Beep(3000, 5);
	if (yd == 7) tocdo = 150;
	else if (yd == 9) tocdo = 100;
	else if (yd == 11) tocdo = 60;
	vtmp = tocdo;
	system("cls");
	menu();
}
void qua10(int& x10, int& y10, int x[], int y[], int xqua, int yqua)
{
	char b = 21;
	int check = 0;
	do {
		x10 = rand() % (xm2 - xm1 - 2) + (xm1 + 1);
		y10 = rand() % (ym2 - ym1 - 2) + (ym1 + 1);
		if (x10 == xqua && y10 == yqua) {
			check = 1;
		}
		if (dequa(x, y, x10, y10) == true) {
			check = 1;
		}
		if (check == 0) {
			setcolor(13);
			gotoxy(x10, y10);
			cout << b;
		}
	} while (check == 1);
	//tao qua 10
}
void xoadi10(int& x10, int& y10, int& dem10)
{
	if (dem - xoa10 == 100) {
		xoa10 = 0;
		gotoxy(x10, y10);
		cout << " ";
		//xoa qua10
		x10 = 0;
		y10 = 1;
		dem10 = 0;
		no10++;
		gotoxy(102, 1);
		cout << "                ";
		//xoa phan ghi diem so
	}
	else if (dem10 > 0 && dem - xoa10 < 100) {
		setcolor(11);
		gotoxy(105, 1);
		cout << "Special bait:";
		setcolor(9);
		gotoxy(118, 1);
		cout << dem - xoa10;
		//in ra thoi diem con ma qua 10 se bien mat
	}
}
void reset(int x[], int y[], int& xo, int& yo, int& xqua, int& yqua, int& x10, int& y10, int& giatoc, int& dem10, int& no10, int& xoa10, int& check, int& mode1, unsigned long long& dem)
{
	resetmang();
	xqua = 0;
	yqua = 0;
	x10 = 20, y10 = 10;
	xo = 50, yo = 13;
	dai = 4;
	score = 0;
	dem = 0;
	giatoc = 0;
	dem10 = 0;
	no10 = 0;
	xoa10 = 0;
	check = 2;
	mode1 = 0;
	tocdo = vtmp;
}
void outgame()
{
	char a = 219;
	setcolor(10);
	gotoxy(28, 8);
	cout << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a;
	gotoxy(28, 9);
	cout << a << "                                                     " << a;
	gotoxy(28, 10);
	cout << a << "                                                     " << a;
	gotoxy(28, 11);
	cout << a << "                                                     " << a;
	gotoxy(28, 12);
	cout << a << "                                                     " << a;
	gotoxy(28, 13);
	cout << a << "                                                     " << a;
	gotoxy(28, 14);
	cout << a << "                                                     " << a;
	gotoxy(28, 15);
	cout << a << "                                                     " << a;
	gotoxy(28, 16);
	cout << a << "                                                     " << a;
	gotoxy(28, 17);
	cout << a << "                                                     " << a;
	gotoxy(28, 18);
	cout << a << "                                                     " << a;
	gotoxy(28, 19);
	cout << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a;
	gotoxy(50, 11);
	cout << "GAME OVER";
	gotoxy(46, 14);
	cout << "Your score is:" << score;
	highscore(checkscore);
	if (checkscore == 1) {
		gotoxy(35, 13);
		cout << "CONGRATULATIONS! YOU JUST SET A NEW RECORD!";
		checkscore = 0;
	}
	gotoxy(40, 15);
	cout << "Press enter to return to the menu";
	gotoxy(45, 16);
	cout << "Press e to exit game";
	char nhap = 0;
	while (true)
	{
		if (_kbhit()) {
			nhap = _getch();
		}
		if (nhap == 'e') {
			Beep(3000, 5);
			exit(1);
		}
		if (nhap == 13) {
			Beep(3000, 5);
			break;
		}
	}
}
void pause(int xqua, int yqua, int x10, int y10, int& cp)
{
	char a = 219;
	setcolor(10);
	gotoxy(28, 8);
	cout << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a;
	gotoxy(28, 9);
	cout << a << "                                                     " << a;
	gotoxy(28, 10);
	cout << a << "                                                     " << a;
	gotoxy(28, 11);
	cout << a << "                                                     " << a;
	gotoxy(28, 12);
	cout << a << "                                                     " << a;
	gotoxy(28, 13);
	cout << a << "                                                     " << a;
	gotoxy(28, 14);
	cout << a << "                                                     " << a;
	gotoxy(28, 15);
	cout << a << "                                                     " << a;
	gotoxy(28, 16);
	cout << a << "                                                     " << a;
	gotoxy(28, 17);
	cout << a << "                                                     " << a;
	gotoxy(28, 18);
	cout << a << "                                                     " << a;
	gotoxy(28, 19);
	cout << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a;
	gotoxy(52, 12);
	cout << "PAUSE";
	gotoxy(45, 14);
	cout << "Press p to continue";
	gotoxy(43, 16);
	cout << "Press q to back to menu";
	int checkw = 0;
	while (true) {
		char w;
		if (_kbhit()) {
			w = _getch();
			if (w == 'q') {
				cp++;
				break;
			}
			if (w == 'p') {
				break;
			}
		}
	}
	system("cls");
	setcolor(11);
	vetuong();
	char r = 15;
	setcolor(14);
	gotoxy(xqua, yqua);
	cout << r;
	if (score % 5 == 0 && score > 0) {
		char i = 21;
		setcolor(13);
		gotoxy(x10, y10);
		cout << i;
		gotoxy(xqua + 1, yqua);
		cout << " ";
	}
}
void snakecolor() {
	system("cls");
	char a = 248;
	setcolor(3);
	gotoxy(52, 4);
	cout << "CHOOSE COLOR OF SNAKE";
	setcolor(11);
	gotoxy(60, 6);
	setcolor(2);
	cout << mid1 << mid2 << mid1 << head;
	gotoxy(60, 8);
	setcolor(1);
	cout << mid1 << mid2 << mid1 << head;
	gotoxy(60, 10);
	setcolor(3);
	cout << mid1 << mid2 << mid1 << head;
	gotoxy(60, 12);
	setcolor(4);
	cout << mid1 << mid2 << mid1 << head;
	gotoxy(60, 14);
	setcolor(5);
	cout << mid1 << mid2 << mid1 << head;
	gotoxy(60, 16);
	setcolor(6);
	cout << mid1 << mid2 << mid1 << head;
	setcolor(11);
	char p2 = 17;
	char p1 = 16;
	int xd = 66, yd = 6;
	gotoxy(xd - 15, yd);
	cout << p1;
	gotoxy(xd + 6, yd);
	cout << p2;
	char phim = 0;
	do {
		if (_kbhit()) {
			gotoxy(xd - 15, yd);
			cout << " ";
			gotoxy(xd + 6, yd);
			cout << " ";
			//xoa mui ten cu
			phim = _getch();
			if (phim == 72) {
				yd -= 2;
			}
			else  if (phim == 80) {
				yd += 2;
			}
			else cout << "";
			if (yd < 6) {
				yd = 16;
			}
			else if (yd > 16) {
				yd = 6;
			}
			gotoxy(xd - 15, yd);
			//tao mui ten moi
			cout << p1;
			gotoxy(xd + 6, yd);
			cout << p2;
		}
	} while (phim != 13);
	Beep(3000, 5);
	if (yd == 6) colors = 2;
	else if (yd == 8) colors = 1;
	else if (yd == 10) colors = 3;
	else if (yd == 12) colors = 4;
	else if (yd == 14) colors = 5;
	else if (yd == 16) colors = 6;
	system("cls");
	setting();
}
void Map() {
	system("cls");
	setcolor(3);
	gotoxy(60, 4);
	cout << "MAP";
	setcolor(11);
	gotoxy(57, 6);
	cout << "DETENTION";
	gotoxy(56, 8);
	cout << "ENDLESS LOOP";
	gotoxy(59, 10);
	cout << "MINI";
	char p2 = 17;
	char p1 = 16;
	int xd = 66, yd = 6;
	gotoxy(xd - 15, yd);
	cout << p1;
	gotoxy(xd + 6, yd);
	cout << p2;
	char phim = 0;
	do {
		if (_kbhit()) {
			gotoxy(xd - 15, yd);
			cout << " ";
			gotoxy(xd + 6, yd);
			cout << " ";
			//xoa mui ten cu
			phim = _getch();
			if (phim == 72) {
				yd -= 2;
			}
			else  if (phim == 80) {
				yd += 2;
			}
			else cout << "";
			if (yd < 6) {
				yd = 10;
			}
			else if (yd > 10) {
				yd = 6;
			}
			gotoxy(xd - 15, yd);
			//tao mui ten moi
			cout << p1;
			gotoxy(xd + 6, yd);
			cout << p2;
		}
	} while (phim != 13);
	Beep(3000, 5);
	if (yd == 6) {
		checkmap = 0;
		xm1 = 10;
		xm2 = 100;
		ym1 = 1;
		ym2 = 26;
	}
	if (yd == 8) {
		checkmap = 1;
		xm1 = 10;
		xm2 = 100;
		ym1 = 1;
		ym2 = 26;
	}
	if (yd == 10) {
		checkmap = 2;
		xm1 = 30;
		xm2 = 80;
		ym1 = 5;
		ym2 = 22;
	}
	system("cls");
	setting();
}
void spmap(int& xo, int& yo) {
	if (check == 2 && xo >= 99) {
		xo = 10;
	}
	else if (check == 3 && xo <= 11) {
		xo = 100;
	}
	if (yo >= 25 && check == 1) {
		yo = 1;
	}
	else if (yo <= 2 && check == 0) {
		yo = 26;
	}
}
void setting() {
	system("cls");
	setcolor(3);
	gotoxy(59, 4);
	cout << "SETTING";
	setcolor(11);
	gotoxy(58, 6);
	cout << "COLOR SNAKE";
	gotoxy(58, 8);
	cout << "HEAD SNAKE";
	gotoxy(58, 10);
	cout << "BODY SNAKE";
	gotoxy(58, 12);
	cout << "BACKGROUND";
	gotoxy(61, 14);
	cout << "MAP";
	gotoxy(61, 16);
	cout << "MODE";
	gotoxy(61, 18);
	cout << "BACK";
	char p2 = 17;
	char p1 = 16;
	int xd = 67, yd = 6;
	gotoxy(xd - 15, yd);
	cout << p1;
	gotoxy(xd + 6, yd);
	cout << p2;
	char phim = 0;
	do {
		if (_kbhit()) {
			gotoxy(xd - 15, yd);
			cout << " ";
			gotoxy(xd + 6, yd);
			cout << " ";
			//xoa mui ten cu
			phim = _getch();
			if (phim == 72) {
				yd -= 2;
			}
			else  if (phim == 80) {
				yd += 2;
			}
			else cout << "";
			if (yd < 6) {
				yd = 18;
			}
			else if (yd > 18) {
				yd = 6;
			}
			gotoxy(xd - 15, yd);
			//tao mui ten moi
			cout << p1;
			gotoxy(xd + 6, yd);
			cout << p2;
		}
	} while (phim != 13);
	Beep(3000, 5);
	system("cls");
	if (yd == 6) snakecolor();
	if (yd == 8) headsnake();
	if (yd == 10) mid();
	if (yd == 12) background();
	if (yd == 14) Map();
	if (yd == 16) mode();
	if (yd == 18) menu();
}
void headsnake() {
	char a = 248;
	char head2 = 1;
	char head3 = 2;
	char head4 = 148;
	char head5 = 4;
	system("cls");
	setcolor(3);
	gotoxy(58, 4);
	cout << "HEAD SNAKE";
	setcolor(colors);
	gotoxy(61, 6);
	cout << mid1 << mid2 << mid1 << "O";
	gotoxy(61, 8);
	cout << mid1 << mid2 << mid1 << head2;
	gotoxy(61, 10);
	cout << mid1 << mid2 << mid1 << head3;
	gotoxy(61, 12);
	cout << mid1 << mid2 << mid1 << head4;
	gotoxy(61, 14);
	cout << mid1 << mid2 << mid1 << head5;
	char p2 = 17;
	char p1 = 16;
	setcolor(11);
	int xd = 66, yd = 6;
	gotoxy(xd - 15, yd);
	cout << p1;
	gotoxy(xd + 6, yd);
	cout << p2;
	char phim = 0;
	do {
		if (_kbhit()) {
			gotoxy(xd - 15, yd);
			cout << " ";
			gotoxy(xd + 6, yd);
			cout << " ";
			//xoa mui ten cu
			phim = _getch();
			if (phim == 72) {
				yd -= 2;
			}
			else  if (phim == 80) {
				yd += 2;
			}
			else cout << "";
			if (yd < 6) {
				yd = 14;
			}
			else if (yd > 14) {
				yd = 6;
			}
			gotoxy(xd - 15, yd);
			//tao mui ten moi
			cout << p1;
			gotoxy(xd + 6, yd);
			cout << p2;
		}
	} while (phim != 13);
	Beep(3000, 5);
	system("cls");
	if (yd == 6) head = 'O';
	if (yd == 8) head = head2;
	if (yd == 10) head = head3;
	if (yd == 12) head = head4;
	if (yd == 14) head = head5;
	system("cls");
	setting();
}
void mid() {
	char mid11 = 'o';
	char mid12 = 248;
	char mid21 = 30;
	char mid22 = 31;
	char mid31 = 'x';
	char mid32 = 'x';
	system("cls");
	setcolor(3);
	gotoxy(58, 4);
	cout << "BODY SNAKE";
	setcolor(colors);
	gotoxy(61, 6);
	cout << mid11 << mid12 << mid11 << head;
	gotoxy(61, 8);
	cout << mid21 << mid22 << mid21 << head;
	gotoxy(61, 10);
	cout << mid31 << mid32 << mid31 << head;
	char p2 = 17;
	char p1 = 16;
	setcolor(11);
	int xd = 66, yd = 6;
	gotoxy(xd - 15, yd);
	cout << p1;
	gotoxy(xd + 6, yd);
	cout << p2;
	char phim = 0;
	do {
		if (_kbhit()) {
			gotoxy(xd - 15, yd);
			cout << " ";
			gotoxy(xd + 6, yd);
			cout << " ";
			//xoa mui ten cu
			phim = _getch();
			if (phim == 72) {
				yd -= 2;
			}
			else  if (phim == 80) {
				yd += 2;
			}
			else cout << "";
			if (yd < 6) {
				yd = 10;
			}
			else if (yd > 10) {
				yd = 6;
			}
			gotoxy(xd - 15, yd);
			//tao mui ten moi
			cout << p1;
			gotoxy(xd + 6, yd);
			cout << p2;
		}
	} while (phim != 13);
	Beep(3000, 5);
	system("cls");
	if (yd == 6) {
		mid1 = mid11;
		mid2 = mid12;
	}
	if (yd == 8) {
		mid1 = mid21;
		mid2 = mid22;
	}
	if (yd == 10) {
		mid1 = mid31;
		mid2 = mid32;
	}
	system("cls");
	setting();
}
void background() {
	char a = 219;
	system("cls");
	setcolor(3);
	gotoxy(56, 4);
	cout << "BACK GROUND";
	setcolor(11);
	gotoxy(59, 6);
	cout << "BLACK";
	setcolor(0);
	gotoxy(59, 7);
	cout << a << a << a << a << a;
	setcolor(11);
	gotoxy(59, 8);
	cout << "GRAY ";
	setcolor(8);
	gotoxy(59, 9);
	cout << a << a << a << a << a;
	char p2 = 17;
	char p1 = 16;
	setcolor(11);
	int xd = 66, yd = 6;
	gotoxy(xd - 15, yd);
	cout << p1;
	gotoxy(xd + 6, yd);
	cout << p2;
	char phim = 0;
	do {
		if (_kbhit()) {
			gotoxy(xd - 15, yd);
			cout << " ";
			gotoxy(xd + 6, yd);
			cout << " ";
			//xoa mui ten cu
			phim = _getch();
			if (phim == 72) {
				yd -= 2;
			}
			else  if (phim == 80) {
				yd += 2;
			}
			else cout << "";
			if (yd < 6) {
				yd = 8;
			}
			else if (yd > 8) {
				yd = 6;
			}
			gotoxy(xd - 15, yd);
			//tao mui ten moi
			cout << p1;
			gotoxy(xd + 6, yd);
			cout << p2;
		}
	} while (phim != 13);
	Beep(3000, 5);
	system("cls");
	if (yd == 6) {
		system("color 0b");
	}
	if (yd == 8) {
		system("color 8b");
	}
	system("cls");
	setting();
}
void mode() {
	char a = 219;
	system("cls");
	setcolor(3);
	gotoxy(60, 4);
	cout << "MODE";
	setcolor(11);
	gotoxy(59, 6);
	cout << "NORMAL";
	gotoxy(59, 8);
	cout << "HUNGRY";
	gotoxy(59, 10);
	cout << "GROWTH";
	char p2 = 17;
	char p1 = 16;
	int xd = 66, yd = 6;
	gotoxy(xd - 15, yd);
	cout << p1;
	gotoxy(xd + 6, yd);
	cout << p2;
	char phim = 0;
	do {
		if (_kbhit()) {
			gotoxy(xd - 15, yd);
			cout << " ";
			gotoxy(xd + 6, yd);
			cout << " ";
			//xoa mui ten cu
			phim = _getch();
			if (phim == 72) {
				yd -= 2;
			}
			else  if (phim == 80) {
				yd += 2;
			}
			else cout << "";
			if (yd < 6) {
				yd = 10;
			}
			else if (yd > 10) {
				yd = 6;
			}
			gotoxy(xd - 15, yd);
			//tao mui ten moi
			cout << p1;
			gotoxy(xd + 6, yd);
			cout << p2;
		}
	} while (phim != 13);
	Beep(3000, 5);
	system("cls");
	if (yd == 6) {
		checkmode = 0;
	}
	if (yd == 8) {
		checkmode = 1;
	}
	if (yd == 10) {
		checkmode = 2;
	}
	system("cls");
	setting();
}
void mod1() {
	if (checkmode == 1) {
		mode1++;
		if (anqua(x, y, xqua, yqua) == true || anqua(x, y, x10, y10) == true) {
			mode1 = 0;
		}
		setcolor(12);
		gotoxy(118, 3);
		cout << mode1 / 2;
	}
}
void drawsnake() {
	char a = 219;
	char q = 223;
	char e = 16;
	setcolor(10);
	gotoxy(45, 19);
	cout << "   Y";;
	gotoxy(45, 20);
	cout << " " << a << a << a << a << a << endl;
	gotoxy(45, 21);
	cout << a << "     " << a << endl;
	gotoxy(45, 22);
	cout << a << " " << a << " " << a << " " << a << endl;
	gotoxy(45, 23);
	cout << a << "     " << a << endl;
	gotoxy(45, 24);
	cout << " " << a << a << a << a << a << endl;
	gotoxy(45, 25);
	cout << " " << a << a << a << a << a << endl;
	gotoxy(45, 26);
	cout << "  " << a << a << a << a << a << endl;
	gotoxy(45, 27);
	cout << "  " << a << a << a << a << a << a << "  " << a << a << a << a << a << a << a << "      " << a << a << a << a << a << a << a << endl;
	gotoxy(45, 28);
	cout << "   " << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << a << q << endl;
	gotoxy(45, 29);
	cout << "    " << a << a << a << a << a << a << a << "     " << a << a << a << a << a << a << a << a << "     " << a << a << a << a << a << a << a << a << endl;
}
void resetmang() {
	for (int i = 0; i < 10000; i++) {
		x[i] = 117;
		y[i] = 0;
	}
}
void highscore(int& checkscore) {
	fstream file("scorein.txt");

	if (!file.is_open()) {
		system("cls");
		cout << "NO";
		Sleep(10000);
	}

	vector<long long> numbers;
	long long num;
	for (int i = 0; i < 5; ++i) {
		if (file >> num) {
			numbers.push_back(num);
		}
		else {
			system("cls");
			cout << "NO";
			Sleep(10000);
		}
	}
	for (int i = 0; i < 5; ++i) {
		if (score > numbers[i]) {
			checkscore = 1;
			swap(score, numbers[i]);
			sort(numbers.begin(), numbers.end(), greater<int>());
		}
	}
	file.clear();
	file.seekp(0);
	for (int i = 0; i < 5; ++i) {
		file << numbers[i] << endl;
	}
	file.close();
}
void playgame(int& xo, int& yo, int& xqua, int& yqua, int& x10, int& y10, int& giatoc, unsigned long long& dem, long long& score) {
	while (gameover(x, y) == false) {
		dem++;
		dichuyen(xo, yo);
		xoaran(x, y);
		xuliran(x, y, xo, yo, xqua, yqua, x10, y10, giatoc);
		diem();
		Sleep(tocdo);
		if (cp != 0) {
			break;
		}
	}
}
void drawingame() {
	char x = 92;
	gotoxy(101, 10);
	cout << "     ---_ ......._-_--." << endl;
	gotoxy(101, 11);
	cout << "    (O" << x << " /      / /O " << x << "  " << x << endl;
	gotoxy(101, 12);
	cout << "    /  /     .'  -=-'   `." << endl;
	gotoxy(101, 13);
	cout << "   /  /    .'             )" << endl;
	gotoxy(101, 14);
	cout << " _/  /   .'        _.)   /" << endl;
	gotoxy(101, 15);
	cout << "/ o   o        _.-' /  .'" << endl;
	gotoxy(101, 16);
	cout << x << "          _.-'    / .'*" << "|" << endl;
	gotoxy(101, 17);
	cout << " " << x << "______.-'//    .'.' " << x << "*|" << endl;
	gotoxy(101, 18);
	cout << "   " << x << "| " << x << " | //   .'.' _ |*|" << endl;
	gotoxy(101, 19);
	cout << "       " << x << "|/  .'.'_ _ _||" << endl;
	gotoxy(101, 20);
	cout << "        // .'.' | _ _ " << x << "*|" << endl;
	gotoxy(101, 21);
	cout << "        |" << x << "_/ /    " << x << " _ _ " << x << "*" << x << endl;
	gotoxy(101, 22);
	cout << "         " << x << "__/      " << x << " _ _ " << x << "*" << x << endl;
	gotoxy(101, 23);
	cout << "                    " << x << " _ _ " << x << "*" << endl;
	gotoxy(101, 24);
	cout << "                     " << x << " _ _ " << x << endl;
	gotoxy(101, 25);
	cout << "                      " << x << " _ _" << endl;
}
void highread() {
	system("cls");
	fstream file("scorein.txt");

	if (!file.is_open()) {
		system("cls");
		cout << "ERROR";
		Sleep(10000);
	}

	vector<long long> numbers;
	long long num;
	for (int i = 0; i < 5; ++i) {
		if (file >> num) {
			numbers.push_back(num);
		}
		else {
			system("cls");
			cout << "ERROR";
			Sleep(10000);
		}
	}
	char p2 = 17;
	char p1 = 16;
	setcolor(3);
	gotoxy(58, 4);
	cout << "HIGH SCORE";
	setcolor(14);
	gotoxy(60, 6);
	cout << "1. "<<numbers[0];
	setcolor(15);
	gotoxy(60, 8);
	cout << "2. "<<numbers[1];
	setcolor(6);
	gotoxy(60, 10);
	cout << "3. "<<numbers[2];
	setcolor(11);
	gotoxy(60, 12);
	cout << "4. "<<numbers[3];
	gotoxy(60, 14);
	cout << "5. "<<numbers[4];
	gotoxy(53, 16);
	cout << p1<<"       BACK       "<<p2;
	while (true) {
		if (_kbhit()) {
			char nhap = _getch();
			if (nhap == 13) break;
		}
	}
	system("cls");
	menu();
}
void drawmutantsnake() {
	char a = 219;
	char s = 223;
	char t = 254;
	char f = 221;
	gotoxy(5, 3);
	cout << a << a << a << a<<"                                                     "<<t;
	gotoxy(5, 4);
	cout << a << a << a << a<<"                                              "<<a<<a;
	gotoxy(124, 7);
	cout << a << f<<"    "<<t;
	gotoxy(17, 2);
	cout << t<<"      "<<a<<a<<"                           "<<t<<a<<a;
	gotoxy(115, 7);
	cout << a << a << a << a << "   " << t;
	gotoxy(115, 8);
	cout << a << a << a << a << "        " << a << a;
	gotoxy(25, 14);
	cout << a << a << a << a<<"                                                                                     "<<a<<a<<"    "<<t;
	gotoxy(25, 15);
	cout << a << a << a << a<<"                                                                                          "<<t<<"  "<<a<<a;
	gotoxy(3, 12);
	cout << a << a << a << a << "                                                                                     " << t<<a<<a;
	gotoxy(3, 12);
	cout << a << a << a << a << "                                                                                            " << a<<a<<"  "<<t;
	gotoxy(3, 8);
	cout << a << a << a << a << "    " << t << "                                                                            " << a << a << "    " << t;
	gotoxy(3, 9); 
	cout << a << a << a << a << "  " << t << "                                                                                              " << a << a << "     " << t;
	gotoxy(119, 11);
	cout << a << a << a << a;
	gotoxy(109, 2);
	cout << a << a << a << a;
	gotoxy(109, 3);
	cout << a << a << a << a<<"   "<<a;
	gotoxy(113, 0);
	cout << t<<"      "<<a<<a;
	gotoxy(15, 1);
	cout << a << a << a << a << "    " << t<<"       "<<t;
	gotoxy(15, 2);
	cout << a << a << a << a<<"    "<<a<<a;
	gotoxy(100, 4);
	cout << a << a << a << a<<"  "<<a<<a;
	gotoxy(100, 5);
	cout << a << a << a << a << " " << t;
	gotoxy(2, 6);
	cout << t << "     " << a << a << a << a << "    " << a << a ;
	gotoxy(8, 7);
	cout << a << a << a << a;
	gotoxy(127, 0);
	cout << t;
	gotoxy(2, 0);
	cout << t << "        " << a << a;
	gotoxy(0, 15);
	cout <<t<<"         "<< a << a << a << a;
	gotoxy(10, 16);
	cout << a << a << a << a;
	gotoxy(3, 7);
	cout << t << "        " << t;
	gotoxy(30, 1);
	cout << a << "         " << a << " " << a << a << "       " << a << a << " " << a << a << a << a << a << a << a << a << a << a << " " << "   " << a << a << a << "     " << a << a << a << "      " << a << a << " " << a << a << a << a << a << a << a << a << a << a;
	gotoxy(30, 2);
	cout << a << a << "       " << a << a << " " << a << a << "       " << a << a << " " << "    " << a << "    " << " " << "   " << a << "   " << a << "    " << a << a << a << a << "     " << a << a << " " << "    " << a << "    ";
	gotoxy(30, 3);
	cout << a << " " << a << "     " << a << " " << a << " " << a << a << "       " << a << a << " " << "    " << a << "    " << " " << "  " << a << "     " << a << "   " << a << a << " " << a << "     " << a << a << " " << "    " << a << "    ";
	gotoxy(30, 4);
	cout << a << "  " << a << "   " << a << "  " << a << " " << a << a << "       " << a << a << " " << "    " << a << "    " << "  " << a << "       " << a << "  " << a << a << "  " << a << "    " << a << a << " " << "    " << a << "    ";
	gotoxy(30, 5);
	cout << a << "   " << a << " " << a << "   " << a << " " << a << a << "       " << a << a << " " << "    " << a << "    " << " " << a << a << a << a << a << a << a << a << a << a << a << " " << a << a << "   " << a << "   " << a << a << " " << "    " << a << "    ";
	gotoxy(30, 6);
	cout << a << "    " << a << "    " << a << " " << a << a << "       " << a << a << " " << "    " << a << "    " << " " << a << "         " << a << " " << a << a << "    " << a << "  " << a << a << " " << "    " << a << "    ";
	gotoxy(30, 7);
	cout << a << "         " << a << " " << " " << a << a << a << "   " << a << a << a << " " << "     " << a << "     " << a << "         " << a << " " << a << a << "     " << a << a << a << a << " " << "    " << a << "    ";
	gotoxy(30, 8);
	cout << a << "         " << a << " " << "   " << a << a << a << a << a << "   " << " " << "    " << a << "     " << a << "         " << a << " " << a << a << "      " << a << a << a << " " << "    " << a << "    ";
	gotoxy(36, 10);
	cout << " " << a << a << a << a << a << a << a << "  " << a << a << a << "      " << a << a << " " << "    " << a << a << a << "     " << a << a << "      " << a << a << " " << a << a << a << a << a << a << a << a << a << a;
	gotoxy(36, 11);
	cout  << a << a << "        " << a << a << a << a << "     " << a << a << " " << "   " << a << "   " << a << "    " << a << a << "     " << a << a << "  " << a;
	gotoxy(36, 12);
	cout  << a << "         " << a << a << " " << a << "     " << a << a << " " << "  " << a << "     " << a << "   " << a << a << "    " << a << a << "   " << a;
	gotoxy(36, 13);
	cout << " " << a << a << a << a << a << a << a << "  " << a << a << "  " << a << "    " << a << a << " " << " " << a << "       " << a << "  " << a << a << "   " << a << a << "    " << a << a << a << a << a << a << a << a << a << a;
	gotoxy(36, 14);
	cout << "       " << a << a << " " << a << a << "   " << a << "   " << a << a << " " << a << a << a << a << a << a << a << a << a << a << a << " " << a << a << a << a << a << a << "     " << a;
	gotoxy(36, 15);
	cout << a << a << "     " << a << a << " " << a << a << "    " << a << "  " << a << a << " " << a << "         " << a << " " << a << a << "   " << a << a << "    " << a << "         ";
	gotoxy(36, 16);
	cout << " " << a << a << a << a << a << a << a << "  " << a << a << "     " << a << a << a << a << " " << a << "         " << a << " " << a << a << "    " << a << a << "   " << a << "         ";
	gotoxy(36, 17);
	cout << " " << s << s << s << s << s << s << s << "  " << a << a << "      " << a << a << a << " " << a << "         " << a << " " << a << a << "     " << a << a << "  " << a << a << a << a << a << a << a << a << a << a;

}
