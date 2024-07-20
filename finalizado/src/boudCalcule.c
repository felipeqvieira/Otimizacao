#include "../lib/define.h"

int boundCalcule(conjunto_t *cl, Result *result, Remaining *remaining){

  printf("\n=====================================\n");
  
  printf("\nFunção boundCalcule\n\n");

  if(cl->card == 0)
    return 0;

  int lastGroups = remaining->remainingGroups->card;

  printf("Cl->card: %d\n\n", cl->card);

  printf("Quantidade de grupos restantes: %d\n", lastGroups);

  int mediaGruposPorCandidato = 0;

  for(int i = 0; i < cl->card; i++){
    mediaGruposPorCandidato += candidates[cl->v[i]].numGroups;
  }

  printf("Quantidade Total de Grupo de todos os candidatos: %d\n", mediaGruposPorCandidato);

  mediaGruposPorCandidato  = ceil(mediaGruposPorCandidato/cl->card);

  printf("Média de grupos por candidato: %d\n", mediaGruposPorCandidato);

  int minimoCandidatosNecessarios = ceil(lastGroups / mediaGruposPorCandidato);

  printf("Mínimo de candidatos necessários: %d\n", minimoCandidatosNecessarios);

  if(minimoCandidatosNecessarios + result->solution->card > result->definitiveSolution->card){
    printf("Função retornou 0\n");
    printf("\n=====================================\n");
    return 0;
  } else{
    printf("Função retornou 1\n");
    printf("\n=====================================\n");
    return 1;
  }


}

int boundCalcule2(conjunto_t *cl, Result *result, Remaining *remaining)
{
  /* 
    B(E,F) = Número de candidatos escolhidos + 
    (Nº grupos não cobertos / número máximo de grupos que um candidato restante cobre)
  */

  int num_remaining_groups = remaining->remainingGroups->card;

  /* Número máximo de grupos que um candidato restante cobre */
  int max_groups_per_candidate = 0;

  for (int i = 0; i < cl->card; i++)
  {
    if(candidates[cl->v[i]].numGroups > max_groups_per_candidate)
      max_groups_per_candidate = candidates[cl->v[i]].numGroups;
  }
  
  /* B(E,F) =  |E| + MinCandidates */
  int minCandidates = result->solution->card + ceil(num_remaining_groups / max_groups_per_candidate);

  return minCandidates;
}