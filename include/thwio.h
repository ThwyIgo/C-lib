#ifndef THWIO_H
#define THWIO_H
#include <time.h>

/* Limpa o stdin para evitar problemas com o '\n'.
 *
 * Use esta função APÓS uma leitura. Utilizar antes "por precaução" pode trazer
 * confusão.
 */
void limpaBuffer();

/* Remove new line
 *
 * Substitui o primeiro caractere '\n' de uma string por '\0'.
 *
 * Retorna 1 caso a string não possua um '\n'.
 * Retorna 0 caso um '\n' tenha sido removido.
 */
int removenl(char *string);

/* Executa fgets, imprime '\n' logo após e limpa o buffer do stdin até o próximo
 * '\n' caso um '\n' não tenha sido lido. Garante que Buf não conterá um '\n'.
 *
 * Retorna o mesmo valor do fgets()
 */
char *fgetsw(char *const Buf, int MaxCount);

#endif // THWIO_H
