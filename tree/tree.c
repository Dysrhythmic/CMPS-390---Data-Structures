#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treenode-stack.h"

#define MAX_SIZE 1000

typedef struct TreeNode {
  int data;
  int frequency;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

typedef struct Tree {
  struct TreeNode *root;
  int buildComparisonCounter;
} Tree;

TreeNode* newTreeNode(int num) {
  TreeNode *newTreeNode = (TreeNode*)malloc(sizeof(TreeNode));
  newTreeNode->data = num;
  newTreeNode->frequency = 1;
  newTreeNode->left = NULL;
  newTreeNode->right = NULL;

  return newTreeNode;
}

Tree* newTree() {
  Tree *newTree = (Tree*)malloc(sizeof(Tree));
  newTree->root = NULL;
  newTree->buildComparisonCounter = 0;

  return newTree;
}

Tree* buildSimpleTree(int *arr, int arrLength) {
  int j, num, searching;
  TreeNode *curr;
  Tree *tree = newTree();

  for (j = 0; j != arrLength; ++j) {
    num = arr[j];
    if (j == 0) { tree->root = newTreeNode(num); }
    else {
      searching = 1;
      curr = tree->root;

      while (searching) {
        if (num == curr->data) { 
          searching = 0;
          curr->frequency++;

          tree->buildComparisonCounter++;
        }
        else if (num < curr->data) { 
          if (curr->left == NULL) { 
            searching = 0;
            curr->left = newTreeNode(num);
          }
          else { curr = curr->left; }

          tree->buildComparisonCounter += 2;
        }
        else if (num > curr->data) {
          if (curr->right == NULL) {
            searching = 0;
            curr->right = newTreeNode(num);
          }
          else { curr = curr->right; }

          tree->buildComparisonCounter += 3;
        }
      }
    }

    tree->buildComparisonCounter++;
  }

  return tree;
}

void inOrderPrintRecur(TreeNode *treeNode) {
  int i;

  if (treeNode->left != NULL) { inOrderPrintRecur(treeNode->left); }

  for(i = treeNode->frequency; i != 0; --i) {
    printf("%d\n", treeNode->data);
  }

  if (treeNode->right != NULL) { inOrderPrintRecur(treeNode->right); }
}

void inOrderPrintIter(Tree *tree){
  int i;
  Stack stack = newStack();
  Stack *stackPtr = &stack;
  TreeNode *curr = tree->root;

  do {
    while (curr != NULL) {
      push(stackPtr, curr);
      curr = curr->left;
    }

    if (!isEmpty(stackPtr)) {
      curr = pop(stackPtr);
      for(i = curr->frequency; i != 0; --i) {
        printf("%d\n", curr->data);
      }
      curr = curr->right;
    }
  } while (curr != NULL || !isEmpty(stackPtr));
}

void freeTreeNode(TreeNode *treeNode) {
  if (treeNode->left != NULL) { freeTreeNode(treeNode->left); }
  if (treeNode->right != NULL) { freeTreeNode(treeNode->right); }
  free(treeNode);
}

void freeTree(Tree *tree) {
  freeTreeNode(tree->root);
  free(tree);
}

int bubbleSort(int *arr, int arrLength) {
  int j, prev, curr, temp;
  int swapping = 1;
  int comparisonCount = 0;

  while(swapping) {
    swapping = 0;
    for(j = 1; j != arrLength; ++j) {
      prev = arr[j - 1];
      curr = arr[j];
      if (prev > curr) {
        arr[j - 1] = curr;
        arr[j] = prev;
        swapping = 1;
      }

      comparisonCount++;
    }
  }

  return comparisonCount;
}

int main() {
  int i = 0;
  int inputArr[MAX_SIZE];

  char fileName[] = "input.txt";
  char line[5];
  FILE* file;
  file = fopen(fileName, "r");
  while (fgets(line, sizeof(line), file)) {
    if (line[strlen(line) - 1] == '\n') { line[strlen(line) - 1] = '\0'; }
    inputArr[i] = atoi(line);
    i++;
  }
  fclose(file);

  Tree *tree = buildSimpleTree(inputArr, MAX_SIZE);
  int sortCount = bubbleSort(inputArr, MAX_SIZE);

  printf("Number of comparisons when building the tree: %d\n", tree->buildComparisonCounter);
  printf("Number of comparisons when bubble sorting the array: %d\n", sortCount);

  free(tree);
}
