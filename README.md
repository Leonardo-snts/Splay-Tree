# Arvore Splay Tree

Este projeto é um sistema de gerenciamento de voos baseado em uma árvore Splay. O sistema permite o cadastro, busca, e remoção de voos, além de gerar portões de desembarque para diferentes terminais de acordo com a companhia aérea.

## Funcionalidades

- Cadastrar Novo Voo: Registre um novo voo informando número, matrícula, modalidade, data e hora de chegada.
- Consultar Voo: Busque um voo pelo número e visualize detalhes como matrícula, modalidade, data e hora de chegada.
- Remover Voo: Remova um voo da base de dados.
- Imprimir Árvore: Visualize a estrutura da árvore Splay que armazena os voos.

## Como Usar

Para compilar o código, utilize um compilador C, como gcc. Execute o seguinte comando no terminal:

```
gcc splay.c -0 splay
```

Após compilar, execute o programa com:

```
./splay
```

### Opções do Menu

Cadastrar Novo Voo

- Insira o número do voo.
- Forneça a matrícula da aeronave.
- Especifique a modalidade (nacional ou internacional).
- Informe a data e hora de chegada.
- O sistema irá gerar um portão para o voo baseado na companhia aérea.

Consultar Voo

- Insira o número do voo para buscar.
= O sistema exibirá os detalhes do voo, se encontrado.

Remover Voo

- Insira o número do voo que deseja remover.
= O sistema remove o voo da árvore e confirma a remoção.

Imprimir Árvore

- Visualize a estrutura atual da árvore Splay com a lista de voos cadastrados.

#### Estrutura do Código

O sistema utiliza uma árvore Splay para armazenar e gerenciar os voos. A árvore Splay é uma estrutura de dados de árvore binária auto-balanceada que oferece boas operações de inserção, busca e remoção com complexidade amortizada O(log n).

Principais Funções

- novo_no(int Nvoo): Cria um novo nó com o número do voo fornecido.
- zig(no *x) e zag(no *x): Realizam rotações na árvore Splay para reestruturar a árvore.
- splay(no *raiz, int Nvoo): Splay realiza a operação de acesso para mover o nó com o número do voo para a raiz.
- insere(no *raiz, int Nvoo): Insere um novo nó na árvore.
- busca(no *raiz, int Nvoo): Busca um nó na árvore.
- remove_no(no *raiz, int key): Remove um nó da árvore.
- verificaTerminal(): Gera um portão com base na companhia aérea informada e determina o terminal adequado.
- printTree(no *raiz, int depth): Imprime a árvore Splay de forma hierárquica.