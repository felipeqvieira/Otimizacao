#include "../lib/define.h"

bool limitantFunction(conjunto_t *solution, conjunto_t *chosenCandidates){

  if(solution->card == 0 || chosenCandidates->card == 0){
    //printf("Fui cortado por dentro!\n");
    return true;
  }

  int mediumCapacity = 0;

  conjunto_t *candidates_lost = cria_conjunto(qtdCandidates);

  for(int i = 0; i < qtdCandidates; i++){
    insere_conjunto(candidates_lost, i);
    mediumCapacity += candidates[i].numGroups;
  }

  conjunto_t *groups_lost = cria_conjunto(qtdGroups);

  for(int i = 0; i < qtdGroups; i++)
    insere_conjunto(groups_lost, i+1);

  candidates_lost = cria_diferenca(candidates_lost, chosenCandidates);
  groups_lost = cria_diferenca(groups_lost, solution);

  int totalGroupsLost = cardinalidade(groups_lost);
  int totalCandidatesLost = cardinalidade(candidates_lost);

  mediumCapacity /= totalCandidatesLost;

  int minimalCandidatesRequest = totalGroupsLost / mediumCapacity;

  //printf("Minimal Candidates Request: %d\n", minimalCandidatesRequest);
  //printf("Total Candidates Lost: %d\n", totalCandidatesLost);

  return minimalCandidatesRequest <= totalCandidatesLost;

}