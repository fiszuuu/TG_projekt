#ifndef PROJEKT_TG_TESTS_H
#define PROJEKT_TG_TESTS_H

#endif //PROJEKT_TG_TESTS_H

#include <iostream>
#include "graf.h"
#include <cstdlib>


void test_incidence_matrix()
{
    ifstream file ("adjacency_list.txt");
    if (!file){
        cerr << "ERROR: Opening file didn't succeed";
        return;
    }
    Graph graph;
    graph.read_adjacency_list(file);
    ofstream os ("result.txt");
    if (!os){
        cerr << "ERROR: Creating file didn't succeed";
        return;
    }
    graph.write_incidence_matrix(os);
}

void test_read_adjacency_list ()
{
    Graph graph;
    ifstream file ("adjacency_list.txt");
    if (!file){
        cerr << "ERROR: Opening file didn't succeed";
        return;
    }
    graph.read_adjacency_list(file);
}

void test_is_cycle (){
    Graph A;
    int range = 6;
    /* OUT OF ORDER :) this function was made protected
    for (int i = 0; i < 100; ++i){
        int x1 = rand()%range,x2 , y1= rand()%range, y2, z1= rand()%range, z2;
        do {
            x2= rand()%range;
        } while (x1 == x2);
        do {
            y2= rand()%range;
        }while (y1==y2);
        do {
            z2= rand()%range;
        }while (z1==z2);
        Edge a(x1,x2), b(y1, y2), c(z1, z2);
        if (A.is_cycle(a,b,c)) {
            cout << a.start << " " << a.end << endl;
            cout << b.start << " " << b.end << endl;
            cout << c.start << " " << c.end << endl << endl;
        }
        //else cout << "nie jest";
        //cout << endl << endl;
    }*/
}

void test_MST (){
    ifstream file ("adjacency_list.txt");
    if (!file){
        cerr << "ERROR: Opening file didn't succeed";
        return;
    }
    Graph graph;
    graph.read_adjacency_list(file);
    graph.minimum_spanning_tree().write_incidence_matrix(cout);
}

void test_read_value_matrix(){
    Graph graph;
    ifstream file ("value_matrix.txt");
    if (!file){
        cerr << "ERROR: Opening file didn't succeed";
        return;
    }
    graph.read_value_matrix(file);
    cout << "Done";
}

void test_going_out_and_to (){
    Graph graph;
    ifstream file ("value_matrix.txt");
    if (!file){
        cerr << "ERROR: Opening file didn't succeed";
        return;
    }
    graph.read_value_matrix(file);
    vector<int> out, to;
    out = graph.going_out_from(1);
    to = graph.going_in_from(1);
    int v1 = 2, v2 = 1;
    cout << "going out from vertex " << v1 << ": " <<graph.single_out(v1) << endl;
    cout << "going in to vertex "<< v2 << ": " <<graph.single_in(v2) << endl;
    cout << graph.find_edge_index(v1, v2) << endl;
    cout << "done";
}

void test_path(){
    Graph graph;
    ifstream file ("value_matrix.txt");
    if (!file){
        cerr << "ERROR: Opening file didn't succeed";
        return;
    }
    graph.read_value_matrix(file);
    graph.find_path(0, 3);
    for (int i = 0; graph.path[i] != -1; ++i){
        cout << graph.path[i] <<" ";
    }
    cout << endl;
    cout << "done";
}

void test_DFS_big(){
    Graph graph;
    ifstream file ("value_matrix_big.txt");
    if (!file){
        cerr << "ERROR: Opening file didn't succeed";
        return;
    }
    graph.read_value_matrix(file);
    graph.find_path(0, 4);
    for (int i = 0; i < graph.vertices; ++i){
        cout << graph.path[i] <<" ";
    }
    cout << endl;
    cout << "done";
}

void test_DFS_deadend(){
    Graph graph;
    ifstream file ("value_matrix_deadend.txt");
    if (!file){
        cerr << "ERROR: Opening file didn't succeed";
        return;
    }
    graph.read_value_matrix(file);
    int end = 7;
    graph.find_path(0, end);
    for (int i = 0; i < graph.vertices; ++i){
        cout << graph.path[i] <<" ";
    }
    cout << endl;
    cout << "done";
}

void test_DFS_cycle(){
    Graph graph;
    ifstream file ("value_matrix_cycle.txt");
    if (!file){
        cerr << "ERROR: Opening file didn't succeed";
        return;
    }
    graph.read_value_matrix(file);
    graph.find_path(0, 4);
    for (int i = 0; i < graph.vertices; ++i){
        cout << graph.path[i] <<" ";
    }
    cout << endl;
    cout << "done";
}

void test_FordFulkerson(){
    Graph graph;
    ifstream file ("value_matrix_ford_3.txt");
    if (!file){
        cerr << "ERROR: Opening file didn't succeed";
        return;
    }
    graph.read_value_matrix(file);
    int end = graph.vertices - 1;
    cout<<"maksymalny przeplyw przez ten graf z wierzcholka 0 do wierzcholka " << end << " wynosi: "<< graph.FordFulkerson(0, end);
}

