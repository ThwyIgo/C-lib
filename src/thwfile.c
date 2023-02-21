#include "thwfile.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void del_linhas_ram(int ini_deletar,
                    int fim_deletar,
                    FILE *arquivo,
                    char mode_return[],
                    long int arq_size)
{
    freopen(NULL, "r", arquivo);
    int linha_atual = 1;
    unsigned short linha_tamanho;

    { // Expandir o tamanho permitido de linhas caso a primeira seja grande
        char *foo = malloc(1024 * sizeof *foo);
        foo[1023] = '\0';
        fscanf(arquivo, "%[^\n] ", foo);
        if (foo[1023] != '\0') {
            fprintf(stderr,
                    "Erro del_linhas: Linha do arquivo é muito grande\n");
            free(foo);
            exit(EXIT_FAILURE);
        }
        linha_tamanho = strlen(foo) + 2; // Incluir o \n e \0
        free(foo);
    }
    rewind(arquivo);
    linha_tamanho =
      fmax(linha_tamanho, 256); // Garantir pelo menos 256 caracteres.
    char arq_linha[linha_tamanho], arq_origin[arq_size];
    arq_origin[0] = '\0'; // '\0' garante que o strcat funcionará

    while (fgets(arq_linha, linha_tamanho, arquivo) != NULL) {
        if (linha_atual < ini_deletar || linha_atual > fim_deletar)
            strcat(arq_origin, arq_linha); // Transferindo o conteúdo do arquivo
                                           // para a string "arq_origin"
        linha_atual++;
    }
    if (linha_atual <= ini_deletar || linha_atual <= fim_deletar) {
        fprintf(stderr,
                "Erro del_linhas: Não foi possível encontrar o intervalo no "
                "arquivo\n");
        exit(EXIT_FAILURE);
    }
    freopen(NULL, "w", arquivo);
    fprintf(arquivo, "%s", arq_origin);

    if (mode_return[0] == 'c')
        fclose(arquivo);
    else
        freopen(NULL, mode_return, arquivo);

    return;
}

void del_linhas(int ini_deletar,
                int fim_deletar,
                FILE *arquivo,
                char mode_return[])
{
    freopen(NULL, "r", arquivo);
    char arq_linha[2048];
    FILE *temp = tmpfile(); // É aberto no modo "wb+"
    int linha_atual = 1;

    if (temp == NULL) {
        fprintf(stderr,
                "Erro del_linhas_disk: Não foi possível criar um arquivo "
                "temporário.");
        fclose(temp);
        exit(EXIT_FAILURE);
    }

    while (fgets(arq_linha, 2048, arquivo) != NULL) {
        if (linha_atual < ini_deletar || linha_atual > fim_deletar)
            fprintf(temp, "%s", arq_linha);
        linha_atual++;
    }
    if (linha_atual <= ini_deletar || linha_atual <= fim_deletar) {
        fprintf(stderr,
                "Erro del_linhas_disk: Não foi possível encontrar o intervalo "
                "no arquivo\n");
        fclose(temp);
        exit(EXIT_FAILURE);
    }

    freopen(NULL, "w", arquivo);
    freopen(NULL, "r", temp);
    while (fgets(arq_linha, 2048, temp) != NULL)
        fprintf(arquivo, "%s", arq_linha);

    if (mode_return[0] == 'c')
        fclose(arquivo);
    else
        freopen(NULL, mode_return, arquivo);
    fclose(temp);

    return;
}
