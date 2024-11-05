#include <iostream>
#include <list>
#include <limits>

using namespace std;

typedef unsigned int uint;

// FILA
class QueueItem {
public:
    int value;
    int key;

    QueueItem(): value(numeric_limits<int>::max()), key(numeric_limits<int>::max()) {};

    QueueItem(int value, int key): value(value), key(key) {};
    bool operator==(const QueueItem& other) const {
        return value == other.value;
    };
};

// HEAP
class PriorityQueueMin {
public:
    QueueItem* heap;
    uint size;
    uint heapSize;

    PriorityQueueMin();
    ~PriorityQueueMin();

    uint parent(uint index) {
        return index/2;
    };

    uint left(uint index) {
        return 2*index;
    };

    uint right(uint index) {
        return 2*index + 1;
    };
    
    void minHeapfy(uint);
    void buildMinHeap();
    void resizeHeap();
    void insert(QueueItem);
    void decreaseMin(int, int);
    QueueItem minumum() {
        return heap[1];
    };
    QueueItem extractMin();
};

PriorityQueueMin::PriorityQueueMin() {
    size = 2;
    heapSize = 0;
    heap = new QueueItem[size];
};

PriorityQueueMin::~PriorityQueueMin() {
    delete [] heap;
};

void PriorityQueueMin::minHeapfy(uint index) {
    uint indexL = left(index);
    uint indexR = right(index);
    uint smallest;

    if(indexL <= heapSize && heap[indexL].key < heap[index].key) {
        smallest = indexL;
    } else {
        smallest = index;
    }
    
    if(indexR <= heapSize && heap[indexR].key < heap[smallest].key) {
        smallest = indexR;
    } 

    if(smallest != index) {
        QueueItem aux = heap[smallest];
        heap[smallest] = heap[index];
        heap[index] = aux;
        minHeapfy(smallest);
    }
};

void PriorityQueueMin::buildMinHeap() {
    for(int i = heapSize/2; i >= 1; --i) {
        minHeapfy(i);
    }
};

void PriorityQueueMin::resizeHeap() {
    size = 2 * size;
    QueueItem* newHeap = new QueueItem[size];

    for(uint i = 0; i <= heapSize+1; ++i){
        newHeap[i] = heap[i];
    }
    
    delete[] heap;

    heap = newHeap;
};

void PriorityQueueMin::insert(QueueItem element) {
    if(heapSize + 1 == size) {
        resizeHeap();
    }
    heap[heapSize+1] = element;
    heapSize++;
    buildMinHeap();
};

QueueItem PriorityQueueMin::extractMin() {
    QueueItem removed = minumum();
    QueueItem emptySpace;
    heap[1] = emptySpace;
    minHeapfy(1);
    for(uint i = 1; i <= heapSize; ++i) {
        if(heap[i].key == numeric_limits<int>::max()){
            for(uint j = i; j <= heapSize; ++j) {
                heap[j] = heap[j+1];
            }
        }
    }
    heapSize--;

    return removed;
};

void PriorityQueueMin::decreaseMin(int previousKey, int Key) {
    if(Key < previousKey) {
        for(uint i = 1; i <= heapSize; ++i) {
            if(heap[i].key == previousKey) {
                QueueItem novo(heap[1].value, Key);
                heap[i] = novo;
                buildMinHeap();
                return;
            }
        }
    }
};

void printHeap(QueueItem* heap, uint size) {
    for (uint i = 1; i < size; ++i) {
        cout << i << " ";
    }
    cout << endl;
    for (uint i = 1; i < size; ++i) {
        if(heap[i].value == numeric_limits<int>::max()) {
            cout << "inf" << " ";
        } else {
            cout << heap[i].value << " ";
        }
    }
    cout << endl;
    for (uint i = 1; i < size; ++i) {
        if(heap[i].key == numeric_limits<int>::max()) {
            cout << "inf" << " ";
        } else {
            cout << heap[i].key << " ";
        }
    }
    cout << endl;
};

int main(){
    PriorityQueueMin test;

    QueueItem a(2,4);
    QueueItem b(4,1);
    QueueItem c(8,3);
    QueueItem d(16, 2);
    QueueItem e(32, 16);
    QueueItem f(64, 9);
    QueueItem g(128, 10);
    QueueItem h(256, 14);
    QueueItem i(512, 8);
    QueueItem j(1024, 7);

    cout << numeric_limits<int>::max();
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;
    test.insert(a);
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;
    test.insert(b);
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;
    test.insert(c);
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;
    test.insert(d);
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;
    test.insert(e);
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;
    test.insert(f);
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;
    test.insert(g);
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;
    test.insert(h);
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;
    test.insert(i);
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;
    test.insert(j);
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;
    test.extractMin();
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;
    test.decreaseMin(8, 1);
    cout << "heapSize: " << test.heapSize << " - size: " << test.size << endl;
    printHeap(test.heap, test.size);
    cout << endl;

    return 0;
};