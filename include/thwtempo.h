#ifndef THWTEMPO_H
#define THWTEMPO_H

#include <time.h>

/* Recebe um tempo em time_t e retorna o nome do mês correspondente em
 * português.
 *
 * Não esqueça do free() no ponteiro retornado!
 */
char *mes(time_t refTime);

/* Recebe um tempo em time_t e retorna o nome do dia da semana em português
 *
 * Não esqueça do free() no ponteiro retornado!
 */
char *dia(time_t refTime);

/* Gera um time_t aleatório dentro do intervalo:
 * (refTime - horasAntes) e (refTime + horasDepois).
 */
time_t randomTime(time_t refTime, int horasAntes, int horasDepois);

#endif // THWTEMPO_H
