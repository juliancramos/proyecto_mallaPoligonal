#ifndef VERTICE_H
#define VERTICE_H
#include <deque>
#include <ostream>

class Vertice{
    private:
        int indice;
        float x;
        float y;
        float z;

    public:
        //Constructor del vertice
        Vertice(float x, float y, float z, int indice);
        Vertice() : indice(-1), x(0), y(0), z(0) {}

        // Getters
        float getX() const;
        float getY() const;
        float getZ() const;
        int getIndice() const;

        // Setters
        void setX(float x);
        void setY(float y);
        void setZ(float z);

        bool operator==(const Vertice& v) const;
        friend std::ostream& operator<<(std::ostream& os, const Vertice& v);

        
};

#endif


