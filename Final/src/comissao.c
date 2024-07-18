#include "../lib/define.h"

Candidate *candidates; // Vetor de candidatos
conjunto_t *groupCovered; // Indica se um grupo já foi coberto
int qtdGroups, qtdCandidates;

int main(){

  printf("Grupos e Candidatos:\n");
  scanf("%d %d", &qtdGroups, &qtdCandidates);

  // cria conjunto de grupos cobertos e adiciona todos os grupos nele
  groupCovered = cria_conjunto(qtdGroups);

  for(int i = 0; i < qtdGroups; i++){
    insere_conjunto(groupCovered, i);
  }

  candidates = (Candidate *) malloc(qtdCandidates * sizeof(Candidate));
  if(candidates == NULL){
    printf("Erro ao alocar memória para os candidatos\n");
    return 1;
  }

  /* Lê a quantidade de grupos de cada candidato e os grupos quais ele participa */
  for(int i = 0; i < qtdCandidates; i++){

    scanf("%d", &candidates[i].numGroups);
    
    candidates[i].groups = (int *) malloc(candidates[i].numGroups * sizeof(int));
    
    if(candidates[i].groups == NULL){
      printf("Erro ao alocar memória para os grupos do candidato %d\n", i);
      return 1;
    }

    for(int j = 0; j < candidates[i].numGroups; j++)
      scanf("%d", &candidates[i].groups[j]);
  }

  print_candidates(candidates, qtdCandidates);
  sort_candidates_by_groups(candidates, qtdCandidates);
  print_candidates(candidates, qtdCandidates);
  printf("\n");

  Result *result = (Result *) malloc(sizeof(Result));
  if(result == NULL){
    printf("Erro ao alocar memória para a solução\n");
    return 1;
  }

  result->solution = cria_conjunto(qtdCandidates);
  result->definitiveSolution = cria_conjunto(qtdCandidates);
  
  for(int i = 0; i < qtdCandidates; i++){
    insere_conjunto(result->definitiveSolution, i);
  }

  Remaining *remaining = (Remaining *) malloc(sizeof(Remaining));
  if(remaining == NULL){
    printf("Erro ao alocar memória para os grupos restantes\n");
    return 1;
  }

  remaining->remainingGroups = cria_conjunto(qtdGroups);
  remaining->remainingCandidates = cria_conjunto(qtdCandidates);

  for(int i = 0; i < qtdGroups; i++){
    insere_conjunto(remaining->remainingGroups, i+1);
  }

  for(int i = 0; i < qtdCandidates; i++){
    insere_conjunto(remaining->remainingCandidates, i);
  }

  Options *options = (Options *) malloc(sizeof(Options));
  /* To do: testar malloc */
  options->otimalidade = 0;
  options->viabilidade = 0;
  options->fprofessor = 0;

  Improvements *improvements = (Improvements *) malloc(sizeof(Improvements));
  /* To do: testar malloc */
  improvements->cl = cria_conjunto(qtdCandidates);
  improvements->bound = cria_conjunto(qtdCandidates);

  backTracking(0, result, remaining, improvements, options);

  imprime(result->definitiveSolution);

  return 0;
  
}