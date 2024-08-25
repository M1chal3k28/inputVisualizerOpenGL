#version 330 core

in float vHeight;  // Otrzymana wysokość z shadera wierzchołków
in float vDist; 
in vec2 fragPos;
out vec4 fragColor;

uniform vec2 rectSize;  // Rozmiar prostokąta
uniform float radius;   // Promień zaokrąglenia rogów

void main()
{
    // Kolor na podstawie wysokości
    vec3 lowColor = vec3(0.0, 1.0, 0.0);  // Kolor dla niskiej wysokości
    vec3 highColor = vec3(0.9, 0.0, 0.0); // Kolor dla wysokiej wysokości
    vec3 rightColor = vec3(0.0, 1.0, 0.0);
    vec3 leftColor = vec3(0.0, 0.0, 1.0);

    // Interpolacja koloru na podstawie wysokości i odległości
    vec3 color = mix(lowColor, highColor, vHeight);
    vec3 color2 = mix(rightColor, leftColor, vDist);
    vec3 finalColor = mix(color, color2, 0.5);

    // Konwersja fragPos z NDC (-1 do 1) do przestrzeni ekranu (0 do rectSize)
    vec2 screenPos = (fragPos * 0.5 + 0.5) * rectSize;

    // Pozycja fragmentu względem środka prostokąta
    vec2 pos = screenPos - 0.5 * rectSize;

    // Wartość zaokrąglenia rogu
    vec2 corner = vec2(rectSize.x * 0.5 - radius, rectSize.y * 0.5 - radius);

    // Obliczenie odległości od narożników
    vec2 dist = abs(pos) - corner;

    // Jeżeli jesteśmy wewnątrz promienia zaokrąglenia, rysujemy piksel, w przeciwnym razie ustawiamy przezroczystość
    if (max(dist.x, dist.y) > radius && length(max(dist, vec2(0.0))) > radius) {
        discard; // Odrzuć fragment (piksel)
    }

    fragColor = vec4(finalColor, 1.0); // Ustawienie końcowego koloru fragmentu
}
