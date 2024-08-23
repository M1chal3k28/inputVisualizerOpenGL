#version 330 core
out vec3 color;

in float height; // Wysokość przekazana z vertex shadera

void main(){
    // Zakres wysokości dla spectrogramu
    float minHeight = 0.0;  // Minimalna wysokość
    float maxHeight = 10.0; // Maksymalna wysokość (zmień według potrzeb)

    // Normalizacja wysokości do zakresu 0.0 - 1.0
    float heightFactor = clamp((height - minHeight) / (maxHeight - minHeight), 1.0, 1.0);

    // Mieszanie koloru zielonego i czerwonego
    color = mix(vec3(0.0, 1.0, 0.0), vec3(1.0, 0.0, 0.0), heightFactor);
}
