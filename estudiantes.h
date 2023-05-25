/*
    Autor:
    Mario Álvarez Gracia
*/

#ifndef ESTUDIANTES_H_INCLUDED
#define ESTUDIANTES_H_INCLUDED

//#ifndef _ESTUDIANTES_
//#define _ESTUDIANTES_
#include <iostream>
#include <sstream>
#include "unizar.h"

using namespace std;

template<typename V> struct estudiantes;

template<typename V> void crear(estudiantes<V>& est);
template<typename V> int cardinal(const estudiantes<V>& est);
template<typename V> bool esVacia(const estudiantes<V>& est);
template<typename V> bool pertenece(const estudiantes<V>& est, const string c);
template<typename V> bool obtenerValor(const estudiantes<V>& est, const string c, V& v);
template<typename V> bool enMatricula(const estudiantes<V>& est);
template<typename V> bool anyadir(estudiantes<V>& est, const string c, const V& v);
template<typename V> bool quitar(estudiantes<V>& est, const string c);
template<typename V> void cerrarInscripcion(estudiantes<V>& est);
template<typename V> int pasarTurno(estudiantes<V>& est);
template<typename V> int obtenerCandidatoSuClave(const estudiantes<V>& est, string& c);
template<typename V> int obtenerCandidatoSuValor(const estudiantes<V>& est, V& v);
template<typename V> int actualizarCandidato(estudiantes<V>& est, const V& v);
template<typename V> int eliminarCandidato(estudiantes<V>& est);
template<typename V> string listar(estudiantes<V>& est);
template<typename V> void iniciarIterador(estudiantes<V>& est);
template<typename V> bool existeSiguiente(const estudiantes<V>& est);
template<typename V> bool siguiente(estudiantes<V>& est);

template<typename V> struct estudiantes {
    friend void crear<V>(estudiantes<V>& est);
    friend int cardinal<V>(const estudiantes<V>& est);
    friend bool esVacia<V>(const estudiantes<V>& est);
    friend bool pertenece<V>(const estudiantes<V>& est, const string c);
    friend bool obtenerValor<V>(const estudiantes<V>& est, const string c, V& v);
    friend bool anyadir<V>(estudiantes<V>& est, const string c, const V& v);
    friend bool quitar<V>(estudiantes<V>& est, const string c);
    friend void cerrarInscripcion<V>(estudiantes<V>& est);

    friend bool enMatricula<V>(const estudiantes<V>& est);
    friend int pasarTurno<V>(estudiantes<V>& est);
    friend int obtenerCandidatoSuClave<V>(const estudiantes<V>& est, string& c);
    friend int obtenerCandidatoSuValor<V>(const estudiantes<V>& est, V& v);
    friend int actualizarCandidato<V>(estudiantes<V>& est, const V& v);
    friend int eliminarCandidato<V>(estudiantes<V>& est);
    friend string listar<V>(estudiantes<V>& est);
    friend void iniciarIterador<V>(estudiantes<V>& est);
    friend bool existeSiguiente<V>(const estudiantes<V>& est);
    friend bool siguiente<V>(estudiantes<V>& est);

private:
    bool inscripcion;
    bool matricula;
    int total;

    struct estudiante{
        V valor;
        string clave;
        estudiante* sig;
    };
    estudiante* iterador;
    estudiante* primerEstudiante;
    estudiante* turno;
};

//{Devuelve una “agrupación de estudiantes” de selección vacía, sin elementos (pares), y en estado de Inscripción.}
template<typename V> void crear(estudiantes<V>& est){
    est.primerEstudiante = nullptr;
    est.total = 0;
    est.matricula = false;
    est.inscripcion = true;
};

//{Devuelve el nº de elementos (de pares) en la “agrupación de estudiantes” est}
template<typename V> int cardinal(const estudiantes<V>& est){
    return est.total;
};

//{Devuelve verdad si y sólo si est no tiene elementos}
template<typename V> bool esVacia(const estudiantes<V>& est){
    return est.total == 0;
};

