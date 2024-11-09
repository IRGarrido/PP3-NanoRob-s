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
    double key;

    QueueItem(): value(numeric_limits<int>::max()), key(numeric_limits<double>::infinity()) {};

    QueueItem(int value, double key): value(value), key(key) {};
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
    void decreaseMin(int, double);
    bool isEmpty() {
        if (heapSize == 0) {
            cout << "ESVAZIOU" << endl;
            return true;
        }
        return false;
    };
    QueueItem minumum() {
        if (heapSize == 0) {
            throw out_of_range("Heap is empty, cannot access minimum.");
        }
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

    if((indexL <= heapSize) && (heap[indexL].key < heap[index].key)) {
        smallest = indexL;
    } else {
        smallest = index;
    }
    
    if((indexR <= heapSize) && (heap[indexR].key < heap[smallest].key)) {
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

    for(uint i = 1; i <= heapSize; ++i){
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
    if (heapSize == 0) {
        throw out_of_range("Heap is empty, cannot extract minimum.");
    }

    QueueItem removed = minumum();

    heap[1] = heap[heapSize];
    heapSize--;
    minHeapfy(1); 

    return removed;
};

void PriorityQueueMin::decreaseMin(int value, double key) {
    for(uint i = 1; i <= heapSize; ++i) {
        if(heap[i].value == value) {
            QueueItem novo(value, key);
            heap[i] = novo;
            buildMinHeap();
            return;
        }
    }
};

class VertexWeightPair {
public:
    Vertex vertex;
    Weight weight;
    VertexWeightPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight) {};
    ~VertexWeightPair() {};

    bool operator==(const VertexWeightPair& other) const {
        return vertex == other.vertex && weight == other.weight;
    }
};


class WeightedGraphAL {
private:
    uint numVertices;
    uint num_edges;
    list<VertexWeightPair> *adj;
public:
    WeightedGraphAL(uint);
    ~WeightedGraphAL();
    void add_edge(Vertex, Vertex, Weight);
    Weight get_weight_edge(Vertex, Vertex);

    uint get_num_vertices(){
        return numVertices;
    };
    uint get_num_edges(){
        return num_edges;
    };
    list<VertexWeightPair> get_adj(Vertex v) {
        if(v <= 0 || v > numVertices) {
            throw out_of_range("Index beyond number of vertices");
        }
        if(adj == nullptr) {
            throw invalid_argument("Nullpointer received");
        } 
        return adj[v];
    };
};

WeightedGraphAL::WeightedGraphAL(uint numVertices): numVertices(numVertices), num_edges(0) {
        adj = new list<VertexWeightPair>[numVertices+1];
};

WeightedGraphAL::~WeightedGraphAL() {
    for(uint i = 0; i <= numVertices; ++i) {
        adj[i].clear();
    }
    delete[] adj;
    adj = nullptr;
    num_edges = numVertices = 0;
};

void WeightedGraphAL::add_edge(Vertex v, Vertex u, Weight w) {
    VertexWeightPair pair_v(u, w);

    adj[v].push_back(pair_v);
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

void print_list(list<VertexWeightPair>& adj){
    for (VertexWeightPair pair: adj) {
        cout << "(" << pair.vertex-1 << ", " << pair.weight << "), ";
    }
};


void print_WeightedGraphAL(WeightedGraphAL& g) {
    for (Vertex v = 1; v <= g.get_num_vertices(); ++v){
        cout << v-1 << ": ";
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
    Dijkstra(WeightedGraphAL&, Vertex);
    ~Dijkstra();
    bool relax(VertexDijkstra&, VertexDijkstra&, Weight, PriorityQueueMin&);
    void init(WeightedGraphAL&, Vertex);
};

Dijkstra::Dijkstra(WeightedGraphAL& graph, Vertex origin): graph(graph) {
    init(graph, origin);
    PriorityQueueMin queue;

    for(uint i = 1; i <= graph.get_num_vertices(); ++i) {
        QueueItem element(listVertex[i].vertex, listVertex[i].distance);
        queue.insert(element);
        cout << element.value << " inserido na fila" << endl;
    }

    while (!queue.isEmpty()) {
        QueueItem u = queue.extractMin();
        cout << u.value << " sai da fila ( " << u.key << " )" << endl;
        minimumPath.push_back(listVertex[u.value]);

        for(VertexWeightPair& pair: graph.get_adj(u.value)) {
            if(relax(listVertex[u.value], listVertex[pair.vertex], pair.weight, queue)) {
                cout << listVertex[u.value].vertex << " e " << listVertex[pair.vertex].vertex << " relaxados para " << pair.weight << endl;
            } 
        }

    }
    
    cout << " Caminho minimo " << endl;
    for(auto vertice: minimumPath) {
        cout << "( " << vertice.vertex << " - " << vertice.distance << " ), ";
    }
    
};

Dijkstra::~Dijkstra() {
    delete[]  listVertex;
    listVertex = nullptr;
    minimumPath.clear();   
};

void Dijkstra::init(WeightedGraphAL& graph, Vertex origin) {

    listVertex = new VertexDijkstra[graph.get_num_vertices() + 1];

    for(uint i = 1; i <= graph.get_num_vertices(); ++i){
        VertexDijkstra v(i);
        listVertex[i] = v;
    }
    listVertex[origin].distance = 0;
};

bool Dijkstra::relax(VertexDijkstra& u, VertexDijkstra& v, Weight w, PriorityQueueMin& queue) {
    if(v.distance > u.distance + w) {
        v.distance = u.distance + w;
        v.previous = &u;
        queue.decreaseMin(v.vertex, u.distance + w);
        return true;
    }

    return false;
};

int main(){
    uint n_vertices = 5;

    WeightedGraphAL g(n_vertices);

    g.add_edge(1, 2, 10);
    g.add_edge(1, 4, 5);
    g.add_edge(2, 3, 1);
    g.add_edge(2, 4, 2);
    g.add_edge(3, 5, 4);
    g.add_edge(4, 2, 3);
    g.add_edge(4, 3, 9);
    g.add_edge(4, 5, 2);
    g.add_edge(5, 3, 6);
    
    cout << "numVertices: " << g.get_num_vertices() << endl;
    cout << "num_edges: " << g.get_num_edges() << endl;

    print_WeightedGraphAL(g);

    Dijkstra(g, 1);

    return 0;
};