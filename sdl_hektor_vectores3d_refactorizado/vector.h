#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector2
{
public:
    double x;
    double y;

    friend std::ostream &operator<<(std::ostream &os, const Vector2 &v);
};

class Vector3
{
public:
    double x;
    double y;
    double z;

    friend std::ostream &operator<<(std::ostream &os, const Vector3 &v);
    
    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);
    void Rotate(Vector3 angles);

    Vector2 OrtographicProjection(float fovFactor);
    Vector2 PerspectiveProjection(float fovFactor);


};

#endif