#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEOPLE 100       // Define o número máximo de pessoas que o grafo pode ter
#define MAX_NAME_LENGTH 50   // Define o tamanho máximo do nome de uma pessoa

// Estrutura que representa uma pessoa no grafo
typedef struct Person {
    char name[MAX_NAME_LENGTH];  // Nome da pessoa
    int friends[MAX_PEOPLE];     // Lista de índices dos amigos
    int friendCount;             // Contagem de amigos
} Person;

// Estrutura que representa o grafo
typedef struct Graph {
    Person people[MAX_PEOPLE];   // Lista de pessoas no grafo
    int personCount;             // Contagem de pessoas no grafo
} Graph;

// Função para inicializar o grafo
void initializeGraph(Graph* graph) {
    graph->personCount = 0;      // Define a contagem de pessoas como 0
}

// Função para adicionar uma pessoa ao grafo
void addPerson(Graph* graph, const char* name) {
    if (graph->personCount < MAX_PEOPLE) {  // Verifica se há espaço para mais pessoas
        strcpy(graph->people[graph->personCount].name, name);  // Copia o nome para a estrutura Person
        graph->people[graph->personCount].friendCount = 0;     // Inicializa a contagem de amigos como 0
        graph->personCount++;                                  // Incrementa a contagem de pessoas
    } else {
        printf("Max number of people reached!\n");             // Mensagem de erro se o grafo estiver cheio
    }
}

// Função para conectar duas pessoas (criar uma amizade)
void connectPeople(Graph* graph, const char* name1, const char* name2) {
    int i;
    int person1Index = -1, person2Index = -1;

    // Procura os índices das duas pessoas no grafo
    for (i = 0; i < graph->personCount; i++) {
        if (strcmp(graph->people[i].name, name1) == 0) {
            person1Index = i;
        }
        if (strcmp(graph->people[i].name, name2) == 0) {
            person2Index = i;
        }
    }

    // Verifica se ambas as pessoas foram encontradas
    if (person1Index == -1 || person2Index == -1) {
        printf("One or both persons not found!\n");
        return;
    }

    // Adiciona cada pessoa à lista de amigos da outra
    graph->people[person1Index].friends[graph->people[person1Index].friendCount] = person2Index;
    graph->people[person1Index].friendCount++;

    graph->people[person2Index].friends[graph->people[person2Index].friendCount] = person1Index;
    graph->people[person2Index].friendCount++;
}

// Função para imprimir o grafo (mostrar as conexões de amizade)
void printGraph(Graph* graph) {
    int i, j;
    for (i = 0; i < graph->personCount; i++) {
        printf("%s is friends with: ", graph->people[i].name);  // Imprime o nome da pessoa
        for (j = 0; j < graph->people[i].friendCount; j++) {
            printf("%s ", graph->people[graph->people[i].friends[j]].name);  // Imprime os nomes dos amigos
        }
        printf("\n");
    }
}

int main() {
    Graph graph;
    initializeGraph(&graph);  // Inicializa o grafo

    // Adiciona pessoas ao grafo
    addPerson(&graph, "Alice");
    addPerson(&graph, "Bob");
    addPerson(&graph, "Carol");
    addPerson(&graph, "Dave");
    addPerson(&graph, "Eve");

    // Conecta as pessoas (cria amizades)
    connectPeople(&graph, "Alice", "Bob");
    connectPeople(&graph, "Alice", "Carol");
    connectPeople(&graph, "Bob", "Dave");
    connectPeople(&graph, "Bob", "Eve");
    connectPeople(&graph, "Carol", "Eve");

    // Imprime o grafo mostrando as conexões de amizade
    printGraph(&graph);

    return 0;  // Termina o programa
}
