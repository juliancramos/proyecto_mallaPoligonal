#ifndef VERTICE_H
#define VERTICE_H
#include <deque>

class Vertice{
    private:
        int indice;
        float x;
        float y;
        float z;

    public:
        //Constructor del vertice
        Vertice(float x, float y, float z, int indice);

        // Getters
        float getX() const;
        float getY() const;
        float getZ() const;
        int getIndice() const;

        // Setters
        void setX(float x);
        void setY(float y);
        void setZ(float z);

        
};

#endif


