/** @file Area_espera.hh
   @brief Especificación de la clase Area_espera
*/


#ifndef Area_espera_HH
#define Area_espera_HH

#include "Proceso.hh"
#include "Cluster.hh"
#include "Prioridad.hh"
#ifndef NO_DIAGRAM
#include <string>
#include <iostream>
#include <vector>
#include <map>
#endif

/** @class Area_espera
    @brief Representa un área de espera formado por procesos pendientes (en espera de ser ejecutados)
*/

class Area_espera {

private:
    /** @brief Mapa de prioridades ordenado lexicográficamente por su id */
    map <string, Prioridad> mprior;

public:
    //Constructoras

    /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un area de espera.
      \pre <em>cierto</em>
      \post El resultado es un conjunto de prioridades vacio.
      \coste Constante
  */
    Area_espera();

    //Modificadoras

    /** @brief Añade un proceso al área de espera
     
      \pre <em>cierto</em>
      \post El resultado es el p.i. más el proceso p con el ID de proridad = id_prior
      \coste Logarítmico sobre coste logarítmico
  */
    void add_job(const Proceso& p, const string& id_prior);

    /** @brief Añade una prioridad al área de espera
     
      \pre <em>cierto</em>
      \post El resultado es el p.i. más la prioridad con id_prior
      \coste Logarítmico (búsqueda del elemento en el árbol de búsqueda binario interno)
  */
    void add_prior(const string& id_prior);

    /** @brief Elimina una prioridad del área de espera
     
        \pre Existe una prioridad en el p.i. con ID de prioridad = id_prior
        \post El p.i. contiene sus prioridades originales menos la prioridad con ID de prioridad = id_prior
        \coste Logarítmico (búsqueda del elemento en el árbol de búsqueda binario interno)
    */
    void eliminar_prior(const string& id_prior);

    /** @brief Intenta enviar una cantidad de procesos del área de espera al cluster 
     
        \pre n > 0
        \post El p.i. ha intentado enviar n procesos al cluster c, los aceptados
        son elimindas del p.i., los rechazados vuelven al p.i. como nuevos
        \coste Lineal sobre lineal (consultar coste de la función en_proceso()
        de la clase Prioridad)
    */
    void enviar_job_a_cluster(int n, Cluster& c);

    //Consultoras
    
    //Lectura y escritura

    /** @brief Operación de lectura

      \pre Hay preparados en el canal standard de entrada un número inicial de prioridades N > 0 y el identificador de N prioridades
      \post El parámetro ímplicito pasa a tener los atributos leídos del canal standard de entrada
      \coste Lineal sobre coste logarítmico (inserción en el mapa)
      respecto al número de prioridades del área de espera leído (nlog(n))
    */
    void leer();

    /** @brief Operación de escritura de todos los procesos de todas las prioridades

      \pre <em>cierto</em>
      \post Se ha escrito todos los procesos pendientes de todas las prioridades 
       del área de espera por orden creciente de prioridad  en el canal standard de salida. 
       \coste Lineal respecto al número procesos de todas las prioridades del área de espera escrito
    */
    void escribir() const; //utiliza la operación "escribir_proc" para todas la id_prior

    /** @brief Operación de escritura de todos los procesos de una prioridad especifica

      \pre Existe una prioridad con ID = id_prior en el p.i.
      \post Se ha escrito todos los procesos pendientes con la prioridad id_prior   
        por orden decreciente de antigüedad en el canal standard de salida. 
      \coste Lineal respecto al número de procesos de la prioridad escrita,
      más logarítmico (búsqueda en el mapa)
    */
    void escribir_prior(const string& id_prior,map <string, Prioridad>::const_iterator& it) const; //escribe todos los procesos pendeintes con esta id_prior

};
#endif