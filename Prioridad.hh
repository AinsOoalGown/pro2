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
    /** @brief Cadena de caracteres que identifica a la prioridad */
    string id_prior;

    /** @brief Cola de enteros correspondientes a los id de los procesos
     
      Ordenada por orden de antigüedad de entrada de los procesos*/
    queue <int> antique;

    /** @brief Numero de procesos enviados (aceptados) al cluster */
    int proc_env;

    /** @brief Numero de procesos enviados (rechazados) al cluster */
    int proc_rechazados;

    /** @brief Mapa de procesos ordenado crecientemente por su id */
    map <int, Proceso> mjob; //Vector de procesos pendientes (puede estar vacio) 

public:
    //Constructoras 

    /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar una prioridad.
      \pre <em>cierto</em>
      \post El resultado es una prioridad con un conjunto de procesos vacío 
      y id_prior -1;
      \coste Constante
  */
    Prioridad();

    /** @brief Creadora con valores concretos.

      Se ejecuta automáticamente al declarar una prioridad.
      \pre <em>cierto</em>
      \post El resultado es una prioridad con ID = id_prior, 
      un conjunto de procesos vacío y los atributos de tipo entero a 0.
      \coste Constante
  */
    Prioridad(const string& id_pri);

    //Modificadoras

    /** @brief Añade un proceso a la prioridad
     
      \pre <em>cierto</em>
      \post El resultado es el p.i. más un proceso p
      \coste Logarítmico
  */
    void add_job(const Proceso& p);

    //Consultoras

    /** @brief Consultora del proceso más antiguo

       \pre El parámetro implícito contiene almenos un proceso 
       \post El resultado es el proceso del p.i. con mayor tiempo en el area de espera 
       \coste *No implementado*
  */
    Proceso consultar_job_mas_antiguo() const; 
    
     /** @brief Consultora de la existencia de un proceso con una prioridad

       \pre El parámetro implícito está inicializado
       \post El resultado indica si el proceso con ID = id existe en el p.i.
       \coste Logarítmico
  */
    bool existe_job(int id) const;

    /** @brief Consulta si esta prioridad tiene procesos pendientes
     
      \pre <em>cierto</em>
      \post El resultado indica si la prioridad tiene procesos pendientes
      \coste Constante
    */
    bool en_espera() const;

    //Lectura y escritura

    /** @brief Operación de escritura de todos los procesos <em>PENDIENTES</em>

      \pre Existe una almenos un proceso pendiente
      \post Se ha escrito todos los procesos pendientes por orden decreciente 
            de antigüedad en el canal standard de salida.
      \coste Lineal (copia de la cola + bucle para todos los elementos de la cola) 
    */
    void escribir_job() const;

    /** @brief Operación de escritura de el numero de procesos aceptados y rechazados en/por el cluster

       \pre <em>cierto</em>
       \post Se ha escrito el número de procesos enviados (aceptados) 
       y el número de rechazos (el total de todos los procesos) al clúster desde el área de
        espera en el canal standard de salida. 
       \coste Constante
    */
    void escribir_env_rech() const;
};
#endif