#include <stdio.h>

// Deleta linhas de um arquivo, número de linhas é inclusivo. Uso: del_linha(número da 1ª linha a ser deletada, número da última linha a ser deletada, ponteiro do arquivo, modo fopen quando a função retornar ou "c" para fechar, tamanho do arquivo em caracteres). A operação é feita na RAM.
/* Limitações:
   Hard-coded para não funcionar em arquivos com mais de 256 caracteres por linha, já que ocuparia muito espaço na stack. Caso isso seja necessário, use uma função que escreva diretamente no disco em vez de um array, como a del_linhas_disk.
   # O limite pode ser expandido até 1023 caracteres. O tamanho da primeira linha define o limite para o resto do arquivo.
*/
extern void del_linhas(int ini_deletar, int fim_deletar, FILE *arquivo, char mode_return[], long int arq_size);

// Deleta linhas de um arquivo, número de linhas é inclusivo. Uso: del_linha(número da 1ª linha a ser deletada, número da última linha a ser deletada, ponteiro do arquivo, modo fopen quando a função retornar ou "c" para fechar, tamanho do arquivo em caracteres). A operação é feita no disco.
/* Limitações:
   As linhas podem conter no máximo 2048 caracteres.
*/
extern void del_linhas_disk(int ini_deletar, int fim_deletar, FILE *arquivo, char mode_return[]);
