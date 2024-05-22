#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TITLE_LENGTH 50
#define AUTHOR_LENGTH 50

// Estrutura do Livro
typedef struct {
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int year;
} Book;

// Estrutura do Nó da Árvore Binária para Busca por Autor
typedef struct AuthorNode {
    Book book;
    struct AuthorNode* left;
    struct AuthorNode* right;
} AuthorNode;

// Estrutura do Nó da Árvore Binária para Busca por Título
typedef struct TitleNode {
    Book book;
    struct TitleNode* left;
    struct TitleNode* right;
} TitleNode;

// Estrutura do Nó da Árvore Binária para Busca por Ano
typedef struct YearNode {
    Book book;
    struct YearNode* left;
    struct YearNode* right;
} YearNode;

// Função para criar um novo nó da árvore
AuthorNode* createAuthorNode(Book book) {
    AuthorNode* newNode = (AuthorNode*)malloc(sizeof(AuthorNode));
    if (newNode == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    newNode->book = book;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TitleNode* createTitleNode(Book book) {
    TitleNode* newNode = (TitleNode*)malloc(sizeof(TitleNode));
    if (newNode == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    newNode->book = book;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

YearNode* createYearNode(Book book) {
    YearNode* newNode = (YearNode*)malloc(sizeof(YearNode));
    if (newNode == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    newNode->book = book;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Funções para inserir um livro nas árvores binárias
AuthorNode* insertByAuthor(AuthorNode* root, Book book) {
    if (root == NULL) {
        return createAuthorNode(book);
    }

    if (strcmp(book.author, root->book.author) < 0) {
        root->left = insertByAuthor(root->left, book);
    } else if (strcmp(book.author, root->book.author) > 0) {
        root->right = insertByAuthor(root->right, book);
    } else {
        // No caso de autores iguais, podemos decidir adicionar à direita (ou à esquerda)
        root->right = insertByAuthor(root->right, book);
    }

    return root;
}

TitleNode* insertByTitle(TitleNode* root, Book book) {
    if (root == NULL) {
        return createTitleNode(book);
    }

    if (strcmp(book.title, root->book.title) < 0) {
        root->left = insertByTitle(root->left, book);
    } else if (strcmp(book.title, root->book.title) > 0) {
        root->right = insertByTitle(root->right, book);
    } else {
        // No caso de títulos iguais, podemos decidir adicionar à direita (ou à esquerda)
        root->right = insertByTitle(root->right, book);
    }

    return root;
}

YearNode* insertByYear(YearNode* root, Book book) {
    if (root == NULL) {
        return createYearNode(book);
    }

    if (book.year < root->book.year) {
        root->left = insertByYear(root->left, book);
    } else if (book.year > root->book.year) {
        root->right = insertByYear(root->right, book);
    } else {
        // No caso de anos iguais, podemos decidir adicionar à direita (ou à esquerda)
        root->right = insertByYear(root->right, book);
    }

    return root;
}

// Funções para buscar e exibir livros nas árvores binárias
void searchByAuthor(AuthorNode* root, char* author) {
    if (root != NULL) {
        searchByAuthor(root->left, author);
        if (strcmp(root->book.author, author) == 0) {
            printf("Autor: %s, Título: %s, Ano: %d\n", root->book.author, root->book.title, root->book.year);
        }
        searchByAuthor(root->right, author);
    }
}

void searchByTitle(TitleNode* root, char* title) {
    if (root != NULL) {
        searchByTitle(root->left, title);
        if (strcmp(root->book.title, title) == 0) {
            printf("Título: %s, Autor: %s, Ano: %d\n", root->book.title, root->book.author, root->book.year);
        }
        searchByTitle(root->right, title);
    }
}

void searchByYear(YearNode* root, int year) {
    if (root != NULL) {
        searchByYear(root->left, year);
        if (root->book.year == year) {
            printf("Ano: %d, Autor: %s, Título: %s\n", root->book.year, root->book.author, root->book.title);
        }
        searchByYear(root->right, year);
    }
}

// Funções para exibir os livros em ordem nas árvores binárias (in-order traversal)
void inorderAuthor(AuthorNode* root) {
    if (root != NULL) {
        inorderAuthor(root->left);
        printf("Autor: %s, Título: %s, Ano: %d\n", root->book.author, root->book.title, root->book.year);
        inorderAuthor(root->right);
    }
}

void inorderTitle(TitleNode* root) {
    if (root != NULL) {
        inorderTitle(root->left);
        printf("Título: %s, Autor: %s, Ano: %d\n", root->book.title, root->book.author, root->book.year);
        inorderTitle(root->right);
    }
}

void inorderYear(YearNode* root) {
    if (root != NULL) {
        inorderYear(root->left);
        printf("Ano: %d, Autor: %s, Título: %s\n", root->book.year, root->book.author, root->book.title);
        inorderYear(root->right);
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
    // Ponteiros para as raízes das árvores
    AuthorNode* authorRoot = NULL;
    TitleNode* titleRoot = NULL;
    YearNode* yearRoot = NULL;

    // Loop para cadastrar e adicionar livros nas árvores
    for (int i = 0; i < 3; i++) {
        printf("\nCadastro do Livro %d\n", i + 1);

        // Criação de um livro através da função createBook
        Book book = createBook();

        // Adiciona o livro nas árvores binárias de busca
        authorRoot = insertByAuthor(authorRoot, book);
        titleRoot = insertByTitle(titleRoot, book);
        yearRoot = insertByYear(yearRoot, book);
    }

    printf("\nTodos os livros foram cadastrados e adicionados nas árvores.\n");

    // Exibir todos os livros em ordem por autor
    printf("\nLivros na árvore por autor (em ordem):\n");
    inorderAuthor(authorRoot);

    // Exibir todos os livros em ordem por título
    printf("\nLivros na árvore por título (em ordem):\n");
    inorderTitle(titleRoot);

    // Exibir todos os livros em ordem por ano
    printf("\nLivros na árvore por ano (em ordem):\n");
    inorderYear(yearRoot);

    // Buscar livros por autor
    char authorToSearch[AUTHOR_LENGTH];
    printf("\nDigite o autor a ser buscado: ");
    fgets(authorToSearch, AUTHOR_LENGTH, stdin);
    authorToSearch[strcspn(authorToSearch, "\n")] = '\0'; // Remover o '\n' do final

    printf("\nResultados da busca por autor '%s':\n", authorToSearch);
    searchByAuthor(authorRoot, authorToSearch);

    // Buscar livros por título
    char titleToSearch[TITLE_LENGTH];
    printf("\nDigite o título a ser buscado: ");
    fgets(titleToSearch, TITLE_LENGTH, stdin);
    titleToSearch[strcspn(titleToSearch, "\n")] = '\0'; // Remover o '\n' do final

    printf("\nResultados da busca por título '%s':\n", titleToSearch);
    searchByTitle(titleRoot, titleToSearch);

    // Buscar livros por ano
    int yearToSearch;
    printf("\nDigite o ano a ser buscado: ");
    scanf("%d", &yearToSearch);
    getchar(); // Limpar o buffer de entrada

    printf("\nResultados da busca por ano '%d':\n", yearToSearch);
    searchByYear(yearRoot, yearToSearch);

    return 0;
}