//devuelve verdad si y solo si en est hay algun par (c,v)
template<typename V> bool pertenece(const estudiantes<V>& est, const string c){

    if(est.primerEstudiante != nullptr){
        typename estudiantes<V>::estudiante* ptrAux;
        ptrAux = est.primerEstudiante;
        while(ptrAux != nullptr){
            if(ptrAux->clave == c){
                return true;
            }else{
                ptrAux = ptrAux->sig;
            }
        }
    }
    return false;
}

//{Devuelve el valor asociado a la clave c en un par en est.
template<typename V> bool obtenerValor(const estudiantes<V>& est, const string c, V& v){

    if (!pertenece(est, c)){
            return false;
    }
    typename estudiantes<V>::estudiante* ptrAux;
    ptrAux = est.primerEstudiante;

    while(ptrAux != nullptr){
        if(ptrAux->clave == c){
            v = ptrAux->valor;
            return true;
        }else{
            ptrAux = ptrAux->sig;
        }
    }
    return false;
}

//{Devuelve verdad si y sólo si est está en estado de Matrícula.}
template<typename V> bool enMatricula(const estudiantes<V>& est){
    return est.matricula;
}


/*{Si en est no hay ningún par con clave c, devuelve una “agrupación de estudiantes” igual a la
resultante de añadir el par (c,v) a est; si en est hay un par (c,v’), entonces devuelve una
“agrupación de estudiantes” igual a la resultante de sustituir (c,v’) por el par (c,v) en est.*/
template<typename V> bool anyadir(estudiantes<V>& est, const string c, const V& v){
        typename estudiantes<V>::estudiante* ptrAux;
        typename estudiantes<V>::estudiante* nodo;

    if (est.primerEstudiante == nullptr){
        est.primerEstudiante = new typename estudiantes<V>::estudiante;
        est.primerEstudiante->clave = c;
        est.primerEstudiante->valor = v;
        est.primerEstudiante->sig=nullptr;
        est.total++;
    }else if(est.primerEstudiante->clave > c){
        ptrAux = est.primerEstudiante;
        est.primerEstudiante->clave = c;
        est.primerEstudiante->valor = v;
        est.primerEstudiante->sig = ptrAux;
        est.total++;

    }else if(c == est.primerEstudiante->clave){
        est.primerEstudiante->valor = v;
    }else{
        ptrAux = est.primerEstudiante;
        while(ptrAux->sig != nullptr && c > ptrAux->sig->clave){
            ptrAux = ptrAux->sig;
        }
        if(ptrAux->sig != nullptr && c == ptrAux->sig->clave){
            ptrAux->sig->valor = v;
        }else{
            nodo = new typename estudiantes<V>::estudiante;
            nodo->clave = c;
            nodo->valor = v;
            nodo->sig = ptrAux->sig;
            ptrAux->sig = nodo;
            est.total++;
        }
    }
    return false;
}


/* {Si c está en est, devuelve una “agrupación de estudiantes” igual a la resultante de borrar en
est el par con clave c; si c no está en est, devuelve una “agrupación de estudiantes” igual a
est.
Parcial: la operación no está definida si enMatrícula?(est).} */
template<typename V> bool quitar(estudiantes<V>& est, const string c){    //revisar si da error

    if(enMatricula(est)){
            return false;
    }
    typename estudiantes<V>::estudiante* ptrAux;
    typename estudiantes<V>::estudiante* ptrAux2;
    bool parar;
    if(est.primerEstudiante != nullptr){
       if(est.primerEstudiante->clave <= c){
            if(est.primerEstudiante->clave == c){
                ptrAux = est.primerEstudiante;
                est.primerEstudiante = est.primerEstudiante->sig;
                delete(ptrAux);
                est.total--;
                return true;
            }else{
                parar = false;
                ptrAux = est.primerEstudiante->sig;
                ptrAux2 = est.primerEstudiante;
                while( ptrAux != nullptr && !parar){
                    if(!pertenece(est,c)){
                        parar = true;
                    }else if(c == ptrAux->clave){
                        ptrAux2->sig = ptrAux->sig;
                        delete(ptrAux);
                        est.total--;
                        return true;
                    }else{
                        ptrAux2 = ptrAux;
                        ptrAux = ptrAux2->sig;
                    }
                }
            }
       }
    }
    return false;
}

