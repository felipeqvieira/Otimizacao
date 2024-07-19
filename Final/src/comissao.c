#include "../lib/define.h"

Candidate *candidates; // Vetor de candidatos
conjunto_t *groupCovered; // Indica se um grupo já foi coberto
int qtdGroups, qtdCandidates;

int main(int argc, char *argv[]){

  Options options = {false, false, false};

  /* Verifica os parâmetros passados na entrada e ativa as devidas opções. */
  if(argc == 1) {
    options.pruneFeasibility = true;
    options.pruneOptimality = true;
  }
  else {
    
    int opt;
    while ((opt = getopt(argc, argv, "foa")) != -1) {
      switch (opt) {
        case 'f':
          options.pruneFeasibility = true;
          break;
        case 'o':
          options.pruneOptimality = true;
          break;
        case 'a':
          options.boundProf = true;
          break;
        default:
          fprintf(stderr, "Usage: %s [-f] [-o] [-a]\n", argv[0]);
          exit(EXIT_FAILURE);
      }
    }

  }
  printOptions(options);

  scanf("%d %d", &qtdGroups, &qtdCandidates);

  if(qtdGroups < 1 || qtdCandidates < 1){
    printf("Erro: quantidade de grupos ou candidatos inválida\n");
    return 1;
  }

  // cria conjunto de grupos cobertos e adiciona todos os grupos nele
  groupCovered = cria_conjunto(qtdGroups);

  for(int i = 0; i < qtdGroups; i++){
    insere_conjunto(groupCovered, i);
  }

  // alocação de memória
  candidates = (Candidate *)alocar_memoria(qtdCandidates, sizeof(Candidate));

  Result *result = (Result *)alocar_memoria(1, sizeof(Result));
  result->solution = cria_conjunto(qtdCandidates);
  result->definitiveSolution = cria_conjunto(qtdCandidates);
  
  for(int i = 0; i < qtdCandidates; i++){
    insere_conjunto(result->definitiveSolution, i);
  }

  Remaining *remaining = (Remaining *)alocar_memoria(1, sizeof(Remaining));
  remaining->remainingGroups = cria_conjunto(qtdGroups);
  remaining->remainingCandidates = cria_conjunto(qtdCandidates);

  Improvements *improvements = (Improvements *)alocar_memoria(1, sizeof(Improvements));
  improvements->cl = cria_conjunto(qtdCandidates);

  for(int i = 0; i < qtdGroups; i++){
    insere_conjunto(remaining->remainingGroups, i+1);
  }

  for(int i = 0; i < qtdCandidates; i++){
    insere_conjunto(remaining->remainingCandidates, i);
  }

  // lê as entradas
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

  if(isInviable(candidates)){
    printf("Solução inviável\n");
    return 1;
  }

  sortCandidatesByGroup(candidates);

  //printa candidatos
  for(int i = 0; i < qtdCandidates; i++){
    printf("Candidato %d cobre %d grupos\n", i, candidates[i].numGroups);
    printf("Grupos: ");
    for(int j = 0; j < candidates[i].numGroups; j++)
      printf("%d ", candidates[i].groups[j]);
    printf("\n");
  }

  backTracking(0, result, remaining, improvements, &options);

  imprime(result->definitiveSolution);

  return 0;
  
}