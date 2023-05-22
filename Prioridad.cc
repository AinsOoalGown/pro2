/** @file Prioridad.cc
    @brief Código de la clase Prioridad
*/

#include "Prioridad.hh"

Prioridad::Prioridad() {
    env.first = env.second = 0;
}

void Prioridad::add_job(const Proceso& p) {
    ant.insert(ant.end(), p);
    mjob.insert(make_pair(p.consultar_ID(),p));
}

void Prioridad::enviar_proceso(int& n, Cluster& c) {    
    if (not ant.empty()) {      //a de haber almenos un proceso en la prioridad
        list<Proceso>::iterator it = ant.begin();
        int size = ant.size();      //cota del bucle
        int i = 0;
        while (n > 0 and i < size) {
            if (c.recibir_job(*it)) {   //el proceso enviado cabe en almenos un procesador
                ++env.first;
                --n;
                mjob.erase((*it).consultar_ID());   //el proceso aceptado ya no debe estar en el area de espera
                it = ant.erase(it);
            }
            else {                              //el proceso ha sido rechazado 
                ant.insert(ant.end(), (*it));   //se devuelve al final de la lista (ahora es el más antiguo)
                it = ant.erase(it);             //lo eliminamos del inicio de la lista y avanzamos al siguiente proceso a enviar 
                ++env.second;   
            }
            ++i;
        }
    }
}

bool Prioridad::existe_job(int id) const {
    return (mjob.size() != 0 and mjob.find(id) != mjob.end());
    
}

bool Prioridad::en_espera() const {
    return (mjob.size() != 0);
}

void Prioridad::escribir_job() const {
    list<Proceso>::const_iterator it = ant.begin();
    while (it != ant.end()) { 
        (*it).escribir();
        ++it;
    }
}

void Prioridad::escribir_env_rech() const {
    cout << env.first << ' ' << env.second << endl; 
}
