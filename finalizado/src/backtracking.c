#include "../lib/define.h"

int node_count = 0;

int todosGruposCobertos(conjunto_t *solution){

  if(solution->card == 0){
    return 0;
  }

  conjunto_t *cobertos = cria_conjunto(qtdGroups);

  for(int i = 0; i < solution->card; i++){
    cobertos = cria_uniao(cobertos, candidates[solution->v[i]].groups);
  }

  if(cobertos->card == qtdGroups){
    return 1;
  } else{
    return 0;
  }

}

void backTracking(int currentLevel, Result *result, Remaining *remaining, Options *options){

  if(todosGruposCobertos(result->solution)){

    if(result->solution->card < result->definitiveSolution->card){
      destroi_conjunto(result->definitiveSolution);
      result->definitiveSolution = cria_copia(result->solution);
    }

  }

  for (int i = currentLevel; i < remaining->candidates->card; i++) {

    if(options->pruneFeasibility){
      if(clCalcule(i, remaining, result) == false)
        return;
    }

    if(options->pruneOptimality){

      if(options->boundProf){
        if(profBound(remaining, result) == 0){
          continue;
        }
      } else{
        if(boundCalcule2(currentLevel, result, remaining) >= result->definitiveSolution->card){
          continue;
        }
      }
    }
    
    int candidate = remaining->candidates->v[i];
    int cardinal = remaining->remainingGroups->card;

    remaining->remainingGroups = cria_diferenca(remaining->remainingGroups, candidates[candidate].groups);

    if (cardinal == remaining->remainingGroups->card){
      continue;
    }

    node_count++;

    insere_conjunto(result->solution, candidate);

    backTracking(i+1, result, remaining, options);

    retira_conjunto_sem_ordenacao(result->solution, candidate);

    destroi_conjunto(remaining->remainingGroups);
    remaining->remainingGroups = cria_conjunto(qtdGroups);

    for(int i = 0; i < qtdGroups; i++){
      insere_conjunto(remaining->remainingGroups, i+1);
    }

    for(int i = 0; i < result->solution->card; i++){
      remaining->remainingGroups = cria_diferenca(remaining->remainingGroups, candidates[result->solution->v[i]].groups);
    } 

  }
    return;

}