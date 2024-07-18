#include "../lib/define.h"

void clCalcule(Remaining *remaining, conjunto_t *cl){

  //printf("Função clCalcule: Calculando CL\n");

  for (int i = 0; i < remaining->remainingCandidates->card; i++) {
    int candidate = remaining->remainingCandidates->v[i];

    for (int j = 0; j < candidates[candidate].numGroups; j++) {
      int group = candidates[candidate].groups[j];

      if (pertence(remaining->remainingGroups, group) >= 0) {
       //printf("Função clCalcule: Candidato %d cobre grupo %d\n", candidate, group);
        insere_conjunto(cl, candidate);
        break; // Pare de verificar grupos para este candidato, já que ele foi adicionado a CL
      }
    }
    
  }



}