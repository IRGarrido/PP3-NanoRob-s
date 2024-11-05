#include<iostream>
#include<list>
#include<limits>

using namespace std;

typedef unsigned int uint;
typedef unsigned int Vertex;
typedef double Weight;


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
    bool isEmpty() {
        return heap[1].key == numeric_limits<int>::max();
    };
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

class VertexWeightPair {
public:
    Vertex vertex;
    Weight weight;
    VertexWeightPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight) {};

    bool operator==(const VertexWeightPair& other) const {
        return vertex == other.vertex && weight == other.weight;
    }
};


class WeightedGraphAL {
private:
    uint num_vertices;
    uint num_edges;
    list<VertexWeightPair> *adj;
public:
    WeightedGraphAL(uint);
    ~WeightedGraphAL();
    void add_edge(Vertex, Vertex, Weight);
    Weight get_weight_edge(Vertex, Vertex);

    uint get_num_vertices(){
        return num_vertices;
    };
    uint get_num_edges(){
        return num_edges;
    };
    list<VertexWeightPair> get_adj(Vertex v) {
        return adj[v];
    };
};

WeightedGraphAL::WeightedGraphAL(uint num_vertices): num_vertices(num_vertices), num_edges(0) {
        adj = new list<VertexWeightPair>[num_vertices+1];
};

WeightedGraphAL::~WeightedGraphAL() {
    for(uint i = 0; i <= num_vertices; ++i) {
        adj[i].clear();
    }
    delete[] adj;
    num_edges = num_vertices = 0;
};

void WeightedGraphAL::add_edge(Vertex v, Vertex u, Weight w) {
    VertexWeightPair pair_v(u, w);
    VertexWeightPair pair_u(v, w);

    adj[v].push_back(pair_v);
    adj[u].push_back(pair_u);
    num_edges++;
};

Weight WeightedGraphAL::get_weight_edge(Vertex v, Vertex u) {
    for (VertexWeightPair pair: adj[v]){
        Vertex vertex = pair.vertex;
        if (vertex == u) {
            return pair.weight;
        }
    }
    return numeric_limits<Weight>::infinity();
};

void print_list(list<VertexWeightPair> adj){
    for (VertexWeightPair pair: adj) {
        cout << "(" << pair.vertex << ", " << pair.weight << "), ";
    }
};


void print_WeightedGraphAL(WeightedGraphAL& g) {
    for (Vertex v = 0; v < g.get_num_vertices(); ++v){
        cout << v << ": ";
        list<VertexWeightPair> adj = g.get_adj(v);
        print_list(adj);
        cout << endl;
    }
}; 

class VertexDijkstra {
public:
    Vertex vertex;
    uint distance;
    VertexDijkstra* previous;

    VertexDijkstra() {
        vertex = numeric_limits<Vertex>::max();
        distance = numeric_limits<uint>::max();
        previous = nullptr;
    };
    VertexDijkstra(Vertex vertex): vertex(vertex), previous(nullptr) {
        distance = numeric_limits<uint>::max();
    };

    bool operator==(const VertexDijkstra& other) const {
        return vertex == other.vertex;
    }
};


class Dijkstra {
private:
    WeightedGraphAL graph;
    VertexDijkstra* listVertex;
    list<VertexDijkstra> minimumPath;
    Vertex origin;
public:
    Dijkstra(WeightedGraphAL, Vertex);
    ~Dijkstra();
    void relax(VertexDijkstra, VertexDijkstra, Weight);
    void init(WeightedGraphAL, Vertex);
};

Dijkstra::Dijkstra(WeightedGraphAL graph, Vertex origin): graph(graph) {
    init(graph, origin);
    PriorityQueueMin queue;

    // for(VertexDijkstra vertex: listVertex) {
    //     QueueItem element(vertex.vertex, vertex.distance);
    //     queue.insert(element);
    // }

    // while (!queue.isEmpty()) {
    //     QueueItem u = queue.extractMin();
    //     for(VertexDijkstra vertex: listVertex) {
    //         if(vertex.vertex == u.value) {
    //             minimumPath.push_back(vertex);
    //         }
    //     }
        
    //     for(VertexWeightPair pair: graph.get_adj(u.value)) {
    //         for(VertexDijkstra vertex: listVertex) {
    //             if(vertex.vertex = pair.vertex) {
    //                 VertexDijkstra Vertex = vertex; 
    //             }
    //             if(vertex.vertex = u) {
    //                 VertexDijkstra Vertex = vertex; 
    //             }
    //         }
    //     };
    // }
    
};

void Dijkstra::init(WeightedGraphAL graph, Vertex origin) {

    listVertex = new VertexDijkstra[graph.get_num_vertices() + 1];

    for(uint i = 1; i <= graph.get_num_vertices(); ++i){
        VertexDijkstra v(i);
        listVertex[i] = v;
    }

    VertexDijkstra s(origin);
    s.distance = 0;
};

void Dijkstra::relax(VertexDijkstra u, VertexDijkstra v, Weight w) {
    if(v.distance > u.distance + graph.get_weight_edge(u.vertex, v.vertex)) {
        v.distance = u.distance + graph.get_weight_edge(u.vertex, v.vertex);
        v.previous = &u;
    }
};