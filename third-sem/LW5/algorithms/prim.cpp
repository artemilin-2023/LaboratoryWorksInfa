#include "../algorithms.h"

#include <iostream>
#include <queue>

void print_tree(const std::vector<std::vector<std::pair<int, int>>> &mst_conn_m, int cur_v, int cur_dist,
                const std::string &prefix = "", bool is_last = true);

void visualise_minimum_spanning_tree(const std::vector<std::vector<std::pair<int, int>>> &conn_m) {
    std::cout << "Начинаем поиск минимального остовного дерева при помощи алгоритма Прима\n";
    std::vector<std::vector<std::pair<int, int>>> mst_conn_m(conn_m.size()); // cur_v: {next_v, dist}...
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<>> pq{}; // {edge distance, edge "from", edge "to"}
    std::vector<bool> visited(conn_m.size(), false);

    const int initial_v = 0;
    std::cout << "Возьмём вершину " << initial_v << " за исходную\n";

    // prime the queue (we will remove this loop later)
    pq.emplace(0, initial_v, initial_v);

    while (!pq.empty()) {
        auto [edge_dist, from_v, cur_v] = pq.top();
        pq.pop();

        if (visited[cur_v])
            // this vertice is already in the MST
            continue;

        std::cout << "Самая близкая непосещённая вершина - " << cur_v + 1
                  << " <- " << from_v + 1 << " (" << edge_dist << ")\n";
        std::cout << "Добавим её в минимальное остовное дерево и добавим смежные непосещённые вершины в кучу" << '\n';

        visited[cur_v] = true;
        mst_conn_m[from_v].emplace_back(cur_v, edge_dist);

        for (auto [next_v, next_dist]: conn_m[cur_v]) {
            if (!visited[next_v]) {
                std::cout << "Вершина " << next_v + 1 << " ещё не была посещена. Добавим ребро "
                          << cur_v + 1 << " -> " << next_v + 1 << " (" << next_dist << ") в кучу\n";
                // add this path to the heap to continue exploring from it
                pq.emplace(next_dist, cur_v, next_v);
            } else {
                std::cout << "Вершина " << next_v + 1 << " уже была посещена. Ничего не меняем\n";
            }
        }
        std::cout << "Все вершины, доступные из текущей, просмотрены\n\n";
    }
    mst_conn_m[0].erase(mst_conn_m[0].begin()); // we added a looping edge to prime the queue earlier
    std::cout << "Непосещённых вершин не осталось, а значит мы построили минимальное остовное дерево. "
                 "На этом алгоритм закончен\n";
    std::cout << "Ниже выведено полученное дерево\n";

    print_tree(mst_conn_m, initial_v, 0);
}

void print_tree(const std::vector<std::vector<std::pair<int, int>>> &mst_conn_m, int cur_v, int cur_dist,
                const std::string &prefix, bool is_last) {

    std::cout << prefix;
    std::cout << (is_last ? "└───" : "├───");
    // print the value of the node
    std::cout << cur_v + 1 << " (" << cur_dist << ")" << std::endl;
    // enter the next tree level
    auto edge_count = mst_conn_m[cur_v].size();
    for (int i = 0; i < edge_count; ++i) {
        auto [next_v, next_dist] = mst_conn_m[cur_v][i];
        print_tree(mst_conn_m, next_v, next_dist,
                   prefix + (is_last ? "    " : "│   "), i == edge_count - 1);
    }
}
