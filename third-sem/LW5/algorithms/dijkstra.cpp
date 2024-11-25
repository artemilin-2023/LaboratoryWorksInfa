#include "../algorithms.h"

#include <iostream>
#include <limits>
#include <queue>

const int INF = std::numeric_limits<int>::max();

// dijkstra
// conn_m = {cur_v: {next_v, dist}...}
void visualise_shortest_paths(const std::vector<std::vector<std::pair<int, int>>> &conn_m, int src) {
    std::cout << "Начинаем поиск кратчайших путей при помощи алгоритма Дейкстры из вершины " << src << '\n';

    std::vector<int> dist(conn_m.size(), INF); // currently the shortest distance to this node from src
    std::vector<int> path(conn_m.size(), -1); // previous vertex to this one
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq{}; // {distance, index}

    dist[src] = 0;
    path[src] = src;

    pq.emplace(0, src);
    while (!pq.empty()) {
        auto [cur_dist, cur_v] = pq.top();
        pq.pop();

        if (cur_dist > dist[cur_v]) {
            // we've already been here
            // another way to check is to keep a set/boolean array of visited vertices
            continue;
        }
        std::cout << "Самая близкая непосещённая вершина - " << cur_v + 1 << " (" << cur_dist << ")\n";
        std::cout << "Уменьшим пути из неё в другие вершины (прорелаксируем её)" << '\n';
        // iterate over all vertices reachable from this one
        for (auto [next_v, next_dist]: conn_m[cur_v]) {
            if (dist[next_v] > dist[cur_v] + next_dist) {
                std::cout << "Путь в вершину " << next_v + 1
                          << " из текущей (" << dist[cur_v] + next_dist
                          << ") меньше, чем уже найденный (" << dist[next_v] << "). "
                          << "Обновим путь в неё и добавим её в кучу с обновлённой длиной пути\n";
                // we found a shorter path! save it and it's distance
                path[next_v] = cur_v;
                dist[next_v] = dist[cur_v] + next_dist;
                // add this path to the heap to continue exploring from it
                pq.emplace(dist[next_v], next_v);
            } else {
                std::cout << "Путь в вершину " << next_v + 1
                          << " из текущей (" << dist[cur_v] + next_dist
                          << ") больше, чем уже найденный (" << dist[next_v] << "). Ничего не меняем\n";
            }
        }
        std::cout << "Все вершины, доступные из текущей, просмотрены\n\n";
    }
    std::cout << "Непосещённых вершин не осталось, а значит мы нашли пути до всех вершин. На этом алгоритм закончен\n";
    std::cout << "Ниже выведены все пути и их стоимость\n";

    // now print all the paths
    for (int i = 1; i < conn_m.size(); ++i) {
        std::vector<int> cur_path;
        int cur_v = path[i];
        while (cur_v != src) {
            cur_path.push_back(cur_v);
            cur_v = path[cur_v];
        }
        cur_path.push_back(src);
        std::cout << i + 1;
        for (auto v: cur_path) {
            std::cout << " <- " << v + 1;
        }
        std::cout << " = " << dist[i] << '\n';
    }
    std::cout << '\n';
}