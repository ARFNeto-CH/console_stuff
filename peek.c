#pragma once
#include "ch-console.h"


int main(int argc, char** argv)
{
	char	c;
	int		total = 0;

	mensagem_em_video_reverso("Tecle 'q' para sair\n");
	while (1)
	{
		c = choice();
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		Sleep(100);

		if (c > 0) printf("choice() retornou '%c'=%d\n", c, c);
		if (c == 'q')break;
	};

	mostra_grade_256_cores();
	return 0;
};	// main()

// fim de peek.c