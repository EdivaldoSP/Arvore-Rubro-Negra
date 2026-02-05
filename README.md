<h1 align="center">Árvore Rubro-Negro</h1>
<P>Edivaldo Sousa Pinheiro (Refatorado, Expandido e AdaptadoOriginal)</P>
<p>Gustavo Rodrigues Barcelos (Original - projeto fork - https://github.com/Gustavo01rb/Arvore-Rubro-Negra)</p>

<h2 border="none"> Introdução </h2>
<p>Árvores do tipo rubro-negra ou vermelho-preto são árvores binárias de busca balanceadas, que, de maneira simplificada, é uma árvore de busca binária que insere e remove de forma inteligente, para assegurar que a árvore permaneça aproximadamente balanceada.</p>
<p>Essa estrutura foi inventada no ano de 1972 por Rudolf Bayer, um professor emérito de informática na Universidade Técnica de Munique, que nomeou a estrutura de “Árvores binárias B simétricas” e posteriormente foi renomeada em um artigo publicado em 1978 escrito por Leonidas J. Guibas e Robert Sedgewick.</p>

<h3 border="none" align="center"> Complexidade de Tempo em Notação big O </h3>
<table align="center">
    <thead>
        <th> Algoritmo </th>
        <th> Caso médio </th>
        <th> Pior caso </th>
    </thead>
    <tbody>
        <tr>
            <td> Espaço </td>
            <td> O(n) </td>
            <td> O(n) </td>
        </tr>
        <tr>
            <td> Busca </td>
            <td> O(log n) </td>
            <td> O(log n) </td>
        </tr>
        <tr>
            <td> Inserção </td>
            <td> O(log n) </td>
            <td> O(log n) </td>
        </tr>
        <tr>
            <td> Remoção </td>
            <td> O(log n) </td>
            <td> O(log n) </td>
        </tr>
    </tbody>
</table>

<h2>Execução do código</h2>
<p>Códigos compilados via GCC (MinGW no Windows). O projeto foi unificado para facilitar a execução e testes.</p>
<p>Para compilar e rodar:</p>
<ol>
  <li><code>gcc Testes.c -o Testes.exe</code></li>
  <li><code>./Testes.exe</code></li>
</ol>
<p>O programa conta agora com um <strong>Menu Interativo Modernizado</strong>:</p>
<ul>
    <li><strong>Inserção Contínua:</strong> Permite inserir múltiplos valores sequencialmente. Ao sair (digitando 0), oferece visualização Web.</li>
    <li><strong>Remoção Completa:</strong> Permite remover nós mantendo todas as propriedades Rubro-Negras. Oferece visualização Web após a operação.</li>
    <li><strong>Visualização Web:</strong> Gera um arquivo <code>arvore.html</code> dinâmico para visualizar a estrutura da árvore no navegador.</li>
</ul>

<h2>Estrutura de dado </h2>

<p>A estrutura usada para cada nó de uma árvore rubro-negra é extremamente semelhante a de uma árvore binária simples, a principal diferença se dá no acrécimo de uma variável do tipo booleana para indicar a cor que um determinado nó representa. Nesse caso foi adotado 'false' para a cor vermelha e 'true' para a cor preta.</p>
<p>Dessa forma a estrutura de um nó possui os seguintes atributos: </p>
<ul>
  <li>Chave (Valor)</li>
  <li>Cor (Red/Black)</li>
  <li>Filho Esquerdo</li>
  <li>Filho Direito</li>
  <li>Pai</li>
</ul>
<p>Caso não exista um pai ou um filho de um nó o atributo do ponteiro correspondente apontará para NULL. Nesse código considera-se que esses valores 'NULL' possuem a cor negra e também são tratados como se fossem ponteiros para as folhas da árvore</p>

~~~C
struct Tree{
    capsule dado;
    bool cor; // false = vermelho; true = preto
    Tree *esq;
    Tree *dir;
    Tree *pai;
};
~~~


<h2>Propriedades</h2>

<p> Uma árvore Rubro-Negra é uma árvore de busca binária que satisfaz as seguintes propriedades Rubro-Negra:<p>
<ol>
  <li>Um nó é vermelho ou é preto</li>
  <li>A raiz é preta</li>
  <li>Toda folha (NULL) é preta</li>
  <li> Se um nó é vermelho então ambos os seus filhos são pretos</li>
  <li>Para cada nó p, todos os caminhos desde p até as folhas contêm o mesmo número de nós pretos (Altura Negra)</li>
</ol>
<p>Essas regras asseguram uma propriedade crítica das árvores rubro-negras: que o caminho mais longo da raiz a qualquer folha não seja mais do que duas vezes o caminho mais curto da raiz a qualquer outra folha naquela árvore.</p>

<h2>Rotações (Refatorado)</h2>
<p>A árvore Rubro-Negro é um sistema muito delicado, que pode ser facilmente desbalanceado a partir de operações de inserção e remoção. Para corrigir isso é utilizado um esquema de rotações.
</p>
<p><strong>Nota de Atualização:</strong> As rotações foram reescritas para utilizar manipulação segura de ponteiros, eliminando o uso excessivo de <code>malloc/free</code> que causava erros de memória nas versões anteriores. Agora elas são rápidas e seguras.</p>

<p>Existem 4 Tipos de rotação:</p>
<h4>Rotação Simples à Direita (RSD)</h4>
<p>Utilizada quando um nó à esquerda da raiz de uma subárvore precisa "subir", descendo a raiz atual para a direita.</p>
<img src="Imagens/RSD.fw.png" title="Rotação Simples a Direita">

~~~C
// ExemploSimplificado da Lógica (Rotacoes.h)
void RotateRight(Tree *no) {
    Tree *L = no->esq;
    Tree *P = no->pai;
    
    // Troca de ponteiros
    no->esq = L->dir;
    if (L->dir) L->dir->pai = no;
    
    L->dir = no;
    no->pai = L;
    
    // Ajuste do Pai
    L->pai = P;
    if (P) {
        if (P->esq == no) P->esq = L;
        else P->dir = L;
    }
}
~~~

<h4>Rotação Simples à Esquerda (RSE)</h4>
<p>O inverso da RSD. Utilizada quando um nó à direita precisa subir.</p>
<img src="Imagens/RSE.fw.png" title="Rotação Simples a Esquerda">

~~~C
// Exemplo Simplificado da Lógica (Rotacoes.h)
void RotateLeft(Tree *no) {
    Tree *R = no->dir;
    Tree *P = no->pai;
    
    no->dir = R->esq;
    if (R->esq) R->esq->pai = no;
    
    R->esq = no;
    no->pai = R;
    
    R->pai = P;
    if (P) {
        if (P->esq == no) P->esq = R;
        else P->dir = R;
    }
}
~~~

<h4>Rotações Duplas</h4>
<p>Combinações de RSE e RSD para corrigir casos de "Zig-Zag" na árvore.</p>
<ul>
    <li><strong>Rotação Dupla à Direita (RDD):</strong> RSE no filho esquerdo, depois RSD no nó.</li>
    <li><strong>Rotação Dupla à Esquerda (RDE):</strong> RSD no filho direito, depois RSE no nó.</li>
</ul>

<h2>Inserções (Correções Aplicadas)</h2>
<p>A lógica de inserção segue os 5 Casos clássicos da Árvore Rubro-Negra. </p>
<p><strong>Correções Importantes Realizadas:</strong></p>
<ul>
    <li><strong>Bug de Recursão:</strong> Corrigido loop infinito no <code>Caso1</code> que ocorria ao tentar rebalancear nós já estabilizados.</li>
    <li><strong>Raiz Vermelha:</strong> Corrigido erro no <code>Caso5</code> que deixava a raiz vermelha em rotações específicas (como na sequência 2,1,4,3,5,6,7,11). Agora a propriedade da Raiz Preta é garantida rigorosamente.</li>
</ul>

<h2>Remoções</h2>

<p>A remoção foi totalmente implementada e valida. Ela segue o algoritmo padrão <code>RB-Delete</code> com a função auxiliar <code>RB-Delete-Fixup</code> para restaurar as cores e propriedades após a retirada de um nó.</p>

<p>O processo de remoção lida com todos os casos complexos:</p>
<ol>
    <li>Nó folha vermelho (simples remoção).</li>
    <li>Nó preto com filhos (requer sucessor e rebalanceamento).</li>
    <li>Rebalanceamento propagado até a raiz (Situações 1 a 4).</li>
</ol>

<table align="center">
    <thead>
        <th> Situação </th>
        <th> Descrição </th>
    </thead>
    <tbody>
        <tr>
            <td> 1 </td>
            <td> Irmão vermelho </td>
        </tr>
        <tr>
            <td> 2 </td>
            <td> Irmão preto, ambos filhos pretos </td>
        </tr>
        <tr>
            <td> 3 </td>
            <td> Irmão preto, filho próximo vermelho </td>
        </tr>
        <tr>
            <td> 4 </td>
            <td> Irmão preto, filho distante vermelho </td>
        </tr>
    </tbody>
</table>

<h2>Visualização Web (Feature Nova)</h2>
<p>Além da visualização em terminal, o projeto agora exporta a árvore para um arquivo <code>arvore.html</code>. Isso permite visualizar a estrutura completa, cores e conexões de forma gráfica e interativa no navegador.</p>
<p>A opção é oferecida automaticamente após inserções e remoções no menu interativo.</p>

<h1>Referências</h1>

  <ul>
    <li><a href="https://pt.wikipedia.org/wiki/%C3%81rvore_AVL">https://pt.wikipedia.org/wiki/%C3%81rvore_AVL</a></li>
    <li><a href="https://pt.wikipedia.org/wiki/%C3%81rvore_rubro-negra">https://pt.wikipedia.org/wiki/%C3%81rvore_rubro-negra</a></li>
    <li>Introduction to Algorithms (Cormen, Leiserson, Rivest, Stein) - CLRS</li>
  </ul>
