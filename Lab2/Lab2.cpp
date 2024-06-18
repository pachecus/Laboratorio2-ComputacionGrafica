#include <FreeImage.h>
#include "../Headers/Luz.h"
#include "../Headers/Camara.h"
#include "../Headers/Opciones.h"
#include "../Headers/utils.h"
#include <time.h>

int main() {

    clock_t start = clock();
    XMLDocument doc;
    doc.LoadFile("config.xml");
    XMLElement* escena = doc.RootElement();

    VEC3D posCam = VEC3D();
    VEC3D lookat = VEC3D();
    VEC3D up = VEC3D();
    VEC3D posLuz = VEC3D();
    double intensidad;
    double fov = 0;
    double ancho = 0;
    double alto = 0;
    double profundidad = 0;
    double c1 = 0;
    double c2 = 0;
    double c3 = 0;
    double iA = 0;
    double cantRayos = 0;
    set<Objeto*> objetos;
    set<Luz*> luces;

    XMLElement* opcionesXML = escena->FirstChildElement("opciones");
    cargarOpciones(opcionesXML, ancho, alto, profundidad, c1, c2, c3, iA, cantRayos);

    cout << "Opciones: " << endl;
    cout << "ancho: " << ancho << endl;
    cout << "alto: " << alto << endl;
    cout << "profundidad: " << profundidad << endl;
    cout << "cantRayos: " << cantRayos << endl;
    cout << "c1: " << c1 << endl;
    cout << "c2: " << c2 << endl;
    cout << "c3: " << c3 << endl;
    cout << "iA: " << iA << endl;

    XMLElement* camara = escena->FirstChildElement("camara");

    cargarCamara(camara, posCam, lookat, up, fov);
    double aspectRatio = ancho / alto;
    Camara cam = Camara(posCam, lookat, up, fov, aspectRatio);

    Opciones opciones;
    opciones.ancho = ancho;
    opciones.alto = alto;
    opciones.profundidad = profundidad;
    opciones.c1 = c1;
    opciones.c2 = c2;
    opciones.c3 = c3;
    opciones.iA = iA;
    opciones.cantRayos = cantRayos;
    XMLElement* objetosXML = escena->FirstChildElement("objetos");
    objetos = cargarObjetos(objetosXML);
    XMLElement* lucesXML = escena->FirstChildElement("luces");

    for (XMLElement* child = lucesXML->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
        cargarLuces(child, posLuz, intensidad);
        luces.insert(new Luz(posLuz, intensidad));
    }

    render(cam, objetos, luces, opciones);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecuccion: %f segundos\n", time_spent);

    return 0;
}