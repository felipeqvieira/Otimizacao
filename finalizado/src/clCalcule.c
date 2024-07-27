#include "../lib/define.h"

bool clCalcule(int currentLevel, Remaining *remaining, Result *result){

  if(remaining->remainingGroups->card == 0){
    return false;
  }

  printf("\n=====================================\n");

  conjunto_t *cl_definitive = cria_conjunto(qtdGroups);

  // passa por todos os candidatos restantes
  for(int i = currentLevel; i < remaining->remainingCandidates->card; i++){
    cl_definitive = cria_uniao(cl_definitive, candidates[remaining->remainingCandidates->v[i]].groups);
  }

  printf("Conjunto de Grupos União: ");
  imprime(cl_definitive);

  printf("\n");

  printf("Conjunto de Grupos Restantes: ");
  imprime(remaining->remainingGroups);

  printf("\n");

  int resultado = contido(remaining->remainingGroups, cl_definitive);

  printf("Resultado: %d\n", resultado);

  if(resultado){
    destroi_conjunto(cl_definitive);
    return true;
  } else{
    destroi_conjunto(cl_definitive);
    return false;
  }
  printf("\n=====================================\n");

}