#include "../lib/define.h"

bool limitantFunction(conjunto_t *solution, Remaining *remaining){

  if(solution->card == 0){
    return false;
  }

  int totalCapacity = 0;

  for(int i = 0; i < qtdCandidates; i++){
    totalCapacity += candidates[i].numGroups;
  }

  int totalGroupsLost = cardinalidade(remaining->remainingGroups);
  int totalCandidatesLost = cardinalidade(remaining->remainingCandidates);

  int mediumCapacity = totalCapacity / totalCandidatesLost;

  int minimalCandidatesRequestByMedium = (totalGroupsLost + mediumCapacity -1) / mediumCapacity;

  int minimalCandidatesRequestByMax = (totalGroupsLost + totalCapacity - 1) / totalCapacity;

  int minimalCandidatesRequest = minimalCandidatesRequestByMedium < minimalCandidatesRequestByMax ? minimalCandidatesRequestByMedium : minimalCandidatesRequestByMax;

  return minimalCandidatesRequest <= totalCandidatesLost;

}