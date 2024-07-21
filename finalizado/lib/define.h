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
  conjunto_t *remainingCandidates;
}Remaining;

typedef struct{
  conjunto_t *cl;
}Improvements;

typedef struct{
  bool pruneOptimality;
  bool pruneFeasibility;
  bool boundProf;
}Options;

extern int qtdGroups, qtdCandidates;
extern Candidate *candidates;
extern conjunto_t **cl_storage;

int todosGruposCobertos(conjunto_t *solution);

void backTracking(int currentLevel, Result *result, Remaining *remaining, Improvements *improvements, Options *options, conjunto_t **cl_storage);

conjunto_t* clCalcule(Remaining *remaining, Result *result);

int boundCalcule(conjunto_t *cl, Result *result, Remaining *remaining);

void *alocar_memoria(size_t qtd, size_t size_of_struct);

void printOptions(Options options);

bool isInfeasible(Candidate *candidates);

void sortCandidatesByGroup(Candidate *candidate);

void imprime_solucao(conjunto_t *c, Candidate *candidates);

int isCovered(int *groupCovered, int valor);

int boundCalcule2(conjunto_t *cl, Result *result, Remaining *remaining);