#define _CRT_SECURE_NO_WARNINGS
#include "head.h"


int main(void)
{
	//���ù�겻�ɼ�
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	srand(time(NULL));

	while (1)
	{
		score = 0;
		speed = 200;

		system("cls");
		menu();
		if (choise == '1')
		{
			int buf = user_name_get();

			if (buf == -1)
			{
				printf("�û������Ȳ���Ϊ��������λ��\n");
				system("pause");
				continue;
			}
			system("cls");
			//������Ϸ����
			//X 1~59 
			//Y 2~19
			game_menu();

			init_snake();
			init_food();

			paint_snake();
			paint_food();

			game_start();

			//�����������
			coord.X = 0;
			coord.Y = 22;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			printf("GAME OVER!!\n");
			printf("�÷֣�%d\n", score * 10);
			user_score_get();

			printf("�밴Ese������\n");
			while (1)
			{
				char ch1 = _getch();
				if (ch1 == 27)
				{
					break;
				}
			}


		}
		else if (choise == '2')
		{
			system("cls");
			printf("����\t�÷�\n");
			all_score_get();
			printf("____________________________________\n");
			users_sort();
			users_paint();

			system("pause");
			
		}
		else if (choise == '3')
			break;
	}
	return EXIT_SUCCESS;
}

void menu(void)
{
	choise = 0;
	printf("--------------̰ �� ��--------------\n");
	printf("------------�� 1 ��ʼ��Ϸ-----------\n");
	printf("------------�� 2 �鿴����-----------\n");
	printf("------------�� 3 �˳���Ϸ-----------\n");
	choise = _getch();

}

int user_name_get(void)
{
	memset(user_name, 0, 20);
	FILE* fp = fopen("users_score.txt", "a");
	if (!fp)
	{
		perror("fope user_name_get");
		system("pause");
		exit(-1);
	}

	printf("�����������û�����");
	fgets(user_name, 20, stdin);

	if (strlen(user_name) == 1)
	{
		fclose(fp);
		memset(user_name, 0, 21);
		return -1;
	}
	if (strlen(user_name) > 8)
	{
		fclose(fp);
		memset(user_name, 0, 21);

		return -1;
	}

	for (size_t i = 0; i < strlen(user_name); i++)
	{
		fputc(user_name[i], fp);
	}

	fclose(fp);

	return 0;
}


void game_menu(void)
{
	for (size_t i = 0; i < HIGH; i++)
	{
		for (size_t j = 0; j < WIDE; j++)
		{
			if (j == WIDE / 2 - 3 && i == 0)
			{
				printf("̰������Ϸ");
				continue;
			}
			if (j == WIDE - 1 || j == 0)
			{
				if (i == 0)
					continue;
				printf("|");
			}
			else if (i == 1 || i == HIGH - 1)
			{
				printf("_");
			}
			else
				printf(" ");
		}
		printf("\n");
	}
}


void init_snake(void)
{
	snake.size = 2;
	for (size_t i = 0; i < snake.size; i++)
	{
		snake.body[i].X = WIDE / 2 - i;
		snake.body[i].Y = HIGH / 2;
	}
}


void init_food(void)
{	//X 1~59 
	//Y 2~19
	while (1)
	{
		food.X = rand() % 58 + 1;
		food.Y = rand() % 17 + 2;
		for (int i = 0; i < snake.size; i++)
		{
			if (food.X == snake.body[i].X && food.Y == snake.body[i].Y)
			{
				continue;
			}
		}

		break;
	}
}


void paint_snake(void)
{

	for (size_t i = 0; i < snake.size; i++)
	{
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (i == 0)
			printf("@");
		else
			printf("*");
	}
}


void paint_food(void)
{
	coord.X = food.X;
	coord.Y = food.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("#");
}


