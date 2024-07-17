#include "../lib/define.h"

boundCalcule(conjunto_t *cl, conjunto_t *solution, Remaining *remaining){

  int mediaGruposPorCandidato = 0;

  for(int i = 0; i < cl->card; i++){
    for(int j = i+1; j < cl->card; j++){
      if(candidates[cl->v[i]].numGroups < candidates[cl->v[j]].numGroups){
        int aux = cl->v[i];
        cl->v[i] = cl->v[j];
        cl->v[j] = aux;
      }
    }
  }

  for(int i = 1; i < cl->card; i++)
    mediaGruposPorCandidato += candidates[cl->v[i]].numGroups;

  mediaGruposPorCandidato /= cl->card;

  int minimoCandidatosNecessarios = remaining->remainingGroups->card / mediaGruposPorCandidato;

  minimoCandidatosNecessarios++;

  if(minimoCandidatosNecessarios > solution->card)
    return 0;
  else
    return 1;

  
}