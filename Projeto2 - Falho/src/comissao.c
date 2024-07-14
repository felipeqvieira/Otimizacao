#include "../lib/define.h"

Candidate *candidates;
bool *groupCovered; // Indica se um grupo já foi coberto
int qtdGroups, qtdCandidates;

int main(){

  scanf("%d %d", &qtdGroups, &qtdCandidates);

  candidates = (Candidate*) malloc(qtdCandidates * sizeof(Candidate));

  groupCovered = (bool*) malloc(qtdGroups * sizeof(bool));
  
  for(int i = 0; i < qtdCandidates; ++i){
    scanf("%d", &candidates[i].numGroups);
    for(int j = 0; j < candidates[i].numGroups; ++j){
      scanf("%d", &candidates[i].groups[j]);
    }
  }

  printf("Grupos: %d\n", qtdGroups);
  printf("Candidatos: %d\n", qtdCandidates);

  for (int i = 0; i < qtdCandidates; ++i) {
      printf("Candidato %d: ", i);
      for (int j = 0; j < candidates[i].numGroups; ++j) {
          printf("%d ", candidates[i].groups[j]);
      }
      printf("\n");
  }

  int *solution; // Armazena a solução parcial

  solution = (int*) malloc(qtdCandidates * sizeof(int)); // Aloca memória para a solução parcial
  
  for(int i = 0; i < qtdCandidates; i++)
    solution[i] = -1;

  for(int i = 0; i < qtdGroups; i++)
    groupCovered[i] = false;
  

  backTracking(0, solution, 0); // Começa o backtracking a partir do nível 0 com uma solução vazia
  
  return 0;
}
