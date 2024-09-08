#pragma once
#ifndef EDGE_H
#define EDGE_H

template <typename T>
class Edge {
 public:
  T vertex;
  float weight;

  Edge(T neighbour_vertex) {
    this->vertex = neighbour_vertex;
    this->weight = 0.0f;
  }

  Edge(T neighbour_vertex, int weight) {
    this->vertex = neighbour_vertex;
    this->weight = weight;
  }

  bool operator<(const Edge &obj) const { return obj.vertex > vertex; }

  bool operator==(const Edge &obj) const { return obj.vertex == vertex; }
};
#endif  // !EDGE_H
