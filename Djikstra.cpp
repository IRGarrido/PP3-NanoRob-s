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
    void remove_edge(Vertex, Vertex);
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
        adj = new list<VertexWeightPair>[num_vertices];
};

WeightedGraphAL::~WeightedGraphAL() {
    for(uint i = 0; i < num_vertices; ++i) {
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
    return 0.0;
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
    uint distancia;
    VertexDijkstra* predecessor;

    VertexDijkstra(Vertex vertex): vertex(vertex), predecessor(nullptr) {
        distancia = numeric_limits<uint>::max();
    };

    bool operator==(const VertexDijkstra& other) const {
        return vertex == other.vertex;
    }
};


class Dijkstra {
private:
    list<VertexDijkstra> listVertex;
    Vertex origin;
public:
    Dijkstra(WeightedGraphAL grafo, Vertex origem);
};

Dijkstra::Dijkstra(WeightedGraphAL grafo, Vertex origem) {

    for(uint i = 0; i < grafo.get_num_vertices(); ++i){
        VertexDijkstra v(i);
        listVertex.push_back(v);
    }

    VertexDijkstra s(origem);
    s.distancia = 0;
}