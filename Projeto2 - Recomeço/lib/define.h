#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "libconjunto.h"

typedef struct{
  int numGroups;
  int* groups;
  conjunto_t *conjunto;
}Candidate;

extern int qtdGroups, qtdCandidates;
extern Candidate *candidates;
extern conjunto_t *groupCovered;

int todosGruposCobertos(conjunto_t *solution);

void backTracking(int currentLevel, conjunto_t *solution);