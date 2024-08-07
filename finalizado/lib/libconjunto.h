struct conjunto {

  int max; /* tamanho maximo do vetor atualmente alocado */
  int card; /* cardinalidade, isto eh, tamanho usado ate max */
  int ptr; /* ponteiro para algum indice do vetor (iterador)*/
  int *v; /* vetor de inteiros com no maximo max elementos*/

};

typedef struct conjunto conjunto_t;

/*
 * Cria um conjunto vazio e o retorna, se falhar retorna NULL.
 * max eh o tamanho maximo do conjunto, isto eh, o tamanho maximo do vetor
 */
conjunto_t * cria_conjunto (int max);

/*
 * Remove todos os elementos do conjunto, libera espaco e devolve NULL.
 */
conjunto_t * destroi_conjunto (conjunto_t *c);

/*
 * Retorna 1 se o conjunto esta vazio e 0 caso contrario.
 */
int conjunto_vazio (conjunto_t *c);

/*
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
 */
int cardinalidade (conjunto_t *c);

/*
 * Insere o elemento no conjunto, garante que nao existam repeticoes.
 * Retorna 1 se a operacao foi bem sucedida, 0 se tenta inserir elemento existente,
 * e retorna -1 em caso de falha por falta de espaco.
 */
int insere_conjunto (conjunto_t *c, int elemento);

/*
 * Remove o elemento elemento do conjunto caso ele exista e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
 */
int retira_conjunto (conjunto_t *c, int elemento);

/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
 */
int pertence (conjunto_t *c, int elemento);

/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
 */
int contido (conjunto_t *c1, conjunto_t *c2);

/*
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
 */
int sao_iguais (conjunto_t *c1, conjunto_t *c2);

/*
 * Cria e retorna o endereco do conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna 0 se a operacao falhou.
 */
conjunto_t * cria_diferenca (conjunto_t *c1, conjunto_t *c2);

/*
 * Cria e retorna o endereco do conjunto interseccao entre os conjuntos c1 e c2.
 * Retorna 0 se a operacao falhou.
 */
conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2);

/*
 * Cria e  o endereco do conjunto uniao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2);

/*
 * Retorna uma copia do conjunto c e 0 caso nao seja possivel.
 */
conjunto_t * cria_copia (conjunto_t *c);

/*
 * Imprime os elementos do conjunto sempre em ordem crescente,
 * mesmo que a estrutura interna nao garanta isso.
 */
void imprime (conjunto_t *c);


int conta_iguais(conjunto_t *c1, conjunto_t *c2);

conjunto_t *cria_uniao_ordenado(conjunto_t *c1, conjunto_t *c2);

int insere_conjunto_ordenado(conjunto_t *c, int elemento);

void compara_e_retira(conjunto_t *c1, conjunto_t *c2);

int retira_conjunto_sem_ordenacao(conjunto_t *c, int elemento);

int pertence_sem_ordenacao(conjunto_t *c, int elemento);