/** @file Procesador.hh
    @brief Especificación de la clase Procesador
*/


#ifndef PROCESADOR_HH
#define PROCESADOR_HH

#include "Proceso.hh"
#include "Prioridad.hh"
#ifndef NO_DIAGRAM
#include <utility>
#include <map>
#include <vector>
#endif
using namespace std;
/** @class Procesador
    @brief Representa un procesador el cual forma el clúster y tiene procesos en ejecución guardados en memoria
*/
class Procesador {

private:
    pair <string, int> id_mem; //id + mem_max
    map <int, Proceso> mjob;
    map <int, pair<int, int> > mmem; //key = index, value = pair; first = space; second = id
    int mem;  //mem <= mem_max
    void search_mem_stack(int memo, int& ind);
    

public:
    //Constructoras

    /** @brief Creadora por defecto.

      Se ejecuta automáticamente al declarar un procesador.
      \pre <em>cierto</em>
      \post El resultado es un procesador de memoria y memoria máxima 0, sin id y un vector vacío de procesos
    */
    Procesador();

    Procesador(string s, int m);
    //Modificadoras

    /** @brief Añade un proceso al procesador 
     
        \pre El p.i. (P) está inicializado, la memoria de p es menor o igual a la memoria actual de P
        \post El p.i. contiene sus procesos originales más p 
    */
    void add_job(Proceso p);

    /** @brief Elimina un proceso del procesador 
     
        \pre Existe un proceso en el p.i. con ID = id
        \post El p.i. contiene sus procesos originales menos el proceso con ID = id 
    */
    void eliminar_job(int id);

    /** @brief Compacta la memoria del procesador 
     
        \pre <em>cierto</em>
        \post El p.i. contiene los procesos originales desplazados al inicio de la memoria
    */
    void compactar_mem();

    //Consultoras

    string consultar_ID() const;

    /** @brief Consultora de la memoria consecutiva más grande
     
      \pre <em>cierto</em>
      \post El resultado es la memoria consecutiva más grande del p.i.
    */
    int consultar_MEM_contigua() const;

    /** @brief Consultora de la existencia de un proceso
     
      \pre El p.i. esta inicializado
      \post El resultado indicia si existe un proceso en el p.i. con ID = id
    */
    bool existe_job(int id) const;

    /** @brief Consultora si el procesador esta activo
     
      \pre <em>cierto</em>
      \post El resultado indica si el procesador contiene almenos un proceso en ejecución
    */
    bool en_curso() const;

    //Lectura y escritura

    /** @brief Operación de lectura

      \pre Hay preparados en el canal standard de entrada los datos de un procesador
      \post El parámetro ímplicito pasa a tener los atributos leídos del canal standard de entrada 
    */
    void leer(); 

    /** @brief Operación de escritura

      \pre <em>cierto</em>
      \post Se han escrito los atributos del parámetro implícito en el canal
      standard de salida. 
    */
    void escribir() const;
};
#endif