#include <stdio.h>
#include <stdlib.h>

struct Node
{
    void *data;
    struct Node *next;
};

struct List
{
    struct Node *head;
    struct Node *tail;
    int size;
};

struct List *createList()
{
    struct List *list = (struct List *)malloc(sizeof(struct List)); // Aloca memória para a lista
    list->head = NULL;                                              // Inicializa a cabeça da lista como NULL
    list->tail = NULL;                                              // Inicializa a fim da lista como NULL
    list->size = 0;                                                 // Inicializa o tamanho da lista como 0
    return list;
}

void addToBackOfList(struct List *list, void *data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node)); // Aloca memória para o nó
    new_node->data = data;                                              // Atribui o dado ao nó
    new_node->next = NULL;                                              // Inicializa o próximo nó como NULL
    if (list->head == NULL)                                             // Se a cabeça da lista for NULL, então a lista está vazia. Logo, o nó será a cabeça e o fim da lista
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else // Se a cabeça da lista não for NULL, então a lista não está vazia. Logo, o nó será adicionado ao fim da lista
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++; // Adiciona 1 ao tamanho da lista
}

void printList(struct List *list, void (*printData)(void *))
{
    struct Node *current = list->head; // Inicializa o nó atual como a cabeça da lista
    while (current != NULL)            // Enquanto o nó atual não for NULL, então a lista não acabou
    {
        printData(current->data); // Imprime o dado do nó atual
        current = current->next;  // Atualiza o nó atual para o próximo nó
    }
}
