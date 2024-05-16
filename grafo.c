#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir as constantes
#define MAX_BOOKS 5
#define TITLE_LENGTH 50
#define AUTHOR_LENGTH 50

// Estrutura do Livro
typedef struct {
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int year;
} Book;

// Estrutura do Grafo
typedef struct {
    Book books[MAX_BOOKS];
    int adjMatrix[MAX_BOOKS][MAX_BOOKS];
    int numBooks;
} Graph;

// Função para inicializar o grafo
void initializeGraph(Graph* graph) {
    graph->numBooks = 0;
    for (int i = 0; i < MAX_BOOKS; i++) {
        for (int j = 0; j < MAX_BOOKS; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
}

// Função para adicionar um livro ao grafo
void addBook(Graph* graph, Book book) {
    if (graph->numBooks < MAX_BOOKS) {
        graph->books[graph->numBooks] = book;
        graph->numBooks++;
        printf("Livro adicionado: %s\n", book.title);
    } else {
        printf("O grafo está cheio. Não é possível adicionar mais livros.\n");
    }
}

// Função para adicionar uma conexão (aresta) entre dois livros
void addConnection(Graph* graph, int book1Index, int book2Index) {
    if (book1Index >= 0 && book1Index < graph->numBooks && book2Index >= 0 && book2Index < graph->numBooks) {
        graph->adjMatrix[book1Index][book2Index] = 1;
        graph->adjMatrix[book2Index][book1Index] = 1;
        printf("Conexão adicionada entre '%s' e '%s'\n", graph->books[book1Index].title, graph->books[book2Index].title);
    } else {
        printf("Índices de livros inválidos.\n");
    }
}

// Função para exibir o grafo
void displayGraph(Graph* graph) {
    printf("\nLista de Livros e suas Conexões:\n");
    for (int i = 0; i < graph->numBooks; i++) {
        printf("Livro: %s\n", graph->books[i].title);
        printf("Conexões: ");
        for (int j = 0; j < graph->numBooks; j++) {
            if (graph->adjMatrix[i][j] == 1) {
                printf("%s ", graph->books[j].title);
            }
        }
        printf("\n");
    }
}

// Função para cadastrar um livro
Book createBook() {
    Book book;
    printf("Digite o título do livro: ");
    fgets(book.title, TITLE_LENGTH, stdin);
    book.title[strcspn(book.title, "\n")] = '\0'; // Remover o '\n' do final

    printf("Digite o autor do livro: ");
    fgets(book.author, AUTHOR_LENGTH, stdin);
    book.author[strcspn(book.author, "\n")] = '\0'; // Remover o '\n' do final

    printf("Digite o ano de publicação: ");
    scanf("%d", &book.year);
    getchar(); // Limpar o buffer de entrada

    return book;
}

int main() {
    // Criação do grafo
    Graph graph;
    initializeGraph(&graph);

    // Adicionar livros ao grafo
    for (int i = 0; i < 3; i++) {
        printf("\nCadastro do Livro %d\n", i + 1);
        Book book = createBook();
        addBook(&graph, book);
    }

    // Adicionar conexões entre os livros
    addConnection(&graph, 0, 1);
    addConnection(&graph, 1, 2);

    // Exibir o grafo
    displayGraph(&graph);

    return 0;
}
