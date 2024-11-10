#include <iostream>
#include <list>
#include <limits>

using namespace std;

typedef unsigned int uint;
typedef unsigned int Vertex;
typedef double Weight;

// ELEMENTO LISTA DE ADJACENCIA DE GRAFO PONDERADO
// -----------------------------------------------------------------------------
class VertexWeightPair {
public:
    Vertex vertex;
    Weight weight;
    VertexWeightPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight) {};
};

// ARESTA
// -----------------------------------------------------------------------------
class Edge {
public:
    Vertex vertex;
    Vertex vertex2;
    Weight weight;
    Edge(Vertex vertex,Vertex vertex2, Weight weight): vertex(vertex),vertex2(vertex2), weight(weight) {};
};

// NEURONIO
// -----------------------------------------------------------------------------
class Neuron {
public:
    Vertex vertex;
    bool sick;
    Neuron(Vertex vertex): vertex(vertex), sick(false){};
};

// SEGUNDO GRAFO - BLOCOS DE NEURONIOS - NEURONIOS - PONDERADO DIRECIONAL - KRUSKAL 
// -----------------------------------------------------------------------------
class NeuronGraph {
private:
    uint numVertices;
    uint numEdges;
    uint numSickNeurons;
    list<VertexWeightPair> *adj;
    list<Neuron> listNeuron; 
    list<Edge> listEdges;
public:
    NeuronGraph(uint);
    ~NeuronGraph();
    list<Neuron>& getListNeurons() {
        return listNeuron;
    };
    list<Edge>& getListEdges() {
        return listEdges;
    };
    void addEdge(Vertex, Vertex, Weight);
    Weight getWeightEdge(Vertex, Vertex);

    uint getNumVertices() {
        return numVertices;
    };
    uint getNumEdges() {
        return numEdges;
    };
    uint getNumSickNeurons() {
        return numSickNeurons;
    };
    list<VertexWeightPair> getAdj(Vertex v) {
        return adj[v];
    };
    void turnSick(Vertex vertex) {
        for(Neuron& neuron: listNeuron) {
            if(neuron.vertex == vertex) {
                neuron.sick = true;
                numSickNeurons++;
                return;
            }
        }
    }
};

NeuronGraph::NeuronGraph(uint numVertices): numVertices(numVertices), numEdges(0) {
    adj = new list<VertexWeightPair>[numVertices+1];
    for(uint i = 1; i <= numVertices; ++i) {
        listNeuron.push_back(i);
    }
};

NeuronGraph::~NeuronGraph() {
    listNeuron.clear();
    listEdges.clear();
    delete[] adj;
    adj = nullptr;
};

void NeuronGraph::addEdge(Vertex v, Vertex u, Weight w) {
    VertexWeightPair pair_v(u, w);
    adj[v].push_back(pair_v);
    listEdges.emplace_back(u,v,w);
    numEdges++;
};

Weight NeuronGraph::getWeightEdge(Vertex v, Vertex u) {
    for (VertexWeightPair pair: adj[v]) {
        Vertex vertex = pair.vertex;
        if (vertex == u) {
            return pair.weight;
        }
    }
    return 0.0;
}

// KRUSKAL
// -----------------------------------------------------------------------------
class Kruskal {
private:
    list<Edge> forest;
public:
    list<Neuron> parent;
    Kruskal(NeuronGraph& g);
    ~Kruskal();
    list<Edge>& get_list_forest() {
        return forest;
    };
    Vertex find_set(Neuron x);
    void union_set(Neuron u, Neuron v);
    Weight getWeight();
};

Kruskal::Kruskal(NeuronGraph& g) {
    for (Neuron v: g.getListNeurons()) {
        parent.push_back(v);
    }
    g.getListEdges().sort([](const Edge& e1, const Edge& e2) {
        return e1.weight<e2.weight;
    });
    for (Edge aresta: g.getListEdges()) {
        if (find_set(aresta.vertex) != find_set(aresta.vertex2)) {
            forest.push_back(aresta);
            union_set(aresta.vertex, aresta.vertex2);
        }
    }
};

Kruskal::~Kruskal() {
    parent.clear();
    forest.clear();
};

Vertex Kruskal::find_set(Neuron x) {
    list<Neuron>::iterator it = parent.begin();
    advance(it,x.vertex-1);
    if(it->vertex!=x.vertex) {
        *it = find_set(*it);
    }
    return it->vertex;
};

void Kruskal::union_set(Neuron u, Neuron v) {
    Vertex parent_u = find_set(u);
    Vertex parent_v = find_set(v);
    for(auto it=parent.begin();it!=parent.end();++it) {
        if(it->vertex == parent_v) {
            it->vertex=parent_u;
        }
    }
};

