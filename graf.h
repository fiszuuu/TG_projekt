#ifndef PROJEKT_TG_GRAF_H
#define PROJEKT_TG_GRAF_H



#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <deque>


using namespace std;

//////////////
//CLASS EDGE//
//////////////

class Edge{
    friend class Graph;
private:
    int start;
    int end;
    int value;
    bool is_directed;
protected:
    void normalize();
public:
    Edge(int s, int e, bool d = false):start(s), end(e), is_directed(d){
        if (!is_directed)
            normalize();
    };
};

void Edge::normalize() {
    if (start > end) swap(start, end);
}

///////////////
//CLASS GRAPH//
///////////////

class Graph{
protected:
    static bool is_cycle(Edge x, Edge y, Edge z);
    static bool potential_for_cycle(Edge x, Edge y);
public:
    bool add_edge(Edge e);
    int vertices;
    vector <Edge> edges;
    int * path;
    Graph();
    ~Graph();
    void read_adjacency_list(ifstream & is);
    void read_value_matrix(ifstream & is);
    int ** incidence_matrix ();
    void write_incidence_matrix(ostream & os);
    Graph minimum_spanning_tree();
    vector <int> going_out_from (int vertex);
    vector <int> going_in_from (int vertex);
    int single_out (int vertex);
    int single_in (int vertex);
    int find_edge_index (int start, int end);
    bool DFS(int start, int end);
    bool find_path (int start, int end);
    int FordFulkerson (int start, int end );
    int FordFulkerson_pathprinter (int start, int end);
};

//GRAPH METHODS

Graph::Graph() {
    vertices = 0;
}

Graph::~Graph() {
    edges.clear();
}

bool Graph::add_edge(Edge e) {
    for (auto & edge: edges){
        if (e.start == edge.start && e.end == edge.end)
            return false;
    }
    edges.push_back(e);
    return true;
}

void Graph::read_adjacency_list(ifstream &is) {
    int v_start = 0;
    string line;
    while (getline(is, line)){
        int v_end;
        const char * c = line.c_str();
        char *separator;
        int numbers_q = 0;
        //counting numbers
        for (char i : line)
            if (i == ' ') numbers_q++;
        //first vertex in the line
        v_end = strtol (c, &separator, 10);
        Edge first_edge(v_start, v_end);
        add_edge(first_edge);
        //following vertices
        for (int i = 1; i < numbers_q; ++i){
            v_end = strtol (separator, &separator, 10);
            Edge edge(v_start, v_end);
            add_edge(edge);
        }
        vertices++;
        v_start++;
    }
}

void Graph::read_value_matrix(ifstream &is){
    string line;
    int row = 0;
    int numbers_q = 1;
    while (getline (is, line)){
        const char * c = line.c_str();
        char *separator;
        int value;
        //in each row there are same quantity of numbers so its enough to do it ones
        if (row == 0)
            for (char i : line)
                if (i == ' ') numbers_q++;
        //adding first edge
        value = strtol (c, &separator, 10);
        if (value != 0){
            Edge first_edge(row, 0, true);
            first_edge.value = value;
            add_edge(first_edge);
        }
        //adding following edges
        for (int column = 1; column < numbers_q; ++column){
            value = strtol (separator, &separator, 10);
            if (value != 0){
                Edge edge(row, column, true);
                edge.value = value;
                add_edge(edge);
            }
        }
        row++;
    }
    vertices = row; //With +1 or without?
}

int ** Graph::incidence_matrix() {
    int **incidence_matrix = new int*[vertices];
    for (int i = 0; i < vertices; ++i){
        incidence_matrix[i] = new int [edges.size()];
    }
    for (int i = 0; i < vertices; ++i)
        for (int j = 0; j < edges.size(); ++j)
            incidence_matrix[i][j] = 0;
    for (int j = 0; j < edges.size(); ++j){
        incidence_matrix[edges[j].start][j] = 1;
        incidence_matrix[edges[j].end][j] = 1;
    }
    return incidence_matrix;
}

void Graph::write_incidence_matrix(ostream &os) {
    int **incidence_matrix = this->incidence_matrix();
    os << "   ";
    for (auto & edge : edges){
        os<<setw(2)<<edge.start<<"-"<<setw(2)<<edge.end;
    }

    os << endl;
    for (int i = 0; i < vertices; ++i){
        os <<setw(2)<< i;
        for (int j = 0; j < edges.size(); ++j)
            os << setw(5) << incidence_matrix[i][j];
        os << endl;
    }
}

bool Graph::potential_for_cycle(Edge x, Edge y) {
    if (x.start == y.end || x.end == y.end || x.end == y.start || x.start == y.start)
        return true;
    return false;
}

