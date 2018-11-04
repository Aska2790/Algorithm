/*
В файле записан некоторый набор чисел, однако мы не знаем,
сколько их. Напишите на псевдокоде алгоритм для подсчета сред-
него значения чисел в файле. Какого типа операции делает Ваш
алгоритм? Сколько операций каждого типа он делает?
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*
	openfile
	if()

*/


int main()
{
    char path[256];
	printf("Input path to file");
    gets(path);
    FILE *file = fopen(path, 'r');
    if(file ==  NULL)
	{
	}
	else
	{
		char *ptr;
		fscanf(file, ptr );
	}



    printf("\n%s", path);
    return 0;
}
