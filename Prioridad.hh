/** @file Prioridad.hh
    @brief Especificación de la clase Prioridad
*/

#ifndef PRIORIDAD_HH
#define PRIORIDAD_HH

#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <queue>
#include <map>
#endif 

/** @class Prioridad
    @brief Representa la prioridad de un proceso en ejecución o pendiente 
*/

class Prioridad {

private:
    string id_prior;
    queue <int> antique;
    int proc_env;
    int proc_rechazados;
    map <int, Proceso> mjob; //Vector de procesos pendientes (puede estar vacio)
    bool pendiente;       //true si hay algun proceso pendiente con id_prior, false si esta vacio

public:
    //Constructoras 

    /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar una prioridad.
      \pre <em>cierto</em>
      \post El resultado es una prioridad con un conjunto de procesos vacío y id_prior -1;
  */
    Prioridad();

    /** @brief Creadora con valores concretos.

      Se ejecuta automáticamente al declarar una prioridad.
      \pre <em>cierto</em>
      \post El resultado es una prioridad con ID = id_prior, un conjunto de procesos vacío y los atributos de tipo entero a 0.
  */
    Prioridad(string id_prior);

    //Modificadoras

    /** @brief Añade un proceso a la prioridad
     
      \pre <em>cierto</em>
      \post El resultado es el p.i. más un proceso p
  */
    void add_job(Proceso p);

    //Consultoras

    /** @brief Consultora del proceso más antiguo

       \pre El parámetro implícito contiene almenos un proceso 
       \post El resultado es el proceso del p.i. con mayor tiempo en el area de espera 
  */
    Proceso consultar_job_mas_antiguo() const;
    
     /** @brief Consultora de la existencia de un proceso con una prioridad

       \pre El parámetro implícito está inicializado
       \post El resultado indica si el proceso con ID = id existe en el p.i.
  */
    bool existe_job(int id) const;

    /** @brief Consulta si esta prioridad tiene procesos pendientes
     
      \pre <em>cierto</em>
      \post El resultado indica si la prioridad tiene procesos pendientes
    */
    bool en_espera() const;
    //Lectura y escritura

    /** @brief Operación de escritura de todos los procesos <em>PENDIENTES</em>

      \pre Existe una almenos un proceso pendiente
      \post Se ha escrito todos los procesos pendientes por orden decreciente 
            de antigüedad en el canal standard de salida. 
    */
    void escribir_job() const;

    /** @brief Operación de escritura de el numero de procesos enviados (correctamente) al clúster

       \pre <em>cierto</em>
       \post Se ha escrito el número de procesos enviados (aceptados) al clúster desde el área de
        espera en el canal standard de salida. 
    */
    void escribir_enviados() const;

    /** @brief Operación de escritura de el numero de rechazos de el envio del área de espera al cluster

       \pre <em>cierto</em>
       \post Se ha escrito el número de rechazos (el total de todos los procesos) en el canal standard de salida. 
    */
    void escribir_rechazados() const;


};
#endif