#include "../lib/define.h"
#include <stdlib.h>
#include <stdbool.h>

int todosGruposCobertos(conjunto_t *solution){

  if(solution->card == 0){
    printf("Função TDC: Solução vazia\n");
    return 0;
  }

  conjunto_t *cobertos = cria_conjunto(qtdGroups);

  for(int i = 0; i < solution->card; i++)
    for(int j = 0; j < candidates[solution->v[i]].numGroups; j++){
      insere_conjunto(cobertos, candidates[solution->v[i]].groups[j]);
      printf("Função todosGruposCobertos: Candidato %d cobre grupo %d\n", solution->v[i], candidates[solution->v[i]].groups[j]);
    }

  if(cobertos->card == qtdGroups){
    printf("Função todosGruposCobertos: Todos os grupos cobertos\n");
    return 1;
  } else{
    printf("Função todosGruposCobertos: Grupos apenas cobertos: ");
    imprime(cobertos);
    return 0;
  }

}

void backTracking(int currentLevel, Result *result, Remaining *remaining, Improvements *improvements, Options *options){

  if(result->solution->card > result->definitiveSolution->card)
    return ;

  if(todosGruposCobertos(result->solution)){
    destroi_conjunto(result->definitiveSolution);
    result->definitiveSolution = cria_copia(result->solution);
    return ;
  }

  /*if(limitantFunction(result->solution, remaining)){
    printf("Fui cortado!\n");
    return ;
  }
  */

 /*
  Calculo Bound
  1. Desses candidatos, ordernar por quem cobre mais grupo
  2. Com o candidato que cobre mais grupos, a solução fica melhor que a já calculada?
 */
  
  for(int i = currentLevel; i < qtdCandidates; i++){

    printf("Candidato  %d\n", i);
    bool canBeAdded = false;

    for(int j = 0; j < candidates[i].numGroups; j++){

      if(retira_conjunto(remaining->remainingGroups, candidates[i].groups[j]) == -1){
        printf("Grupo %d do candidato %d já coberto\n", candidates[i].groups[j], i);
      } else{
        printf("Grupo %d do candidato %d não coberto\n", candidates[i].groups[j], i);
        canBeAdded = true;
      }
    }

    if(canBeAdded){
      insere_conjunto(result->solution, i);
      retira_conjunto(remaining->remainingCandidates, i);
      backTracking(currentLevel+1, result, remaining, improvements, options);
      insere_conjunto(remaining->remainingCandidates, i);
      retira_conjunto(result->solution, i);

      for(int j = 0; j < candidates[i].numGroups; j++){
        insere_conjunto(remaining->remainingGroups, candidates[i].groups[j]);
        printf("Grupo %d do candidato %d reestabelecido\n", candidates[i].groups[j], i);
      }
    }
  }
}

/* 
  Compara dois candidatos pelo número de grupos cobertos
  por cada um dos candidatos.
*/
int compare_candidates_by_groups(const void *a, const void *b) {
  Candidate *candidateA = (Candidate *)a;
  Candidate *candidateB = (Candidate *)b;
  return candidateB->numGroups - candidateA->numGroups;
}

/*
  Ordena os candidatos de forma decrescente em relação
  ao número de grupos cobertos por cada um.
*/
void sort_candidates_by_groups(Candidate *candidates, int num_candidates) {
    qsort(candidates, num_candidates, sizeof(Candidate), compare_candidates_by_groups);
}

/*
  Imprime os candidatos e os grupos que cada um cobre. Função de debug.
*/
void print_candidates(Candidate *candidates, int num_candidates) {
  printf("\nprint_candidates():\n");
  for (int i = 0; i < num_candidates; i++) {
    printf("Candidate %d: %d groups", i + 1, candidates[i].numGroups);
    printf("{");
    for (int j = 0; j < candidates[i].numGroups; j++) {
      printf(" [%d]", candidates[i].groups[j]);
    }
    printf(" }\n");
  }
}

/*
  Verifica a inviabilidade do problema antes de tentar resolver. 
  Se o problema for inviável, retorna FALSE.
  Caso contrário, retorna TRUE.
*/
bool is_unfeasible(int qtdGroups, int qtdCandidates, Candidate *candidates, conjunto_t *groups_covered) {

  conjunto_t *allGroups = cria_conjunto(qtdGroups);

  /* Insere os grupos cobertos pelos candidatos em um conjunto */
  for(int i = 0; i < qtdCandidates; i++)
    for(int j = 0; j < candidates[i].numGroups; j++)
      insere_conjunto(allGroups, candidates[i].groups[j]);

  /* Verifica se o conjunto de grupos cobertos pelos candidatos é igual ao conjunto de grupos da entrada. */
  if(!sao_iguais(allGroups, groups_covered)){
    destroi_conjunto(allGroups);
    return true; 
    /* O conjunto de grupos cobertos pelos candidatos não é igual ao conjunto de grupos da entrada. */
  }

  /* O conjunto de grupos cobertos pelos candidatos é igual ao conjunto de grupos da entrada.*/
  destroi_conjunto(allGroups);
  return false;
}
