#include <stdio.h>
#include <string.h>

// Definindo constantes
#define TITLE_LENGTH 50
#define AUTHOR_LENGTH 50
#define MAX_BOOKS 5

// Estrutura do Livro
typedef struct {
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int year;
} Book;

int main() {
    // Definindo um array de livros
    Book books[MAX_BOOKS] = {
        {"The Great Gatsby", "F. Scott Fitzgerald", 1925},
        {"1984", "George Orwell", 1949},
        {"To Kill a Mockingbird", "Harper Lee", 1960},
        {"Pride and Prejudice", "Jane Austen", 1813},
        {"The Catcher in the Rye", "J.D. Salinger", 1951}
    };

    // Acessando e exibindo informações sobre os livros
    for (int i = 0; i < MAX_BOOKS; i++) {
        printf("Livro %d:\n", i + 1);
        printf("  Título: %s\n", books[i].title);
        printf("  Autor: %s\n", books[i].author);
        printf("  Ano: %d\n\n", books[i].year);
    }

    return 0;
}
