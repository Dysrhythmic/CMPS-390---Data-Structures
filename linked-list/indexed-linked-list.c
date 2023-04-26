#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME_SIZE 32
#define CHARS_TO_CALC 3

typedef struct Node {
  char name[MAX_NAME_SIZE];
  int nameCode;
  int frequency;
  struct Node *next;
} Node;

typedef struct Linkedlist {
  int length;
  Node *start;
  Node *end;
} Linkedlist;

typedef struct Index {
  Node **indexArray;
  int countArray[26];
} Index;

int calcNameCode(char* name) {
  int nameCode = 0;
  for (int i = 0; i != strlen(name) && i != CHARS_TO_CALC; ++i) {
    nameCode += (name[i] - 'a') * (int)pow(26, CHARS_TO_CALC - 1 - i);
  }

  return nameCode;
}

int calcIndexRangeSize() {
  int e = CHARS_TO_CALC - 1;
  int nextCharValue = 0;
  int aIndexRange = pow(26, e);
  int bIndexRange = 2 * pow(26, e);
  e--;
  for (; e != 0; --e) {
    nextCharValue = 25 * pow(26, e);
    aIndexRange += nextCharValue;
    bIndexRange += nextCharValue;
  }

  return (bIndexRange - aIndexRange);
}

Node* newNode(char* name) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  strncpy(newNode->name, name, MAX_NAME_SIZE - 1);
  newNode->nameCode = calcNameCode(name);
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

Index newIndex(Linkedlist *list) {
  Index newIndex;
  Node *curr = list->start;
  newIndex.indexArray = (Node**)malloc(sizeof(Node*) * 26);
  int i;

  for (i = 0; i != 26; ++i) {
    newIndex.indexArray[i] = NULL;
    newIndex.countArray[i] = 0;
  }

  while (curr != NULL) {
    int rangeSize = calcIndexRangeSize();
    i = curr->nameCode / rangeSize;
    newIndex.countArray[i]++;
    if (newIndex.indexArray[i] == NULL) { newIndex.indexArray[i] = curr; }
    curr = curr->next;
  }

  return newIndex;
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

void insert(Linkedlist *list, char* name) {
  Node *node  = newNode(name);
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
    else if (curr->nameCode == node->nameCode) {
      searching = 0;
      curr->frequency++;
      list->length++;
    }
    else if (curr->nameCode > node->nameCode) {
      searching = 0;
      if (curr == list->start) { prepend(list, node); }
      else {
        node->next = curr;
        prev->next = node;
        list->length++;
      }
    }
    else if (curr->nameCode < node->nameCode) {
      prev = curr;
      curr = curr->next;
    }
  }
}

void delete(Linkedlist *list, char* name) {
  if (list->length != 0) {
    int num = calcNameCode(name);
    Node *prev = list->start;
    Node *curr = list->start;
    int searching = 1;

    while(searching) {
      if (curr->nameCode == num) {
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
    printf("Start: %s\n", list->start->name);
    printf("End: %s\n", list->end->name);
    
    while (curr != NULL) {
      printf("%s\n", curr->name);
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

void showIndex(Index index) {
  for (int i = 0; i != 26; ++i) {
    char letter = i + 'a';
    if (index.indexArray[i] == NULL) {
        printf("No names starting with letter %c\n\n", letter);
    } else {
        printf("First for letter %c is: %s\n", letter, index.indexArray[i]->name);
        printf("Count for letter %c is: %d\n\n", letter, index.countArray[i]);
    }
  }
}

void showSection(Index index, char section) {
  int i = section - 'a';
  Node *curr = index.indexArray[i];

  for (int j = 0; j != index.countArray[i]; ++j) {
    printf("%s\n", curr->name);
    curr = curr->next;
  }
}

int main() {
  Linkedlist list = newLinkedlist();
  Linkedlist *listPtr = &list;

  char fileName[] = "names.txt";
  char line[MAX_NAME_SIZE];
  FILE* file;
  file = fopen(fileName, "r");
  while (fgets(line, sizeof(line), file)) {
    if (line[strlen(line) - 1] == '\n') { line[strlen(line) - 1] = '\0'; }
    insert(listPtr, line);
  }
  fclose(file);
  
  delete(listPtr, "zeus");
  Index indexArray = newIndex(listPtr);

  showList(listPtr);
  printf("--------------------\n");
  showIndex(indexArray);
  printf("--------------------\n");
  showSection(indexArray, 'j');

  freeList(listPtr);
  free(indexArray.indexArray);
}
