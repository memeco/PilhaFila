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

// Estrutura do Nó da Lista Encadeada
typedef struct Node {
    Book book;
    struct Node* next;
} Node;

// Função para criar um novo nó
Node* createNode(Book book) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    newNode->book = book;
    newNode->next = NULL;
    return newNode;
}

// Função para inserir um livro na lista (no início)
void insertAtBeginning(Node** head, Book book) {
    Node* newNode = createNode(book);
    newNode->next = *head;
    *head = newNode;
    printf("Livro inserido na lista: %s\n", book.title);
}

// Função para remover um livro da lista (do início)
Book removeFromBeginning(Node** head) {
    if (*head == NULL) {
        printf("A lista está vazia. Não há livros para remover.\n");
        Book emptyBook = {"", "", 0};
        return emptyBook;
    } else {
        Node* temp = *head;
        Book book = temp->book;
        *head = (*head)->next;
        free(temp);
        return book;
    }
}

// Função para exibir todos os livros da lista
void displayList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("Título: %s, Autor: %s, Ano: %d\n", current->book.title, current->book.author, current->book.year);
        current = current->next;
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
    // Ponteiro para o início da lista
    Node* head = NULL;

    // Loop para cadastrar e adicionar livros na lista
    for (int i = 0; i < 3; i++) {
        printf("\nCadastro do Livro %d\n", i + 1);

        // Criação de um livro através da função createBook
        Book book = createBook();

        // Adiciona o livro na lista
        insertAtBeginning(&head, book);
    }

    printf("\nTodos os livros foram cadastrados e adicionados na lista.\n");

    // Exibir todos os livros da lista
    printf("\nLivros na lista:\n");
    displayList(head);

    // Loop para remover e mostrar todos os livros da lista
    while (head != NULL) {
        // Remove o livro do início da lista
        Book book = removeFromBeginning(&head);

        // Exibe as informações do livro removido
        printf("Livro removido da lista: %s por %s (%d)\n", book.title, book.author, book.year);
    }

    return 0;
}
