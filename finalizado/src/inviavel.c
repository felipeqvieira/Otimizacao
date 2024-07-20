#include "../lib/define.h"

bool isInfeasible(Candidate *candidates){

  conjunto_t *allGroups = cria_conjunto(qtdGroups*2);

  for(int i = 0; i < qtdCandidates; i++)
    allGroups = cria_uniao(allGroups, candidates[i].groups);

  if(allGroups->card == qtdGroups){
    destroi_conjunto(allGroups);
    return false;
  }

  return true;
  
}