#include "../lib/define.h"

int boundCalcule2(int currentLevel, Result *result, Remaining *remaining)
{

  //printf("\nFunção boundCalcule2\n\n");
  
  /* 
    B(E,F) = Número de candidatos escolhidos + 
    (Nº grupos não cobertos / número máximo de grupos que um candidato restante cobre)
  */
  
  if (remaining->remainingGroups->card == 0) return 0;

  float num_remaining_groups = remaining->remainingGroups->card;

  /* Número máximo de grupos que um candidato restante cobre */
  float max_groups_per_candidate = 0;

  for (int i = currentLevel; i < remaining->candidates->card; i++)
  {
    if(candidates[remaining->candidates->v[i]].numGroups > max_groups_per_candidate)
      max_groups_per_candidate = candidates[remaining->candidates->v[i]].numGroups;
  }
  
  /* B(E,F) =  |E| + MinCandidates */
  int minCandidates = result->solution->card + ceil(num_remaining_groups / max_groups_per_candidate);

  //retorna 0 se o bound não for promissor
  return minCandidates;
}