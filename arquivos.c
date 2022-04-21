#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAMANHO_BUFFER 128
#define MAX_LINHAS 16

// Deleta linhas de um arquivo, número de linhas é inclusivo. Uso: del_linha(número da 1ª linha a ser deletada, número da última linha a ser deletada, ponteiro do arquivo, modo fopen quando a função retornar ou "c" para fechar, tamanho do arquivo em caracteres)
// Hard-coded para não funcionar em arquivos com mais de 256 caracteres por linha, já que ocuparia muito espaço na stack. Caso isso seja necessário, use uma função que escreva diretamente no disco em vez de um array.
// O limite pode ser expandido até 1024 caracteres. O tamanho da primeira linha define o limite para o resto do arquivo.
void del_linhas(int ini_deletar, int fim_deletar, FILE *arquivo, char mode_return[], long int arq_size)
{
    freopen(NULL, "r", arquivo);
    int linha_atual=1, linha_tamanho;
    
    {
        char foo[1024] = {'\0'}; // Será apagado da stack logo ao sair do escopo, não tem tanto problema ser grande
        fscanf(arquivo, "%[^\n] ", foo);
        if (foo[1023] != '\0') {
            fprintf(stderr, "Erro del_linhas: Linha do arquivo é muito grande\n");
            exit(EXIT_FAILURE);
        }
        linha_tamanho = strlen(foo); // Margem de segurança para arquivos que já comecem com linhas enormes.
        rewind(arquivo);
    }
    linha_tamanho = fmax(linha_tamanho, 256); // Garantir pelo menos 256 caracteres.
    
    char arq_linha[linha_tamanho], arq_origin[arq_size]; arq_origin[0] = '\0'; // '\0' garante que o strcat funcionará

    while (fgets(arq_linha, linha_tamanho, arquivo) != NULL) {
        if (linha_atual < ini_deletar || linha_atual > fim_deletar)
            strcat(arq_origin, arq_linha); // Transferindo o conteúdo do arquivo para a string "arq_origin"
        linha_atual++;
    }
    freopen(NULL, "w", arquivo);
    fprintf(arquivo, "%s", arq_origin);

    if (mode_return[0] == 'c')
        fclose(arquivo);
    else
        freopen(NULL, mode_return, arquivo);

    return;
}

int main(int argc, char *argv[])
{
    char linha[TAMANHO_BUFFER];
    FILE *arquivo = fopen("farquivo.txt", "a");
    del_linhas(2, 4, arquivo, "c", TAMANHO_BUFFER * MAX_LINHAS);
    fgets(linha, TAMANHO_BUFFER, arquivo);
    printf("%s", linha); // Nada será impresso, pois o modo de retorno é "c"

    return 0;
}
