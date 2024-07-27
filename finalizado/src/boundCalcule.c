#include "../lib/define.h"

int boundCalcule(int currentLevel, Result *result, Remaining *remaining){

  //printf("\n=====================================\n");
  
  //printf("\nFunção boundCalcule\n\n");

  // pega a quantidade de grupos restantes
  int lastGroups = remaining->remainingGroups->card;

  //printf("Quantidade de grupos restantes: %d\n", lastGroups);

  float mediaGruposPorCandidato = 0;

  //quantidade total de grupos de todos os candidatos
  for(int i = currentLevel; i < remaining->remainingCandidates->card; i++){
    mediaGruposPorCandidato += candidates[remaining->remainingCandidates->v[i]].numGroups;
  }

  //printf("Quantidade Total de Grupo de todos os candidatos: %f\n", mediaGruposPorCandidato);

  //calcula a média de grupo por candidato cl
  mediaGruposPorCandidato  = (mediaGruposPorCandidato/(remaining->remainingCandidates->card - currentLevel));

  mediaGruposPorCandidato = ceil(mediaGruposPorCandidato);

  //printf("Média de grupos por candidato: %f\n", mediaGruposPorCandidato);

  //todos os grupos restantes para a solução dividido pela média de grupo por candidato
  float minimoCandidatosNecessarios = (lastGroups / mediaGruposPorCandidato);

  minimoCandidatosNecessarios = ceil(minimoCandidatosNecessarios);

  //printf("Mínimo de candidatos necessários: %f\n", minimoCandidatosNecessarios);

  //printf("Minimo de candidatos necessarios + tamanho da solução atual = %f\n", minimoCandidatosNecessarios + result->solution->card);

  //printf("Tamanho da solução definitiva: %d\n", result->definitiveSolution->card);

  if(minimoCandidatosNecessarios + result->solution->card >= result->definitiveSolution->card){
    //printf("Função retornou 0\n");
    //printf("\n=====================================\n");
    return 0;
  } else{
    //printf("Função retornou 1\n");
    //printf("\n=====================================\n");
    return 1;
  }


}

int boundCalcule2(int currentLevel, Result *result, Remaining *remaining)
{

  //printf("\n=====================================\n");

  //printf("\nFunção boundCalcule2\n\n");
  
  /* 
    B(E,F) = Número de candidatos escolhidos + 
    (Nº grupos não cobertos / número máximo de grupos que um candidato restante cobre)
  */
  
  if (remaining->remainingCandidates->card == 0) return 0;

  float num_remaining_groups = remaining->remainingGroups->card;

  //printf("Número de grupos restantes: %f\n", num_remaining_groups);

  /* Número máximo de grupos que um candidato restante cobre */
  float max_groups_per_candidate = 0;

  for (int i = currentLevel; i < remaining->remainingCandidates->card; i++)
  {
    if(candidates[remaining->remainingCandidates->v[i]].numGroups > max_groups_per_candidate)
      max_groups_per_candidate = candidates[remaining->remainingCandidates->v[i]].numGroups;
  }

  //printf("Número máximo de grupos que um candidato restante cobre: %f\n", max_groups_per_candidate);
  
  /* B(E,F) =  |E| + MinCandidates */
  int minCandidates = result->solution->card + ceil(num_remaining_groups / max_groups_per_candidate);

  //printf("Número mínimo de candidatos necessários para preencher uma resposta: %d\n", minCandidates);

  //retorna 0 se o bound não for promissor
  return minCandidates;
}