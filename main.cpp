/*
    Autor:
    Mario Álvarez Gracia
*/
#include <iostream>
#include <sstream>
#include "estudiantes.h"
#include "unizar.h"
using namespace std;

const int INSCRIBIR_ESTUDIANTE = 1;
const int BORRAR_ESTUDIANTE = 2;
const int MOSTRAR_ESTUDIANTE = 3;
const int CERRAR_INSCRIPCION = 4;
const int OBTENER_ESTUDIANTE_EN_MAT = 5;
const int DESCARTAR_ESTUDIANTE_EN_MAT = 6;
const int ACTUALIZAR_ESTUDIANTE_EN_MAT = 7;
const int PASAR_TURNO = 8;
const int LISTAR_ESTUDIANTES = 9;

estudiantes<estudiante>uni;

void menu();
void inscribirEstudiante(estudiantes<estudiante> &est);
void borrarEstudiante(estudiantes<estudiante> &est);
void mostrarEstudiante(estudiantes<estudiante> &est);
void cerrarInscripciones(estudiantes<estudiante> &est);
void obtenerEstudianteEnMatricula(estudiantes<estudiante> &est);
void descartarEstudianteEnMatricula(estudiantes<estudiante> &est);
void actualizarEstudianteEnMatricula(estudiantes<estudiante> &est);
void pasarTurnoEstudiante(estudiantes<estudiante> &est);
string listarEstudiantes(estudiantes<estudiante> &est);


void crearAsignatura(int id, int nota, estudiante& e);
string mostrarExpediente(estudiante& e);
string mostrarAsignaturas(const estudiante& e);


int main() {
    int opcion = 0;
    string nip = " ";

    crear(uni);
    menu();
    cout << "Elige una opción: " << endl;
    cin >> opcion;

    while(opcion != 0){

        switch(opcion) {
            case INSCRIBIR_ESTUDIANTE:
                inscribirEstudiante(uni);
                break;
            case BORRAR_ESTUDIANTE:
                borrarEstudiante(uni);
                break;
            case MOSTRAR_ESTUDIANTE:
                mostrarEstudiante(uni);
                break;
            case CERRAR_INSCRIPCION:
                cerrarInscripciones(uni);
                break;
            case OBTENER_ESTUDIANTE_EN_MAT:
                obtenerEstudianteEnMatricula(uni);
                break;
            case DESCARTAR_ESTUDIANTE_EN_MAT:
                descartarEstudianteEnMatricula(uni);
                break;
            case ACTUALIZAR_ESTUDIANTE_EN_MAT:
                actualizarEstudianteEnMatricula(uni);
                break;
            case PASAR_TURNO:
                pasarTurnoEstudiante(uni);
                break;
            case LISTAR_ESTUDIANTES:
                cout << listarEstudiantes(uni);
                break;

        }
    menu();
    cout << "Elige una opción: " << endl;
    cin >> opcion;
    }

    return 0;
}

void menu(){
        cout << "**  Menu  **" << endl;
        cout << "** Elige una opción:  **" << endl;
        cout << "1. Inscribir estudiante " << endl;
        cout << "2. Borrar estudiante " << endl;
        cout << "3. Mostrar estudiante" << endl;
        cout << "4. Cerrar Inscripcion" << endl;
        cout << "5. Obtener estudiante en matricula " << endl;
        cout << "6. Descartar estudiante en matricula " << endl;
        cout << "7. Actualizar estudiante en matricula" << endl;
        cout << "8. Pasar turno" << endl;
        cout << "9. Listar estudiantes " << endl;
        cout << "0. SALIR" << endl;
}

void inscribirEstudiante(estudiantes<estudiante> &est){
    estudiante e;
    string nombre;
    string titulacion;
    string nip;
    if (!enMatricula(est)){

        cout << "Introduzca el nombre del estudiante: " << endl;
        cin >> nombre;
        cout << "Introduzca la titulacion del estudiante: " << endl;
        cin >> titulacion;
        cout << "Introduzca el nip del estudiante: " << endl;
        cin >> nip;
        crear(nombre,titulacion,e);
        anyadir(est,nip,e);
        cout << "ESTUDIANTE INSCRITO" << endl;

    }else {
        cout << "Ya nos se pueden inscribir estudiantes" << endl;
    }
}

void borrarEstudiante(estudiantes<estudiante> &est){
    string nip;
    cout << "Introduzca el nip" << endl;
    cin >> nip;

    if(!pertenece(est,nip)){
        cout << "ESTUDIANTE DESCONOCIDO" << endl;
    }
    if(quitar(est,nip)){
        cout << "ESTUDIANTE ELIMINADO" << endl;
    }else{
        cout << "ERROR EN EL PROCESO DE ELIMINACIÓN" << endl;
    }
}
void mostrarEstudiante(estudiantes<estudiante> &est){
    string nip;
    estudiante e;
    cout << "Introduzca el nip" << endl;
    cin >> nip;
    if(!pertenece(est,nip)){
        cout << "ESTUDIANTE DESCONOCIDO" << endl;
    }else{
        cout << "ESTUDIANTE ENCONTRADO" << endl;
        obtenerValor(est,nip,e);
        cout << infoEstudiante(e) << endl;
    }

}
void cerrarInscripciones(estudiantes<estudiante> &est){

    if(enMatricula(est)){
        cout << "NO SE ADMITEN MAS INSCRIPCIONES." << endl;
    }else{
        cerrarInscripcion(est);
        int numEstudiantes;
        numEstudiantes = cardinal(est);
        cout << "INSCRIPCION CERRADA CON " << numEstudiantes << " ESTUDIANTES" << endl;

    }
}

