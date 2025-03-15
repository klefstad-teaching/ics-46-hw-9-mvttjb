#include "./dijkstras.h"

// g++ -std=c++20 ./src/dijkstras_main.cpp ./src/dijkstras.cpp -o d_main

int main(int argc, char *argv[]) {

    Graph G;
    file_to_graph("./src/largest.txt", G);

    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    for (int i = 0; i < G.numVertices; ++i) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

    return 0;
}
