#include "../lib/define.h"

bool isInviable(Candidate *candidates){

  bool *groupCovered = (bool *)calloc(qtdGroups, sizeof(bool));

  for(int i = 0; i < qtdCandidates; i++)
    for(int j = 0; j < candidates[i].numGroups; j++){
      groupCovered[candidates[i].groups[j]] = true;
      printf("Grupo %d coberto\n", candidates[i].groups[j]);
    }

  for(int i = 1; i < qtdGroups; i++)
    if(!groupCovered[i]){
      printf("Grupo %d não coberto\n", i);
      return true;
    }
  
  return false;
}