#version 330 core

in float vHeight;  // Otrzymana wysokość z shadera wierzchołków
out vec4 fragColor;

void main()
{
    // Kolor na podstawie wysokości
    // Możesz tu użyć dowolnej funkcji, np. interpolacji pomiędzy dwoma kolorami
    vec3 lowColor = vec3(0.0, 1.0, 0.0);  // Kolor dla niskiej wysokości (np. niebieski)
    vec3 highColor = vec3(1.0, 0.0, 0.0); // Kolor dla wysokiej wysokości (np. czerwony)

    // Interpolacja koloru na podstawie wysokości
    vec3 color = mix(lowColor, highColor, vHeight);

    fragColor = vec4(color, 1.0); // Ustawienie końcowego koloru fragmentu
}