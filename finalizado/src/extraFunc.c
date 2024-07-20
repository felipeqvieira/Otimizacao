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