bool Graph::is_cycle(Edge x, Edge y, Edge z) {
    if (x.end == y.start && y.end == z.end && z.start == x.start)
        return true;
    //same conditions as higher but with swapped y and z
    if (x.end == z.start && z.end == y.end && y.start == x.start)
        return true;

    if (x.end == y.end && y.start == z.end && z.start == x.start)
        return true;
    if (x.end == y.end && y.start == z.start && z.end == x.start)
        return true;
    swap(y.start, z.start);
    swap (y.end, z.end);
    //same conditions as higher but with swapped y and z
    if (x.end == y.end && y.start == z.end && z.start == x.start)
        return true;
    if (x.end == y.end && y.start == z.start && z.end == x.start)
        return true;
    return false;
}

//DOES NOT WORK
Graph Graph::minimum_spanning_tree() {
    Graph MST;
    //sort_by_value();
    MST.add_edge(edges[0]);
    MST.add_edge(edges[1]);
    for (int i = 2; i < edges.size(); ++i) {
        for (int j = 0; j < MST.edges.size(); ++j){
            for (int k = j+1 ; k < MST.edges.size(); ++k){
                if (!MST.is_cycle(edges[i], MST.edges[j], MST.edges[k]))
                    MST.add_edge(edges[i]);
            }
        }
    }
    return MST;
}

vector <int> Graph::going_out_from(int vertex) {
    vector<int> result;
    for (auto & edge: edges){
        if (edge.start == vertex)
            result.push_back(edge.end);
    }
    return result;
}

vector <int> Graph::going_in_from(int vertex) {
    vector<int> result;
    for (auto & edge: edges){
        if (edge.end == vertex)
            result.push_back(edge.start);
    }
    return result;
}

// -> given vertex
int Graph::single_in(int vertex) {
    int result;
    for (auto & edge: edges)
        if (edge.end == vertex){
            //cout << edge.value <<endl;
            return edge.start;
        }
    return -1;
}

//given vertex ->
int Graph::single_out(int vertex) {
    int result;
    for (auto & edge: edges)
        if (edge.start == vertex){
            //cout << edge.value << endl;
            return edge.end;
        }
    return -1;
}

int Graph::find_edge_index(int start, int end) {
    for (int i = 0; i < edges.size(); ++i){
        if (edges[i].start == start && edges[i].end == end)
            return i;
    }
    return -1;
}


//Ford Fulkerson

bool Graph::find_path(int start, int end) {
    path = new int [vertices];
    for (int i = 0; i < vertices; ++i)
        path[i] = -1;
    if (!DFS(start, end))
        return false;
    int * path_readable = new int [vertices];
    for (int i = 0; i < vertices; ++i)
        path_readable[i] = -1;
    path_readable[0] = start;
    for (int i = 1; path_readable[i-1] != end; ++i){
        path_readable[i] = path[path_readable[i-1]];
    }
    path = path_readable;
    return true;
}

bool Graph::DFS(int start, int end){
    //if (start == -1) return;
    //int next_vertex = single_out(start);
    if (start == end) return true;
    vector<int> out = going_out_from(start);
    if (out.empty()) return false;
    for (int v: out){
        int edge_index = find_edge_index(start, v);
        if (edges[edge_index].value > 0) {
            //condition to deal with cycles (NOT WORKING RIGHT NOW)
            if (path[v] == -1) {
                if(DFS(v, end)){
                    path[start] = v;
                    return true;
                }
            }
        }
    }
    return false;
}

int Graph::FordFulkerson(int start, int end) {
    int result = 0;
    while (find_path(start, end)){
        //needed to debug easier
        deque<int> edges_indexes;
        int min_value = INT_MAX;
        for (int i = 0; path[i+1] != -1; ++i){
            //cout << path[i]<< " ";
            int index = find_edge_index(path[i], path[i+1]);
            if (min_value > edges[index].value){
                min_value = edges[index].value;
            }
            edges_indexes.push_back(index);
        }
        for (int i = 0; i < edges.size(); ++i){
            if (i == edges_indexes[0]){
                edges[i].value -= min_value;
                edges_indexes.pop_front();
            }
        }
        result +=  min_value;
    }
    return result;
}

int Graph::FordFulkerson_pathprinter(int start, int end) {
    int result = 0;
    while (find_path(start, end)){
        //needed to debug easier
        cout << "sciezka po wierzcholkach: ";
        for (int i = 0; path [i] != -1; ++i){
            cout << path [i] << " ";
        }
        cout << endl;
        deque<int> edges_indexes;
        int min_value = INT_MAX;
        for (int i = 0; path[i+1] != -1; ++i){
            //cout << path[i]<< " ";
            int index = find_edge_index(path[i], path[i+1]);
            if (min_value > edges[index].value){
                min_value = edges[index].value;
            }
            edges_indexes.push_back(index);
        }
        for (int i = 0; i < edges.size(); ++i){
            if (i == edges_indexes[0]){
                edges[i].value -= min_value;
                edges_indexes.pop_front();
            }
        }
        cout << "waskie gardlo: " << min_value << endl;
        result +=  min_value;
    }
    return result;
}

#endif //PROJEKT_TG_GRAF_H