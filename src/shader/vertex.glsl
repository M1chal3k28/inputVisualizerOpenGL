#version 330 core
layout (location = 0) in vec3 aPos; // Współrzędne wierzchołków
layout (location = 1) in float aHeight; // Wysokość prostokąta

out float height; // Przekazanie wysokości do fragment shadera

void main()
{
    gl_Position = vec4(aPos, 1.0); // Przekształć pozycję wierzchołka do współrzędnych ekranu
    height = aHeight; // Przekazanie wysokości
}
