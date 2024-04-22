#include <iostream>
#include "window.h"
#include "vector.h"

float fovFactor = 100;

Vector3 cameraPosition{0, 0, -5};

// Rotación cubo
Vector3 cubeRotation;

Vector2 OrtoraphicProjection(Vector3 p)
{
    return Vector2{
        fovFactor * p.x, 
        fovFactor * p.y};
}

Vector2 PerspectiveProjection(Vector3 p)
{
    return Vector2{
        (fovFactor * p.x) / p.z, 
        (fovFactor * p.y) / p.z};
}


int main(int argc, char *argv[])
{
    Window window(640, 480);

    Vector2 cubeProjectedPoints[9 * 9 * 9];
    
    // Cubo de 9x9x9 píxeles
    int counterPoints;
    Vector3 cubePoints[9 * 9 * 9];

    // Cargar el array de vectores de -1 a 1 en el cubo 9x9x9
    for (double x = -1; x <= 1; x += 0.25)
    {
        for (double y = -1; y <= 1; y += 0.25)
        {
            for (double z = -1; z <= 1; z += 0.25)
            {
                cubePoints[counterPoints++] = Vector3{x, y, z};
                
            }
        }
    }

    window.Init();
    window.Setup();

    while (window.running)
    {


        window.ProcessInput();

        window.Update();

       
       // Rotation transformations per frame
        cubeRotation.x += 0.01;
        cubeRotation.y += 0.01;
        cubeRotation.z += 0.01;

        for (size_t i = 0; i < 9 * 9 * 9; i++)
        {
            Vector3 point = cubePoints[i];

            // Rotation transformations
            point.RotateX(cubeRotation.x);
            point.RotateY(cubeRotation.y);
            point.RotateZ(cubeRotation.z);

            // Restamos la distancia de la cámara
            point.z -= cameraPosition.z;

            // Proyeccion del punto
            cubeProjectedPoints[i] = PerspectiveProjection(point);
        }


        window.Render();

        window.DrawGrid(0xFF616161);

        /* Dibujar proyección */
        /* Dibujar proyección reposicionada al centro */
        for (int i = 0; i < 9 * 9 * 9; i++)
        {
            window.DrawPixel(
                cubeProjectedPoints[i].x + window.windowWidth / 2,
                cubeProjectedPoints[i].y + window.windowHeight / 2,
                0xFF00FFFF);
        }     

        window.PostRender();
    }

    return 0;
}