void obtenerEstudianteEnMatricula(estudiantes<estudiante> &est){  //revisaaaaaaaaaaaaaaaaaaaaaaaaar

    int estado_error;
    estudiante e;
    estado_error = obtenerCandidatoSuValor(est,e);
    if(estado_error == 1){
        cout << "NO EXISTEN ESTUDIANTES" << endl;
    }else if(estado_error == 0){
        cout << "TODAVÍA NO HA COMENZADO EL PROCESO DE MATRICULA" <<endl;
    }else{
        cout << "ESTUDIANTE EN MATRICULA: \n" << infoEstudiante(e) << endl;
    }

}
void descartarEstudianteEnMatricula(estudiantes<estudiante> &est){   //dudaaaaaaaaaaaaaaaaaaaaaaaa

    int estado_error;
    estudiante e;
    estado_error = eliminarCandidato(est);

    if(estado_error == 1){
        cout << "NO EXISTEN ESTUDIANTES" << endl;
    }else if(estado_error == 0){
        cout << "TODAVÍA NO HA COMENZADO EL PROCESO DE MATRICULA" <<endl;
    }else{
        obtenerCandidatoSuValor(est,e);
        cout << "ESTUDIANTE ELIMINADO" << endl;
        cout << " Turno de: \n" << infoEstudiante(e) << endl;

    }
}
void actualizarEstudianteEnMatricula(estudiantes<estudiante> &est){

    estudiante e;
    string nip;
    int id = 0;
    int nota = 0;
    int estado_error;
    estado_error = obtenerCandidatoSuValor(est,e);
    if(estado_error == 1){
        cout << "NO EXISTEN ESTUDIANTES" << endl;
    }else if(estado_error == 0){
        cout << "TODAVÍA NO HA COMENZADO EL PROCESO DE MATRICULA" <<endl;
    }else{
        cout << "Introduzca el id de la asignatura: " << endl;
        cin >> id;
        cout << "Introduzca la nota de la asignatura: " << endl;
        cin >> nota;
        if (id <= 9999 && nota <= 99){
            crearAsignatura(id,nota,e);
            obtenerCandidatoSuClave(est, nip);
            cout << "ESTUDIANTE ACTUALIZADO " << endl;
            cout << "Nip: " + nip << endl;
            cout <<  infoEstudiante(e);
            actualizarCandidato(est, e);
        }else {
            if ( id > 9999) {
                cout << "El id es incorrecto" << endl;
            }
            else if (nota > 99) {
                cout << "El valor de la nota es incorrecto" << endl;
            }
            cout << "Datos de la asignatura incorrectos" << endl;
        }
    }

}
void crearAsignatura(int id, int nota, estudiante& e){
    if (e.numAsignaturas < MAX_ASIGNATURAS) {

        e.asignaturas[e.numAsignaturas].id = id;
        e.asignaturas[e.numAsignaturas].nota = nota;
        e.numAsignaturas++;
    }else {
            cout << "Numero de asignaturas alcanzado" << endl;
    }
}

void pasarTurnoEstudiante(estudiantes<estudiante> &est){
    int estado_error;
    estudiante e;
    obtenerCandidatoSuValor(est,e);
    estado_error = pasarTurno(est);
    if(estado_error == 1){
        cout << "NO EXISTEN ESTUDIANTES" << endl;
    }else if(estado_error == 0){
        cout << "TODAVÍA NO HA COMENZADO EL PROCESO DE MATRICULA" <<endl;
    }else{
        obtenerCandidatoSuValor(est,e);
        cout << "TURNO EN ESTUDIANTE: \n" << infoEstudiante(e) << endl;
    }
}

string listarEstudiantes(estudiantes<estudiante> &est){
    ostringstream lista;
    string nip;
    estudiante e;
    if(enMatricula(est)){
        lista << "LISTADO DE ESTUDIANTES" << endl;
    }else{
        lista << "INSCRIPCION" << endl;
    }
    lista << "TOTAL ESTUDIANTES: " << cardinal(est) << endl;
    lista << listar(est) << endl;

    if(enMatricula(est)){
        lista << "TURNO DE MATRICULA EN ESTUDIANTE ";
        if(esVacia(est)){
            lista << "---" << endl;
        }else{
            obtenerCandidatoSuClave(est, nip);
            lista << nip << endl;
        }
    }else{
        lista << "NO HA COMENZADO EL PROCESO DE MATRICULA" << endl;
    }
    lista << "*****" << endl;

    return lista.str();

}

void crear(string nom, string tit, estudiante& e){
    e.nombre = nom;
    e.titulacion = tit;
    e.numAsignaturas = 0;
}
string mostrarAsignaturas(const estudiante& e){
    string asignatura;
    string id;
    string nota;
    string numAsignaturas;
    int codigo = 0;
    int calificacion = 0;
    for (int i = 0; i < e.numAsignaturas; i++){
        codigo = e.asignaturas[i].id;
        calificacion = e.asignaturas[i].nota;
        id = to_string(codigo);
        nota = to_string(calificacion);
        numAsignaturas= to_string(i+1);
        asignatura = asignatura + (numAsignaturas + "->"+ id + ":" + nota + " ");
    }

    return asignatura;
}

string nombre (const estudiante& e){
    return e.nombre;
}
string tit(const estudiante& e){
    return e.titulacion;
}

string infoEstudiante(const estudiante& e){
    ostringstream inf;
    inf << "NOMBRE: "<< e.nombre << endl;
    inf << "TIT: " << e.titulacion <<endl;
    if (e.numAsignaturas > 0){
        inf << "Asignaturas: " << mostrarAsignaturas(e) << endl;
    }
    return inf.str();
}
