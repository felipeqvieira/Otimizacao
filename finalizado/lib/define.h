#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
#include <time.h>
#include "libconjunto.h"

typedef struct{
  int numGroups;
  conjunto_t *groups;
  int id;
}Candidate;

typedef struct{
  conjunto_t *solution;
  conjunto_t *definitiveSolution;
}Result;

typedef struct{
  conjunto_t *remainingGroups;
  conjunto_t *candidates;
}Remaining;

typedef struct{
  bool pruneOptimality;
  bool pruneFeasibility;
  bool boundProf;
}Options;

extern int qtdGroups, qtdCandidates, node_count;
extern Candidate *candidates;

int todosGruposCobertos(conjunto_t *solution);

void backTracking(int currentLevel, Result *result, Remaining *remaining, Options *options);

bool clCalcule(int currentLevel, Remaining *remaining, Result *result);

void *alocar_memoria(size_t qtd, size_t size_of_struct);

void printOptions(Options options);

bool isInfeasible(Candidate *candidates);

void sortCandidatesByGroup(Candidate *candidate);

void imprime_solucao(conjunto_t *c, Candidate *candidates);

int isCovered(int *groupCovered, int valor);

int boundCalcule2(int currentLevel, Result *result, Remaining *remaining);

void print_report(double cpu_time_used, Options options);

int profBound(Remaining *remaining, Result *result);