#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <limits.h>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "edge.hpp"

template <typename T>
class Graph {
 public:
  std::map<T, std::set<Edge<T>>> adj; /* 邻接表 */

  bool Contains(const T &u);             /* 判断顶点u是否在图中 */
  bool Adjacent(const T &u, const T &v); /* 判断顶点u和v是否相邻 */

  void AddVertex(const T &u);                       /* 添加顶点 */
  void AddEdge(const T &u, const T &v, int weight); /* 添加边和权重 */

  void ChangeWeight(const T &u, const T &v, int weight); /* 修改权重 */

  void RemoveWeight(const T &u, const T &v); /* 移除权重 */
  void RemoveVertex(const T &u);             /* 移除顶点 */
  void RemoveEdge(const T &u, const T &v);   /* 移除边 */

  int Degree(const T &u); /* 求顶点的度数 */
  int NumVertices();      /* 求图中顶点的总数 */
  int NumEdges();         /* 求图中边的总数*/
  int LargestDegree();    /* 求图中的最大度数 */

  int GetWeight(const T &u, const T &v);      /* 得到某两个顶点之间边的权重 */
  std::vector<T> GetVertices();               /* 得到图中所有顶点 */
  std::map<T, int> GetNeighbours(const T &u); /* 得到顶点u的所有边 */

  void Show();

  void DftRecursion(const T &u, std::set<T> &visited, std::vector<T> &result); /* 深度优先遍历递归辅助函数 */
  std::vector<T> DepthFirstRec(const T &u);                                    /* 深度优先遍历递归法 */
  std::vector<T> DepthFirstItr(const T &u);                                    /* 深度优先遍历迭代法*/
  std::vector<T> BreadthFirst(const T &u);                                     /* 广度优先遍历迭代法 */

  Graph<T> Prim(T v); /* prim最小生成树算法 */

  std::map<T, int> Dijkstra(T start); /*  dijkstra最短路径算法 */

  std::vector<std::vector<T>> GetConnectedComponents(); /* 获得图中的连通分量 */
  void PrintConnectedComponents(const std::vector<std::vector<T>> &connected_components); /* 打印连通分量 */

  std::vector<T> ArticulationPoints(int choice); /* 获得图中的关节点（分割点）*/

 private:
  void Dft(T u, T root, T parent, std::set<T> &visited_vertices, /* 获得关节点的Tarjan算法 */
           int &dfn_cnt, std::map<T, int> &dfn, std::map<T, int> &low, std::vector<T> &articulation_point_collection);
  void ViolentSolution(std::vector<T> &articulation_point_collection); /* 获得关节点的暴力求解法 */
};

template <typename T>
void Graph<T>::Show() {
  for (const auto &u : adj) {
    std::cout << "Vertex" << u.first << ": ";
    for (const auto &v : adj[u.first])
      std::cout << "(Adjacent Vertex: " << v.vertex << ", weight of edge: " << v.weight << ") ";
    std::cout << std::endl;
  }
}

template <typename T>
bool Graph<T>::Contains(const T &u) {
  return adj.find(u) != adj.end();
}

template <typename T>
bool Graph<T>::Adjacent(const T &u, const T &v) {
  if (Contains(u) && Contains(v) && u != v) {
    for (auto edge : adj[u])
      if (edge.vertex == v) return true;
  }
  return false;
}

template <typename T>
void Graph<T>::AddVertex(const T &u) {
  if (!Contains(u)) {
    std::set<Edge<T>> edge_list;
    adj[u] = edge_list;
  }
}

template <typename T>
void Graph<T>::AddEdge(const T &u, const T &v, int weight) {
  if (!Adjacent(u, v)) {
    adj[u].insert(Edge<T>(v, weight));
    adj[v].insert(Edge<T>(u, weight));
  }
}

template <typename T>
void Graph<T>::ChangeWeight(const T &u, const T &v, int weight) {
  if (Contains(u) && Contains(v)) {
    if (adj[u].find(Edge<T>(v)) != adj[u].end()) {
      adj[u].erase(Edge<T>(v));
      adj[u].insert(Edge<T>(v, weight));
    }

    if (adj[v].find(Edge<T>(u)) != adj[v].end()) {
      adj[v].erase(Edge<T>(u));
      adj[v].insert(Edge<T>(u, weight));
    }
  }
}

