#ifndef __head_h__
#define __head_h__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>


#define WIDE 60
#define HIGH 20
#define MAX_SCORE 58*17

COORD coord;

int start_X = 0;
int start_Y = 0;
int score = 0;
int speed = 200;
char user_name[21];
int users_num = 0;

char after_input = 0;

//游戏开始用户选择
char choise = 0;

//创建蛇和食物结构体
struct BODY
{
	int X;
	int Y;
};

struct SNAKE
{
	int size;
	struct BODY body[MAX_SCORE];
}snake;

struct FOOD
{
	int X;
	int Y;
}food;

//定义一个结构体保存用户的分数

struct Users
{
	char name[20];
	int score;
}users[1024];

void menu(void);

int user_name_get(void);

void game_menu(void);

void init_snake(void);

void init_food(void);

void paint_snake(void);

void paint_food(void);

void game_start(void);

void user_score_get(void);

void all_score_get(void);

void users_sort(void);

void users_paint(void);


#endif