#include <iostream>
#include <list>

using namespace std;

typedef unsigned int uint;

// HEAP
class HeapBinarioMinimo {
public:
    int* heap;
    uint size;
    HeapBinarioMinimo(uint size);
    ~HeapBinarioMinimo();

    int parent(int index) {
        return index/2;
    }
    int left(int index) {
        return 2*index;
    }
    int right(int index) {
        return 2*index + 1;
    }
    
    void minHeapfy(int index);
    void buildMinHeap();
};

HeapBinarioMinimo::HeapBinarioMinimo(uint size): size(size) {
    heap = new int[size];
    buildMinHeap();
};

HeapBinarioMinimo::~HeapBinarioMinimo() {
    delete [] heap;
};

void HeapBinarioMinimo::minHeapfy(int index) {
    int indexL = left(index);
    int indexR = right(index);
    int smallest = 0;

    if(indexL <= size && heap[indexL] < heap[index]) {
        smallest = indexL;
    } else {
        smallest = index;
    }
    
    if(indexR <= size && heap[indexL] < heap[smallest]) {
        smallest = indexR;
    } 

    if(smallest != index) {
        heap[index] = heap[smallest];
        minHeapfy(smallest);
    }
};

void HeapBinarioMinimo::buildMinHeap() {
    for(int i = size/2; i >= 1; --i) {
        minHeapfy(i);
    }
};

// FILA
class ItemFila {
public:
    int valor;
    int chave;
    ItemFila(int valor, int chave): valor(valor), chave(chave) {};
    bool operator==(const ItemFila& other) const {
        return chave == other.chave;
    }
};

class FilaPrioridade {
public:
    list<ItemFila> fila;
    HeapBinarioMinimo chave;
    ~FilaPrioridade();
    void order();
    void insert(ItemFila elemento);
    void increaseMax(int elemento, int chave);
    int maximum();
    int extractMax();
};

FilaPrioridade::~FilaPrioridade() {
    fila.clear();
};

void FilaPrioridade::insert(ItemFila elemento) {
    fila.push_back(elemento);
}

void FilaPrioridade::increaseMax(int elemento, int chave) {

}

int main(){

    return 0;
};