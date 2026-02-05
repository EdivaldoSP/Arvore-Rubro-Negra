#ifndef __VISUALIZER__
#define __VISUALIZER__

#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

// Helper para imprimir nós no formato JSON
void DumpNodesJSON(Tree *t, FILE *f) {
    if (t == NULL) return;
    
    int paiKey = (t->pai != NULL) ? t->pai->dado.key : -999999;
    char *cor = (t->cor == true) ? "black" : "red";
    
    fprintf(f, "{ key: %d, color: '%s', parent: %d },\n", t->dado.key, cor, paiKey);
    
    DumpNodesJSON(t->esq, f);
    DumpNodesJSON(t->dir, f);
}

void ShowWebTree(Tree *raiz) {
    FILE *f = fopen("arvore.html", "w");
    if (f == NULL) {
        printf("\nERRO: Nao foi possivel criar arvore.html\n");
        return;
    }
    
    // HTML Header e CSS
    fprintf(f, "<!DOCTYPE html>\n<html>\n<head>\n");
    // Removed auto-refresh as requested (only final view)
    // fprintf(f, "<meta http-equiv='refresh' content='1'>\n"); 
    fprintf(f, "<style>\n");
    fprintf(f, "body { font-family: sans-serif; text-align: center; }\n");
    fprintf(f, "svg { border: 1px solid #ccc; background-color: #f9f9f9; }\n");
    fprintf(f, ".node circle { stroke: #333; stroke-width: 2px; transition: all 0.5s; }\n");
    fprintf(f, ".node text { font: 14px sans-serif; fill: white; font-weight: bold; pointer-events: none; text-anchor: middle; alignment-baseline: middle; }\n");
    fprintf(f, ".link { fill: none; stroke: #555; stroke-width: 2px; transition: all 0.5s; }\n");
    fprintf(f, "</style>\n</head>\n<body>\n");
    
    fprintf(f, "<h2>Visualizacao Rubro-Negra (Final)</h2>\n");
    fprintf(f, "<div><svg width='1000' height='600' id='treeSvg'></svg></div>\n");
    
    // Script com dados da árvore
    fprintf(f, "<script>\n");
    fprintf(f, "const treeData = [\n");
    
    if (raiz != NULL) {
        DumpNodesJSON(raiz, f);
    }
    
    fprintf(f, "];\n");
    
    // Lógica JS de desenho (Inlined para ser self-contained)
    fprintf(f, "const svg = document.getElementById('treeSvg');\n");
    fprintf(f, "const width = +svg.getAttribute('width');\n");
    fprintf(f, "const height = +svg.getAttribute('height');\n");
    fprintf(f, "const nodeRadius = 20;\n");
    fprintf(f, "const levelHeight = 60;\n");
    fprintf(f, "const nodesMap = {};\n");
    fprintf(f, "let root = null;\n");
    
    fprintf(f, "treeData.forEach(d => {\n");
    fprintf(f, "  nodesMap[d.key] = { ...d, children: [], x: 0, y: 0 };\n");
    fprintf(f, "});\n");
    
    fprintf(f, "treeData.forEach(d => {\n");
    fprintf(f, "  if (d.parent === -999999) {\n");
    fprintf(f, "    root = nodesMap[d.key];\n");
    fprintf(f, "  } else {\n");
    fprintf(f, "    if (nodesMap[d.parent]) {\n");
    fprintf(f, "       if (d.key < d.parent) nodesMap[d.parent].children.push(nodesMap[d.key]);\n");
    fprintf(f, "       else nodesMap[d.parent].children.push(nodesMap[d.key]);\n");
    fprintf(f, "       // Ordenar filhos para garantir esq/dir visualmente\n");
    fprintf(f, "       nodesMap[d.parent].children.sort((a,b) => a.key - b.key);\n");
    fprintf(f, "    }\n");
    fprintf(f, "  }\n");
    fprintf(f, "});\n");

    // Algoritmo de posicionamento simples (Recursivo)
    fprintf(f, "function assignCoordinates(node, depth, minX, maxX) {\n");
    fprintf(f, "  if (!node) return;\n");
    fprintf(f, "  node.y = depth * levelHeight + 50;\n");
    fprintf(f, "  node.x = (minX + maxX) / 2;\n");
    fprintf(f, "  if (node.children.length > 0) {\n");
    fprintf(f, "     const mid = (minX + maxX) / 2;\n");
    fprintf(f, "     // Se tem 1 filho, precisamos saber se é esq ou dir pela chave\n");
    fprintf(f, "     node.children.forEach(child => {\n");
    fprintf(f, "        if (child.key < node.key) assignCoordinates(child, depth+1, minX, mid);\n");
    fprintf(f, "        else assignCoordinates(child, depth+1, mid, maxX);\n");
    fprintf(f, "     });\n");
    fprintf(f, "  }\n");
    fprintf(f, "}\n");
    
    fprintf(f, "if (root) assignCoordinates(root, 0, 0, width);\n");
    
    fprintf(f, "function drawLinks(node) {\n");
    fprintf(f, "  if(!node) return;\n");
    fprintf(f, "  node.children.forEach(child => {\n");
    fprintf(f, "     const line = document.createElementNS('http://www.w3.org/2000/svg', 'line');\n");
    fprintf(f, "     line.setAttribute('x1', node.x); line.setAttribute('y1', node.y);\n");
    fprintf(f, "     line.setAttribute('x2', child.x); line.setAttribute('y2', child.y);\n");
    fprintf(f, "     line.setAttribute('class', 'link');\n");
    fprintf(f, "     svg.appendChild(line);\n");
    fprintf(f, "     drawLinks(child);\n");
    fprintf(f, "  });\n");
    fprintf(f, "}\n");
    
    fprintf(f, "function drawNodes(node) {\n");
    fprintf(f, "  if(!node) return;\n");
    fprintf(f, "  const g = document.createElementNS('http://www.w3.org/2000/svg', 'g');\n");
    fprintf(f, "  g.setAttribute('class', 'node');\n");
    fprintf(f, "  g.setAttribute('transform', `translate(${node.x},${node.y})`);\n");
    fprintf(f, "  const circle = document.createElementNS('http://www.w3.org/2000/svg', 'circle');\n");
    fprintf(f, "  circle.setAttribute('r', nodeRadius);\n");
    fprintf(f, "  circle.setAttribute('fill', node.color);\n");
    fprintf(f, "  const text = document.createElementNS('http://www.w3.org/2000/svg', 'text');\n");
    fprintf(f, "  text.textContent = node.key;\n");
    fprintf(f, "  text.setAttribute('dy', '.3em');\n");
    fprintf(f, "  g.appendChild(circle);\n");
    fprintf(f, "  g.appendChild(text);\n");
    fprintf(f, "  svg.appendChild(g);\n");
    fprintf(f, "  node.children.forEach(drawNodes);\n");
    fprintf(f, "}\n");
    
    fprintf(f, "if(root) { drawLinks(root); drawNodes(root); }\n");
    fprintf(f, "</script>\n</body>\n</html>\n");
    
    fclose(f);
    printf("\n\tArquivo 'arvore.html' atualizado. Abrindo no navegador...\n");
    system("start arvore.html"); 
}

#endif
