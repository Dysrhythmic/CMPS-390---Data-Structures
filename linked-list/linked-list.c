#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  int frequency;
  struct Node *next;
} Node;

typedef struct Linkedlist {
  int length;
  Node *start;
  Node *end;
} Linkedlist;

Node* newNode(int num) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->data = num;
  newNode->frequency = 1;
  newNode->next = NULL;

  return newNode;
}

Linkedlist newLinkedlist() {
  Linkedlist newList;
  newList.length = 0;
  newList.start = NULL;
  newList.end = NULL;

  return newList;
}

void prepend(Linkedlist *list, Node *node) {
  if (list->length == 0) { list->end = node; }

  node->next = list->start;
  list->start = node;
  list->length++;
}

void append(Linkedlist *list, Node *node) {
  if (list->length == 0) { list->start = node; }
  else { list->end->next = node; }

  list->end = node;
  list->length++;
}

void insert(Linkedlist *list, int num) {
  Node *node  = newNode(num);
  Node *prev = list->start;
  Node *curr = list->start;
  int searching = 1;

  while (searching) {
    if (list->length == 0) {
      searching = 0;
      prepend(list, node);
    }
    else if (curr == NULL) {
      searching = 0;
      append(list, node);
    }
    else if (curr->data == node->data) {
      searching = 0;
      curr->frequency++;
      list->length++;
    }
    else if (curr->data > node->data) {
      searching = 0;
      if (curr == list->start) { prepend(list, node); }
      else {
        node->next = curr;
        prev->next = node;
        list->length++;
      }
    }
    else if (curr->data < node->data) {
      prev = curr;
      curr = curr->next;
    }
  }
}

void delete(Linkedlist *list, int num) {
  if (list->length != 0) {
    Node *prev = list->start;
    Node *curr = list->start;
    int searching = 1;

    while(searching) {
      if (curr->data == num) {
        searching = 0;

        if (curr->frequency > 1) {
          curr->frequency--;
          list->length--;
          break;
        }
        else if (curr == list->start) { list->start = prev->next; }
        else if (curr == list->end) { list->end = prev; }

        prev->next = curr->next;
        curr->next = NULL;

        list->length -= curr->frequency;
        free(curr);
      }
      else if (curr->next == NULL) { 
        searching = 0;
        printf("Did not find %d in list.", num);
      }
      else {
        prev = curr;
        curr = curr->next;
      }
    }
  }
  else { printf("Nothing to delete."); }
}

void showList(Linkedlist *list) {
  Node *curr = list->start;

  if (curr == NULL) { printf("List is empty\n"); }
  else {
    printf("Length (including duplicate values): %d\n", list->length);
    printf("Start: %d\n", list->start->data);
    printf("End: %d\n", list->end->data);
    
    while (curr != NULL) {
      printf("%d\n", curr->data);
      curr = curr->next;
    }
  }
}

void freeList(Linkedlist *list) {
  Node *prev = NULL;
  Node *curr = list->start;

  if (curr == NULL) { printf("List is already empty."); }
  else {
    while (curr != NULL) {
      prev = curr;
      curr = curr->next;
      free(prev);
    }

    list->length = 0;
    list->start = NULL;
    list->end = NULL;
  }
}

int main() {
  Linkedlist list = newLinkedlist();
  Linkedlist *listPtr = &list;

  insert(listPtr, 5);
  insert(listPtr, 2);
  insert(listPtr, 1);
  insert(listPtr, 3);
  insert(listPtr, 3);
  insert(listPtr, 4);

  delete(listPtr, 3);
  delete(listPtr, 1);
  
  showList(listPtr);

  freeList(listPtr);
}
