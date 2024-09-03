#include "../lib/define.h"

bool clCalcule(int currentLevel, Remaining *remaining, Result *result){

  if(remaining->remainingGroups->card == 0){
    return false;
  }

  conjunto_t *cl_definitive = cria_conjunto(qtdGroups);

  for(int i = currentLevel; i < remaining->candidates->card; i++){

    cl_definitive = cria_uniao(cl_definitive, candidates[remaining->candidates->v[i]].groups);
  }

  int resultado = contido(remaining->remainingGroups, cl_definitive);

  if(resultado){
    destroi_conjunto(cl_definitive);
    return true;
  } else{
    destroi_conjunto(cl_definitive);
    return false;
  }
  

}