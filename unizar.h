/*
    Autor:
    Mario Álvarez Gracia
*/
#ifndef UNIZAR_H_INCLUDED
#define UNIZAR_H_INCLUDED
#include <iostream>
#include "estudiantes.h"
using namespace std;

// Interfaz del TAD estudiante. Pre-declaraciones
struct estudiante;
void crear (string nom, string tit, estudiante& e);
string nombre (const estudiante& e);
string tit (const estudiante& e);

string mostrarAsignaturas(const estudiante& e);
void crearAsignatura(int id, int nota, estudiante& e);


string infoEstudiante (const estudiante& e);
const int MAX_ASIGNATURAS = 40;


// Declaración:
struct estudiante {
    friend void crear (string nom, string tit, estudiante& e);
    friend string nombre (const estudiante& e);
    friend string tit (const estudiante& e);

    friend void crearAsignatura(int id, int nota, estudiante& e);
    friend string mostrarAsignaturas(const estudiante& e);

    friend string infoEstudiante(const estudiante& e);
    private: // Declaración interna del tipo
        string nombre;
        string titulacion;
        struct asignatura{
            int id;
            int nota;
        };
        asignatura asignaturas[MAX_ASIGNATURAS];
        int numAsignaturas;

};
#endif

