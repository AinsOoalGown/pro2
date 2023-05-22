/** @file Prioridad.hh
    @brief Especificación de la clase Prioridad
*/

#ifndef PRIORIDAD_HH
#define PRIORIDAD_HH

#include "Proceso.hh"
#include "Cluster.hh"
#ifndef NO_DIAGRAM
#include <list>
#include <map>
#endif

/** @class Prioridad
    @brief Representa la prioridad de un proceso en ejecución o pendiente
*/

class Prioridad
{

private:
  /** @brief Lista de procesos

    Ordenada por orden de antigüedad de entrada de los procesos*/
  list<Proceso> ant;

  /** @brief Numero de procesos enviados (aceptados) y (rechazados) al cluster */
  pair <int, int> env;

  /** @brief Mapa de procesos ordenado crecientemente por su id */
  map<int, Proceso> mjob;

public:
  // Constructoras

  /** @brief Creadora por defecto.

    Se ejecuta automáticamente al declarar una prioridad.
    \pre <em>cierto</em>
    \post El resultado es una prioridad con un conjunto de procesos vacío
    y pair de enviados a 0
    \coste Constante
*/
  Prioridad();

  // Modificadoras

  /** @brief Añade un proceso a la prioridad

    \pre <em>cierto</em>
    \post El resultado es el p.i. más un proceso p
    \coste Logarítmico
*/
  void add_job(const Proceso &p);

  // Consultoras

  /** @brief Intenta enviar una cantidad de procesos de el área de espera al cluster

     \pre n > 0
     \post El p.i. ha intentado enviar n procesos al cluster c, los procesos
     aceptados son borrados de la prioridad, y los rechazados vuelven a la lista
     de la prioridad como nuevos (reinicio de antigüedad)
     \coste Lineal sobre lineal (consultar recibir_job() de la clase cluster)
*/
  void enviar_proceso(int& n, Cluster& c);

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

  // Lectura y escritura

  /** @brief Operación de escritura de todos los procesos pendientes

    \pre Existe almenos un proceso pendiente
    \post Se ha escrito todos los procesos pendientes por orden decreciente
          de antigüedad en el canal standard de salida.
    \coste Lineal (bucle para todos los elementos de la lista)
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