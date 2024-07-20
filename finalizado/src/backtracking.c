#include "../lib/define.h"

int todosGruposCobertos(conjunto_t *solution){

  printf("\n=====================================\n");

  printf("\nFunção: Todos Grupos Cobertos!\n\n");

  if(solution->card == 0){
    printf("Função TDC: Solução vazia!\n");
     printf("\n=====================================\n");
    return 0;
  }

  printf("Solution: ");
  imprime(solution);

  printf("\n");

  conjunto_t *cobertos = cria_conjunto(qtdGroups);

  for(int i = 0; i < solution->card; i++){
    cobertos = cria_uniao(cobertos, candidates[solution->v[i]].groups);
    printf("Grupo inserido: ");
    imprime(candidates[solution->v[i]].groups);
  }

  printf("\n");

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

  if(todosGruposCobertos(result->solution)){

    if(result->solution->card < result->definitiveSolution->card){
      destroi_conjunto(result->definitiveSolution);
      result->definitiveSolution = cria_copia(result->solution);
    }

    retira_conjunto(result->solution, result->solution->v[result->solution->card-1]);

    destroi_conjunto(remaining->remainingGroups);
    remaining->remainingGroups = cria_conjunto(qtdGroups);

    for(int i = 0; i < qtdGroups; i++){
      insere_conjunto(remaining->remainingGroups, i+1);
    }

    for(int i = 0; i < result->solution->card; i++){
      remaining->remainingGroups = cria_diferenca(remaining->remainingGroups, candidates[result->solution->v[i]].groups);
    }

    printf("Solução com o ultimo retirado: ");
    imprime(result->solution);

    printf("Grupos restantes: ");
    imprime(remaining->remainingGroups);

    printf("Definitive Solution: ");
    imprime(result->definitiveSolution);
    
    currentLevel++;

    //return ;
  }

  improvements->cl = clCalcule(remaining, result);

  for(int i = 0; i < improvements->cl->card; i++){
    for(int j = i+1; j < improvements->cl->card; j++){
      if(candidates[improvements->cl->v[i]].numGroups < candidates[improvements->cl->v[j]].numGroups){
        int aux = improvements->cl->v[i];
        improvements->cl->v[i] = improvements->cl->v[j];
        improvements->cl->v[j] = aux;
      }
    }
  }

  printf("Cl: ");
  imprime(improvements->cl);

  printf("\n");

  for (int i = currentLevel; i < improvements->cl->card; i++) {
    
        int candidate = improvements->cl->v[i];
        int cardinal = remaining->remainingGroups->card;

        printf("\nInicializando for com i = %d\n\n", i);
        
        //talvez criar uma função para isso
        remaining->remainingGroups = cria_diferenca(remaining->remainingGroups, candidates[candidate].groups);

        printf("Remaining Groups: ");
        imprime(remaining->remainingGroups);

        if (cardinal == remaining->remainingGroups->card){
            continue;
        }

        if (!boundCalcule(improvements->cl, result, remaining)) {
            printf("Saiu pelo Bound!\n");
            continue;
        }

        insere_conjunto(result->solution, candidate);
        printf("Solution: ");
        imprime(result->solution);
        printf("\n");

        retira_conjunto(remaining->remainingCandidates, candidate);
        printf("Remaining Candidates: ");
        imprime(remaining->remainingCandidates);
        printf("\n");

        printf("Remaining Groups: ");
        imprime(remaining->remainingGroups);

        printf("Chamando backtracking i = %d\n", i);

        backTracking(i, result, remaining, improvements, options);

        insere_conjunto(remaining->remainingCandidates, candidate);
    }

    printf("Saiu fora!\n");
    return;

}