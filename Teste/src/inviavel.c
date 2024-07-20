#include "../lib/define.h"

bool isInfeasible(Candidate *candidates){

  int *groupCovered = (int *)alocar_memoria(qtdGroups, sizeof(int));

  int count = 0;

  for(int i = 0; i < qtdCandidates; i++)
    for(int j = 0; j < candidates[i].numGroups; j++){

      if(! isCovered(groupCovered, candidates[i].groups[j])){
        
        if(count < qtdGroups){
          groupCovered[count] = candidates[i].groups[j];
        }

        count++;

        if(count > qtdGroups){
          return 1;
        }
          
      }      
    }

  if(count < qtdGroups)
    return 1;

  return 0;

}

int isCovered(int *groupCovered, int valor){

  for(int i = 0; i < qtdGroups; i++){
    if(groupCovered[i] == valor)
      return 1;
  }

  return 0;

}