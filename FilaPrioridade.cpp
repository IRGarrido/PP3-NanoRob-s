#include <iostream>
#include <list>
#include <limits>

using namespace std;

typedef unsigned int uint;

// FILA
class ItemFila {
public:
    int valor;
    int chave;

    ItemFila(): valor(numeric_limits<int>::max()), chave(numeric_limits<int>::max()) {};

    ItemFila(int valor, int chave): valor(valor), chave(chave) {};
    bool operator==(const ItemFila& other) const {
        return valor == other.valor;
    };
};

// HEAP
class FilaPrioridadeMin {
public:
    ItemFila* heap;
    uint size;
    uint heapSize;

    FilaPrioridadeMin();
    ~FilaPrioridadeMin();

    uint parent(uint index) {
        return index/2;
    };

    uint left(uint index) {
        return 2*index;
    };

    uint right(uint index) {
        return 2*index + 1;
    };
    
    void minHeapfy(uint index);
    void buildMinHeap();
    void resizeHeap();
    void insert(ItemFila element);
    void decreaseMin();
    ItemFila minumum() {
        return heap[1];
    };
    ItemFila extractMin();
};

FilaPrioridadeMin::FilaPrioridadeMin() {
    size = 2;
    heapSize = 0;
    heap = new ItemFila[size];
};

FilaPrioridadeMin::~FilaPrioridadeMin() {
    delete [] heap;
};

void FilaPrioridadeMin::minHeapfy(uint index) {
    uint indexL = left(index);
    uint indexR = right(index);
    uint smallest;

    if(indexL <= heapSize && heap[indexL].chave < heap[index].chave) {
        smallest = indexL;
    } else {
        smallest = index;
    }
    
    if(indexR <= heapSize && heap[indexR].chave < heap[smallest].chave) {
        smallest = indexR;
    } 

    if(smallest != index) {
        ItemFila aux = heap[smallest];
        heap[smallest] = heap[index];
        heap[index] = aux;
        minHeapfy(smallest);
    }
};

void FilaPrioridadeMin::buildMinHeap() {
    for(int i = heapSize/2; i >= 1; --i) {
        minHeapfy(i);
    }
};

void FilaPrioridadeMin::resizeHeap() {
    size = 2 * size;
    ItemFila* newHeap = new ItemFila[size];

    for(uint i = 0; i <= heapSize+1; ++i){
        newHeap[i] = heap[i];
    }
    
    delete[] heap;

    heap = newHeap;
};

void FilaPrioridadeMin::insert(ItemFila element) {
    if(heapSize + 1 == size) {
        resizeHeap();
    }
    heap[heapSize+1] = element;
    heapSize++;
    buildMinHeap();
};

ItemFila FilaPrioridadeMin::extractMin() {
    ItemFila removido = minumum();
    ItemFila espacoVazio;
    heap[1] = espacoVazio;
    minHeapfy(1);
    for(uint i = 1; i <= heapSize; ++i) {
        if(heap[i].chave == numeric_limits<int>::max()){
            for(uint j = i; j <= heapSize; ++j) {
                heap[j] = heap[j+1];
            }
        }
    }
    heapSize--;

    return removido;
}

void imprimirVetor(ItemFila* vetor, uint tamanho) {
    for (uint i = 1; i < tamanho; ++i) {
        cout << i << " ";
    }
    cout << endl;
    for (uint i = 1; i < tamanho; ++i) {
        if(vetor[i].valor == numeric_limits<int>::max()) {
            cout << "inf" << " ";
        } else {
            cout << vetor[i].valor << " ";
        }
    }
    cout << endl;
    for (uint i = 1; i < tamanho; ++i) {
        if(vetor[i].chave == numeric_limits<int>::max()) {
            cout << "inf" << " ";
        } else {
            cout << vetor[i].chave << " ";
        }
    }
    cout << endl;
};

int main(){
    FilaPrioridadeMin teste;

    ItemFila a(2,4);
    ItemFila b(4,1);
    ItemFila c(8,3);
    ItemFila d(16, 2);
    ItemFila e(32, 16);
    ItemFila f(64, 9);
    ItemFila g(128, 10);
    ItemFila h(256, 14);
    ItemFila i(512, 8);
    ItemFila j(1024, 7);

    cout << numeric_limits<int>::max();
    cout << "heapSize: " << teste.heapSize << " - size: " << teste.size << endl;
    imprimirVetor(teste.heap, teste.size);
    cout << endl;
    teste.insert(a);
    cout << "heapSize: " << teste.heapSize << " - size: " << teste.size << endl;
    imprimirVetor(teste.heap, teste.size);
    cout << endl;
    teste.insert(b);
    cout << "heapSize: " << teste.heapSize << " - size: " << teste.size << endl;
    imprimirVetor(teste.heap, teste.size);
    cout << endl;
    teste.insert(c);
    cout << "heapSize: " << teste.heapSize << " - size: " << teste.size << endl;
    imprimirVetor(teste.heap, teste.size);
    cout << endl;
    teste.insert(d);
    cout << "heapSize: " << teste.heapSize << " - size: " << teste.size << endl;
    imprimirVetor(teste.heap, teste.size);
    cout << endl;
    teste.insert(e);
    cout << "heapSize: " << teste.heapSize << " - size: " << teste.size << endl;
    imprimirVetor(teste.heap, teste.size);
    cout << endl;
    teste.insert(f);
    cout << "heapSize: " << teste.heapSize << " - size: " << teste.size << endl;
    imprimirVetor(teste.heap, teste.size);
    cout << endl;
    teste.insert(g);
    cout << "heapSize: " << teste.heapSize << " - size: " << teste.size << endl;
    imprimirVetor(teste.heap, teste.size);
    cout << endl;
    teste.insert(h);
    cout << "heapSize: " << teste.heapSize << " - size: " << teste.size << endl;
    imprimirVetor(teste.heap, teste.size);
    cout << endl;
    teste.insert(i);
    cout << "heapSize: " << teste.heapSize << " - size: " << teste.size << endl;
    imprimirVetor(teste.heap, teste.size);
    cout << endl;
    teste.insert(j);
    cout << "heapSize: " << teste.heapSize << " - size: " << teste.size << endl;
    imprimirVetor(teste.heap, teste.size);
    cout << endl;
    teste.extractMin();
    cout << "heapSize: " << teste.heapSize << " - size: " << teste.size << endl;
    imprimirVetor(teste.heap, teste.size);
    cout << endl;
    return 0;
};