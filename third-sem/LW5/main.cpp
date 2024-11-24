/******************************************************************
*                     КАФЕДРА № 304 2 КУРС                        *
*-----------------------------------------------------------------*
* Project Type  : Win32 Console Application                       *
* Project Name  : DijkstraPrim                                    *
* File Name     : main.cpp                                        *
* Language      : C/C++                                           *
* Programmer(s) : Романов Д.И., Ильин А.А                         *
* Modified By   :                                                 *
* Created       : 20/09/2024                                      *
* Last Revision : 18/11/2024                                      *
* Comment(s)    : Графы                                           *
******************************************************************/

#include <iostream>
#include <random>

#include "algorithms.h"

// make a connectivity matrix out of an adjacency matrix
std::vector<std::vector<std::pair<int, int>>> make_connectivity_matrix(const std::vector<std::vector<int>> &adj_m) {
    std::vector<std::vector<std::pair<int, int>>> conn_m(adj_m.size());
    for (int i = 0; i < adj_m.size(); ++i) {
        for (int j = 0; j < adj_m[i].size(); ++j) {
            if (adj_m[i][j] == 0)
                continue;
            conn_m[i].emplace_back(j, adj_m[i][j]); // {index, distance}
        }
    }
    return conn_m; // move semantics
}

// removes orientations on an adjacency matrix
std::vector<std::vector<int>> deorient_graph(const std::vector<std::vector<int>> &adj_m) {
    std::vector<std::vector<int>> deoriented_adj_m(adj_m);
    for (int i = 0; i < deoriented_adj_m.size(); ++i) {
        for (int j = 0; j < deoriented_adj_m[i].size(); ++j) {
            if (deoriented_adj_m[i][j] == 0)
                // not an edge
                continue;
            deoriented_adj_m[j][i] = deoriented_adj_m[i][j];
        }
    }
    return deoriented_adj_m;
}

int main() {
    std::cout << "Лабораторная работа №5 - Линейные списки\n";
    std::cout << "    Вариант №4\n\n";

    // adjacency matrix, as stated in the assignment
    std::vector<std::vector<int>> adj_m = {
            {0,   275, 0,   0,  0,   454, 0,   0,   0,   0},
            {0,   0,   0,   0,  0,   0,   0,   0,   0,   0},
            {377, 212, 0,   0,  0,   110, 0,   0,   0,   58},
            {0,   0,   0,   0,  0,   0,   0,   346, 0,   0},
            {0,   0,   0,   0,  0,   0,   0,   0,   223, 61},
            {0,   0,   0,   0,  309, 0,   0,   0,   0,   0},
            {0,   0,   323, 90, 458, 0,   0,   153, 0,   278},
            {0,   0,   0,   0,  0,   0,   0,   0,   0,   46},
            {0,   0,   0,   0,  0,   0,   127, 0,   0,   0},
            {296, 0,   0,   0,  0,   0,   0,   0,   0,   0},
    };

    // connectivity matrix, because it's easier to use in dijkstra's
    auto conn_m = make_connectivity_matrix(adj_m); // cur_v: {next_v, dist}...

    visualise_shortest_paths(conn_m, 0);

    auto deoriented_adj_m = deorient_graph(adj_m);
    auto deoriented_conn_m = make_connectivity_matrix(deoriented_adj_m);

    visualise_minimum_spanning_tree(deoriented_conn_m);

    return 0;
}
