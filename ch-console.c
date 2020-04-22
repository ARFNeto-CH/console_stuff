#pragma once
#include "ch-console.h"


int		cls()
{	// limpa a tela no windows, do jeito oficial
	CONSOLE_SCREEN_BUFFER_INFO		info;
	HANDLE		H = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD		origem = { 0,0 };
	int			total;
	if (H == INVALID_HANDLE_VALUE) return -1;
	GetConsoleScreenBufferInfo(H, &info);
	int r = FillConsoleOutputCharacter(H, (TCHAR)' ',
		info.dwSize.X * info.dwSize.Y,
		origem, &total);
	int s = FillConsoleOutputAttribute(
		H, info.wAttributes,
		info.dwSize.X * info.dwSize.Y,
		origem, &total);
	SetConsoleCursorPosition(H, origem);
	return 0;
};	// end cls()


char	choice()
{
	HANDLE		I = GetStdHandle(STD_INPUT_HANDLE);
	int		total = 0;
	typedef struct _INPUT_RECORD Input;
	char	c;
	Input	buffer[2];
	int n = PeekConsoleInput(I, buffer, 2, (LPDWORD)&total);
	if (total == 0) return 0;
	if (buffer[0].EventType == KEY_EVENT)
	{
		if (buffer[0].Event.KeyEvent.bKeyDown)
		{
			c = buffer[0].Event.KeyEvent.uChar.AsciiChar;
			FlushConsoleInputBuffer(I);
			return c;
		};	// if
	};	// if()
	return 0;
};	// choice()


void	gotoYX(int linha, int coluna)
{
	static COORD	coord;
	HANDLE			H = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = coluna; coord.Y = linha;
	SetConsoleCursorPosition(H, coord);
	return;
};	// gotoXY


void	mensagem_em_video_reverso(char* mensagem)
{
	HANDLE	H = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO		info;
	GetConsoleScreenBufferInfo(H, &info);
	WORD foreground = info.wAttributes & 0xF;
	WORD background = info.wAttributes & 0xF0;
	printf("\n");
	text_color(background, foreground);
	printf("%s\n", mensagem);
	text_color(foreground, background);
	return;
}	// mensagem_em_video_reverso()


void mostra_grade_256_cores()
{
	cls();
	text_color(15, 0);	/* preto sobre branco */
	printf("Gabarito (Frente|Fundo) escrito em (5,10)\n");
	printf("    os numeros sao das cores que o windows usa\n\n\n");

	for (int letra = 0; letra < 16; letra += 1)
	{
		for (int fundo = 0; fundo < 16; fundo += 1)
		{
			text_color(letra, fundo);
			printf(" %2d %2d ", letra, fundo);
			text_color(_branco_, _preto_);
			printf("  ");
		}
		text_color(_branco_, _preto_);
		printf(" \n");
	}

	printf("\nteste: antes de escrever em amarelo sobre preto\n");
	text_color(_amarelo_, _preto_);
	printf("Amarelo sobre preto: os numeros sao das cores que o windows usa\n");
	text_color(_branco_, _preto_);
	printf("teste depois de restaurar a cor\n");
	mensagem_em_video_reverso(" r e v e r s o ");
	return;
};	// mostra_grade_256_cores()


void	text_color(int letras, int fundo)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letras | (fundo << 4));
}	// text_color

// fim de ch-console.c