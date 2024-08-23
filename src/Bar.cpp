#include <Bar.hpp>

Bar::Bar(std::vector<float> vertices, std::vector<unsigned int> indices) {
    this->indices = indices;
    this->vertices = vertices;
}

std::vector<float>& Bar::getVertices() {
    return this->vertices;
}

std::vector<unsigned int>& Bar::getIndices() {
    return this->indices;
}