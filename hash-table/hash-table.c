#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define HASH1SIZE 200
#define HASH2SIZE 400
#define HASH3SIZE 700

int genHashTableIndex(int nameHash, int tableSize) {  
  int q = 1;

  if (tableSize == HASH1SIZE) { q = 460; }
  else if (tableSize == HASH2SIZE) { q = 220; }
  else if (tableSize == HASH3SIZE) { q = 125; }
  else { printf("Invalid table size: %d", tableSize); }

  int hashIndex = ((int)((nameHash - 351) / q)) * 5;

  return hashIndex;
}

int insertName(char** table, int index, char* name) {
  int collisionFlag = 0;
  while (table[index] != NULL) {
    collisionFlag = 1;
    index++;
  }
  table[index] = (char*)malloc(strlen(name) + 1);
  strcpy(table[index], name);

  return collisionFlag;
}

void showTable(char** table, int tableSize) {
  for(int j = 0; j != tableSize; ++j) {
    char* name = table[j];
    if (name != NULL) { printf("%d: %s\n", j, table[j]); }
  }
  printf("\n");
}

void freeTable(char** table, int tableSize) {
  for (int j = 0; j != tableSize; ++j) {
    if (table[j] != NULL) { free(table[j]); }
  }
}

int main() {
  char* hashTable1[HASH1SIZE] = {NULL};
  char* hashTable2[HASH2SIZE] = {NULL};
  char* hashTable3[HASH3SIZE] = {NULL};

  int collision1Count = 0;
  int collision2Count = 0;
  int collision3Count = 0;

  char fileName[] = "input.txt";
  char line[30];
  FILE* file;
  file = fopen(fileName, "r");
  while (fgets(line, sizeof(line), file)) {
    if (line[strlen(line) - 1] == '\n') { line[strlen(line) - 1] = '\0'; }

    int nameHash = (line[0] - 'a') * (int)pow(26, 2) + (line[1] - 'a') * 26 + (line[2] - 'a');

    int index1 = genHashTableIndex(nameHash, HASH1SIZE);
    collision1Count += insertName(hashTable1, index1, line);

    int index2 = genHashTableIndex(nameHash, HASH2SIZE);
    collision2Count += insertName(hashTable2, index2, line);

    int index3 = genHashTableIndex(nameHash, HASH3SIZE);
    collision3Count += insertName(hashTable3, index3, line);
  }
  fclose(file);

  showTable(hashTable1, HASH1SIZE);
  showTable(hashTable2, HASH2SIZE);
  showTable(hashTable3, HASH3SIZE);
  printf("Collision Count for Table 1: %d\n", collision1Count);
  printf("Collision Count for Table 2: %d\n", collision2Count);
  printf("Collision Count for Table 3: %d\n", collision3Count);
  freeTable(hashTable1, HASH1SIZE);
  freeTable(hashTable2, HASH2SIZE);
  freeTable(hashTable3, HASH3SIZE);
}
