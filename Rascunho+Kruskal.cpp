#include<iostream>
#include<list>
#include<limits>

using namespace std;

typedef unsigned int uint;
typedef unsigned int Vertex;
typedef double Weight;

class VertexWeightPair {
public:
    Vertex vertex;
    Weight weight;
    NeuronGraph* blocoNeuronios = nullptr;
    VertexWeightPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight) {};
    bool operator==(const VertexWeightPair& other) const {
        return vertex == other.vertex && weight == other.weight;
    }
};

class Edge {
public:
    Vertex vertex;
    Vertex vertex2;
    Weight weight;
    Edge(Vertex vertex,Vertex vertex2, Weight weight): vertex(vertex),vertex2(vertex2), weight(weight) {};
};


class BrainGraph{
private:
    uint numVertices;
    uint numEdges;
    list<VertexWeightPair> *adj;
    Vertex begin;
    Vertex end;

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
};

BrainGraph::BrainGraph(uint numVertices): numVertices(numVertices), numEdges(0), begin(0), end(0) {
    adj = new list<VertexWeightPair>[numVertices];
};

BrainGraph::~BrainGraph() {
    for(uint i = 0; i < numVertices; ++i) {
        adj[i].clear();
    }
    delete[] adj;
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
    for (VertexWeightPair pair: adj[v]){
        Vertex vertex = pair.vertex;
        if (vertex == u) {
            return pair.weight;
        }
    }
    return 0.0;
}

class NeuronGraph {
private:
    uint numVertices;
    uint num_edges;
    list<VertexWeightPair> *adj;
    list<Vertex> listNeuron;
    list<Edge> listEdges;

public:
    NeuronGraph(uint);
    ~NeuronGraph();
    list<Vertex>& get_lista_vertices() {
        return listNeuron;
    };
    list<Edge>& get_lista_arestas() {
        return listEdges;
    };
    void add_edge(Vertex, Vertex, Weight);
    Weight get_weight_edge(Vertex, Vertex);

    uint get_num_vertices(){
        return numVertices;
    };
    uint get_num_edges(){
        return num_edges;
    };
    list<VertexWeightPair> get_adj(Vertex v) {
        return adj[v];
    };
};

NeuronGraph::NeuronGraph(uint numVertices): numVertices(numVertices), num_edges(0) {
        adj = new list<VertexWeightPair>[numVertices];
        for(uint i = 1; i <= numVertices; i++) {
            listNeuron.push_back(i);
        }
};

NeuronGraph::~NeuronGraph() {
    for(uint i = 0; i < numVertices; ++i) {
        adj[i].clear();
    }
    delete[] adj;
    num_edges = numVertices = 0;
};

void NeuronGraph::add_edge(Vertex v, Vertex u, Weight w) {
    VertexWeightPair pair_v(u, w);
    VertexWeightPair pair_u(v, w);

    adj[v].push_back(pair_v);
    adj[u].push_back(pair_u);

    listEdges.emplace_back(u,v,w);
    num_edges++;
};

Weight NeuronGraph::get_weight_edge(Vertex v, Vertex u) {
    for (VertexWeightPair pair: adj[v]){
        Vertex vertex = pair.vertex;
        if (vertex == u) {
            return pair.weight;
        }
    }
    return 0.0;
}

void print_list(list<VertexWeightPair> adj){
    for (VertexWeightPair pair: adj) {
        cout << "(" << pair.vertex << ", " << pair.weight << "), ";
    }
};

void print_WeightedGraphAL(NeuronGraph& graph) {
    for (Vertex v = 0; v < graph.get_num_vertices(); ++v){
        cout << v << ": ";
        list<VertexWeightPair> adj = graph.get_adj(v);
        print_list(adj);
        cout << endl;
    }
};

class Kruskal {
public:
    list<Vertex> mst;
    list<Edge> floresta;
    
    Kruskal(NeuronGraph& graph);
    void union_set(Vertex u, Vertex v);
    Vertex find_set(Vertex x);
};

Kruskal::Kruskal(NeuronGraph& graph) {
    for (Vertex v: graph.get_lista_vertices()) {
        mst.push_back(v);
    }

    mst.sort();

    for (Edge aresta: graph.get_lista_arestas()) {
        if (find_set(aresta.vertex) != find_set(aresta.vertex2)) {
            floresta.push_back(aresta);
            union_set(aresta.vertex, aresta.vertex2);
        }
    }
    //pegar a floresta
}

Vertex Kruskal::find_set(Vertex x) {
    for(Vertex vertex: mst) {
        if((vertex == x) && (vertex != x+1)) {
            vertex = find_set(vertex);
        }
    }
    return x;
}

void Kruskal::union_set(Vertex u, Vertex v) {
    for(Vertex vertex: mst) {
        if(vertex == v) {
            vertex = u;
        }
    }
}

int main(){
    int nVerticesGrafoCerebro,  nArestasGrafoCerebro;
    cin >> nVerticesGrafoCerebro;
    cin >> nArestasGrafoCerebro;

    // BrainGraph Cerebro(nVerticesGrafoCerebro, nArestasGrafoCerebro);

    for(int i = 0; i < nArestasGrafoCerebro; ++i){
        Vertex u, v;
        Weight weightUV;
        cin >> u;
        cin >> v;
        cin >> weightUV;
        // Cerebro.add_edge(u, v, weightUV);
    }

    Vertex blocoNeuronioEntrada, blocoNeuronioSaida;
    cin >> blocoNeuronioEntrada;
    cin >> blocoNeuronioSaida;
    // Cerebro.setEntrada(blocoNeuronioEntrada);
    // Cerebro.setSaida(blocoNeuronioSaida);

  for(int i = 1; i <= nVerticesGrafoCerebro; ++i){
        int nVerticesGrafoBloco,  nArestasGrafoBloco;
        cin >> nVerticesGrafoBloco;
        cin >> nArestasGrafoBloco;

        // Cerebro.getNeuronio(i) = new GrafoNeuronios(nVerticesGrafoCerebro, nArestasGrafoCerebro);

        for(int i = 0; i < nArestasGrafoBloco; ++i){
            Vertex u, v;
            uint nDoentes;
            Weight weightUV;
            cin >> nDoentes;
            for(int j = 0; j < nDoentes; ++j) {
                Vertex doente;
                cin >> doente;
                // Cerebro.getNeuronio(i).add_doente(doente);
            }
            cin >> u;
            cin >> v;
            cin >> weightUV;
            // Cerebro.getNeuronio(i).add_edge(u, v, weightUV);

            Vertex neuronioEntrada, neuronioSaida;
            cin >> neuronioEntrada;
            cin >> neuronioSaida;
            // Cerebro.getNeuronio(i).setEntrada(neuronioEntrada);
            // Cerebro.getNeuronio(i).setSaida(neuronioSaida);
        }       
    }

    return 0;
};