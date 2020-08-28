#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20

typedef struct {
  char * titulo;
  int paginas;
} libro;

/* Tipos de funciones */
typedef void (*t_print)(void *);

typedef void (*t_recorre)(void *, size_t, size_t, t_print);



/* Funciones genéricas */

void recorre(t_recorre, void *, size_t, size_t, t_print);


void fordwardIterator(void * vector, size_t count, size_t size, t_print print);
void reverseIterator(void * vector, size_t count, size_t size, t_print print);
void bidirectional(void * vector, size_t count, size_t size, t_print print);

/* Funciones de impresión */

void printInt(void * vector);
void printLibro(void * l);

void *next(void * vector, void * aux, size_t count, size_t size);
void *prev(void * vector, void * aux, size_t count, size_t size);
void *begin(void * vector);
void *end(void * vector,size_t count, size_t size);

int main(int argc, const char * args []){

    int * vector = (int *) malloc(N * sizeof(int));
    
    int * aux = vector;
    int * last = vector + N;
    
    for (; aux < last; ++aux) {
        *aux = rand() % 100;
    }
    recorre(&reverseIterator, vector, N, sizeof(*vector), &printInt);
    recorre(&fordwardIterator, vector, N, sizeof(*vector), &printInt);
    recorre(&bidirectional,vector, N, sizeof(*vector), &printInt);

    free(vector);
    libro * libros = (libro *) malloc(N * sizeof(libro));
    libro * auxl = libros;
    libro * lastl = libros + N;
    int count = 0;
    for (; auxl < lastl; ++auxl) {
        auxl-> titulo = ("Title");
        auxl->paginas = count+1;
        count++;
    }
    recorre(&bidirectional,libros, N, sizeof(*libros), &printLibro);
    free(libros);
    return 0;
    
}
void recorre(t_recorre algorithm, void * vector, size_t count, size_t size, t_print print)
{
   (*algorithm)(vector, count, size, print);
}

void fordwardIterator(void * vector, size_t count, size_t size, t_print print){
    void *p;
    printf("\nForward: \n");
    p = begin(vector);
    //printf("%d", *(int*)p);
    while(next(vector, p, count, size)!=NULL){
        (*print)(p);
        p = next(vector, p, count, size);
    }
}
void reverseIterator(void * vector, size_t count, size_t size, t_print print){
    void *q;
    q = end(vector, count, size);
    //printf("%i", *(int *)q);
    printf("\nReverse: \n");
    while(prev(vector, q, count, size)!=NULL){
        (*print)(q);
        q = prev(vector, q, count, size);
    }
}
void bidirectional(void * vector, size_t count, size_t size, t_print print){
    printf("\n\nBidirectional\n ");
    fordwardIterator(vector,count, size, print);
    reverseIterator(vector,count, size, print);
}
void printInt(void * p){
    int * a = (int *)p;
    if(*a){
        printf("%i ", *a);
    }
    
}
void printLibro(void * l){
    libro * book = (libro *)l;
    if(book->paginas){
    printf("Libro: %s",book->titulo);
    printf(" %i\n", book->paginas);
    }
}

void *next(void * vector, void * aux, size_t count, size_t size){
    void * next = aux+size;
    void * start = vector+size;
    void * last = start + (count * size);

    if(next>last){
        return NULL;
    }
    else{
        return next;
    }
    
}
void *prev(void * vector, void * aux, size_t count, size_t size){
    void * prev = aux-size;
    void * start = vector-size;

    if(prev<start){
        return NULL;
    }
    else{
        return prev;
    }
}

void *begin(void * vector){
    void * begin = vector;
    return begin;
}
void *end(void * vector,size_t count, size_t size){
    void * start = vector;
    void * last = start + (count * size);
    return last;
}
