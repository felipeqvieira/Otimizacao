#include "../lib/define.h"

int todosGruposCobertos(conjunto_t *solution){

  if(solution->card == 0){
    //printf("Função TDC: Solução vazia\n");
    return 0;
  }

  conjunto_t *cobertos = cria_conjunto(qtdGroups);

  for(int i = 0; i < solution->card; i++)
    for(int j = 0; j < candidates[solution->v[i]].numGroups; j++){
      insere_conjunto(cobertos, candidates[solution->v[i]].groups[j]);
      //printf("Função todosGruposCobertos: Candidato %d cobre grupo %d\n", solution->v[i], candidates[solution->v[i]].groups[j]);
    }

  if(cobertos->card == qtdGroups){
    //printf("Função todosGruposCobertos: Todos os grupos cobertos\n");
    return 1;
  } else{
   // printf("Função todosGruposCobertos: Grupos apenas cobertos: ");
    //imprime(cobertos);
    return 0;
  }

}

void backTracking(int currentLevel, Result *result, Remaining *remaining, Improvements *improvements, Options options){

  if(result->solution->card > result->definitiveSolution->card)
    return ;

  if(todosGruposCobertos(result->solution)){
    destroi_conjunto(result->definitiveSolution);
    result->definitiveSolution = cria_copia(result->solution);
    return ;
  }

  /*
  Calculo Cl = Quais candidatos podem ser selecionados?
  */

 clCalcule(remaining, improvements->cl);

 /*
  Calculo Bound
  1. Desses candidatos, ordernar por quem cobre mais grupo
  2. Com o candidato que cobre mais grupos, a solução fica melhor que a já calculada?
 */
  boundCalcule(improvements->cl, result->solution, remaining);
  

  for(int i = currentLevel; i < improvements->cl->card; i++){

    //printf("Candidato  %d\n", i);
    bool canBeAdded = false;

    for(int j = 0; j < candidates[improvements->cl->v[i]].numGroups; j++){

      if(retira_conjunto(remaining->remainingGroups, candidates[improvements->cl->v[i]].groups[j]) == -1){
        //printf("Grupo %d do candidato %d já coberto\n", candidates[i].groups[j], i);
      } else{
        //printf("Grupo %d do candidato %d não coberto\n", candidates[i].groups[j], i);
        canBeAdded = true;
      }
    }

    if(canBeAdded){
      insere_conjunto(result->solution, improvements->cl->v[i]);
      retira_conjunto(remaining->remainingCandidates, improvements->cl->v[i]);
      backTracking(currentLevel+1, result, remaining, improvements, options);
      insere_conjunto(remaining->remainingCandidates, improvements->cl->v[i]);
      retira_conjunto(result->solution, improvements->cl->v[i]);

      for(int j = 0; j < candidates[i].numGroups; j++){
        insere_conjunto(remaining->remainingGroups, candidates[improvements->cl->v[i]].groups[j]);
        //printf("Grupo %d do candidato %d reestabelecido\n", candidates[i].groups[j], i);
      }
    }
  }
}