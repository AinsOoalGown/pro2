/** @file Proceso.hh
    @brief Especificación de la clase Proceso
*/


#ifndef PROCESO_HH
#define PROCESO_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <utility>
#endif
using namespace std;

/** @class Proceso
    @brief Representa un proceso en ejecución o en espera con id, memoria ocupada, tiempo de ejecución y prioridad del propio proceso

*/
class Proceso {

private:
    int id;
    int t_ejec;
    pair <int, int> ind_mem; //first = indice que ocupa en el mem, second = mem que ocupa
    bool en_curso;
public:
    //Constructoras

    /** @brief Creadora por defecto.
     
        Se ejecuta automáticamente al declarar un proceso.
        \pre <em>cierto</em>
        \post El resultado es un proceso con todos los atributos enteros a -1 y la string con "???" 
    */
    Proceso();

    //Modificadoras

    void add_indice (int ind);

    void restar_tiempo(int t);

    //Consultoras

    /** @brief Consultora del id del proceso
        \pre <em>cierto</em>
        \post El resultado el id del parámetro implícito
    */
    int consultar_ID() const;

    /** @brief Consultora de la memoria del proceso
        \pre <em>cierto</em>
        \post El resultado la memoria del parámetro implícito
    */
    int consultar_MEM() const;

    int consultar_ind() const;

    int consultar_tiempo() const;

    //Lectura y escritura

    /** @brief Operación de lectura

      \pre Hay preparados en el canal standard de entrada los datos de un proceso
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