/*{Si enMatrícula?(est), devuelve una “agrupación de estudiantes”
igual a est; si no
enMatrícula?(est), devuelve una “agrupación de estudiantes” igual a la resultante de poner est
en estado de Matrícula y además, si no esVacía?(est), fijar el turno en el elemento inscrito en
primer lugar en la “agrupación de estudiantes” est.} */
template<typename V> void cerrarInscripcion(estudiantes<V>& est){
    est.matricula = true;
    est.turno = est.primerEstudiante;
}


/*{Si enMatrícula?(est), devuelve una “agrupación de estudiantes” igual a la resultante de pasar
el turno del elemento que actualmente tenga el turno al que le siga en el orden de inscripción,
y teniendo en cuenta que si el que tenía el turno era el último inscrito, el turno deberá pasar
al primer inscrito.
Parcial: la operación no está definida si no es verdad enMatrícula?(est) o si es verdad
esVacía?(est).} */
template<typename V> int pasarTurno(estudiantes<V>& est){
    if(!est.matricula){
        return 0;
    }else if(esVacia(est)){
        return 1;
    }else{
        if(est.turno->sig == nullptr){
            est.turno = est.primerEstudiante;
        }else{
            est.turno = est.turno->sig;
        }
        return 2;
    }
}

/* {Si enMatrícula?(est), devuelve la clave c del par (c,v) que tiene el turno en la “agrupación de
estudiantes” est.
Parcial: la operación no está definida si no es verdad enMatrícula?(est) o si esVacía?(est).} */
template<typename V> int obtenerCandidatoSuClave(const estudiantes<V>& est, string& c){

    if(!est.matricula){
        return 0;
    }else if(esVacia(est)){
        return 1;
    }else{
        c = est.turno->clave;
        return 2;
    }
}

template<typename V> int obtenerCandidatoSuValor(const estudiantes<V>& est, V& v){
    if(!est.matricula){
        return 0;
    }else if(esVacia(est)){
        return 1;
    }else{
        v = est.turno->valor;
        return 2;
    }
}

template<typename V> int actualizarCandidato(estudiantes<V>& est, const V& v){

    if(!est.matricula){
        return 0;
    }else if(esVacia(est)){
        return 1;
    }else{
        est.turno->valor = v;
        return 2;
    }
}

template<typename V> int eliminarCandidato(estudiantes<V>& est){

   if(!est.matricula){
        return 0;
    }else if(esVacia(est)){
        return 1;
    }else{
       typename estudiantes<V>::estudiante* ptrAux;
       ptrAux = est.turno;
       est.turno = est.turno->sig;
       est.matricula = false;
       quitar(est, ptrAux->clave);
       est.matricula = true;
       return 2;
    }
}

template<typename V> string listar(estudiantes<V>& est){

    ostringstream infoEstudiantes;
    iniciarIterador(est);
    if(!esVacia(est)){
        infoEstudiantes << "Nip: " << est.iterador->clave << endl;
        infoEstudiantes << infoEstudiante(est.iterador->valor) << endl;
        while(existeSiguiente(est)){
            siguiente(est);
            infoEstudiantes << "Nip: " << est.iterador->clave << endl;
            infoEstudiantes << infoEstudiante(est.iterador->valor) << endl;
        }
    }
    return infoEstudiantes.str();
}



template<typename V> void iniciarIterador(estudiantes<V>& est){
    est.iterador = est.primerEstudiante;
}

template<typename V> bool existeSiguiente(const estudiantes<V>& est){
    return(est.iterador->sig != nullptr);
}

template<typename V> bool siguiente(estudiantes<V>& est){
    if(existeSiguiente(est)){
        est.iterador = est.iterador->sig;
        return true;
    } else {
        return false;
    }
}


#endif // ESTUDIANTES_H_INCLUDED
