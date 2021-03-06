#include <iostream>
#include <cstdlib>
using namespace std;

#include <assert.h>
#define SIZE 10

// Eduardo Reis Nobre && Gabriel Tranquilli

typedef int obj_t;

typedef struct heap_st {
  obj_t items[SIZE];
  int end;
} heap;

bool enqueue(heap *p, obj_t obj);
bool empty(heap p);
obj_t dequeue(heap *p);
obj_t next(heap *p);

void status(heap h);

int main(int argc, char const *argv[]) {
  heap h;
  h.end = 0;
  obj_t o;
  int N, i = 0, value;
  char ctrl;
  std::cin >> N;
  while (N != 0) {
    for (i = 0; i < N ; i++) {
      std::cin >> ctrl;
      if (ctrl == 'E') {
        std::cin >> value;
        enqueue(&h, value);
        status(h);
      } else {
        std::cout << dequeue(&h) << '\n';
      }
    }
    while (!empty(h)) dequeue(&h);
    std::cout << '\n';
    std::cin >> N;
  }

  // while(!empty(h)) dequeue(&h); status(h);
  return 0;
}

bool enqueue (heap *p, obj_t obj) {
  int i;
  obj_t aux;
  if (p->end != SIZE) {
    p->items[p->end++] = obj;
    i = p->end;
    while ((i > 1) && (p->items[i - 1] > p->items[i/2 - 1])) {
      aux = p->items[i - 1];
      p->items[i - 1] = p->items[i / 2 - 1];
      p->items[i / 2 - 1] = aux;
      i = i / 2;
    }
    return true;
  }
  return false;
}

obj_t dequeue(heap *p) {
  int i = 1, max = 1;
  obj_t o, aux;
  bool stop = false;
  assert(p->end != 0);
  o = p->items[0]; // elemento que sai
  p->items[0] = p->items[--p->end];  // ultimo vai para o começo da fila
  while(!stop) {         // max-heapfy
    if(((2*i) <= p->end) && (p->items[i-1] < p->items[2*i-1])) max = 2*i;
    if(((2*i+1) <= p->end) && (p->items[max-i] < p->items[2*i])) max = 2*i+1;
    if(i != max) {
      aux = p->items[i-1];
      p->items[i-1] = p->items[max-1];
      p->items[max-1] = aux;
      i = max;
    } else stop = true;
  }
  return o;
}

obj_t next(heap *p) {
  return p->items[0];
}

bool empty(heap p) {
  return (p.end == 0);
}

void status(heap h) {
  int i = 0;
  if(!empty(h)) {
    do {
      std::cout << h.items[i] << ' ';
      i++;
    } while(i != h.end);
    std::cout << '\n';
  }
  return;
}
