#include "../Headers/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <direct.h>
#include <cstdlib>

using namespace std;

VEC3D cargarCoordenadas(XMLElement* vectorElement) {
    // Cargar coordenadas x y z de elementos
    double x;
    double y;
    double z;
    x = vectorElement->FindAttribute("x")->DoubleValue();
    y = vectorElement->FindAttribute("y")->DoubleValue();
    z = vectorElement->FindAttribute("z")->DoubleValue();

    return VEC3D(x, y, z);
}


void cargarCamara(XMLElement* camaraElement, VEC3D& posicion, VEC3D& lookat, VEC3D& up, double& fov) {
    // Cargar elementos de la camara
    posicion = cargarCoordenadas(camaraElement->FirstChildElement("posicion"));
    lookat = cargarCoordenadas(camaraElement->FirstChildElement("lookat"));
    up = cargarCoordenadas(camaraElement->FirstChildElement("up"));
    camaraElement->FirstChildElement("fov")->QueryDoubleText(&fov);
}

void cargarLuces(XMLElement* luzElement, VEC3D& posicion, double& intensidad) {
    // Cargar elementos de las luces
    posicion = cargarCoordenadas(luzElement->FirstChildElement("posicion"));
    luzElement->FirstChildElement("intensidad")->QueryDoubleText(&intensidad);
}

void cargarOpciones(XMLElement* opcionesElement, double& ancho, double& alto, double& profundidad, double& c1, double& c2, double& c3, double& iA,double &cantRayos) {
    // Cargar elementos de las opciones
    opcionesElement->FirstChildElement("ancho")->QueryDoubleText(&ancho);
    opcionesElement->FirstChildElement("alto")->QueryDoubleText(&alto);
    opcionesElement->FirstChildElement("profundidad")->QueryDoubleText(&profundidad);
    opcionesElement->FirstChildElement("cantRayos")->QueryDoubleText(&cantRayos);
    opcionesElement->FirstChildElement("c1")->QueryDoubleText(&c1);
    opcionesElement->FirstChildElement("c2")->QueryDoubleText(&c2);
    opcionesElement->FirstChildElement("c3")->QueryDoubleText(&c3);
    opcionesElement->FirstChildElement("intensidadLuzAmbiente")->QueryDoubleText(&iA);
}

material obtenerMaterial(XMLElement* materialElement) {
    // Cargar elementos del material
    materialElement = materialElement->FirstChildElement("material");
    double kA; // coefRefleccionAmbiente
    double kD; //coefRefleccionDifusa
    double kS; //coefRefleccionEspecular
    double eN; // exponenteEspecular
    double kT; // coefTransmision
    double iR; // indiceRefraccion
    color_RR color; // colorMaterial
    color_RR colorDifuso; //colorDifuso Material
    color_RR colorEspecular; // colorEspecular Material
    materialElement->FirstChildElement("coefRefleccionAmbiente")->QueryDoubleText(&kA);
    materialElement->FirstChildElement("coefRefleccionDifusa")->QueryDoubleText(&kD);
    materialElement->FirstChildElement("coefRefleccionEspecular")->QueryDoubleText(&kS);
    materialElement->FirstChildElement("exponenteEspecular")->QueryDoubleText(&eN);
    materialElement->FirstChildElement("coefTransmision")->QueryDoubleText(&kT);
    materialElement->FirstChildElement("indiceRefraccion")->QueryDoubleText(&iR);

    XMLElement* colorElement = materialElement->FirstChildElement("color");
    color.r = colorElement->FindAttribute("r")->DoubleValue();
    color.g = colorElement->FindAttribute("g")->DoubleValue();
    color.b = colorElement->FindAttribute("b")->DoubleValue();

    XMLElement* colorElementD = materialElement->FirstChildElement("colorD");
    colorDifuso.r = colorElementD->FindAttribute("r")->DoubleValue();
    colorDifuso.g = colorElementD->FindAttribute("g")->DoubleValue();
    colorDifuso.b = colorElementD->FindAttribute("b")->DoubleValue();

    XMLElement* colorElementE = materialElement->FirstChildElement("colorE");
    colorEspecular.r = colorElementE->FindAttribute("r")->DoubleValue();
    colorEspecular.g = colorElementE->FindAttribute("g")->DoubleValue();
    colorEspecular.b = colorElementE->FindAttribute("b")->DoubleValue();

    material res;
    res.kA = kA;
    res.kD = kD;
    res.kS = kS;
    res.eN = eN;
    res.kT = kT;
    res.iR = iR;
    res.color = color;
    res.colorE = colorEspecular;
    res.colorD = colorDifuso;

    return res;
}

