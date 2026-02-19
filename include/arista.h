#ifndef ARISTA_H
#define ARISTA_H

class Arista {
public:
    int v1, v2;
    float distancia;

    Arista(int v1, int v2, float distancia = -1.0f);
    int getVertice1() const;
    int getVertice2() const;
    float getDistancia() const;
    void setDistancia(float dist);
};

#endif // ARISTA_H
