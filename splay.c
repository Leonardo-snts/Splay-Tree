#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VOO 100      // número máximo de voos que podem ser registrados
#define MAX_COMPANHIA 1000 // tamanho máximo do companhia da companhia aérea
#define MAX_MATRICULA 10 // tamanho máximo da matrícula da aeronave

typedef struct no
{
    int Nvoo;
    char matricula[MAX_MATRICULA];
    char companhia[MAX_COMPANHIA];
    int portao;
    int modalidade; // 0 para nacional, 1 para internacional
    char data_chegada[20];
    char hora_chegada[10];
    int permanencia; // tempo de permanência em minutos
    struct no *esq, *dir;
} no;

no *novo_no(int Nvoo)
{
    no *temp = (no *)malloc(sizeof(no));
    temp->Nvoo = Nvoo;
    temp->esq = temp->dir = NULL;
    return temp;
}

no *zig(no *x)
{
    no *y = x->esq;
    x->esq = y->dir;
    y->dir = x;
    return y;
}

no *zag(no *x)
{
    no *y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    return y;
}

no *splay(no *raiz, int Nvoo)
{
    if (!raiz || raiz->Nvoo == Nvoo)
        return raiz;

    if (Nvoo < raiz->Nvoo)
    {
        if (!raiz->esq)
            return raiz;
        if (Nvoo < raiz->esq->Nvoo)
        {
            raiz->esq->esq = splay(raiz->esq->esq, Nvoo);
            raiz = zig(raiz);
        }
        else if (Nvoo > raiz->esq->Nvoo)
        {
            raiz->esq->dir = splay(raiz->esq->dir, Nvoo);
            if (raiz->esq->dir)
                raiz->esq = zag(raiz->esq);
        }

        if (raiz->esq)
            raiz = zig(raiz);
    }
    else
    {
        if (!raiz->dir)
            return raiz;
        if (Nvoo < raiz->dir->Nvoo)
        {
            raiz->dir->esq = splay(raiz->dir->esq, Nvoo);
            if (raiz->dir->esq)
                raiz->dir = zig(raiz->dir);
        }
        else if (Nvoo > raiz->dir->Nvoo)
        {
            raiz->dir->dir = splay(raiz->dir->dir, Nvoo);
            raiz = zag(raiz);
        }

        if (raiz->dir)
            raiz = zag(raiz);
    }

    return raiz;
}

no *insere(no *raiz, int Nvoo)
{
    if (!raiz)
        return novo_no(Nvoo);

    raiz = splay(raiz, Nvoo);

    if (raiz->Nvoo == Nvoo)
        return raiz;

    no *novo = novo_no(Nvoo);

    if (Nvoo < raiz->Nvoo)
    {
        novo->dir = raiz;
        novo->esq = raiz->esq;
        raiz->esq = NULL;
    }
    else
    {
        novo->esq = raiz;
        novo->dir = raiz->dir;
        raiz->dir = NULL;
    }

    return novo;
}

no *busca(no *raiz, int Nvoo)
{
    return splay(raiz, Nvoo);
}

no *remove_no(no *raiz, int key)
{
    if (raiz == NULL)
    {
        return raiz;
    }
    raiz = splay(raiz, key);

    if (raiz->Nvoo != key)
    {
        return raiz;
    }

    if (raiz->esq == NULL)
    {
        no *temp = raiz->dir;
        free(raiz);
        return temp;
    }
    no *maxesq = raiz->esq;
    while (maxesq->dir != NULL)
    {
        maxesq = maxesq->dir;
    }
    raiz = splay(raiz, maxesq->Nvoo);
    raiz->dir = maxesq->dir;
    free(maxesq);
    return raiz;
}

no *search(no *raiz, int key)
{
    raiz = splay(raiz, key);
    if (raiz == NULL || raiz->Nvoo != key)
    {
        return NULL;
    }
    return raiz;
}

void geraPortao(int terminal)
{
    int min, max;
    switch (terminal)
    {
    case 1:
        min = 101;
        max = 109;
        break;
    case 2:
        min = 201;
        max = 246;
        break;
    case 3:
        min = 301;
        max = 326;
        break;
    default:
        printf("Terminal inválido.\n");
        return;
    }

    int num = rand() % (max - min + 1) + min;
    printf("%d\n", num);
}

