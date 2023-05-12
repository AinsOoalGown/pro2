/** @file Prioridad.cc
    @brief Código de la clase Prioridad
*/

#include "Prioridad.hh"

Prioridad::Prioridad() {
    env.first = env.second = 0;
}

void Prioridad::add_job(const Proceso& p) {
    antique.insert(antique.end(), p);
    mjob.insert(make_pair(p.consultar_ID(),p));
}

void Prioridad::enviar_proceso(int& n, Cluster &c) {        //funciona
    if (not antique.empty()) {
        list<Proceso>::iterator it = antique.begin();
        int size = antique.size();
        int i = 0;
        while (n > 0 and i < size) {
            if (c.recibir_job(*it)) {
                ++env.first;
                --n;
                it = antique.erase(it);
                mjob.erase((*it).consultar_ID());
            }
            else {
                antique.insert(antique.end(), (*it));
                it = antique.erase(it);
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
    list<Proceso>::const_iterator it = antique.begin();
    while (it != antique.end()) { 
        (*it).escribir();
        ++it;
    }
}


void Prioridad::escribir_env_rech() const {
    cout << env.first << ' ' << env.second << endl;
}