template <typename T>
void Graph<T>::RemoveWeight(const T &u, const T &v) {
  if (Contains(u) && Contains(v)) {
    if (adj[u].find(Edge<T>(v)) != adj[u].end()) {
      adj[u].erase(Edge<T>(v));
      adj[u].insert(Edge<T>(v, 0));
    }

    if (adj[v].find(Edge<T>(u)) != adj[v].end()) {
      adj[v].erase(Edge<T>(u));
      adj[v].insert(Edge<T>(u, 0));
    }
  }
}

template <typename T>
void Graph<T>::RemoveVertex(const T &u) {
  if (Contains(u)) {
    for (auto &vertex : adj) {
      if (vertex.second.find(Edge<T>(u)) != vertex.second.end()) vertex.second.erase(Edge<T>(u));
    }
    adj.erase(u);
  }
}

template <typename T>
void Graph<T>::RemoveEdge(const T &u, const T &v) {
  if (u == v || !Contains(u) || !Contains(v)) return;

  if (adj[u].find(Edge<T>(v)) != adj[u].end()) {
    adj[u].erase(Edge<T>(v));
    adj[v].erase(Edge<T>(u));
  }
}

template <typename T>
int Graph<T>::Degree(const T &u) {
  if (Contains(u)) return adj[u].size();

  return -1;  // 度数为-1说明图中没有该顶点
}

template <typename T>
int Graph<T>::NumVertices() {
  return adj.size();
}

template <typename T>
int Graph<T>::NumEdges() {
  int count = 0;
  std::set<Edge<T>> vertex_set;

  for (auto vertex : adj) {
    vertex_set.insert(Edge<T>(vertex.first, 0));
    for (auto edge : vertex.second) {
      if (vertex_set.find(edge) != vertex_set.end()) continue;
      count++;
    }
  }
  return count;
}

template <typename T>
int Graph<T>::LargestDegree() {
  if (NumVertices() == 0) return 0;

  unsigned max_degree = 0;
  for (auto vertex : adj) {
    if (vertex.second.size() > max_degree) max_degree = vertex.second.size();
  }
  return max_degree;
}

template <typename T>
int Graph<T>::GetWeight(const T &u, const T &v) {
  if (Contains(u) && Contains(v)) {
    for (Edge<T> edge : adj[u])
      if (edge.vertex == v) return edge.weight;
  }
  return -1;
}

template <typename T>
std::vector<T> Graph<T>::GetVertices() {
  std::vector<T> vertices;
  for (auto vertex : adj) vertices.push_back(vertex.first);

  return vertices;
}

template <typename T>
std::map<T, int> Graph<T>::GetNeighbours(const T &u) {
  std::map<T, int> neighbours;

  if (Contains(u)) {
    for (Edge<T> edge : adj[u]) neighbours[edge.vertex] = edge.weight;
  }

  return neighbours;
}

template <typename T>
void Graph<T>::DftRecursion(const T &u, std::set<T> &visited, std::vector<T> &result) {
  result.push_back(u);
  visited.insert(u);

  for (Edge<T> edge : adj[u])
    if (visited.find(edge.vertex) == visited.end()) DftRecursion(edge.vertex, visited, result);
}

template <typename T>
std::vector<T> Graph<T>::DepthFirstRec(const T &u) {
  std::vector<T> result;
  std::set<T> visited;
  if (Contains(u)) DftRecursion(u, visited, result);
  return result;
}

template <typename T>
std::vector<T> Graph<T>::DepthFirstItr(const T &u) {
  std::vector<T> result;
  std::set<T> visited;
  std::stack<T> s;

  s.push(u);
  while (!s.empty()) {
    T v = s.top();
    s.pop();

    if (visited.find(v) != visited.end()) {
      continue;
    }
    visited.insert(v);
    result.push_back(v);

    for (auto w : adj[v]) {
      if (visited.find(w.vertex) == visited.end()) {
        s.push(w.vertex);
      }
    }
  }
  return result;
}

template <typename T>
std::vector<T> Graph<T>::BreadthFirst(const T &u) {
  std::vector<T> result;
  std::set<T> visited;
  std::queue<T> q;

  q.push(u);
  while (!q.empty()) {
    T v = q.front();
    q.pop();

    if (visited.find(v) != visited.end()) {
      continue;
    }

    visited.insert(v);
    result.push_back(v);

    for (Edge<T> edge : adj[v]) {
      if (visited.find(edge.vertex) == visited.end()) {
        q.push(edge.vertex);
      }
    }
  }
  return result;
}

