#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Arvore.h"
#include "Insere.h"
#include "Remove.h"

// Dump Helper
void DumpTree(Tree *t, FILE *f) {
    if (t == NULL) return;
    fprintf(f, "Node: %d (%s) | Pai: %d | Esq: %d | Dir: %d\n",
        t->dado.key,
        t->cor ? "PRETO" : "VERMELHO",
        t->pai ? t->pai->dado.key : -1,
        t->esq ? t->esq->dado.key : -1,
        t->dir ? t->dir->dado.key : -1
    );
    DumpTree(t->esq, f);
    DumpTree(t->dir, f);
}

// Verification Helper
int CheckBlackHeight(Tree *t, int currentHeight, int *expectedHeight, FILE *f) {
    if (t == NULL) {
        if (*expectedHeight == -1) *expectedHeight = currentHeight + 1;
        else if (*expectedHeight != currentHeight + 1) {
             fprintf(f, "ERRO: Altura Negra inconsistente. Esperado %d, Encontrado %d\n", *expectedHeight, currentHeight + 1);
             return 0;
        }
        return 1;
    }
    if (t->cor) currentHeight++;
    else {
        if ((t->esq && !t->esq->cor) || (t->dir && !t->dir->cor)) {
            fprintf(f, "ERRO: No Vermelho %d tem filho Vermelho!\n", t->dado.key);
            return 0;
        }
    }
    return CheckBlackHeight(t->esq, currentHeight, expectedHeight, f) &&
           CheckBlackHeight(t->dir, currentHeight, expectedHeight, f);
}

void VerifyRB(Tree *root, FILE *f) {
    if (root == NULL) { fprintf(f, "Arvore Vazia (Valida)\n"); return; }
    if (!root->cor) fprintf(f, "ERRO: Raiz Vermelha!\n");
    int expectedBH = -1;
    if (CheckBlackHeight(root, 0, &expectedBH, f)) fprintf(f, "VERIFICACAO: Estrutura RB VALIDA. Altura Negra: %d\n", expectedBH);
    else fprintf(f, "VERIFICACAO: Estrutura RB INVALIDA.\n");
}

int main() {
    FILE *f = fopen("debug_remove_8.txt", "w");
    if (!f) return 1;

    Tree *raiz = CreateTree();
    int valores[] = {2, 1, 4, 3, 5, 6, 7};
    capsule temp;

    fprintf(f, "=== Construindo Base (2,1,4,3,5,6,7) ===\n");
    for(int i=0; i<7; i++) {
        temp.key = valores[i];
        Insere(&raiz, raiz, temp);
    }
    DumpTree(raiz, f);
    VerifyRB(raiz, f);

    fprintf(f, "\n=== Inserindo 8 ===\n");
    temp.key = 8;
    Insere(&raiz, raiz, temp);
    DumpTree(raiz, f);
    VerifyRB(raiz, f);

    fprintf(f, "\n=== Removendo 8 ===\n");
    temp.key = 8;
    RemoveTree(&raiz, temp);
    DumpTree(raiz, f);
    VerifyRB(raiz, f);
    
    fclose(f);
    return 0;
}