set<Objeto*> cargarObjetos(XMLElement* objetosElement) {
    set<Objeto*> objetos;
    for (XMLElement* child = objetosElement->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
        string nombreElemento = child->Name();
        //XMLElement* a = child->FirstChildElement("material");
        material mat;
        mat = obtenerMaterial(child);
        if (nombreElemento == "cilindro" || nombreElemento == "esferaDerecha" || nombreElemento == "esferaIzquierda" || nombreElemento == "esfera") {
            double radio;
            VEC3D centro = cargarCoordenadas(child->FirstChildElement("centro"));;
            //centro = cargarCoordenadas(child->FirstChildElement("centro"));
            child->FirstChildElement("radio")->QueryDoubleText(&radio);

            if (nombreElemento == "cilindro") {
                double altura;
                child->FirstChildElement("altura")->QueryDoubleText(&altura);
                objetos.insert(new Cilindro(altura, radio, centro, mat, nombreElemento));
            }
            else {
                objetos.insert(new Esfera(radio, centro, mat, nombreElemento));
            }
        }

       else if (nombreElemento == "paredIzquierda" || nombreElemento == "paredDerecha" || nombreElemento == "paredAtras" || nombreElemento == "Techo" || nombreElemento == "Piso" || nombreElemento == "espejo") {
            VEC3D arr[4];
            int cont = 0;
            for (XMLElement* punto = child->FirstChildElement(); punto != nullptr && cont < 4; punto = punto->NextSiblingElement()) {
                arr[cont] = cargarCoordenadas(punto);
                cont++;
            }
            objetos.insert(new Plano(arr[0], arr[1], arr[2], arr[3], mat, nombreElemento));

        }
        else if (nombreElemento == "mesa") {
            const int maxCaras = 5;
            const int maxTriangulos = 2;
            const int maxPuntos = 3;
            int contCaras = 0;
            int contTriangulos = 0;
            int contPuntos = 0;
            int i = 0;
            VEC3D arr[30];
            set<Triangulo*> triangulos;

            for (XMLElement* cara = child->FirstChildElement(); cara != nullptr && contCaras < maxCaras; cara = cara->NextSiblingElement()) {
                contTriangulos = 0;
                string nombreTriangulo = cara->Name();
                for (XMLElement* triangulo = cara->FirstChildElement(); triangulo != nullptr && contTriangulos < maxTriangulos; triangulo = triangulo->NextSiblingElement()) {
                    contPuntos = 0;
                    for (XMLElement* punto = triangulo->FirstChildElement(); punto != nullptr && contPuntos < maxPuntos; punto = punto->NextSiblingElement()) {
                        arr[i] = cargarCoordenadas(punto);
                        contPuntos++;
                        i++;
                    }
                    Triangulo* t = new Triangulo(arr[0], arr[1], arr[2], nombreTriangulo);
                    triangulos.insert(t);
                    i = 0;

                }
                contCaras++;
            }
            objetos.insert(new Mesa(mat, triangulos, nombreElemento));
        }
    }
    return objetos;
}

string getCurrentDateTime() {
    // Obtener el tiempo actual
    time_t now = std::time(nullptr);
    // Convertirlo a tiempo local
    tm localTime;
#ifdef _WIN32
    localtime_s(&localTime, &now); // Función segura para Windows
#else
    localtime_r(&now, &localTime); // Función segura para POSIX
#endif

    // Formatear la fecha y hora en una cadena
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &localTime);

    return std::string(buffer);
}

