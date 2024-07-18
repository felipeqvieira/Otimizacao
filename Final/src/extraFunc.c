#include "../lib/define.h"

int compare_candidates_by_groups(const void *a, const void *b) {
  Candidate *candidateA = (Candidate *)a;
  Candidate *candidateB = (Candidate *)b;
  return candidateB->numGroups - candidateA->numGroups;
}

void sort_candidates_by_groups(Candidate *candidates, int num_candidates) {
    qsort(candidates, num_candidates, sizeof(Candidate), compare_candidates_by_groups);
}

void print_candidates(Candidate *candidates, int num_candidates) {
  printf("\nprint_candidates():\n");
  for (int i = 0; i < num_candidates; i++) {
    printf("Candidate %d: %d groups", i + 1, candidates[i].numGroups);
    printf("{");
    for (int j = 0; j < candidates[i].numGroups; j++) {
      printf(" [%d]", candidates[i].groups[j]);
    }
    printf(" }\n");
  }
  // printf("\n");
}

void *alocar_memoria(size_t qtd, size_t size_of_struct) {
    void *ptr = malloc(qtd * size_of_struct);

    if (ptr == NULL) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    return ptr;
}