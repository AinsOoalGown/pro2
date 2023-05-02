/** @file Prioridad.cc
    @brief Código de la clase Prioridad
*/

#include "Prioridad.hh"

Prioridad::Prioridad() {
    proc_env = proc_rechazados = 0;
}

Prioridad::Prioridad(const string& id_pri) {
    id_prior = id_pri;
    proc_env = proc_rechazados = 0;
}

void Prioridad::add_job(const Proceso& p) {
    antique.push(p.consultar_ID());
    mjob.insert(make_pair(p.consultar_ID(),p));
}

Proceso Prioridad::consultar_job_mas_antiguo() const { //posible inutilidad
    Proceso p;
    return p;
}

bool Prioridad::existe_job(int id) const {
    return (mjob.size() != 0 and mjob.find(id) != mjob.end());
    
}

bool Prioridad::en_espera() const {
    return (mjob.size() != 0);
}

void Prioridad::escribir_job() const {
    queue<int> c = antique;
    while (not c.empty()) {
        mjob.at(c.front()).escribir();
        c.pop();
    }
}


void Prioridad::escribir_env_rech() const {
    cout << proc_env << ' ' << proc_rechazados << endl;
}
