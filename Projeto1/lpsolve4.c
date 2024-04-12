#include <stdio.h>
#include <stdlib.h>

typedef struct recursos{
  float recurso;
}recursos;

typedef struct rotas{
  int x, y;
  float capacidade, usado;
  recursos *recursosr;
}rotas;

typedef struct pacotes{
  float custo;
  recursos *recursosp;
}pacotes;

int main(){

  // Leitura inicial

  float n, m, k, q, p = 0;

  scanf("%f %f %f %f %f", &n, &m, &k, &q, &p);

  rotas *rotas_array = malloc(m * sizeof(rotas));

  if(! rotas_array){
    printf("Erro ao alocar memória\n");
    exit(1);
  }

  // Leitura das rotas
  for(int i = 0; i < m; i++){
    rotas_array[i].recursosr = malloc(k * sizeof(recursos));

    rotas_array[i].usado = 0;

    if(! rotas_array[i].recursosr){
      printf("Erro ao alocar memória\n");
      exit(1);
    }

    scanf("%d", &rotas_array[i].x);

    scanf("%d", &rotas_array[i].y);
    scanf("%f", &rotas_array[i].capacidade);

    for(int j = 0; j < k; j++){
      scanf("%f", &rotas_array[i].recursosr[j].recurso);
    }

  }

  //Leitura pacotes

  pacotes *pacotes_array = malloc(q * sizeof(pacotes));

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

    for(int j = 0; j < k; j++){
      scanf("%f", &pacotes_array[i].recursosp[j].recurso);
    }

  }

  //Início escrita

  FILE *arq = fopen("entrada.txt", "w");

  if(! arq){
    printf("Erro ao abrir arquivo\n");
    exit(1);
  }

  // Escrita da função objetivo

  fprintf(arq, "max: ");

  fprintf(arq, " 0");

  for(int i = 0; i < m; i++){
    if(rotas_array[i].x == 1){
      fprintf(arq, " + %.2f*x%d%d", p, rotas_array[i].x, rotas_array[i].y);
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
    fprintf(arq, "-%.2f <= x%d%d <= %.2f;\n", rotas_array[i].capacidade, rotas_array[i].x, rotas_array[i].y, rotas_array[i].capacidade);
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

      fprintf(arq, "%.2f*f%d%d", rotas_array[j].recursosr[i].recurso, rotas_array[j].x, rotas_array[j].y);

      if(j < m - 1){
        fprintf(arq, " + ");
      }
      
    }

    fprintf(arq, " <= 0");

    for(int j = 0; j < q; j++){

      if(pacotes_array[j].recursosp[i].recurso != 0){
        fprintf(arq, " + %.2f*y%d", pacotes_array[j].recursosp[i].recurso, j+1);
      }

    }
    fprintf(arq, ";");
    fprintf(arq, "\n\n");
  }

  fprintf(arq, "\n");
  
  int x, y;

  //Equações das rotas

  for(int i = 0; i < m; i++){
    
    //condição 1 e 4
    if (rotas_array[i].usado == 0 && rotas_array[i].y != n){
      fprintf(arq, "x%d%d", rotas_array[i].x, rotas_array[i].y);
      x = rotas_array[i].x;
      y = rotas_array[i].y;
    
      for(int j = i; j < m; j++){
        //condição 2
        if(rotas_array[j].y == y && rotas_array[j].x != x){
          fprintf(arq, " + x%d%d", rotas_array[j].x, rotas_array[j].y);
          rotas_array[j].usado = 1;
        }
      }

      fprintf(arq, " = 0");

      for(int k = i; k < m; k++){
        //condicao 3 e 1
        if(rotas_array[k].x == y && rotas_array[k].y != x && rotas_array[k].usado == 0)
          fprintf(arq, " + x%d%d", rotas_array[k].x, rotas_array[k].y);
        
      }

      fprintf(arq, ";\n");

    }
    //condição 1
    rotas_array[i].usado = 1;
  }

  return 0;
}