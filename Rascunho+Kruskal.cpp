#include<iostream>
#include<list>

using namespace std;

typedef unsigned int uint;
typedef unsigned int Vertex;
typedef double Weight;

class VertexWeightPair {
public:
    Vertex vertex;
    Weight weight;
    GrafoNeuronios* blocoNeuronios = nullptr;
    VertexWeightPair(Vertex vertex, Weight weight): vertex(vertex), weight(weight) {};
    bool operator==(const VertexWeightPair& other) const {
        return vertex == other.vertex && weight == other.weight;
    }
};

class Aresta {
public:
    Vertex vertex;
    Vertex vertex2;
    Weight weight;
    Aresta(Vertex vertex,Vertex vertex2, Weight weight): vertex(vertex),vertex2(vertex2), weight(weight) {};
};


class GrafoCerebro{
private:
    uint num_vertices;
    uint num_edges;
    list<VertexWeightPair> *adj;
public:
    GrafoCerebro(uint);
    ~GrafoCerebro();
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

GrafoCerebro::GrafoCerebro(uint num_vertices): num_vertices(num_vertices), num_edges(0) {
        adj = new list<VertexWeightPair>[num_vertices];
};

GrafoCerebro::~GrafoCerebro() {
    for(uint i = 0; i < num_vertices; ++i) {
        adj[i].clear();
    }
    delete[] adj;
    num_edges = num_vertices = 0;
};

void GrafoCerebro::add_edge(Vertex v, Vertex u, Weight w) {
    VertexWeightPair pair_v(u, w);
    VertexWeightPair pair_u(v, w);

    adj[v].push_back(pair_v);
    adj[u].push_back(pair_u);
    num_edges++;
};

Weight GrafoCerebro::get_weight_edge(Vertex v, Vertex u) {
    for (VertexWeightPair pair: adj[v]){
        Vertex vertex = pair.vertex;
        if (vertex == u) {
            return pair.weight;
        }
    }
    return 0.0;
}

class Neuronio {
private:
    uint num_vertices;
    uint num_edges;
    list<VertexWeightPair> *adj;
    list<Vertex> lista_vertices;
    list<Aresta> lista_arestas;
public:
    Neuronio(uint);
    ~Neuronio();
    list<Vertex>& get_lista_vertices(){return lista_vertices;};
    list<Aresta>& get_lista_arestas(){return lista_arestas;};
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

Neuronio::Neuronio(uint num_vertices): num_vertices(num_vertices), num_edges(0) {
        adj = new list<VertexWeightPair>[num_vertices];
        for(uint i = 1; i <= num_vertices; i++) {
            lista_vertices.push_back(i);
        }
};

Neuronio::~Neuronio() {
    for(uint i = 0; i < num_vertices; ++i) {
        adj[i].clear();
    }
    delete[] adj;
    num_edges = num_vertices = 0;
};

void Neuronio::add_edge(Vertex v, Vertex u, Weight w) {
    VertexWeightPair pair_v(u, w);
    VertexWeightPair pair_u(v, w);

    adj[v].push_back(pair_v);
    adj[u].push_back(pair_u);

    lista_arestas.emplace_back(u,v,w);
    num_edges++;
};

Weight Neuronio::get_weight_edge(Vertex v, Vertex u) {
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


void print_WeightedGraphAL(Neuronio& g) {
    for (Vertex v = 0; v < g.get_num_vertices(); ++v){
        cout << v << ": ";
        list<VertexWeightPair> adj = g.get_adj(v);
        print_list(adj);
        cout << endl;
    }
};

class Kruskal {
public:
    Kruskal(Neuronio& g);
    vector<Vertex> pai;
    list<Aresta> floresta;
    Vertex find_set(Vertex x);
    void union_set(Vertex u, Vertex v);
};
Kruskal::Kruskal(Neuronio& g) {
    for (Vertex v: g.get_lista_vertices()) {
        pai.push_back(v);
    }
    //espaço para o heapsort
    for (Aresta aresta: g.get_lista_arestas()) {
        if (find_set(aresta.vertex) != find_set(aresta.vertex2)) {
            floresta.push_back(aresta);
            union_set(aresta.vertex, aresta.vertex2);
        }
    }
    //pegar a floresta
}

Vertex Kruskal::find_set(Vertex x) {
    if(pai[x]!=x+1) {
        pai[x] = find_set(pai[x]);
    }
    return pai[x];
}

void Kruskal::union_set(Vertex u, Vertex v) {
    pai[v]=u;
}

int main(){
    int nVerticesGrafoCerebro,  nArestasGrafoCerebro;
    cin >> nVerticesGrafoCerebro;
    cin >> nArestasGrafoCerebro;

    // GrafoCerebro Cerebro(nVerticesGrafoCerebro, nArestasGrafoCerebro);

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