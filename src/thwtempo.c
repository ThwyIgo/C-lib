#include <stdlib.h>
#include <string.h>
#include <time.h>

char *mes(time_t refTime)
{
    struct tm *tm_refTime = localtime(&refTime);
    char lookupMonth[12][9] = { "Janeiro",  "Feveiro", "Março",    "Abril",
                                "Maio",     "Junho",   "Julho",    "Agosto",
                                "Setembro", "Outubro", "Novembro", "Dezembro" };
    char *ret = (char *)malloc(25 * sizeof(char));
    strcpy(ret, lookupMonth[tm_refTime->tm_mon]);

    return ret;
}

char *dia(time_t refTime)
{
    struct tm *tm_refTime = localtime(&refTime);
    char lookupWeek[7][8] = { "Domingo", "Segunda", "Terca", "Quarta",
                              "Quinta",  "Sexta",   "Sabado" };
    char *ret = (char *)malloc(25 * sizeof(char));
    strcpy(ret, lookupWeek[tm_refTime->tm_wday]);

    return ret;
}

time_t randomTime(time_t refTime, int horasAntes, int horasDepois)
{
    srand(time(NULL));

    // 1 hora tem 3600 segundos
    time_t limiteInferior = refTime - horasAntes * 3600;
    time_t limiteSuperior = refTime + horasDepois * 3600;
    rand();

    return (rand() % (limiteSuperior - limiteInferior + 1)) + limiteInferior;
}
