/** @file Procesador.hh
    @brief Especificación de la clase Procesador
*/


#ifndef PROCESADOR_HH
#define PROCESADOR_HH

#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <utility>
#include <set>
#include <map>
#include <vector>
#endif
using namespace std;
/** @class Procesador
    @brief Representa un procesador el cual forma el clúster y tiene procesos en ejecución guardados en memoria
*/
class Procesador {

private:

    string id;
    /** @brief Pair con memoria libre y memoria maxima del procesador
     
      first = entero con memoria libre, 
      second = entero con capacidad/memoria máxima del procesador 
    */
    pair <int, int> id_mem; //mem_libre + mem_max

    pair<int,int> alt_izq;  //altura + grado izq

    /** @brief Mapa de indices de cada proceso ordenado crecientemente por su id */
    map <int, int> mjob;

    /** @brief Mapa del los huecos de memoria con la posicion para cada tamaño
      
     */
    map <int, set<int> > mmem; //key = hueco de espacio, value = indices de los huecos libres de memoria

     /** @brief Mapa del los proceso del procesador ordenado por lo indices de menor a mayor
      
     */
    map <int, Proceso> mpos; //key = ind del proceso, value = proceso
    
public:
    //Constructoras

    /** @brief Creadora por defecto.

      Se ejecuta automáticamente al declarar un procesador.
      \pre <em>cierto</em>
      \post El resultado es un procesador de memoria y memoria máxima 0, 
      sin id y un vector vacío de procesos
      \coste Constante
    */
    Procesador();

    /** @brief Creadora con valores concretos.

      \pre m > 0
      \post El resultado es un proceso con id "s" y memoria máxima "m"
      \coste Constante
    */
    Procesador(const string& s, int m, int altura, int left);

    //Modificadoras

    void añadir_alt_izq(int alt, int izq);

    /** @brief Avanza el tiempo del procesador 
     
        \pre El p.i. (P) está inicializado, t > 0
        \post El p.i. contiene los procesos con T - t > 0, 
        en caso que los procesos son eliminados T - t <= 0 los procesos son eliminados
        \coste Lineal (todo el mapa) sobre logaritmico (eliminar_job) 
    */
    void avanzar_tiempo(int t);
    
    /** @brief Añade un proceso al procesador 
     
        \pre El p.i. (P) está inicializado, la memoria de p es menor 
        o igual a la memoria actual de P
        \post El p.i. contiene sus procesos originales más p 
        \coste Logarítmico
    */
    void add_job(const Proceso& p);

    /** @brief Elimina un proceso del procesador 
     
        \pre Existe un proceso en el p.i. con ID = id,
        it puede estar referenciando a un valor o no
        \post El p.i. contiene sus procesos originales menos el proceso con ID = id
        y it apunta al siguiente valor de el elemento borrado
        \coste Logarítmico 
    */
    void eliminar_job(int id, map <int,Proceso>::iterator& it);

    /** @brief Compacta la memoria del procesador 
     
        \pre <em>cierto</em>
        \post El p.i. contiene los procesos originales desplazados 
        al inicio de la memoria
        \coste *No implementado*
    */
    void compactar_mem();

    //Consultoras

    pair<int,int> height_left() const;

    int MEM_libre() const;

    int hueco(int mem) const;

    /** @brief Consultora de el ID del procesador
     
      \pre <em>cierto</em>
      \post El resultado es el ID del p.i.
      \coste Constante
    */
    string consultar_ID() const;

    /** @brief Consultora de la existencia de un proceso
     
      \pre El p.i. esta inicializado
      \post El resultado indicia si existe un proceso en el p.i. con ID = id
      \coste Logarítmico
    */
    bool existe_job(int id) const;

    /** @brief Consultora si el procesador esta activo
     
      \pre <em>cierto</em>
      \post El resultado indica si el procesador contiene almenos 
      un proceso en ejecución
      \coste Constante
    */
    bool en_curso() const;

    //Lectura y escritura

    /** @brief Operación de escritura

      \pre <em>cierto</em>
      \post Se han escrito los atributos del parámetro implícito en el canal
      standard de salida.
      \coste Lineal 
    */
    void escribir() const;
};
#endif