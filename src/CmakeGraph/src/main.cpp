/**
 * @file main.cpp
 * @author Jia-Baos (18383827268@163.com)
 * @brief Cpp临时项目
 * @version 0.1
 * @date 2024-03-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>

#include "./graph.hpp"

void Test01(Graph<char> g) {
  std::cout << "'A' 和 'D'之间边的权重为：" << g.GetWeight('A', 'D') << std::endl;
  g.ChangeWeight('A', 'D', 100);
  std::cout << "将'A' 和 'D'之间边的权重更改为100后，其权重为：" << g.GetWeight('A', 'D') << std::endl;
  g.RemoveWeight('A', 'D');
  std::cout << "将'A' 和 'D'之间边的权重删除后，其权重为：" << g.GetWeight('A', 'D') << std::endl;
  std::cout << "将'A' 和 'D'之间边的权重重新设置为5" << std::endl;
  g.ChangeWeight('A', 'D', 5);

  std::cout << "顶点总数：" << g.NumVertices() << std::endl;
  std::cout << "边的总数：" << g.NumEdges() << std::endl;

  std::cout << "图中包含'F'吗？" << (g.Contains('F') ? "包含" : "不包含") << std::endl;
  std::cout << "图中包含'G'吗？" << (g.Contains('G') ? "包含" : "不包含") << std::endl;
  std::cout << "'A'和'D'相邻吗？" << (g.Adjacent('A', 'D') ? "相邻" : "不相邻") << std::endl;
  std::cout << "'B'和'E'相邻吗？" << (g.Adjacent('B', 'E') ? "相邻" : "不相邻") << std::endl;
  std::cout << "顶点'A'的度数为： " << g.Degree('A') << std::endl;
  std::cout << "最大度数为：" << g.LargestDegree() << std::endl;

  auto vertices = g.GetVertices();
  std::cout << "图中的顶点分别为：";
  for (auto u : vertices) std::cout << " " << u;
  std::cout << std::endl;

  std::map<char, int> nbrs = g.GetNeighbours('F');
  std::cout << "顶点F的邻接顶点ID及其权重为：";
  for (auto u : nbrs) std::cout << " (" << u.first << ": " << u.second << ")";
  std::cout << std::endl;
}

void Test02(Graph<char> g) {
  auto dft = g.DepthFirstRec('A');
  std::cout << "从顶点A进行深度优先遍历（递归）: {";
  for (auto u : dft) std::cout << u << " ";
  std::cout << "}" << std::endl;

  std::vector<char> dft_itr = g.DepthFirstItr('A');
  std::cout << "从顶点A进行深度优先遍历（迭代）: {";
  for (auto u : dft_itr) std::cout << u << " ";
  std::cout << "}" << std::endl;

  auto bft = g.BreadthFirst('A');
  std::cout << "从顶点A进行广度优先遍历: {";
  for (auto u : bft) std::cout << u << " ";
  std::cout << "}" << std::endl;
}

void Test03(Graph<char> g) {
  std::cout << "生成的最小生成树如下：" << std::endl;
  Graph<char> result = g.Prim('A');
  result.Show();
}

void Test04(Graph<char> g) {
  std::cout << "最短路径结果如下：" << std::endl;
  auto dis = g.Dijkstra('A');
  std::vector<char> vertices = g.GetVertices();
  for (auto vertex : vertices)
    if (dis[vertex] >= 0) std::cout << vertex << ": " << dis[vertex] << std::endl;
}

void Test05(Graph<int> g) {
  std::vector<std::vector<int>> connected_components = g.GetConnectedComponents();
  g.PrintConnectedComponents(connected_components);
}

void Test06(Graph<int> g) {
  std::cout << "暴力求解得到的分割点为：";
  auto articulation_points2 = g.ArticulationPoints(1);
  for (auto u : articulation_points2) std::cout << " " << u;
  std::cout << std::endl;

  std::cout << "Targan算法求得的分割点为：";
  auto articulation_points1 = g.ArticulationPoints(2);
  for (auto u : articulation_points1) std::cout << " " << u;
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  Graph<char> g;
  g.AddVertex('A');
  g.AddVertex('B');
  g.AddVertex('C');
  g.AddVertex('D');
  g.AddVertex('E');
  g.AddVertex('F');
  g.AddVertex('G');

  g.AddEdge('A', 'B', 7);
  g.AddEdge('A', 'D', 5);
  g.AddEdge('B', 'C', 8);
  g.AddEdge('B', 'D', 9);
  g.AddEdge('B', 'E', 7);
  g.AddEdge('C', 'E', 5);
  g.AddEdge('D', 'E', 15);
  g.AddEdge('D', 'F', 6);
  g.AddEdge('E', 'F', 8);
  g.AddEdge('E', 'G', 9);
  g.AddEdge('F', 'G', 11);

  g.AddVertex('H');
  g.AddEdge('B', 'H', 9);
  g.AddEdge('A', 'H', 10);
  g.AddEdge('D', 'H', 11);
  g.AddEdge('A', 'H', 12);
  g.RemoveVertex('H');
  std::cout << "Info about graph......" << std::endl;
  g.Show();
  std::cout << std::endl;

  Test01(g);
  Test02(g);
  Test03(g);
  Test04(g);

  // Graph<int> g;

  // g.AddVertex(0);
  // g.AddVertex(1);
  // g.AddVertex(2);
  // g.AddVertex(3);
  // g.AddVertex(4);
  // g.AddVertex(5);
  // g.AddVertex(6);
  // g.AddVertex(7);
  // g.AddVertex(8);
  // g.AddVertex(9);
  // g.AddVertex(10);
  // g.AddVertex(11);
  // g.AddVertex(12);

  // g.AddEdge(0, 1, 1);
  // g.AddEdge(0, 2, 1);
  // g.AddEdge(1, 2, 1);
  // g.AddEdge(1, 3, 1);
  // g.AddEdge(1, 4, 1);
  // g.AddEdge(3, 6, 1);
  // g.AddEdge(4, 5, 1);
  // g.AddEdge(7, 8, 1);
  // g.AddEdge(7, 9, 1);
  // g.AddEdge(7, 12, 1);
  // g.AddEdge(8, 9, 1);
  // g.AddEdge(8, 12, 1);
  // g.AddEdge(9, 10, 1);
  // g.AddEdge(9, 11, 1);
  // g.AddEdge(9, 12, 1);
  // g.AddEdge(10, 11, 1);
  // std::cout << "打印图中顶点及其邻接表的详细信息如下" << std::endl;
  // g.Show();
  // std::cout << std::endl;

  // Test05(g);
  // Test06(g);

  return 0;
}
