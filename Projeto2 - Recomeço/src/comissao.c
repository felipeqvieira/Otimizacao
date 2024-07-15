#include "../lib/define.h"

Candidate *candidates;
conjunto_t *groupCovered; // Indica se um grupo já foi coberto
conjunto_t *chosenCandidates; // Indica os candidatos escolhidos
conjunto_t *definitiveSolution; // Indica a solução definitiva
int qtdGroups, qtdCandidates;

int main(){

  scanf("%d %d", &qtdGroups, &qtdCandidates);

  groupCovered = cria_conjunto(qtdGroups);

  for(int i = 0; i < qtdGroups; i++){
    insere_conjunto(groupCovered, i+1);
  }

  candidates = (Candidate *) malloc(qtdCandidates * sizeof(Candidate));

  if(candidates == NULL){
    printf("Erro ao alocar memória para os candidatos\n");
    return 1;
  }

  for(int i = 0; i < qtdCandidates; i++){

    scanf("%d", &candidates[i].numGroups);
    
    candidates[i].groups = (int *) malloc(candidates[i].numGroups * sizeof(int));
    
    if(candidates[i].groups == NULL){
      printf("Erro ao alocar memória para os grupos do candidato %d\n", i);
      return 1;
    }

    candidates[i].conjunto = cria_conjunto(qtdCandidates);

    for(int j = 0; j < candidates[i].numGroups; j++){
      scanf("%d", &candidates[i].groups[j]);
      insere_conjunto(candidates[i].conjunto, candidates[i].groups[j]);
    }

  }

  
  printf("\nGrupos: %d\n", qtdGroups);
  printf("Candidatos: %d\n", qtdCandidates);

  for(int i = 0; i < qtdCandidates; i++){
    printf("\nCandidato %d: ", i);
    imprime(candidates[i].conjunto);
  }
  

  conjunto_t *solution = cria_conjunto(qtdGroups);
  chosenCandidates = cria_conjunto(qtdCandidates);

  int solucaoTam = qtdGroups;

  backTracking(0, solution, solucaoTam);

  imprime(definitiveSolution);

  return 0;
  
}