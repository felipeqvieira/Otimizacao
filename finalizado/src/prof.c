#include "../lib/define.h"

//Bdada(E,F) é o tamanho de E mais 1 (um) caso existam grupos ainda não atendidos

void profBound(Remaining *remaining, Result *result){

  int resposta = 0;

  if(remaining->remainingGroups->card == 0){
    resposta = result->solution->card;
  } else {
    resposta = result->solution->card + 1;
  }	

  if(resposta >= result->definitiveSolution->card)
    return 0;
  else
    return 1;
    
}