#include "../lib/define.h"

void clCalcule(Remaining *remaining, conjunto_t *cl, bool *grupoCoberto){

  printf("Função clCalcule: Calculando CL\n");

  for (int i = 0; i < remaining->remainingCandidates->card; i++) {
    
    int candidate = remaining->remainingCandidates->v[i];

    printf("Candidato escolhido: %d\n", candidate);
    printf("Número de grupos do candidato: %d\n", candidates[candidate].numGroups);

    for (int j = 0; j < candidates[candidate].numGroups; j++) {

      int group = candidates[candidate].groups[j];

      printf("Grupo escolhido: %d\n", group);

      if (pertence(remaining->remainingGroups, group) >= 0 && !grupoCoberto[group]) {
        grupoCoberto[group] = true;
        printf("Função clCalcule: Candidato %d cobre grupo %d\n", candidate+1, group);
        insere_conjunto(cl, candidate);
      }
    }
    
  }



}