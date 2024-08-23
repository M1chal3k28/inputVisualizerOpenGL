#pragma once 

#include <vector>
#include <iostream>

class Bar {
public:
    Bar(std::vector<float> vertices, std::vector<unsigned int> indices);

     std::vector<unsigned int>& getIndices();
    std::vector<float>& getVertices();

private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};