int estaNaLista(char **lista, int tamanhoLista, char *companhia)
{
    for (int i = 0; i < tamanhoLista; i++)
    {
        if (strcmp(lista[i], companhia) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void verificaTerminal()
{
    char companhia[100];
    char *T1[] = {"Azul"};
    char *T2[] = {"Aerolineas", "Argentinas", "Aeromexico", "Air Europa", "Austral Lineas Aereas", "Avianca", "Boliviana de Aviacion", "Copa Airlines", "Cubana de Aviacion", "Delta Air Lines", "Ethiopian Airlines", "Gol", "Latam", "Oceanair", "Passaredo", "Royal Air Maroc", "TAAG", "Taca"};
    char *T3[] = {"Air Canada", "Air China", "Air France", "Alitalia", "American Airlines", "British Airways", "Emirates", "Etihad Airways", "Iberia", "KLM", "Korean Air", "Latam", "Lufthansa", "Qatar Airways", "Singapore Airlines", "South African Airways", "Swissair", "TAP", "Turkish Airlines", "United Airlines"};

    int tamanhoT1 = 1, tamanhoT2 = 17, tamanhoT3 = 20;

    printf("Digite uma companhia: ");
    scanf("%s", companhia);

    if (estaNaLista(T1, tamanhoT1, companhia))
    {
        printf("DESLOCAR aeronave para portão: ");
        geraPortao(1);
        printf("Terminal 1.\n");
    }
    else if (estaNaLista(T2, tamanhoT2, companhia))
    {
        printf("DESLOCAR aeronave para portão: ");
        geraPortao(2);
        printf("Terminal 2.\n");
    }
    else if (estaNaLista(T3, tamanhoT3, companhia))
    {
        printf("DESLOCAR aeronave para portão: ");
        geraPortao(3);
        printf("Terminal 3.\n");
    }
    else
    {
        printf("Companhia não encontrada\n");
    }
}

void printTree(no *raiz, int depth)
{
    if (raiz == NULL)
    {
        return;
    }

    printTree(raiz->dir, depth + 1);

    for (int i = 0; i < depth; i++)
    {
        printf("    ");
    }

    printf("%d\n", raiz->Nvoo);

    printTree(raiz->esq, depth + 1);
}

int main()
{
    no *raiz = NULL;
    int opcao;
    int Nvoo, dia, mes, ano, hora, min, seg;
    char matricula[MAX_MATRICULA];
    char modalidade[20];
    
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios
    
    do
    {
        printf("Selecione uma opção:\n");
        printf("1 - Cadastrar novo voo\n");
        printf("2 - Consultar voo\n");
        printf("3 - Remover voo\n");
        printf("4 - Imprimir árvore\n");
        printf("0 - Sair\n");
        scanf(" %d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Digite o número do voo: ");
            scanf("%d", &Nvoo);
            raiz = insere(raiz, Nvoo);
            printf("Digite a matrícula: ");
            scanf("%s", matricula);
            printf("Digite a modalidade (nacional/internacional): ");
            scanf("%s", modalidade);
            printf("Digite a data: (dd/mm/aaaa) ");
            scanf("%d/%d/%d", &dia, &mes, &ano);
            printf("Digite a hora: (hh:min:seg) ");
            scanf("%d:%d:%d", &hora, &min, &seg);
            verificaTerminal();
            break;
        case 2:
            printf("Digite o número do voo a ser buscado: ");
            scanf("%d", &Nvoo);
            no *resultado = search(raiz, Nvoo);
            if (resultado == NULL)
            {
                printf("Número do voo %d não encontrado!\n", Nvoo);
            }
            else
            {
                printf("Número do voo %d encontrado!\n", Nvoo);
                printf("Avião de matrícula: %s\n", resultado->matricula);
                printf("Modalidade: %s\n", resultado->modalidade == 0 ? "nacional" : "internacional");
                printf("Data de chegada: %s\n", resultado->data_chegada);
                printf("Hora de chegada: %s\n", resultado->hora_chegada);
                printf("Tempo de permanência: %d minutos\n", resultado->permanencia);
            }
            break;
        case 3:
            printf("Digite o número do voo a ser removido: ");
            scanf("%d", &Nvoo);
            raiz = remove_no(raiz, Nvoo);
            printf("Número do voo %d removido!\n", Nvoo);
            break;
        case 4:
            printf("\n");
            printTree(raiz, 0);
            printf("\n");
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}
