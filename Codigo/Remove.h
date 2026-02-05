#ifndef _REMOVE_
#define _REMOVE_

#include "Arvore.h"
#include "Rotacoes.h" 
#include "Exibe.h"

// Protótipos
void RemoveTree(Tree **raiz, capsule c);
void RBDeleteFixup(Tree **raiz, Tree *x, Tree *x_pai);
Tree* TreeMinimum(Tree *no);
void RBTransplant(Tree **raiz, Tree *u, Tree *v);

// Helper: Mínimo da Súbarvore
Tree* TreeMinimum(Tree *no) {
    while (no->esq != NULL)
        no = no->esq;
    return no;
}

// Helper: Transplante de Nós (Substitui subárvore u por v)
void RBTransplant(Tree **raiz, Tree *u, Tree *v) {
    if (u->pai == NULL)
        *raiz = v;
    else if (u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;
    
    if (v != NULL)
        v->pai = u->pai;
}

void RemoveTree(Tree **raiz, capsule c) {
    Tree *z = *raiz;
    Tree *x, *y;
    
    // Busca nó
    while (z != NULL) {
        if (z->dado.key == c.key) break;
        if (z->dado.key > c.key) z = z->esq;
        else z = z->dir;
    }
    
    if (z == NULL) {
        printf("\n\nERRO: Dado inexistente\n");
        return;
    }
    
    y = z;
    bool y_cor_original = y->cor;
    Tree *x_pai = NULL; 

    if (z->esq == NULL) {
        x = z->dir;
        x_pai = z->pai;
        RBTransplant(raiz, z, z->dir);
    } else if (z->dir == NULL) {
        x = z->esq;
        x_pai = z->pai;
        RBTransplant(raiz, z, z->esq);
    } else {
        y = TreeMinimum(z->dir); // Sucessor
        y_cor_original = y->cor;
        x = y->dir;
        
        if (y->pai == z) {
            x_pai = y; 
            if (x) x->pai = y; 
        } else {
            x_pai = y->pai;
            RBTransplant(raiz, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        
        RBTransplant(raiz, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }
    
    free(z);
    
    // Rebalancear se removeu Preto
    if (y_cor_original == true) {
        RBDeleteFixup(raiz, x, x_pai);
    }
}

// Rebalanceamento Pós-Remoção
void RBDeleteFixup(Tree **raiz, Tree *x, Tree *x_pai) {
    Tree *w;
    
    while (x != *raiz && (x == NULL || x->cor == true)) {
        if (x == x_pai->esq) {
            w = x_pai->dir; // Irmão Direita
            
            // Caso 1: Irmão Vermelho
            if (w != NULL && w->cor == false) {
                w->cor = true;
                x_pai->cor = false;
                RSE(&w); 
                if (w->pai == NULL) *raiz = w; 
                
                x_pai = w->esq;
                w = x_pai->dir; 
            }
            
            if (w == NULL) {
                x = x_pai;
                x_pai = x->pai;
                continue;
            }

            // Caso 2: Irmão Preto e Filhos Pretos
            if ((w->esq == NULL || w->esq->cor == true) && 
                (w->dir == NULL || w->dir->cor == true)) {
                w->cor = false;
                x = x_pai;
                x_pai = x->pai;
            } else {
                // Caso 3: Irmão Preto, Filho Esq Vermelho
                if (w->dir == NULL || w->dir->cor == true) {
                    if (w->esq != NULL) w->esq->cor = true;
                    w->cor = false;
                    RSD(&w); 
                    w = x_pai->dir;
                }
                
                // Caso 4: Irmão Preto, Filho Dir Vermelho
                w->cor = x_pai->cor;
                x_pai->cor = true;
                if (w->dir != NULL) w->dir->cor = true;
                RSE(&w); 
                if (w->pai == NULL) *raiz = w;
                
                x = *raiz; // Fim
            }
        } else {
            // Espelho (x é filho direita)
            w = x_pai->esq; // Irmão Esquerda
            
            // Caso 1
            if (w != NULL && w->cor == false) {
                w->cor = true;
                x_pai->cor = false;
                RSD(&w); 
                if (w->pai == NULL) *raiz = w;
                
                x_pai = w->dir;
                w = x_pai->esq;
            }
            
            if (w == NULL) {
                x = x_pai;
                x_pai = x->pai;
                continue;
            }

            // Caso 2
            if ((w->dir == NULL || w->dir->cor == true) && 
                (w->esq == NULL || w->esq->cor == true)) {
                w->cor = false;
                x = x_pai;
                x_pai = x->pai;
            } else {
                // Caso 3
                if (w->esq == NULL || w->esq->cor == true) {
                    if (w->dir != NULL) w->dir->cor = true;
                    w->cor = false;
                    RSE(&w); 
                    w = x_pai->esq;
                }
                
                // Caso 4
                w->cor = x_pai->cor;
                x_pai->cor = true;
                if (w->esq != NULL) w->esq->cor = true;
                RSD(&w); 
                if (w->pai == NULL) *raiz = w;
                
                x = *raiz;
            }
        }
    }
    
    if (x != NULL)
        x->cor = true;
}

#endif