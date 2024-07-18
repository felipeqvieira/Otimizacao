#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "libconjunto.h"

typedef struct{
  int numGroups;
  int* groups;
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
  int otimalidade;
  int viabilidade;
  int fprofessor;
}Options;

extern int qtdGroups, qtdCandidates;
extern Candidate *candidates;

int todosGruposCobertos(conjunto_t *solution);

void backTracking(int currentLevel, Result *result, Remaining *remaining, Improvements *improvements, Options *options);

void clCalcule(Remaining *remaining, conjunto_t *cl);

int boundCalcule(conjunto_t *cl, conjunto_t *solution, Remaining *remaining);

void print_candidates(Candidate *candidates, int num_candidates);

void sort_candidates_by_groups(Candidate *candidates, int num_candidates);