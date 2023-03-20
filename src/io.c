#include "thw/io.h"
#include "thw/tempo.h"
#include <stdio.h>
#include <string.h>

void limpaBuffer()
{
    char ch;
    while ((ch = getchar()) != EOF && ch != '\n')
        ;
}

int removenl(char *string)
{
    // nlpos retorna número de caracteres até que '\r' ou '\n' sejam encontrados
    unsigned long nlpos = strcspn(string, "\r\n");
    /* Se '\r' ou '\n' não forem encontrados, então nlpos será igual ao tamanho
       de string
    */
    int r = strlen(string) == nlpos ? 1 : 0;

    string[nlpos] = 0;

    return r;
}

char *fgetsw(char *const Buf, int MaxCount)
{
    char *r = fgets(Buf, MaxCount, stdin);
    putchar('\n');

    if (removenl(Buf) == 1)
        limpaBuffer();

    return r;
}
