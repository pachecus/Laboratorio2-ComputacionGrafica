#pragma once

#ifndef UTILS_H
#define UTILS_H

#include "Esfera.h" // Suponiendo que tienes archivos de encabezado para todas las clases de objetos
#include "Cilindro.h"
#include "Objeto.h"
#include "Luz.h"
#include "Camara.h"
#include "Rayo.h"
#include "Opciones.h"
#include "Vector.h"
#include "Plano.h"
#include <FreeImage.h>
#include <set>
#include "tinyxml2.h"
#include "Triangulo.h"
#include "Mesa.h"
#include <cstdlib>

using namespace tinyxml2;


VEC3D cargarCoordenadas(XMLElement* vectorElement);

void cargarCamara(XMLElement* camaraElement, VEC3D& posicion, VEC3D& direccion, VEC3D& up, double& fov);

void cargarOpciones(XMLElement* opcionesElement, double& ancho, double& alto, double& profundidad, double& c1, double& c2, double& c3, double& iA,double & cantRayos);

set<Objeto*> cargarObjetos(XMLElement* objetosElement);

void cargarLuces(XMLElement* luzElement, VEC3D& posicion, double& intensidad);

void render(Camara cam, set<Objeto*> objetos, set<Luz*> luces, Opciones opciones);

color_RR traza_RR(Rayo rayo, set<Objeto*> objetos, set<Luz*> luces, Opciones opciones, int profundidad, double iR, double &kT, double &kS);

color_RR static sombra_RR(Objeto* obj, Rayo rayo, VEC3D nuevoOrigen, VEC3D normal, double profundidad, set<Luz*> luces, Opciones opc, set<Objeto*> objetos, double iR);

bool interseccion(Rayo rayo, set<Objeto*> objetos, Objeto*& obj, VEC3D& normal, VEC3D& nuevoOrigen);

void liberarObjetos(set<Objeto*>& objetos);

material obtenerMaterial(XMLElement* materialElement);

#endif