void render(Camara cam, set<Objeto*> objetos, set<Luz*> luces, Opciones opciones) {
    FreeImage_Initialise();
    FIBITMAP* image1 = FreeImage_Allocate(opciones.ancho, opciones.alto, 32); // Imagen con todo
    FIBITMAP* image2 = FreeImage_Allocate(opciones.ancho, opciones.alto, 32); // Imagen de Reflexion
    FIBITMAP* image3 = FreeImage_Allocate(opciones.ancho, opciones.alto, 32); // Imagen de Transmisión

    // Obtener acceso a los datos del bitmap
    BYTE* bits1 = FreeImage_GetBits(image1); 
    BYTE* bits2 = FreeImage_GetBits(image2);
    BYTE* bits3 = FreeImage_GetBits(image3);

    double kT = 0;
    double kS = 0;
    for (int j = 0; j < opciones.alto; ++j) {
    #pragma omp parallel for
        for (int i = 0; i < opciones.ancho; ++i) {
            color_RR pixel;
            pixel.r = 0;
            pixel.g = 0;
            pixel.b = 0;
            pixel.alpha = 0;
            for (int m = 0; m < opciones.cantRayos; m++) {
                double u = ((double)(i) + (double)(rand() / RAND_MAX))/ opciones.ancho;
                double v = ((double)(j)+ (double)(rand() / RAND_MAX)) / opciones.alto;
                Rayo rayo = cam.getRayo(u, v);
                color_RR color = traza_RR(rayo, objetos, luces, opciones, 1,1, kT, kS);
                pixel.r += color.r;
                pixel.g += color.g;
                pixel.b += color.b;
            }
            pixel.r /= opciones.cantRayos;
            pixel.g /= opciones.cantRayos;
            pixel.b /= opciones.cantRayos;
            if (pixel.r >= 0.999) {
                pixel.r = 0.999;
            }
            if (pixel.g >= 0.999) {
                pixel.g = 0.999;
            }
            if (pixel.b >= 0.999) {
                pixel.b = 0.999;
            }
            if (pixel.r < 0) {
                pixel.r = 0;
            }
            if (pixel.g < 0) {
                pixel.g = 0;
            }
            if (pixel.b < 0) {
                pixel.b = 0;
            }

            bits1[4 * (j * (int)opciones.ancho + i) + 0] = pixel.b * 255.0; // Blue
            bits1[4 * (j * (int)opciones.ancho + i) + 1] = pixel.g * 255.0; // Green
            bits1[4 * (j * (int)opciones.ancho + i) + 2] = pixel.r * 255.0; // Red
            bits1[4 * (j * (int)opciones.ancho + i) + 3] = 255;   // Alpha

            bits2[4 * (j * (int)opciones.ancho + i) + 0] = kT * 255.0; // Blue
            bits2[4 * (j * (int)opciones.ancho + i) + 1] = kT * 255.0; // Green
            bits2[4 * (j * (int)opciones.ancho + i) + 2] = kT * 255.0; // Red
            bits2[4 * (j * (int)opciones.ancho + i) + 3] = 255;   // Alpha

            bits3[4 * (j * (int)opciones.ancho + i) + 0] = kS * 255.0; // Blue
            bits3[4 * (j * (int)opciones.ancho + i) + 1] = kS * 255.0; // Green
            bits3[4 * (j * (int)opciones.ancho + i) + 2] = kS * 255.0; // Red
            bits3[4 * (j * (int)opciones.ancho + i) + 3] = 255;   // Alpha

        }
        cout << "Progreso: " << (int)(j * 100 / (opciones.alto - 1)) << "%\r";
        cout.flush();
    }

    // Obtener la fecha y hora actual
    if (_mkdir("Images"));
        cout << "Se creo la carpeta" << endl;
    string fecha = "Images/" + getCurrentDateTime();
    if (_mkdir(fecha.c_str()))
        cout << "Se creo la carpeta" << endl;
    string directorio = fecha + "/image.png";

    if (image1) {
        if (FreeImage_Save(FIF_PNG, image1, directorio.c_str(), PNG_DEFAULT)) {
            cout << "Imagen guardada" << endl;
            string command = "start " + directorio;
            system(command.c_str());
        }
    }else
        cout << "No se guardo la imagen bien";

    FreeImage_Unload(image1);
    directorio = fecha + "/kT.png";

    if (image2) {
        if (FreeImage_Save(FIF_PNG, image2, directorio.c_str(), PNG_DEFAULT)) {
            cout << "Imagen guardada" << endl;
            string command = "start " + directorio;
            system(command.c_str());
        }
    }
    else
        cout << "No se guardo la imagen bien";

    FreeImage_Unload(image2);
    directorio = fecha + "/kS.png";

    if (image3) {
        if (FreeImage_Save(FIF_PNG, image3, directorio.c_str(), PNG_DEFAULT)) {
            cout << "Imagen guardada" << endl;
            string command = "start " + directorio;
            system(command.c_str());
        }
    }
    else
        cout << "No se guardo la imagen bien";
    cout << "Precione enter para continuar ... ";
    cin.get();;
    FreeImage_DeInitialise();
}