Weight Kruskal::getWeight() {
    Weight totalWeight = 0.0;
    for (Edge& edge: forest) {
        totalWeight += edge.weight;
    }
    return totalWeight;
};

// VERTICE DO GRAFO CEREBRO
// -----------------------------------------------------------------------------
class BrainVertex {
public:
    Vertex vertex;
    NeuronGraph* neuronBlockGraph;
    BrainVertex(): vertex(numeric_limits<Vertex>::max()) {
        neuronBlockGraph = nullptr;
    };
    BrainVertex(Vertex vertex): vertex(vertex) {};
    ~BrainVertex() {
        neuronBlockGraph = nullptr;
    };
};

// PRIMEIRO GRAFO - CEREBRO - BLOCOS DE NEURONIOS - PONDERADO BIDIRECIONAL - DIJKSTRA
// -----------------------------------------------------------------------------
class BrainGraph {
private:
    uint numVertices;
    uint numEdges;
    Vertex begin;
    Vertex end;
    BrainVertex* neuronBlocks;
    list<VertexWeightPair> *adj;
    
public:
    BrainGraph(uint);
    ~BrainGraph();
    void addEdge(Vertex, Vertex, Weight);
    void setBegin(Vertex begin) {
        this->begin = begin;
    };
    void setEnd(Vertex end) {
        this->end = end;
    };
    Vertex getBegin() {
        return begin;
    }
    Vertex getEnd() {
        return end;
    }
    Weight getWeightEdge(Vertex, Vertex);

    uint getNumVertices(){
        return numVertices;
    };
    uint getNumEdges(){
        return numEdges;
    };
    list<VertexWeightPair> getAdj(Vertex v) {
        return adj[v];
    };
    NeuronGraph*& getNeuron(Vertex v) {
        return neuronBlocks[v].neuronBlockGraph;
    }
    void setNeuron(Vertex v, NeuronGraph* graph) {
        neuronBlocks[v].neuronBlockGraph = graph;
    }
};

BrainGraph::BrainGraph(uint numVertices): numVertices(numVertices), numEdges(0) {
    adj = new list<VertexWeightPair>[numVertices+1];
    neuronBlocks = new BrainVertex[numVertices+1];
    for(uint i = 1; i <= numVertices; ++i) {
        BrainVertex block(i);
        neuronBlocks[i] = block;
    }
};

BrainGraph::~BrainGraph() {
    for (uint i = 1; i <= numVertices; ++i) {
        delete neuronBlocks[i].neuronBlockGraph;
        neuronBlocks[i].neuronBlockGraph = nullptr;
    }
    delete[] adj;
    adj = nullptr;
    delete[] neuronBlocks;
    neuronBlocks = nullptr;
    numEdges = numVertices = 0;
};

void BrainGraph::addEdge(Vertex v, Vertex u, Weight w) {
    VertexWeightPair pair_v(u, w);
    VertexWeightPair pair_u(v, w);
    adj[v].push_back(pair_v);
    adj[u].push_back(pair_u);
    numEdges++;
};

Weight BrainGraph::getWeightEdge(Vertex v, Vertex u) {
    for (VertexWeightPair pair: adj[v]) {
        Vertex vertex = pair.vertex;
        if (vertex == u) {
            return pair.weight;
        }
    }
    return 0.0;
}

// ELEMENTO FILA DE PRIORIDADE
// -----------------------------------------------------------------------------
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

// FILA DE PRIORIDADE
// -----------------------------------------------------------------------------
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
            return true;
        }
        return false;
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
    heap = nullptr;
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
    QueueItem emptySpace;
    QueueItem removed = minumum();
    heap[1] = emptySpace;
    minHeapfy(1);
    for(uint i = 1; i <= heapSize; ++i) {
        if(heap[i].key == numeric_limits<double>::infinity()){
            for(uint j = i; j <= heapSize; ++j) {
                heap[j] = heap[j+1];
            }
        }
    }
    heapSize--;
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

// ITEM DIJKSTRA
// -----------------------------------------------------------------------------
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
};

// DIJKSTRA
// -----------------------------------------------------------------------------
class Dijkstra {
private:
    BrainGraph& graph;
    Vertex origin;
    VertexDijkstra* listNeuron;
    list<VertexDijkstra> distances;

public:
    Dijkstra(BrainGraph&, Vertex);
    ~Dijkstra();
    void relax(VertexDijkstra&, VertexDijkstra&, Weight, PriorityQueueMin&);
    void init(BrainGraph&, Vertex);
    void setToMinimunPath(VertexDijkstra&, list<VertexDijkstra>&);
    list<VertexDijkstra> getMinimunPath(Vertex);
};

