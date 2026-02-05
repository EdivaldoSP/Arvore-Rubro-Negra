#ifndef __ROTACOES__
#define __ROTACOES__

#include "Arvore.h"

/* Prototipos */
void RSD(Tree **t); // Rotação Simples a Direita
void RSE(Tree **t); // Rotação Simples a Esquerda
void RDD(Tree **t); // Rotação Dupla a Direita
void RDE(Tree **t); // Rotação Dupla a Esquerda

void RotateRight(Tree *no);
void RotateLeft(Tree *no);


/* Helpers de Rotação (Manipulação segura de ponteiros) */

// Rotação à Direita
void RotateRight(Tree *no) {
    Tree *L = no->esq;
    if (L == NULL) return; 

    Tree *P = no->pai;

    // Se raiz, usa Swap de Dados
    if (P == NULL) {
        capsule tempD = no->dado;
        bool tempC = no->cor;
        
        no->dado = L->dado;
        no->cor = L->cor;
        
        L->dado = tempD;
        L->cor = tempC;
        
        Tree *A = L->esq;
        Tree *B = L->dir;
        Tree *C = no->dir;
        
        no->esq = A;
        if(A) A->pai = no;
        
        no->dir = L; 
        L->pai = no;
        
        L->esq = B;
        if(B) B->pai = L;
        
        L->dir = C;
        if(C) C->pai = L;
        
    } else {
        // Rotação Padrão (Ponteiros)
        no->esq = L->dir;
        if (L->dir != NULL) L->dir->pai = no;
        
        L->pai = P;
        if (P->esq == no) P->esq = L;
        else P->dir = L;
        
        L->dir = no;
        no->pai = L;
    }
}

// Rotação à Esquerda
void RotateLeft(Tree *no) {
    Tree *R = no->dir;
    if (R == NULL) return;

    Tree *P = no->pai;

    // Se raiz, usa Swap de Dados
    if (P == NULL) {
        capsule tempD = no->dado;
        bool tempC = no->cor;
        
        no->dado = R->dado;
        no->cor = R->cor;
        
        R->dado = tempD;
        R->cor = tempC;
        
        Tree *A = no->esq;
        Tree *B = R->esq;
        Tree *C = R->dir;
        
        no->dir = C;
        if(C) C->pai = no;
        
        no->esq = R;
        R->pai = no;
        
        R->esq = A;
        if(A) A->pai = R;
        
        R->dir = B;
        if(B) B->pai = R;
        
    } else {
        // Rotação Padrão (Ponteiros)
        no->dir = R->esq;
        if (R->esq != NULL) R->esq->pai = no;
        
        R->pai = P;
        if (P->esq == no) P->esq = R;
        else P->dir = R;
        
        R->esq = no;
        no->pai = R;
    }
}


/* Rotações Wrapper (Compatibilidade) */

void RSD(Tree **t){
    Tree *no = (*t);
    // Ajusta o nó correto para descer
    if (no->pai != NULL && no->pai->esq == no) {
        RotateRight(no->pai);
    } 
    else {
        RotateRight(no);
    }
}

void RSE(Tree **t){
    Tree *no = (*t);
    if (no->pai != NULL && no->pai->dir == no) {
        RotateLeft(no->pai);
    }
    else {
        RotateLeft(no);
    }
}

void RDD(Tree **t){
    RSE(t);
    RSD(&(*t)->esq); 
}

void RDE(Tree **t){
    RSD(t);
    RSE(&(*t)->dir); 
}

#endif
