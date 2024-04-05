#include <stdio.h>
#include <stdlib.h>

typedef struct recursos{
  int recurso;
} recursos;

typedef struct rotas{
  int x, y, capacidade, usado;
  recursos *recursosr;
}rotas;

typedef struct pacotes{
  int custo;
  recursos *recursosp;
}pacotes;



int main(){

  int n, m, k, q, p, primeiro = 0;

  scanf("%d %d %d %d %d", &n, &m, &k, &q, &p);

  printf("\ncidades = %d\nrotas = %d\nrecursos = %d\npacotes = %d\nganho = %d\n", n, m, k, q, p);

  rotas *rotas_array = malloc(m * sizeof(rotas));

  if(! rotas_array){
    printf("Erro ao alocar memória\n");
    exit(1);
  }

  int rotasprimarias = 0;
  
  for(int i=0; i<m; i++){
    rotas_array[i].recursosr = malloc(k * sizeof(recursos));

    rotas_array[i].usado = 0; 

    if(! rotas_array[i].recursosr){
      printf("Erro ao alocar memória\n");
      exit(1);
    }

    scanf("%d", &rotas_array[i].x);

    scanf("%d", &rotas_array[i].y);
    scanf("%d", &rotas_array[i].capacidade);

    if(rotas_array[i].x == 1){
      printf("rotas[%d].x = %d;\n", i, rotas_array[i].x);
      printf("rotas[%d].y = %d;\n", i, rotas_array[i].y);
      rotasprimarias++;
    }

    //printf("\nrotas[%d].x = %d;\n", i, rotas_array[i].x);
    //printf("rotas[%d].y = %d;\n", i, rotas_array[i].y);
    //printf("rotas[%d].capacidade = %d;\n", i, rotas_array[i].capacidade);
    

    for(int j = 0; j < k; j++){
      scanf("%d", &rotas_array[i].recursosr[j].recurso);
      //printf("rotas[%d].recursos[%d] = %d;\n", i, j, rotas_array[i].recursosr[j].recurso);
    }

    //printf("rotas[0].recursos[0] = %d;\n", rotas_array[0].recursosr[0].recurso);

  }

  printf("rotasprimarias = %d\n", rotasprimarias);

  pacotes *pacotes_array = malloc(q * sizeof(pacotes_array));

  if(! pacotes_array){
    printf("Erro ao alocar memória\n");
    exit(1);
  }

  //printf("\nIniciando leitura dos pacotes_array!\n");

  //Leitura dos dados dos pacotes de recursos

  for(int i = 0; i < q; i++){
    pacotes_array[i].recursosp = malloc(k * sizeof(recursos));

    if(! pacotes_array[i].recursosp){
      printf("Erro ao alocar memória\n");
      exit(1);
    }

    scanf("%d", &pacotes_array[i].custo);

    for(int j = 0; j < k; j++){
      scanf("%d", &pacotes_array[i].recursosp[j].recurso);
      //printf("pacotes[%d].recursos[%d] = %d;\n", i, j, pacotes_array[i].recursosp[j].recurso);
    }

    //printf("pacotes[0].recursos[0] = %d\n", pacotes_array[0].recursosp[0].recurso);
  }

  FILE *arq = fopen("entrada.txt", "w");

  if(arq == NULL){
    printf("Erro ao abrir arquivo\n");
    exit(1);
  }

  fprintf(arq, "max: ");

  for(int i = 0; i < m; i++){
    if(rotas_array[i].x == 1){
      fprintf(arq, "%d*x%d%d", p, rotas_array[i].x, rotas_array[i].y);
      if(i < rotasprimarias - 1)
        fprintf(arq, " + ");
    }
  }

  fprintf(arq, " - ");

  for(int i = 0; i < q; i++){
    fprintf(arq, "%d*y%d", pacotes_array[i].custo, i+1);
    if(i < q - 1)
      fprintf(arq, " - ");
  }

  fprintf(arq, ";\n");

  fprintf(arq, "\n");

  //restrições

  for(int i = 0; i < m; i++){
    fprintf(arq, "-%d <= x%d%d <= %d;\n", rotas_array[i].capacidade, rotas_array[i].x, rotas_array[i].y, rotas_array[i].capacidade);
  }

  fprintf(arq, "\n");

  for(int i = 0; i < m; i++){
    fprintf(arq, "f%d%d >= -x%d%d;\n", rotas_array[i].x, rotas_array[i].y, rotas_array[i].x, rotas_array[i].y);
    fprintf(arq, "f%d%d >= x%d%d;\n", rotas_array[i].x, rotas_array[i].y, rotas_array[i].x, rotas_array[i].y);
    fprintf(arq, "f%d%d >= 0;\n", rotas_array[i].x, rotas_array[i].y);  
  }

  fprintf(arq, "\n");

  //restrições de recursos

  for(int i = 0; i < k; i++){
    for(int j = 0; j < m; j++){

      if(rotas_array[j].recursosr[i].recurso != 0){
        fprintf(arq, "%d*x%d%d", rotas_array[j].recursosr[i].recurso, rotas_array[j].x, rotas_array[j].y);

        if(j < m - 1)
          fprintf(arq, " + ");
      }
    }

    fprintf(arq, " <= ");

    for(int j = 0; j < q; j++){

      if(pacotes_array[j].recursosp[i].recurso != 0){
        fprintf(arq, "%d*y%d", pacotes_array[j].recursosp[i].recurso, j+1);

        if(j < q - 1)
          fprintf(arq, " + ");
      }

    }
    fprintf(arq, ";");
    fprintf(arq, "\n");
  }

  fprintf(arq, "\n");
  
  int x, y;
  
  for(int i = 0; i < m; i++){

    if(rotas_array[i].usado == 0){
      fprintf(arq, "x%d%d", rotas_array[i].x, rotas_array[i].y);
      x = rotas_array[i].x;
      y = rotas_array[i].y;
    }

    if(rotas_array[i].usado == 0){
      for(int j = i; j < m; j++){
        
        if(rotas_array[j].y == y && rotas_array[j].x != x){
          fprintf(arq, " + x%d%d", rotas_array[j].x, rotas_array[j].y);
        }

      }

      for(int k = i; k < m; k++){
        if(rotas_array[k].x == y && rotas_array[k].y != x && rotas_array[k].usado == 0){
          
          if (primeiro == 0){
            fprintf(arq, " = 0");
            primeiro = 1;
          }

          fprintf(arq, " + x%d%d", rotas_array[k].x, rotas_array[k].y);
          rotas_array[k].usado = 1;
        }
      }
      fprintf(arq, ";\n");
    }
    primeiro = 0;

    rotas_array[i].usado = 1;

    
  }
  
  return 0;
}