template <typename T>
Graph<T> Graph<T>::Prim(T v) {
  Graph<T> min_spanning_tree;
  // 在生成树中添加顶点v
  min_spanning_tree.AddVertex(v);

  // 设置带权重的队列，按第一个元素（权值）进行从小到大的排列
  std::priority_queue<std::pair<int, std::pair<T, T>>, std::vector<std::pair<int, std::pair<T, T>>>,
                      std::greater<std::pair<int, std::pair<T, T>>>>
      q;

  // 设置集合visited来存放已经访问过的顶点
  std::set<T> visited;

  // 入队：入队的元素是一个pair类型，第一个值是权重，第二个值也是pair
  // 第二个值的pair里面第一个值是u（只在生成树中存在的顶点）,
  // 第二个值是v（只在在原图中存在的点）
  for (auto neighbour : adj[v]) {
    q.push(std::make_pair(neighbour.weight, std::make_pair(v, neighbour.vertex)));
  }

  while (!q.empty()) {
    // 队首元素出队
    auto front = q.top();
    q.pop();

    // 获得已在生成树中的顶点u
    T u = front.second.first;

    // 获得在原图中, 但不在生成树中的顶点v
    T v = front.second.second;

    // 如果顶点v已经访问过则跳过本此循环
    if (visited.find(v) != visited.end())
      continue;
    else
      visited.insert(v);

    // 在生成树中添加新的顶点v以及v和u之间的边
    min_spanning_tree.AddVertex(v);
    min_spanning_tree.AddEdge(u, v, front.first);

    // 依次将顶点v尚未访问过的邻居放入优先队列中
    for (auto neighbour : adj[v]) {
      if (visited.find(neighbour.vertex) == visited.end()) {
        q.push(std::make_pair(neighbour.weight, std::make_pair(v, neighbour.vertex)));
      }
    }
  }
  return min_spanning_tree;
}

template <typename T>
std::map<T, int> Graph<T>::Dijkstra(T start) {
  // 设置dis用来存放初始点到图中任何一个顶点的距离
  std::map<T, int> dis;

  // 设置带权重的队列，按每个pair的第一个元素进行从小到大的排列
  std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<std::pair<int, T>>> q;

  for (T vertex : GetVertices()) {
    // 设置初始顶点到自己的距离为0
    if (vertex == start) dis[start] = 0;
    // 设置初始顶点到其他顶点的距离为无穷大
    else
      dis[vertex] = INT_MAX;
  }

  // 设置集合visited来存放已经访问过的顶点
  std::set<T> visited;

  // 入队：入队的元素是一个pair类型，第一个值是权重，第二个值是顶点
  q.push(std::make_pair(0, start));

  while (!q.empty()) {
    // 队首元素出队
    auto front = q.top();
    q.pop();

    // 获得当前顶点
    T u = front.second;

    // 如果该顶点已经访问过则跳过本此循环，否则存入到集合visited中表示已经访问过
    if (visited.find(u) != visited.end())
      continue;
    else
      visited.insert(u);

    // 获得到顶点u的最短路径"shortest_distance_to_u"，将此路径存入到dis结果中
    int shortest_distance_to_u = front.first;
    dis[u] = shortest_distance_to_u;

    // 依次访问顶点u尚未访问过的邻居
    for (auto v : adj[u]) {
      if (visited.find(v.vertex) == visited.end()) {
        // 从顶点u到邻居v的路径记为“distance_to_v”
        int distance_to_v = v.weight;
        q.push(std::make_pair(shortest_distance_to_u + distance_to_v, v.vertex));
      }
    }
  }
  return dis;
}

template <typename T>
std::vector<std::vector<T>> Graph<T>::GetConnectedComponents() {
  std::set<T> visited_vertices;
  std::vector<std::vector<T>> connected_components;

  for (auto vertex : adj) {
    // 对每一个未访问过的顶点进行深度优先遍历
    if (visited_vertices.find(vertex.first) == visited_vertices.end()) {
      std::stack<T> s;
      s.push(vertex.first);

      // 定义一个临时变量"connected_component"用来存储当前连通分量中的顶点
      std::vector<T> connected_component;

      // 深度优先遍历
      while (!s.empty()) {
        T u = s.top();
        s.pop();

        // 将未访问过的顶点放入连通分量"connected_component"中
        if (visited_vertices.find(u) == visited_vertices.end()) {
          connected_component.push_back(u);
          visited_vertices.insert(u);
        }

        // 当前顶点未访问过的邻居入栈
        for (auto neighbour : adj[u])
          if (visited_vertices.find(neighbour.vertex) == visited_vertices.end()) s.push(neighbour.vertex);
      }
      // 将连通分量放到连通分量的集合"connected_components"中
      connected_components.push_back(connected_component);
    }
  }

  return connected_components;
}

