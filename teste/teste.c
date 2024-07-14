#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CANDIDATES 100
#define MAX_GROUPS 100

typedef struct {
    int numGroups; // Número de grupos que o candidato pode cobrir
    int groups[MAX_GROUPS]; // IDs dos grupos que o candidato pode cobrir
} Candidate;

Candidate candidates[MAX_CANDIDATES];
bool groupCovered[MAX_GROUPS]; // Indica se um grupo já foi coberto
int numGroups, numCandidates;

void backtrack(int currentLevel, int* solution, int solutionSize) {
    if (currentLevel == numGroups) {
        printf("Solução encontrada: ");
        for (int i = 0; i < solutionSize; ++i) {
            printf("%d ", solution[i] + 1); // +1 para converter de índice de 0 para 1
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < numCandidates; ++i) {
        bool canBeAdded = false;
        for (int j = 0; j < candidates[i].numGroups; ++j) {
            if (!groupCovered[candidates[i].groups[j] - 1]) { // -1 para converter de índice de 1 para 0
                canBeAdded = true;
                break;
            }
        }

        if (canBeAdded) {
            for (int j = 0; j < candidates[i].numGroups; ++j) {
                groupCovered[candidates[i].groups[j] - 1] = true; // -1 para converter de índice de 1 para 0
            }
            solution[solutionSize++] = i; // Adiciona o candidato à solução parcial
            backtrack(currentLevel + 1, solution, solutionSize); // Vai para o próximo nível
            solution[--solutionSize] = -1; // Remove o último candidato da solução parcial (backtrack)
            
            // Restaura a cobertura dos grupos
            for (int j = 0; j < candidates[i].numGroups; ++j) {
                groupCovered[candidates[i].groups[j] - 1] = false; // -1 para converter de índice de 1 para 0
            }
        }
    }
}

int main() {
    scanf("%d %d", &numGroups, &numCandidates);
    for (int i = 0; i < numCandidates; ++i) {
        scanf("%d", &candidates[i].numGroups);
        for (int j = 0; j < candidates[i].numGroups; ++j) {
            scanf("%d", &candidates[i].groups[j]);
        }
    }

    printf("Grupos: %d\n", numGroups);
    printf("Candidatos: %d\n", numCandidates);

    for (int i = 0; i < numCandidates; ++i) {
        printf("Candidato %d: ", i);
        for (int j = 0; j < candidates[i].numGroups; ++j) {
            printf("%d ", candidates[i].groups[j]);
        }
        printf("\n");
    }

    int solution[MAX_GROUPS]; // Armazena a solução parcial
    memset(solution, -1, sizeof(solution)); // Inicializa a solução parcial

    memset(groupCovered, false, sizeof(groupCovered)); // Inicializa todos os grupos como não cobertos

    backtrack(0, solution, 0); // Começa o backtracking a partir do nível 0 com uma solução vazia

    return 0;
}
