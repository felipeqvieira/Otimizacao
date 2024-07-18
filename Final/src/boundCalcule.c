#include "../lib/define.h"

int boundCalcule(conjunto_t *cl, conjunto_t *solution, Remaining *remaining){

  int mediaGruposPorCandidato = 0;

  //printf("Função boundCalcule: Calculando Bound\n");

  for(int i = 0; i < cl->card; i++){
    for(int j = i+1; j < cl->card; j++){
      if(candidates[cl->v[i]].numGroups < candidates[cl->v[j]].numGroups){
        int aux = cl->v[i];
        cl->v[i] = cl->v[j];
        cl->v[j] = aux;
      }
    }
  }

  //printf("Função boundCalcule: Candidatos ordenados por grupos cobertos\n");

  //printa ordenado
  //for(int i = 0; i < cl->card; i++)
    //printf("Função boundCalcule: Candidato %d cobre %d grupos\n", cl->v[i], candidates[cl->v[i]].numGroups);

  for(int i = 0; i < cl->card; i++)
    mediaGruposPorCandidato += candidates[cl->v[i]].numGroups;

  //printf("Função boundCalcule: Média de grupos por candidato: %d\n", mediaGruposPorCandidato);
  //printf("Função boundCalcule: Card do cl: %d\n", cl->card);

  mediaGruposPorCandidato /= cl->card;

  //printf("Função boundCalcule: Média de grupos por candidato depois da divisão: %d\n", mediaGruposPorCandidato);

  int minimoCandidatosNecessarios = remaining->remainingGroups->card / mediaGruposPorCandidato;

  minimoCandidatosNecessarios++;

  //printf("Função boundCalcule: Mínimo de candidatos necessários: %d\n", minimoCandidatosNecessarios);
  
  //printf("Função boundCalcule: Grupos restantes: ");
  //imprime(remaining->remainingGroups);

  if(minimoCandidatosNecessarios > solution->card)
    return 0;
  else
    return 1;

  
}