#include "../lib/define.h"

clCalcule(Remaining *remaining, conjunto_t *cl, conjunto_t *solution){

  for(int i = 0; i < remaining->remainingCandidates->card; i++){
    for(int j = 0; j < candidates[remaining->remainingCandidates->v[i]].numGroups; j++){
      if(!pertence_conjunto(remaining->remainingGroups, candidates[remaining->remainingCandidates->v[i]].groups[j])){
        insere_conjunto(cl, remaining->remainingCandidates->v[i]);
        break;
      }
    }
  }

}