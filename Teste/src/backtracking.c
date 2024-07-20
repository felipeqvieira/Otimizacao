#include "../lib/define.h"

int todosGruposCobertos(conjunto_t *solution){

  printf("\n=====================================\n");

  printf("\nFunção: Todos Grupos Cobertos!\n\n");

  if(solution->card == 0){
    printf("Função TDC: Solução vazia\n");
    return 0;
  }

  printf("Solution Card: %d\n", solution->card);
  printf("Solution: ");
  imprime(solution);

  printf("\n");

  conjunto_t *cobertos = cria_conjunto(qtdGroups);

  for(int i = 0; i < solution->card; i++)
    for(int j = 0; j < candidates[solution->v[i]].numGroups; j++){
      insere_conjunto(cobertos, candidates[solution->v[i]].groups[j]);
      printf("Grupo %d do candidato %d foi inserido no conjunto de cobertos!\n", candidates[solution->v[i]].groups[j], solution->v[i]);
    }

  if(cobertos->card == qtdGroups){
    printf("\nTodos os grupos cobertos\n");
    printf("\n=====================================\n");

    return 1;
  } else{
    printf("\nTotal dos Grupos cobertos: ");
    imprime(cobertos);
    printf("\n=====================================\n");
    return 0;
  }

}

void backTracking(int currentLevel, Result *result, Remaining *remaining, Improvements *improvements, Options *options){

  printf("\n=====================================\n");

  printf("\nFunção BackTracking\n\n");

  if(result->solution->card > result->definitiveSolution->card)
    return ;

  if(todosGruposCobertos(result->solution)){
    destroi_conjunto(result->definitiveSolution);
    result->definitiveSolution = cria_copia(result->solution);
    return ;
  }

  printf("Grupos restantes: ");
  imprime(remaining->remainingGroups);
  printf("\n");

  //bool *grupoCoberto = calloc(qtdGroups, sizeof(bool));

  /*if(grupoCoberto == NULL){
    printf("Erro ao alocar memória para grupoCoberto\n");
    return ;
  }
  */

  if(improvements->cl->card > 0){
    destroi_conjunto(improvements->cl);
    improvements->cl = cria_copia(result->solution);
  }
    
  clCalcule(remaining, improvements->cl, result);

  printf("\n");

  printf("Cl: ");
  imprime(improvements->cl);

  printf("\n");

  if(! boundCalcule(improvements->cl, result, remaining)){
    printf("Função retornou no bound!\n");
    return ;
  }

  printf("Grupos restantes: ");
  imprime(remaining->remainingGroups);
  printf("\n");

  //free(grupoCoberto);

  for(int i = currentLevel; i < improvements->cl->card; i++){

    printf("\nCandidato %d!\n", improvements->cl->v[i]);

    bool canBeAdded = false;

    for(int j = 0; j < candidates[improvements->cl->v[i]].numGroups; j++){
      
      if(retira_conjunto(remaining->remainingGroups, candidates[improvements->cl->v[i]].groups[j]) > -1){
        canBeAdded = true;
        printf("Grupo %d do candidato %d foi retirado do conjunto de grupos restantes!\n", candidates[improvements->cl->v[i]].groups[j], improvements->cl->v[i]);
      }

    }

    printf("\n");

    if(canBeAdded){
      insere_conjunto(result->solution, improvements->cl->v[i]);

      printf("Candidato %d foi inserido na solução!\n", improvements->cl->v[i]);

      printf("\nSolucao: ");
      imprime(result->solution);

      retira_conjunto(remaining->remainingCandidates, improvements->cl->v[i]);

      printf("\nCandidato %d foi retirado do conjunto de candidatos restantes!\n", improvements->cl->v[i]);

      printf("\nCandidatos restantes: ");

      imprime(remaining->remainingCandidates);

      backTracking(currentLevel+1,result, remaining, improvements, options);

      insere_conjunto(remaining->remainingCandidates, improvements->cl->v[i]);

      printf("\nCandidato %d foi inserido no conjunto de candidatos restantes!\n", improvements->cl->v[i]);

      printf("\nCandidatos restantes: ");

      imprime(remaining->remainingCandidates);

      retira_conjunto(result->solution, improvements->cl->v[i]);

      printf("\nCandidato %d foi retirado da solução!\n", improvements->cl->v[i]);

      printf("\nSolucao: ");

      imprime(result->solution);

      conjunto_t *eliminate_group = cria_conjunto(qtdGroups);

      for(int j = 0; j < candidates[improvements->cl->v[i]].numGroups; j++){
        inserir_conjunto(eliminate_group, candidates[improvements->cl->v[i]].groups[j]);
      }
    }

  }

  printf("\n=====================================\n");

}