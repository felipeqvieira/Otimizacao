#include "../lib/define.h"

int todosGruposCobertos(int *solution, int tamanhoSolucao){

  if(tamanhoSolucao == 0){
    printf("Função todosGruposCobertos: Solução vazia\n");
    return 0;
  }  // Se a solução está vazia, não cobre nenhum grupo

  int cobertos[MAX_GROUPS] = {0};

  for(int i = 0; i < tamanhoSolucao; i++)
    for(int j = 0; j < candidates[solution[i]].numGroups; j++){

      printf("Função todosGruposCobertos: Candidato %d cobre grupo %d\n", solution[i], candidates[i].groups[j]);
      cobertos[candidates[i].groups[j]] = 1;
    }

  for(int i = 1; i < qtdGroups+1; i++)
    if(!cobertos[i]){
      printf("Função todosGruposCobertos: Grupo %d não coberto\n", i);
      return 0;
    }
  
  printf("Função todosGruposCobertos: Todos os grupos cobertos\n");
  return 1;

}

void backTracking(int currentLevel, int *solution, int solutionSize){

  if(todosGruposCobertos(solution, solutionSize)){
    for(int i = 0; i < solutionSize; i++)
      printf("%d ", solution[i]);
    printf("\n");
    return;
  }

  for(int i = 0; i < qtdCandidates; ++i){

    printf("Candidato %d\n", i);
    bool canBeAdded = false;
    
    for(int j = 0; j < candidates[i].numGroups; ++j){
      if(!groupCovered[candidates[i].groups[j]-1]){
        printf("Grupo %d do candidato %d não coberto\n", candidates[i].groups[j], i);
        canBeAdded = true;
        break;
      }
    }

    if(canBeAdded){
      for(int j = 0; j < candidates[i].numGroups; ++j){
        groupCovered[candidates[i].groups[j]-1] = true;
        printf("Grupo %d do candidato %d coberto\n", candidates[i].groups[j], i);
      }

      solution[solutionSize++] = i;
      backTracking(currentLevel + 1, solution, solutionSize);
      printf("Voltei, i: %d\n", i);
      solution[--solutionSize] = -1;

      for(int j = 0; j < candidates[i].numGroups; ++j)
        groupCovered[candidates[i].groups[j]-1] = false;

      //printa solution
      printf("\nSolution:");
      for(int i = 0; i < solutionSize; i++)
        printf("%d ", solution[i]);

      printf("\nGroupCovered:");
      //printa groupcovered
      for(int i = 0; i < qtdGroups; i++)
        printf("%d ", groupCovered[i]);

      printf("\n");
    }
  }
}