void Dijkstra::init(BrainGraph& graph, Vertex origin) {
    listNeuron = new VertexDijkstra[graph.getNumVertices() + 1];
    for(uint i = 1; i <= graph.getNumVertices(); ++i){
        VertexDijkstra v(i);
        listNeuron[i] = v;
    }
    listNeuron[origin].distance = 0;
};

void Dijkstra::relax(VertexDijkstra& u, VertexDijkstra& v, Weight w, PriorityQueueMin& queue) {
    if(v.distance > u.distance + w) {
        v.distance = u.distance + w;
        if(v.previous) {
            v.previous = nullptr;
        }
        v.previous = &u;
        queue.decreaseMin(v.vertex, u.distance + w);
    }
};

Dijkstra::Dijkstra(BrainGraph& graph, Vertex origin): graph(graph) {
    init(graph, origin);
    PriorityQueueMin queue;
    for(uint i = 1; i <= graph.getNumVertices(); ++i) {
        QueueItem element(listNeuron[i].vertex, listNeuron[i].distance);
        queue.insert(element);
        // cout << element.value << " inserido na fila" << endl;
    }
    while (!queue.isEmpty()) {
        QueueItem u = queue.extractMin();
        distances.push_back(listNeuron[u.value]);
        for(VertexWeightPair& pair: graph.getAdj(u.value)) {
            relax(listNeuron[u.value], listNeuron[pair.vertex], pair.weight, queue); 
        }
    }
};

void Dijkstra::setToMinimunPath(VertexDijkstra& vertex, list<VertexDijkstra>& minimunPath) {
    minimunPath.push_front(vertex);
    if(vertex.previous == nullptr) {
        return;
    }
    setToMinimunPath(*vertex.previous, minimunPath);
}

list<VertexDijkstra> Dijkstra::getMinimunPath(Vertex end) {
    list<VertexDijkstra> minimunPath;
    VertexDijkstra* addressVertex = nullptr;
    for(VertexDijkstra& vertex: distances) {
        if(vertex.vertex == end) {
            addressVertex = &vertex;
            break;
        }
    }

    if(addressVertex == nullptr) {
        return minimunPath;
    }

    setToMinimunPath(*addressVertex, minimunPath);

    return minimunPath;
};

Dijkstra::~Dijkstra() {
    for(VertexDijkstra& element: distances) {
        if(element.previous) {
            element.previous = nullptr;
        }
    }
    distances.clear();   
    delete[]  listNeuron;
    listNeuron = nullptr;
};

// MAIN
// -----------------------------------------------------------------------------
int main(){
    int numVerticesBrainGraph,  numEdgesBrainGraph;
    cin >> numVerticesBrainGraph;
    cin >> numEdgesBrainGraph;
    BrainGraph brain(numVerticesBrainGraph);
    for(int i = 0; i < numEdgesBrainGraph; ++i){
        Vertex u, v;
        Weight weightUV;
        cin >> u;
        cin >> v;
        cin >> weightUV;
        brain.addEdge(u, v, weightUV);
    }
    Vertex beginVertex, endVertex;
    cin >> beginVertex;
    cin >> endVertex;
    brain.setBegin(beginVertex);
    brain.setEnd(endVertex);
    for(int i = 1; i <= numVerticesBrainGraph; ++i){
        int numVerticesNeuronGraph,  numEdgesNeuronGraph;
        cin >> numVerticesNeuronGraph;
        cin >> numEdgesNeuronGraph;
        NeuronGraph* neurons = new NeuronGraph(numVerticesNeuronGraph);
        brain.setNeuron(i, neurons);
        uint numSickNeurons;
        cin >> numSickNeurons;
        for(uint j = 0; j < numSickNeurons; ++j) {
            Vertex sickNeuron;
            cin >> sickNeuron;
            brain.getNeuron(i)->turnSick(sickNeuron);
        }
        for(int j = 0; j < numEdgesNeuronGraph; ++j){
            Vertex u, v;
            Weight weightUV;
            cin >> u;
            cin >> v;
            cin >> weightUV;
            brain.getNeuron(i)->addEdge(u, v, weightUV);
        }       
    }
    Dijkstra minimunPath(brain, brain.getBegin());
    list<VertexDijkstra> path = minimunPath.getMinimunPath(brain.getEnd());
    Weight sumOfWeights = 0;
    for(VertexDijkstra vertex: path) {
        if(brain.getNeuron(vertex.vertex)->getNumSickNeurons() > 0) {
            Kruskal mst(*brain.getNeuron(vertex.vertex));
            sumOfWeights += mst.getWeight();
        }
    }
    cout << sumOfWeights;
    return 0;
};