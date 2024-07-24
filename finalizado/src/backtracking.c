#include "../lib/define.h"

int node_count = 0;

int todosGruposCobertos(conjunto_t *solution){

  //printf("\n=====================================\n");

  //printf("\nFunção: Todos Grupos Cobertos!\n\n");

  if(solution->card == 0){
    //printf("Função TDC: Solução vazia!\n");
     //printf("\n=====================================\n");
    return 0;
  }

  //printf("\n");

  conjunto_t *cobertos = cria_conjunto(qtdGroups);

  for(int i = 0; i < solution->card; i++){
    cobertos = cria_uniao(cobertos, candidates[solution->v[i]].groups);
    //printf("Grupo inserido: ");
    //imprime(candidates[solution->v[i]].groups);
  }

  //printf("\n");

  if(cobertos->card == qtdGroups){
    //printf("\nTodos os grupos cobertos\n");
    //printf("\n=====================================\n");
    return 1;
  } else{
    //printf("\nTotal dos Grupos cobertos: ");
    //imprime(cobertos);
    //printf("\n=====================================\n");
    return 0;
  }

}

void backTracking(int currentLevel, Result *result, Remaining *remaining, Improvements *improvements, Options *options, conjunto_t **cl_storage){
  
  //printf("\n=====================================\n");

  //printf("\nFunção BackTracking (Nivel: %d)\n\n", currentLevel);

  if(todosGruposCobertos(result->solution)){

    if(result->solution->card < result->definitiveSolution->card){
      destroi_conjunto(result->definitiveSolution);
      result->definitiveSolution = cria_copia(result->solution);

      //printf("Solução definitiva atualizada: ");
      //imprime(result->definitiveSolution);

      //printf("\n");
    }

  }

  if(options->pruneFeasibility)
    improvements->cl = clCalcule(remaining, result);
  else
    improvements->cl = remaining->remainingCandidates;


  for(int i = 0; i < improvements->cl->card; i++){
    for(int j = i+1; j < improvements->cl->card; j++){
      if(candidates[improvements->cl->v[i]].numGroups < candidates[improvements->cl->v[j]].numGroups){
        int aux = improvements->cl->v[i];
        improvements->cl->v[i] = improvements->cl->v[j];
        improvements->cl->v[j] = aux;
      }
    }
  }
  

  cl_storage[currentLevel] = cria_copia(improvements->cl);

  //printf("Cl: ");
  //imprime(improvements->cl);

  //printf("\n");

  for (int i = 0; i < improvements->cl->card; i++) {

    /*if (boundCalcule(improvements->cl, result, remaining) == 0) {
        //printf("Saiu pelo Bound!\n");
        continue;
    }
    */
    if(options->pruneOptimality){
      if(boundCalcule2(improvements->cl, result, remaining) >= result->definitiveSolution->card){
        //printf("Saiu pelo Bound!\n");
        continue;
      }
    }

    node_count++;
    
    int candidate = improvements->cl->v[i];
    int cardinal = remaining->remainingGroups->card;

    //printf("\nInicializando for com i = %d\n\n", i);

    //printf("Grupo do candidato %d: ", candidate);
    //imprime(candidates[candidate].groups);

    //printf("\n");

    //printf("Remaining Groups: ");
    //imprime(remaining->remainingGroups);

    //printf("\n");
        
    //talvez criar uma função para isso
    remaining->remainingGroups = cria_diferenca(remaining->remainingGroups, candidates[candidate].groups);

    //printf("Resultado da diferença: ");
    //imprime(remaining->remainingGroups);

    //printf("\n");
    

    if (cardinal == remaining->remainingGroups->card){
      continue;
    }

    //printf("Candidatos restantes: ");
    //imprime(remaining->remainingCandidates);
    //printf("\n");

    insere_conjunto(result->solution, candidate);
    //printf("Candidato inserido no conjunto da solução: ");
    //imprime(result->solution);
    //printf("\n");

    retira_conjunto(remaining->remainingCandidates, candidate);

    //printf("Candidatos restantes: ");
    //imprime(remaining->remainingCandidates);
    //printf("\n");

    //printf("Grupos restantes: ");
    //imprime(remaining->remainingGroups);

    //printf("\n");

    //printf("Chamando Backtracking %d\n", currentLevel+1);

    //printf("\n=====================================\n");

    backTracking(currentLevel+1, result, remaining, improvements, options, cl_storage);

    //printf("\n=====================================\n");

    //printf("Voltou para o Backtracking %d\n", currentLevel);

    retira_conjunto_sem_ordenacao(result->solution, candidate);

    //printf("Candidato %d retirado da solução: ", candidate);
    //imprime(result->solution);

    //printf("\n");

    destroi_conjunto(remaining->remainingGroups);
        remaining->remainingGroups = cria_conjunto(qtdGroups);

    for(int i = 0; i < qtdGroups; i++){
      insere_conjunto(remaining->remainingGroups, i+1);
    }

    for(int i = 0; i < result->solution->card; i++){
      remaining->remainingGroups = cria_diferenca(remaining->remainingGroups, candidates[result->solution->v[i]].groups);
    } 

    //printf("Grupos restantes: ");
    //imprime(remaining->remainingGroups);

    //printf("\n");

    insere_conjunto_ordenado(remaining->remainingCandidates, candidate);

    //printf("Candidato %d inserido no conjunto de candidatos restantes: ", candidate);
    //imprime(remaining->remainingCandidates); 

    //printf("\n"); 

    improvements->cl = cria_copia(cl_storage[currentLevel]);

    //printf("Cl substituído para: ");
    //imprime(improvements->cl);

    //printf("\n");
  }

    //printf("Solucao: ");
    //imprime(result->solution);

    //printf("\n");

    //printf("Saiu fora!\n");
    return;

}