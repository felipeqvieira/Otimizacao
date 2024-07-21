#include "../lib/define.h"

conjunto_t * clCalcule(Remaining *remaining, Result *result){

  conjunto_t* cl_definitive = cria_conjunto(qtdCandidates);

  //printf("\n=====================================\n");

  //printf("\nFunção clCalcule: Calculando CL\n\n");

  // passa por todos os candidatos restantes
  for(int i = 0; i < remaining->remainingCandidates->card; i++){

    // pega o candidato
    int candidate = remaining->remainingCandidates->v[i];

    // se o candidato cobrir algum dos grupos restantes, ele é inserido no conjunto de CL
    if(conta_iguais(candidates[candidate].groups, remaining->remainingGroups)){
      //printf("Candidato %d inserido no conjunto de Cl!\n", candidate);
      insere_conjunto_ordenado(cl_definitive, candidate);
    }

  }
  //printf("\n=====================================\n");

  return cl_definitive;
}