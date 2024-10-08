#include "../lib/define.h"

Candidate *candidates;
conjunto_t *groupCovered;

int qtdGroups, qtdCandidates;

int main(int argc, char *argv[]){

  clock_t start, end;
  double cpu_time_used;

  Options options = {true, true, false};

  int opt;

  while((opt = getopt(argc, argv, "foa")) != -1){

    switch(opt){
      case 'f':
        options.pruneFeasibility = false;
        break;
      case 'o':
        options.pruneOptimality = false;
        break;
      case 'a':
        options.boundProf = true;
        break;
      default: 
        fprintf(stderr, "Usage: %s [-f] [-o] [-a]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  //printOptions(options);

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
  remaining->candidates = cria_conjunto(qtdCandidates);

  for(int i = 0; i < qtdGroups; i++){
    insere_conjunto(remaining->remainingGroups, i+1);
  }

  int group = 0;
  
  // lê as entradas
  for(int i = 0; i < qtdCandidates; i++){

    scanf("%d", &candidates[i].numGroups);
    
    candidates[i].groups = cria_conjunto(candidates[i].numGroups);
    candidates[i].id = i+1;

    for(int j = 0; j < candidates[i].numGroups; j++){
      scanf("%d", &group);
      insere_conjunto(candidates[i].groups, group);
    }
    
  }

  if(options.pruneFeasibility){
    if(isInfeasible(candidates)){
      printf("Inviavel\n");
      return 1;
    }
  }

  sortCandidatesByGroup(candidates);
  
  for(int i = 0; i < qtdCandidates; i++){
    insere_conjunto_ordenado(remaining->candidates, i);
  }

  start = clock();
  backTracking(0, result, remaining, &options);
  end = clock();

  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

  imprime_solucao(result->definitiveSolution, candidates);
  print_report(cpu_time_used, options);

  return 0;

}