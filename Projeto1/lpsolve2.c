#include <stdio.h>
#include <stdlib.h>

typedef struct recursos{
  float recurso;
} recursos;

typedef struct rotas{
  float x, y, capacidade, usado;
  recursos *recursosr;
}rotas;

typedef struct pacotes{
  float custo;
  recursos *recursosp;
}pacotes;



int main(){

  float n, m, k, q, p, primeiro = 0;

  scanf("%f %f %f %f %f", &n, &m, &k, &q, &p);

  printf("\ncidades = %f\nrotas = %f\nrecursos = %f\npacotes = %f\nganho = %f\n", n, m, k, q, p);

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

    scanf("%f", &rotas_array[i].x);

    scanf("%f", &rotas_array[i].y);
    scanf("%f", &rotas_array[i].capacidade);

    if(rotas_array[i].x == 1){
      printf("rotas[%d].x = %f;\n", i, rotas_array[i].x);
      printf("rotas[%d].y = %f;\n", i, rotas_array[i].y);
      rotasprimarias++;
    }
    
    for(int j = 0; j < k; j++){
      scanf("%f", &rotas_array[i].recursosr[j].recurso);
    }

  }

  printf("rotasprimarias = %d\n", rotasprimarias);

  pacotes *pacotes_array = malloc(q * sizeof(pacotes_array));

  if(! pacotes_array){
    printf("Erro ao alocar memória\n");
    exit(1);
  }

  for(int i = 0; i < q; i++){
    pacotes_array[i].recursosp = malloc(k * sizeof(recursos));

    if(! pacotes_array[i].recursosp){
      printf("Erro ao alocar memória\n");
      exit(1);
    }

    scanf("%f", &pacotes_array[i].custo);
    printf("pacotes[%d].custo = %f;\n", i, pacotes_array[i].custo);

    for(int j = 0; j < k; j++){
      scanf("%f", &pacotes_array[i].recursosp[j].recurso);
      printf("pacotes[%d].recursosp[%d].recurso = %f;\n", i, j, pacotes_array[i].recursosp[j].recurso);
    }

  }

  FILE *arq = fopen("entrada.txt", "w");

  if(arq == NULL){
    printf("Erro ao abrir arquivo\n");
    exit(1);
  }

// Escrita da função objetivo

  fprintf(arq, "max: ");

  for(int i = 0; i < m; i++){
    if(rotas_array[i].x == 1){
      fprintf(arq, "%.2f*x%.0f%.0f", p, rotas_array[i].x, rotas_array[i].y);
      if(i < rotasprimarias - 1)
        fprintf(arq, " + ");
    }
  }

  fprintf(arq, " - ");

  for(int i = 0; i < q; i++){
    fprintf(arq, "%.2f*y%d", pacotes_array[i].custo, i+1);
    if(i < q - 1)
      fprintf(arq, " - ");
  }

  fprintf(arq, ";\n");

  fprintf(arq, "\n");

  //restrições

  for(int i = 0; i < m; i++){
    fprintf(arq, "-%.2f <= x%.0f%.0f <= %.2f;\n", rotas_array[i].capacidade, rotas_array[i].x, rotas_array[i].y, rotas_array[i].capacidade);
  }

  fprintf(arq, "\n");

  for(int i = 0; i < m; i++){
    fprintf(arq, "f%.0f%.0f >= -x%.0f%.0f;\n", rotas_array[i].x, rotas_array[i].y, rotas_array[i].x, rotas_array[i].y);
    fprintf(arq, "f%.0f%.0f >= x%.0f%.0f;\n", rotas_array[i].x, rotas_array[i].y, rotas_array[i].x, rotas_array[i].y);
    fprintf(arq, "f%.0f%.0f >= 0;\n", rotas_array[i].x, rotas_array[i].y);  
  }

  fprintf(arq, "\n");

  //restrições de recursos

  for(int i = 0; i < k; i++){
    for(int j = 0; j < m; j++){

      if(rotas_array[j].recursosr[i].recurso != 0){
        fprintf(arq, "%.2f*f%.0f%.0f", rotas_array[j].recursosr[i].recurso, rotas_array[j].x, rotas_array[j].y);

        if(j < m - 1)
          fprintf(arq, " + ");
      }
    }

    fprintf(arq, " <= 0");

    for(int j = 0; j < q; j++){

      if(pacotes_array[j].recursosp[i].recurso != 0){
        printf("pacotes_array[%d].recursosp[%d].recurso = %.2f\n", j, i, pacotes_array[j].recursosp[i].recurso);
        fprintf(arq, " + %.2f*y%d", pacotes_array[j].recursosp[i].recurso, j+1);
      }

    }
    fprintf(arq, ";");
    fprintf(arq, "\n");
  }

  fprintf(arq, "\n");
  
  int x, y, expressoes = 0;

  //Equações das rotas
  
  for(int i = 0; i < m; i++){

    if(rotas_array[i].usado == 0 && expressoes < n-2){
      fprintf(arq, "x%.0f%.0f", rotas_array[i].x, rotas_array[i].y);
      x = rotas_array[i].x;
      y = rotas_array[i].y;
    
      for(int j = i; j < m; j++){
        
        if(rotas_array[j].y == y && rotas_array[j].x != x){
          fprintf(arq, " + x%.0f%.0f", rotas_array[j].x, rotas_array[j].y);
        }

      }

      for(int k = i; k < m; k++){
        if(rotas_array[k].x == y && rotas_array[k].y != x && rotas_array[k].usado == 0){
          
          if (primeiro == 0){
            fprintf(arq, " = 0");
            primeiro = 1;
          }

          fprintf(arq, " + x%.0f%.0f", rotas_array[k].x, rotas_array[k].y);
          rotas_array[k].usado = 1;
        }
      }
      fprintf(arq, ";\n");
      expressoes++;
    }

    primeiro = 0;

    rotas_array[i].usado = 1;

  }
  
  return 0;
}