bool interseccion(Rayo rayo, set<Objeto*> objetos, Objeto*& obj, VEC3D& normal, VEC3D& nuevoOrigen) {
    VEC3D norm;
    VEC3D origen;
    double distancia = HUGE_VAL;
    bool hay_interseccion = false;
    for (Objeto* objeto : objetos) {
        if (objeto->interseccion(rayo, distancia, origen, norm)) {
            distancia = (rayo.getOrigen() - origen).norma();
            nuevoOrigen = origen;
            normal = norm;
            hay_interseccion = true;
            obj = objeto;
        }
    }
    return hay_interseccion;
}

double static fatt(double distancia, Opciones opc) {
    distancia = distancia * 8 / 500;
    double p1 = opc.c1;
    double p2 = opc.c2 * distancia;
    double p3 = opc.c3 * pow(distancia, 2);
    double f = (1 / (p1 + p2 +  p3));
    return f < 1 ? f : 1;
}

double static calcularRV(VEC3D normal, VEC3D luz, VEC3D dir) {
    return (normal * normal.escalar(luz) * 2 - luz).escalar(dir * -1);
}

color_RR static sombra_RR(Objeto* obj, Rayo rayo, VEC3D nuevoOrigen, VEC3D normal, double profundidad, set<Luz*> luces, Opciones opc, set<Objeto*> objetos,double iR) {
    color_RR color;
    
    if (profundidad > opc.profundidad) {
        color.r = 0;
        color.g = 0;
        color.b = 0;
        return color;
    }
    
    material mat = obj->getMaterial();
    //parte de la izquierda de la ecuacion de traza de rayos recursivas
    color.r = opc.iA * mat.color.r * mat.kA;
    color.g = opc.iA * mat.color.g * mat.kA;
    color.b = opc.iA * mat.color.b * mat.kA;



    for (Luz* it : luces) {
        /*rayo_s = rayo desde el punto a la luz*/
        VEC3D dirLuz = (it->getPosicion() - nuevoOrigen).normalizar();
        float distancia = (it->getPosicion() - nuevoOrigen).norma();
        Rayo rayoLuz = Rayo(nuevoOrigen + dirLuz * 0.001, dirLuz);
        double kTobjeto = 1.0;
        if (normal.escalar(dirLuz) > 0) {
            kTobjeto = 1;
       
            /*calcular cuanta luz es bloqueada por sup.opacas y transp., y
            usarlo para escalar los terminos difusos y especulares antes de a�adirle color*/
            VEC3D interseccion, nuevaNormal = normal;
            color_RR colorsito;
            colorsito.b = 0;
            colorsito.r = 0;
            colorsito.g = 0;
            for (Objeto* o : objetos) {   
                if(o->interseccion(rayoLuz, distancia, interseccion, nuevaNormal)) { // HAY INTERSECCION 
                     VEC3D vector = (interseccion - rayoLuz.getOrigen()).normalizar();
                     if (vector.escalar(normal) >= 0) {
                         kTobjeto *= o->getMaterial().kT; // S_i
                         colorsito.r += o->getMaterial().color.r;
                         colorsito.b += o->getMaterial().color.b;
                         colorsito.g += o->getMaterial().color.g;
                     }
                }
            }

            if (colorsito.r == 0 && colorsito.b == 0 && colorsito.g == 0) {
                colorsito.b = 1;
                colorsito.r = 1;
                colorsito.g = 1;
            }

            if (kTobjeto > 0.1) {
                kTobjeto = log10(kTobjeto) + 1;
            }
            
            double izq = kTobjeto * fatt(distancia, opc) * it->getIntensidad();
            double NL = normal.escalar(rayoLuz.getDireccion());
            double RV = calcularRV(normal, rayoLuz.getDireccion(), rayo.getDireccion());
            color.r += (izq * colorsito.r) * ((mat.kD * mat.colorD.r * NL) + (mat.kS * mat.colorE.r * pow(RV, mat.eN)));
            color.g += (izq * colorsito.g) * ((mat.kD * mat.colorD.g * NL) + (mat.kS * mat.colorE.g * pow(RV, mat.eN)));
            color.b += (izq * colorsito.b) * ((mat.kD * mat.colorD.b * NL) + (mat.kS * mat.colorE.b * pow(RV, mat.eN)));
        }
    }

    double kT = 0;
    double kS = 0;

    if (profundidad < opc.profundidad) {
        if (mat.kS > 0) { // es reflejante
            VEC3D dirNuevoRayo = (rayo.getDireccion() - (normal * (2 * rayo.getDireccion().escalar(normal)))).normalizar();
            Rayo rayo_r = Rayo(nuevoOrigen + dirNuevoRayo*0.001, dirNuevoRayo);
            color_RR color1 = traza_RR(rayo_r, objetos, luces, opc, profundidad + 1,iR, kT, kS);
            color.r += color1.r * mat.kS;
            color.g += color1.g * mat.kS;
            color.b += color1.b * mat.kS;
        }

        if (mat.kT > 0) { // es transparente
            // El 1 = n1 es el indice de refraccion del vacio
            double cosTheta = rayo.getDireccion().escalar(normal);
            double eta = iR / mat.iR;
            double sinTheta2sq = eta * eta * sqrt(1 - cosTheta * cosTheta);
            VEC3D T, O;
            if (eta > 1) {
                T = VEC3D(0, 0, 0);
                O = VEC3D(0, 0, 0);
            }
            else {
                double cosTheta2 = sqrt(1 - sinTheta2sq);
                VEC3D refrac = rayo.getDireccion() + normal * (eta * cosTheta - cosTheta2);
                O = nuevoOrigen;
                T = refrac.normalizar();
            }
            Rayo rayo_t = Rayo(O + T* 0.001, T);
            if (T.getX() != 0 && T.getY() != 0 && T.getZ() != 0) {
                color_RR color1 = traza_RR(rayo_t, objetos, luces, opc, profundidad + 1, mat.iR, kT, kS);
                color.r += color1.r * mat.kT;
                color.g += color1.g * mat.kT;
                color.b += color1.b * mat.kT;
            }
        }
    }
    return color;
}

color_RR traza_RR(Rayo rayo, set<Objeto*> objetos, set<Luz*> luces, Opciones opciones, int profundidad,double iR, double &kT, double &kS) {
    Objeto* obj = nullptr;
    VEC3D normal;
    VEC3D nuevoOrigen;

    if (interseccion(rayo, objetos, obj, normal, nuevoOrigen)) {
        kS = obj->getMaterial().kS;
        kT = obj->getMaterial().kT;
        return sombra_RR(obj, rayo, nuevoOrigen, normal, profundidad, luces, opciones, objetos,iR);
    }
    else {
        color_RR negro;
        negro.r = 0;
        negro.g = 0;
        negro.b = 0;
        return negro;
    }
}

void liberarObjetos(set<Objeto*>& objetos) {
    for (Objeto* objeto : objetos) {
        delete objeto;
    }
}