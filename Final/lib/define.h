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
  conjunto_t *bound;
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

bool limitantFunction(conjunto_t *solution, Remaining *remaining);

bool is_unfeasible(int qtdGroups, int qtdCandidates, Candidate *candidates, conjunto_t *groups_covered);
/*
  Verifica a inviabilidade do problema antes de tentar resolver. 
  Se o problema for inviável, retorna FALSE.
  Caso contrário, retorna TRUE.
*/

void sort_candidates_by_groups(Candidate *candidates, int num_candidates);
/*
  Ordena os candidatos de forma decrescente em relação
  ao número de grupos cobertos por cada um.
*/

void print_candidates(Candidate *candidates, int num_candidates);
/*
  Imprime os candidatos e os grupos que cada um cobre.
*/

