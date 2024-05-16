#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir as constantes
#define TABLE_SIZE 10
#define TITLE_LENGTH 50
#define AUTHOR_LENGTH 50

// Estrutura do Livro
typedef struct {
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int year;
} Book;

// Estrutura do Nó da Lista Encadeada para tratamento de colisões
typedef struct Node {
    Book book;
    struct Node* next;
} Node;

// Estrutura da Tabela Hash
typedef struct {
    Node* table[TABLE_SIZE];
} HashTable;

// Função para inicializar a tabela hash
void initializeHashTable(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }
}

// Função de hash
unsigned int hash(char* title) {
    unsigned int hashValue = 0;
    for (int i = 0; title[i] != '\0'; i++) {
        hashValue = 31 * hashValue + title[i];
    }
    return hashValue % TABLE_SIZE;
}

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

// Função para inserir um livro na tabela hash
void insertBook(HashTable* hashTable, Book book) {
    unsigned int index = hash(book.title);
    Node* newNode = createNode(book);
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
    printf("Livro inserido: %s\n", book.title);
}

// Função para buscar um livro na tabela hash
Node* searchBook(HashTable* hashTable, char* title) {
    unsigned int index = hash(title);
    Node* current = hashTable->table[index];
    while (current != NULL && strcmp(current->book.title, title) != 0) {
        current = current->next;
    }
    return current;
}

// Função para remover um livro da tabela hash
void removeBook(HashTable* hashTable, char* title) {
    unsigned int index = hash(title);
    Node* current = hashTable->table[index];
    Node* previous = NULL;

    while (current != NULL && strcmp(current->book.title, title) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Livro com o título '%s' não encontrado.\n", title);
        return;
    }

    if (previous == NULL) {
        hashTable->table[index] = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Livro removido: %s\n", title);
}

// Função para exibir a tabela hash
void displayHashTable(HashTable* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Índice %d: ", i);
        Node* current = hashTable->table[i];
        while (current != NULL) {
            printf("-> [Título: %s, Autor: %s, Ano: %d] ", current->book.title, current->book.author, current->book.year);
            current = current->next;
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
    // Criação da tabela hash
    HashTable hashTable;
    initializeHashTable(&hashTable);

    // Adicionar livros à tabela hash
    for (int i = 0; i < 3; i++) {
        printf("\nCadastro do Livro %d\n", i + 1);
        Book book = createBook();
        insertBook(&hashTable, book);
    }

    // Exibir a tabela hash
    printf("\nTabela Hash:\n");
    displayHashTable(&hashTable);

    // Buscar um livro na tabela hash
    char titleToSearch[TITLE_LENGTH];
    printf("\nDigite o título do livro a ser buscado: ");
    fgets(titleToSearch, TITLE_LENGTH, stdin);
    titleToSearch[strcspn(titleToSearch, "\n")] = '\0'; // Remover o '\n' do final

    Node* found = searchBook(&hashTable, titleToSearch);
    if (found != NULL) {
        printf("Livro encontrado: Título: %s, Autor: %s, Ano: %d\n", found->book.title, found->book.author, found->book.year);
    } else {
        printf("Livro com o título '%s' não foi encontrado.\n", titleToSearch);
    }

    // Remover um livro da tabela hash
    char titleToRemove[TITLE_LENGTH];
    printf("\nDigite o título do livro a ser removido: ");
    fgets(titleToRemove, TITLE_LENGTH, stdin);
    titleToRemove[strcspn(titleToRemove, "\n")] = '\0'; // Remover o '\n' do final

    removeBook(&hashTable, titleToRemove);

    // Exibir a tabela hash após a remoção
    printf("\nTabela Hash após a remoção:\n");
    displayHashTable(&hashTable);

    return 0;
}
