#include "../lib/define.h"

bool clCalcule(int currentLevel, Remaining *remaining, Result *result){

  //printf("\n=====================================\n");

  //printf("Solucao Atual: ");
  //imprime(result->solution);

  //printf("\n");

  //printf("currentLevel: %d\n", currentLevel);

  if(remaining->remainingGroups->card == 0){
    return false;
  }

  conjunto_t *cl_definitive = cria_conjunto(qtdGroups);

  //printf("Conjunto de Grupos Restantes: ");
  //imprime(remaining->remainingGroups);
  //printf("\n");

  // passa por todos os candidatos restantes
  for(int i = currentLevel; i < remaining->remainingCandidates->card; i++){
    //printf("Candidato: %d\n", remaining->remainingCandidates->v[i]);

    cl_definitive = cria_uniao(cl_definitive, candidates[remaining->remainingCandidates->v[i]].groups);

    //printf("Grupo após união do Candidato: ");
    //imprime(cl_definitive);
    //printf("\n");
  }

  
  int resultado = contido(remaining->remainingGroups, cl_definitive);

  //printf("Resultado: %d\n", resultado);

  //printf("\n=====================================\n");

  if(resultado){
    destroi_conjunto(cl_definitive);
    return true;
  } else{
    destroi_conjunto(cl_definitive);
    return false;
  }
  

}