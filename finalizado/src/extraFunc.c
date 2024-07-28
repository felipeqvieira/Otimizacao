#include "../lib/define.h"

int compare_candidates_by_groups(const void *a, const void *b) {
  Candidate *candidateA = (Candidate *)a;
  Candidate *candidateB = (Candidate *)b;
  return candidateB->numGroups - candidateA->numGroups;
}

void sort_candidates_by_groups(Candidate *candidates, int num_candidates){
    qsort(candidates, num_candidates, sizeof(Candidate), compare_candidates_by_groups);
}


void *alocar_memoria(size_t qtd, size_t size_of_struct) {
    void *ptr = malloc(qtd * size_of_struct);

    if (ptr == NULL) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    return ptr;
}

void printOptions(Options options) {
    printf("Options:\n");
    printf("  Prune Optimality: %s\n", options.pruneOptimality ? "ON" : "OFF");
    printf("  Prune Feasibility: %s\n", options.pruneFeasibility ? "ON" : "OFF");
    printf("  Bound Prof: %s\n", options.boundProf ? "ON" : "OFF");
}

void sortCandidatesByGroup(Candidate *candidate){

   for(int i = 0; i < qtdCandidates; i++){
    for(int j = i+1; j < qtdCandidates; j++){
      if(candidate[i].numGroups < candidate[j].numGroups){
        Candidate aux = candidate[i];
        candidate[i] = candidate[j];
        candidate[j] = aux;
      }
    }
   }
   
}

void imprime_solucao(conjunto_t *c, Candidate *candidates){

   for (int i = 0; i < c->card; i++)
    printf("%d ", candidates[c->v[i]].id);

  printf("\n");
}

void print_report(double cpu_time_used, Options options)
{
  fprintf(stderr, "\n\n====== Relatório ==================================================\n\n");
  fprintf(stderr, "n = número de nós visitados\n");
  fprintf(stderr, "t = tempo de execução (excluindo I/O)\n");

  fprintf(stderr, "___________________________________________________________________\n");
  if(options.boundProf)
    fprintf(stderr, "   Bound   | Professor\n");
  else
    fprintf(stderr, "   Bound   | Alunos\n");

  // if(options.pruneFeasibility || options.pruneFeasibility)
    fprintf(stderr, "   Pruning | ");
  
  if (options.pruneOptimality && options.pruneFeasibility)
    fprintf(stderr, "Otimalidade e Viabilidade\n");
  else if (options.pruneOptimality)
    fprintf(stderr, "Otimalidade\n");
  else if (options.pruneFeasibility)
    fprintf(stderr, "Viabilidade\n");
  else
    fprintf(stderr, "No pruning\n");
  

  fprintf(stderr, "      n    | %d\n", node_count);
  fprintf(stderr, "      t    | %.6f segundos\n", cpu_time_used);
  fprintf(stderr, "\n====== Fim Relatório ==============================================\n\n");

}