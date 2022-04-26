#include <stdio.h>

extern void del_linhas(int ini_deletar, int fim_deletar, FILE *arquivo, char mode_return[], long int arq_size);
extern void del_linhas_disk(int ini_deletar, int fim_deletar, FILE *arquivo, char mode_return[]);
