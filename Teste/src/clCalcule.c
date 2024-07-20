#include "../lib/define.h"

void clCalcule(Remaining *remaining, conjunto_t *cl, Result *result){

  printf("\n=====================================\n");

  printf("\nFunção clCalcule: Calculando CL\n\n");

  for(int i = 0; i < remaining->remainingCandidates->card; i++){
    
    if(pertence(result->solution, remaining->remainingCandidates->v[i]) > -1){
      continue;
    }

    int candidate = remaining->remainingCandidates->v[i];

    printf("Candidato escolhido: %d\n", candidate);
    printf("Número de grupos do candidato: %d\n", candidates[candidate].numGroups);

    for(int j = 0; j < candidates[candidate].numGroups; j++){

      int group = candidates[candidate].groups[j];

      printf("Grupo escolhido: %d\n", group);

      printf("Grupos restantes: ");
      imprime(remaining->remainingGroups);
      printf("\n");

      if(pertence(remaining->remainingGroups, group) > -1){
        printf("Grupo %d do candidato %d inserido no conjunto de Cl!\n", group, candidate);
        insere_conjunto(cl, candidate);
        break;
      }
    }
  }
  printf("\n=====================================\n");
}