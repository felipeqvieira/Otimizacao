#include "../lib/define.h"

int todosGruposCobertos(conjunto_t *solution){

  if(solution->card == 0){
    printf("Função todosGruposCobertos: Solução vazia\n");
    return 0;
  }  

  conjunto_t *cobertos = cria_conjunto(qtdGroups);

  for(int i = 0; i < qtdGroups; i++)
    insere_conjunto(cobertos, i+1);

  printf("Função todosGruposCobertos: Grupos cobertos: ");
  imprime(cobertos);

  for(int i = 0; i < solution->card; i++)
    for(int j = 0; j < candidates[solution->v[i]].numGroups; j++){

      retira_conjunto(cobertos, candidates[solution->v[i]].groups[j]);
      printf("Função todosGruposCobertos: Candidato %d cobre grupo %d\n", solution->v[i], candidates[solution->v[i]].groups[j]);
      
    }

  if(cobertos->card == 0){
    printf("Função todosGruposCobertos: Todos os grupos cobertos\n");
    return 1;
  } else{
    printf("Função todosGruposCobertos: Grupos não cobertos: ");
    imprime(cobertos);
    return 0;
  }
}

void backTracking(int currentLevel, conjunto_t *solution, int solucaoTam){

  if(todosGruposCobertos(solution)){

    if(solucaoTam > solution->card){
      solucaoTam = solution->card;
      definitiveSolution = cria_copia(solution);
    }

    return;
  }

  if(! limitantFunction(solution, chosenCandidates)){
    printf("Fui cortado!\n");
    return;
  }

  for(int i = 0; i < qtdCandidates; i++){

    printf("Candidato %d\n", i);
    bool canBeAdded = false;
    
    for(int j = 0; j < candidates[i].numGroups; j++){
      if(retira_conjunto(groupCovered, candidates[i].groups[j]) == -1){
        printf("Grupo %d do candidato %d já coberto\n", candidates[i].groups[j], i);
      }
      else{
        printf("Grupo %d do candidato %d não coberto\n", candidates[i].groups[j], i);
        canBeAdded = true;
      }
    }

    if(canBeAdded){
      insere_conjunto(chosenCandidates, i);
      insere_conjunto(solution, i);
      backTracking(currentLevel + 1, solution, solucaoTam);
      printf("Voltei, i: %d\n", i);
      retira_conjunto(solution, i);
      retira_conjunto(chosenCandidates, i);

      for(int j = 0; j < candidates[i].numGroups; j++){
        insere_conjunto(groupCovered, candidates[i].groups[j]);
        printf("Grupo %d do candidato %d reestabelecido\n", candidates[i].groups[j], i);
      }
    }
  }
}