#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CANDIDATES 100
#define MAX_GROUPS 100

typedef struct {
  int numGroups;
  int groups[MAX_GROUPS];
} Candidate;

extern Candidate *candidates;
extern bool *groupCovered; // Indica se um grupo já foi coberto
extern int qtdGroups, qtdCandidates;

int todosGruposCobertos(int* solution, int tamanhoSolucao);

void backTracking(int currentLevel, int *solution, int solutionSize);

//int calculateBound(Candidate* partialSolution, int partialSize);
//void branchAndBound(Candidate* partialSolution, int partialSize, int bestSolutionSize, Candidate* bestSolution);