void game_start(void)
{

	char input = 'd';

	while (1)
	{
		//��¼�仯ǰ��ͷ��λ�ã����ڽ���

		start_X = snake.body[0].X;
		start_Y = snake.body[0].Y;


		while (_kbhit())
		{
			input = _getch();
		}

		switch (input)
		{
		case 'w':
			if (after_input == 's')
			{
				input = after_input;
				continue;
			}
			snake.body[0].Y -= 1;
			after_input = 'w';
			break;
		case 's':
			if (after_input == 'w')
			{
				input = after_input;
				continue;
			}
			snake.body[0].Y += 1;
			after_input = 's';

			break;
		case 'a':
			if (after_input == 'd')
			{
				input = after_input;
				continue;
			}
			snake.body[0].X -= 1;
			after_input = 'a';

			break;
		case 'd':
			if (after_input == 'a')
			{
				input = after_input;
				continue;
			}
			snake.body[0].X += 1;
			after_input = 'd';

			break;
		default:
			input = after_input;
			continue;
		}

		//��ͷ�仯���ж��Ƿ�ײǽ��ײ���÷�

		if (snake.body[0].X == 0 || snake.body[0].X == 59)
			return;
		if (snake.body[0].Y == 1 || snake.body[0].Y == 19)
			return;
		if (snake.size == 2)
		{
			if (snake.body[0].X == snake.body[1].X && snake.body[0].Y == snake.body[1].Y)
				return;
		}

		for (size_t i = 1; i < snake.size; i++)
		{
			if (snake.body[0].X == snake.body[i].X && snake.body[0].Y == snake.body[i].Y)
				return;
		}

		//����Ϊ����� if ���ֻ����������Ż�ִ�У���������ֱ�Ӹ�ֵ�����ִ�о͸��������ֵ

		coord.X = snake.body[snake.size - 1].X;
		coord.Y = snake.body[snake.size - 1].Y;


		if (snake.body[0].X == food.X && snake.body[0].Y == food.Y)
		{
			init_food();
			paint_food();


			//��Ϊ�˹����Ǽ�¼���ƶ�ǰ�����һ��λ�õ�
			//��������if�жϻ�ı� snake.size ��ֵ��������ǰ��¼ 

			//����Ϊ paint_food ���������coord.X Y ��ֵ �����ں���������ô˹���

			coord.X = snake.body[snake.size - 1].X;
			coord.Y = snake.body[snake.size - 1].Y;

			snake.size += 1;

			score += 1;

			if (speed > 50)
				speed -= 10;
		}

		//���ƶ�ǰ�����һλȥ��
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		printf(" ");

		//�����һλȡ��ǰһλ������
		for (size_t i = snake.size - 1; i > 1; i--)
		{

			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;

		}
		snake.body[1].X = start_X;
		snake.body[1].Y = start_Y;

		paint_snake();
		
		Sleep(speed);
	}




}


void user_score_get(void)
{
	FILE* fp = fopen("users_score.txt", "a");
	if (!fp)
	{
		perror("fopen user_score_get");
		system("pause");
		exit(-1);
	}

	fprintf(fp, "%d\n", score * 10);

	fclose(fp);

}


void all_score_get(void)
{
	users_num = 0;
	FILE* fp = fopen("users_score.txt", "r");
	if (!fp)
	{
		perror("open:all_score_get");
		system("pause");
		exit(-1);
	}

	while (!feof(fp))
	{
		//memset(ch, 0, 20);
		fscanf(fp, "%s\n%d\n", users[users_num].name, &users[users_num].score);
		
		users_num++;
	}
	fclose(fp);
}


void users_sort(void)
{
	for (size_t i = 0; i < users_num - 1; i++)
	{
		for (size_t j = 0; j < users_num - 1 - i; j++)
		{
			if (users[j].score < users[j + 1].score)
			{
				struct Users temp = users[j];
				users[j] = users[j + 1];
				users[j + 1] = temp;
			}
		}
	}

	for (size_t j = 0; j < users_num - 1; j++)
	{
		for (size_t k = 0; k < users_num - 1 - j; k++)
		{
			int a = strcmp(users[k + 1].name, users[k].name);
			if (a == 1)
			{
				struct Users temp = users[k];
				users[k] = users[k + 1];
				users[k + 1] = temp;
			}

		}
	}
}


void users_paint(void)
{
	printf("%s\t%d\n", users[0].name, users[0].score);
	for (size_t i = 1; i < users_num; i++)
	{
		int a = strcmp(users[i].name, users[i - 1].name);
		if (a == 0)
		{
			printf("%s\t%d\n", " ", users[i].score);
			continue;
		}
		if (a != 0)
		{
			printf("\n");
		}
		printf("%s\t%d\n", users[i].name, users[i].score);
	}
	printf("\n");


}