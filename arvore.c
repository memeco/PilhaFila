#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir as constantes
#define TITLE_LENGTH 50
#define AUTHOR_LENGTH 50

// Estrutura do Livro
typedef struct {
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int year;
} Book;

// Estrutura do Nó da Árvore Binária
typedef struct TreeNode {
    Book book;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Função para criar um novo nó da árvore
TreeNode* createNode(Book book) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    newNode->book = book;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um livro na árvore binária de busca
TreeNode* insert(TreeNode* root, Book book) {
    if (root == NULL) {
        return createNode(book);
    }

    if (strcmp(book.title, root->book.title) < 0) {
        root->left = insert(root->left, book);
    } else if (strcmp(book.title, root->book.title) > 0) {
        root->right = insert(root->right, book);
    } else {
        printf("Livro com o título '%s' já existe na árvore.\n", book.title);
    }

    return root;
}

// Função para buscar um livro na árvore binária de busca
TreeNode* search(TreeNode* root, char* title) {
    if (root == NULL || strcmp(root->book.title, title) == 0) {
        return root;
    }

    if (strcmp(title, root->book.title) < 0) {
        return search(root->left, title);
    } else {
        return search(root->right, title);
    }
}

// Função para exibir os livros em ordem na árvore binária de busca (in-order traversal)
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Título: %s, Autor: %s, Ano: %d\n", root->book.title, root->book.author, root->book.year);
        inorder(root->right);
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
    // Ponteiro para a raiz da árvore
    TreeNode* root = NULL;

    // Loop para cadastrar e adicionar livros na árvore
    for (int i = 0; i < 3; i++) {
        printf("\nCadastro do Livro %d\n", i + 1);

        // Criação de um livro através da função createBook
        Book book = createBook();

        // Adiciona o livro na árvore binária de busca
        root = insert(root, book);
    }

    printf("\nTodos os livros foram cadastrados e adicionados na árvore.\n");

    // Exibir todos os livros em ordem
    printf("\nLivros na árvore (em ordem):\n");
    inorder(root);

    // Buscar um livro na árvore
    char titleToSearch[TITLE_LENGTH];
    printf("\nDigite o título do livro a ser buscado: ");
    fgets(titleToSearch, TITLE_LENGTH, stdin);
    titleToSearch[strcspn(titleToSearch, "\n")] = '\0'; // Remover o '\n' do final

    TreeNode* found = search(root, titleToSearch);
    if (found != NULL) {
        printf("Livro encontrado: Título: %s, Autor: %s, Ano: %d\n", found->book.title, found->book.author, found->book.year);
    } else {
        printf("Livro com o título '%s' não foi encontrado.\n", titleToSearch);
    }

    return 0;
}
