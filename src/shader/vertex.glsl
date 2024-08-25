#version 330 core
layout(location = 0) in vec3 position; // Pozycja wierzchołka
layout(location = 1) in float height;  // Wysokość wierzchołka

out float vHeight; // Przekazanie wysokości do shadera fragmentów
out float vDist; 
out vec2 fragPos; // Współrzędne fragmentu

void main()
{
    gl_Position = vec4(position, 1.0);
    vHeight = 1.4 + position.y;
    vDist = 0.7 + position.x;
    fragPos = position.xy; // Używamy współrzędnych x, y bez dodatkowych przekształceń
}
