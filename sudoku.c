#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  for(int f = 0; f < 9; f++) {
    int arreglo[10] = {0};  
    for(int c = 0; c < 9; c++) {
      int numero = n->sudo[f][c];
      if (numero != 0) { 
        if (arreglo[numero] == 1)
          return 0;  
        else
            arreglo[numero] = 1;
      }
    }
  }

  // Comprobamos columnas
  for(int f = 0; f < 9; f++) {
    int arreglo[10] = {0}; 
    for(int c = 0; c < 9; c++) {
      int numero = n->sudo[c][f];
      if (numero != 0) { 
        if (arreglo[numero] == 1)
          return 0;
        else
          arreglo[numero] = 1;
        }
    }
  }

  // Comprobamos subcuadros 3x3
  for(int i = 0; i < 9; i += 3) {
    for(int j = 0; j < 9; j += 3) {
      int arreglo[10] = {0};  
      for(int p = 0; p < 9; p++) {
        int f = i + p / 3; 
        int c = j + p % 3;  
        int numero = n->sudo[f][c];
        if (numero != 0) { 
          if (arreglo[numero] == 1)
            return 0; 
          else
            arreglo[numero] = 1;
        }
      }
    }
  }

  return 1;  
}


List* get_adj_nodes(Node* n){
    List* list = createList();
    if (n == NULL) return list;

    for(int f = 0; f < 9; f++) {
      for(int c = 0; c < 9; c++) {
        if(n->sudo[f][c] == 0) {
          for(int num = 1; num <= 9; num++) {
            Node* new_node = copy(n);
            new_node->sudo[f][c] = num;
            if(is_valid(new_node))
              pushBack(list, new_node); 
          }
            return list; 
        }
      }
    }
    return list;
}


int is_final(Node* n){
  for(int f = 0; f < 9; f++)
      for(int c = 0; c < 9; c++)
        if(n->sudo[f][c] == 0)
          return 0;
  return 1;
}

Node* DFS(Node* initial, int* cont){
    if (initial == NULL || cont == NULL) return NULL;

    Stack* S = createStack();
    push(S, initial);
    *cont = 0;

    while (!is_empty(S)) {
        Node* current = (Node*) top(S);
        pop(S);
        (*cont)++;

        if (is_final(current)) {
            return current;
        }

        List* adj = get_adj_nodes(current);
        void* ptr = first(adj);
        while (ptr != NULL) {
            push(S, ptr);
            ptr = next(adj);
        }

        free(current); // liberamos el nodo actual ya que no es solución
    }
    return NULL; 
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/