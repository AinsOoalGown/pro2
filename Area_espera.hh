/** @file Area_espera.hh
   @brief Especificación de la clase Area_espera
*/


#ifndef Area_espera_HH
#define Area_espera_HH

#include "Proceso.hh"
#include "Cluster.hh"
#include "Prioridad.hh"
#ifndef NO_DIAGRAM
#include <vector>
#include <map>
#endif

/** @class Area_espera
    @brief Representa un área de espera formado por procesos pendientes (en espera de ser ejecutados)
*/

class Area_espera {

private:

    map <string, Prioridad> mprior;

public:
    //Constructoras

    /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un area de espera.
      \pre <em>cierto</em>
      \post El resultado es un conjunto de prioridades vacio.
  */
    Area_espera();

    //Modificadoras

    /** @brief Añade un proceso al área de espera
     
      \pre <em>cierto</em>
      \post El resultado es el p.i. más el proceso p con el ID de proridad = id_prior
  */
    void add_job(Proceso p, string id_prior);

    /** @brief Añade una prioridad al área de espera
     
      \pre <em>cierto</em>
      \post El resultado es el p.i. más la prioridad con id_prior
  */
    void add_prior(string id_prior);

    /** @brief Elimina una prioridad del área de espera
     
        \pre Existe una prioridad en el p.i. con ID de prioridad = id_prior
        \post El p.i. contiene sus prioridades originales menos la prioridad con ID de prioridad = id_prior
    */
    void eliminar_prior(string id_prior);

    /** @brief Envia un proceso del área de espera al clúster 
     
        \pre Existe almenos un proceso pendiente en el p.i.
        \post Envia un proceso pendiente al cluster, si cabe en el cluster se designa un procesador según un orden,
        en caso contrario se vuelve a enviar al área de espera
    */
    void enviar_job_a_cluster(); //envia un proceso pendiente al cluster

    //Consultoras

    /** @brief Consultora del estado global de los procesos

       \pre El parámetro implícito está inicializado
       \post El resultado indica si aun quedan procesos pendientes
  */
    bool pendiente_global() const; //devuelve true si aun quedan procesos pendientes

    /** @brief Consultora del estado de los procesos con un identificador de prioridad

       \pre El parámetro implícito contiene un prioridad con ID = id_prioridad
       \post El resultado indica si aun quedan procesos pendientes con ID de prioridad = id_prior 
  */
    bool id_prior_pendiente (string id_prior) const; //devuelve true si hay algun proceso pendiente con id_prior
    
    /** @brief Consultora de la existencia de una prioridad en el área de espera 

       \pre El parámetro implícito está inicializado
       \post El resultado indica si existe la prioridad con id_prior en el p.i.
  */
    bool existe_prior(string id_prior) const;
    
      /** @brief Consultora de la existencia de un proceso con una prioridad en el área de espera  

        \pre El parámetro implícito está inicializado
        \post El resultado indica si el proceso con ID = id y la prioridad con id_prior existe en el p.i.
    */
    bool existe_prior_job(string id_prior, int id) const;

    //Lectura y escritura

    /** @brief Operación de lectura

      \pre Hay preparados en el canal standard de entrada un número inicial de prioridades N > 0 y el identificador de N prioridades
      \post El parámetro ímplicito pasa a tener los atributos leídos del canal standard de entrada
    */
    void leer();

    /** @brief Operación de escritura de todos los procesos de todas las prioridades

      \pre <em>cierto</em>
      \post Se ha escrito todos los procesos pendientes de todas las prioridades 
       del área de espera por orden creciente de prioridad  en el canal standard de salida. 
    */
    void escribir() const; //utiliza la operación "escribir_proc" para todas la id_prior

    /** @brief Operación de escritura de todos los procesos de una prioridad especifica

      \pre Existe una prioridad con ID = id_prior en el p.i.
      \post Se ha escrito todos los procesos pendientes con la prioridad id_prior   
        por orden decreciente de antigüedad en el canal standard de salida. 
    */
    void escribir_prior(string id_prior) const; //escribe todos los procesos pendeintes con esta id_prior

    /** @brief Operación de escritura de los intentos de envio del área de espera al cluster

       \pre Existe la prioridad con ID DE PRIORIDAD = id_prior en el p.i.
       \post Se ha escrito el número de procesos enviados (aceptados) al clúster desde el área de
        espera y el número de rechazos (el total de todos los procesos) parámetro implícito en el canal standard de salida. 
    */
    void escribir_intentos(string id_prior) const; //escribe num proc con id_prior ENVIADOS al cluster + num de rechazos

};
#endif