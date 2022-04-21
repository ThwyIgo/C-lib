#include <stdio.h>
#include <stdlib.h>
#include "libthwfile.h"

#define TAMANHO_BUFFER 128
#define MAX_LINHAS 16

int main()
{
    char linha[TAMANHO_BUFFER];
    FILE *arquivo = fopen("farquivo.txt", "a");
    del_linhas(2, 4, arquivo, "c", TAMANHO_BUFFER * MAX_LINHAS);
    fgets(linha, TAMANHO_BUFFER, arquivo); // Provavelmente ocorrerá um erro, pois o modo de retorno é "c"
    printf("%s", linha); // Nada será impresso

    return 0;
}
