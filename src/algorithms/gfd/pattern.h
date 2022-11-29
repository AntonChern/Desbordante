#pragma once
#include <../../../lib/eigen/Eigen/Dense>
#include <map>
#include <set>
#include <string>

class Pattern {
protected:
    std::set<int> indices;
    std::map<int, std::string> vertices;
    std::map<std::pair<int, int>, std::string> edges;

    Eigen::MatrixXi adjacencyMatrix;
    Eigen::MatrixXi degrees;
    int size;
    int vertexNum;
public:
    Pattern() = default;
    Pattern(const std::map<int, std::string>&, const std::map<std::pair<int, int>, std::string>&) noexcept(false);
    //Pattern(const std::map<int, std::string>& vertices_, const std::map<std::pair<int, int>, std::string>& edges_) noexcept(false) {
    //    int max = 0;
    //    for (auto node : vertices_) {
    //        int index = node.first;
    //        this->indices.insert(index);
    //        max = max < index ? index : max;
    //    }
    //    if (max != this->indices.size() - 1) {
    //        throw std::out_of_range("index mismatch");
    //    }
    //    this->vertices = vertices_;
    //    this->edges = edges_;

    //    this->adjacencyMatrix = Eigen::MatrixXi::Zero(this->indices.size(), this->indices.size());
    //    for (auto edge_label : this->edges) {
    //        std::pair<int, int> edge = edge_label.first;
    //        this->adjacencyMatrix(edge.first, edge.second) = 1;
    //    }
    //    this->degrees = Eigen::MatrixXi::Zero(this->adjacencyMatrix.rows(), 2);
    //    for (int i = 0; i < this->adjacencyMatrix.rows(); ++i) {
    //        this->degrees(i, 0) = this->adjacencyMatrix.row(i).sum();
    //        this->degrees(i, 1) = this->adjacencyMatrix.col(i).sum();
    //    }
    //    this->vertexNum = this->vertices.size();
    //    this->size = vertexNum + this->edges.size();
    //}
    bool operator==(const Pattern&) const;
    bool operator!=(const Pattern&) const;

    std::set<int> getIndices() const { return this->indices; }
    std::map<int, std::string> getVertices() const { return this->vertices; }
    std::map<std::pair<int, int>, std::string> getEdges() const { return this->edges; }
    Eigen::MatrixXi getAdjacencyMatrix() const { return this->adjacencyMatrix; }
    Eigen::MatrixXi getVertexDegrees() const { return this->degrees; }
    int getSize() const { return this->size; }
    int getVertexNum() const { return this->vertexNum; }

    void print() const;
};