template <typename T>
void Graph<T>::PrintConnectedComponents(const std::vector<std::vector<T>> &connected_components) {
  int number = connected_components.size();
  if (number == 1)
    std::cout << "The graph is a connected graph with only one connected component, "
                 "which is itself."
              << std::endl;
  else if (number > 1) {
    std::cout << "Graph has" << number << "connected components" << std::endl;
    for (unsigned i = 0; i < connected_components.size(); i++) {
      std::cout << "The" << i + 1 << "nd connected component's vertexes are";
      for (unsigned j = 0; j < connected_components[i].size(); j++) {
        std::cout << " " << connected_components[i][j];
      }
      std::cout << std::endl;
    }
  }
}

template <typename T>
std::vector<T> Graph<T>::ArticulationPoints(int choice) {
  // 计算深度优先遍历的次数
  int dfn_cnt = 0;

  // 记录图中出现的分割点
  std::vector<T> articulation_point_collection;

  // 记录深度优先遍历顺序
  std::map<T, int> dfn;

  // 记录以某个特定顶点为根的子树能回溯到的最早的祖先顶点
  std::map<T, int> low;

  // 记录已访问过的顶点
  std::set<T> visited_vertices;

  if (choice == 1) {
    ViolentSolution(articulation_point_collection);
  }

  else if (choice == 2) {
    // 对未访问过的顶点进行深度优先遍历求分割点（实际上是在每一个连通分量中使用一次深度优先遍历）
    for (auto u : adj) {
      if (visited_vertices.find(u.first) == visited_vertices.end())
        Dft(u.first, u.first, u.first, visited_vertices, dfn_cnt, dfn, low, articulation_point_collection);
    }
    int a = 1;
  }

  return articulation_point_collection;
}

template <typename T>
void Graph<T>::ViolentSolution(std::vector<T> &articulation_point_collection) {
  // 获得原来的图的连通分量数量
  unsigned original_number = GetConnectedComponents().size();

  // 获得图中的所有顶点
  std::vector<T> vertices = GetVertices();

  for (T vertex : vertices) {
    // 暂存要删除的顶点附近的邻居
    std::map<T, int> temp_neighbours = GetNeighbours(vertex);
    // 删除顶点
    RemoveVertex(vertex);

    // 将删除后的连通分量数量与删除前的比较
    unsigned current_number = GetConnectedComponents().size();
    if (current_number > original_number) articulation_point_collection.push_back(vertex);

    // 添加回顶点及对应的边
    AddVertex(vertex);
    for (auto neighbour : temp_neighbours) {
      AddEdge(vertex, neighbour.first, neighbour.second);
    }
  }
}

template <typename T>
void Graph<T>::Dft(T u, T root, T parent, std::set<T> &visited_vertices, int &dfn_cnt, std::map<T, int> &dfn,
                   std::map<T, int> &low, std::vector<T> &articulation_point_collection) {
  // 记录深度优先遍历次序
  dfn_cnt++;
  dfn[u] = dfn_cnt;

  // 初始化low[u]
  low[u] = dfn[u];

  // 标记当前顶点为已访问
  visited_vertices.insert(u);

  // 记录子树数量
  int n_subtree = 0;

  // 记录该顶点是否为关节点
  bool is_cut = false;

  for (auto edge : adj[u]) {
    T v = edge.vertex;

    // 当(u,v)边为树边时
    if (visited_vertices.find(v) == visited_vertices.end()) {
      n_subtree++;

      // 对u的孩子v进行深度优先遍历，此时u作为parent
      Dft(v, root, u, visited_vertices, dfn_cnt, dfn, low, articulation_point_collection);

      // 以v为根节点的子树能访问到的祖先必然也能从u结点出发访问到，依此来更新u值
      low[u] = std::min(low[u], low[v]);

      // 以v为根节点的子树能访问到的最早的祖先为u或者v时，则可判断出顶点u（非根节点）为关节点
      if (u != root && low[v] >= dfn[u]) is_cut = true;
    }

    // 当(u,v)边为回边时
    // 使用v的深度优先遍历次序来更新low[u]
    else if (v != parent)
      low[u] = std::min(low[u], dfn[v]);
  }

  // u为根节点且子树数量大于等于2的情况
  if (n_subtree >= 2 && u == root) is_cut = true;

  // 记录关节点
  if (is_cut) articulation_point_collection.push_back(u);
}

#endif  // !GRAPH_H
