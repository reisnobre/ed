#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <string>

using namespace std;

typedef int obj_t;

typedef struct tree_st {
  obj_t info;
  struct tree_st *leftChild, *rightChild;
  struct tree_st *father;
} tree;

void init(tree *a, obj_t info);
obj_t info(tree *a);
int height(tree *a);
int depth(tree *a);
tree *father(tree *a);
tree *leftChild(tree *a);
tree *rightChild(tree *a);
void insertRightChild(tree *a, tree *c);
void insertLeftChild(tree *a, tree *c);
void removeRightChild(tree *a);
void removeLeftChild(tree *a);

void preOrder(tree *a);
void posOrder(tree *a);
void order(tree *a);

bool isOperator(char a);

int main(int argc, char const *argv[]) {
  int i;
  string expr;
  tree *main, *auxLeft, *auxRight;

  main = auxLeft = auxRight = (tree *) malloc(sizeof(tree));
  getline(cin, expr);
  for (i = 0 ; i < expr.length() ; i++) {
    if (isOperator(expr[i]) == true) {
      init(main, expr[i]);
    } else {
      init(auxLeft, expr[i - 1]);
      init(auxRight, expr[i + 1]);
      insertLeftChild(main, auxLeft);
      insertRightChild(main, auxRight);
    }
  }
  
  order(main);

  return 0;
}

bool isOperator(char a) {
  switch (a) {
    case '+':
      return true;
      break;
    case '-':
      return true;
      break;
    case '*':
      return true;
      break;
    case '/':
      return true;
      break;
    case '^':
      return true;
      break;
    default:
      return false;
      break;
  }
}
//  Funcs
void init(tree *a, obj_t info) {
  a->info = info;
  a->father = NULL;
  a->leftChild = NULL;
  a->rightChild = NULL;
}

obj_t info(tree *a) {
  if (a != NULL) {
    return a->info;
  }
  return false;
}

int height(tree *a) {
  int retHeight = -1, leftHeight, rightHeight;
  if (a != NULL) {
    leftHeight = height(leftChild(a)) + 1;
    rightHeight = height(rightChild(a)) + 1;
    retHeight = (leftHeight < rightHeight) ? leftHeight : rightHeight;
  }
  return retHeight;
}

int depth(tree *a) {
  int d = 0;
  assert(a != NULL);
  if (a->father != NULL) d = depth(a->father) + 1;
  return d;
}

tree *father(tree *a) {
  return a->father;
}

tree *leftChild(tree *a){
  tree *child = NULL;
  if (a != NULL) {
    child = a->leftChild;
  }
  return child;
}

tree *rightChild(tree *a){
  tree *child = NULL;
  if (a != NULL) {
    child = a->rightChild;
  }
  return child;
}

void insertLeftChild(tree *a, tree *c){
  assert(a != NULL && c != NULL);
  c->father = a;
  a->leftChild = c;
}

void insertRightChild(tree *a, tree *c){
  assert(a != NULL && c != NULL);
  c->father = a;
  a->rightChild = c;
}

void removeLeftChild(tree *a){
  tree *child = NULL;
  if (a != NULL) {
    child = a->leftChild;
    a->leftChild = NULL;
    if (child != NULL){
      removeLeftChild(child);
      removeRightChild(child);
    }
    free(child);
  }
  return;
}

void removeRightChild(tree *a){
  tree *child = NULL;
  if (a != NULL) {
    child = a->rightChild;
    a->rightChild = NULL;
    if (child != NULL){
      removeLeftChild(child);
      removeRightChild(child);
    }
    free(child);
  }
  return;
}

void preOrder(tree *a){
  if (a != NULL) {
    info(a);
    preOrder(leftChild(a));
    preOrder(rightChild(a));
  }
}

void posOrder(tree *a){
  if (a != NULL) {
    posOrder(leftChild(a));
    posOrder(rightChild(a));
    info(a);
  }
}

void order(tree *a){
  if (a != NULL) {
    order(leftChild(a));
    info(a);
    order(rightChild(a));
  }
}
