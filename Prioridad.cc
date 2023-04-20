#include "Prioridad.hh"

Prioridad::Prioridad() {
    pendiente = false;
    proc_env = proc_rechazados = 0;
}

Prioridad::Prioridad(string id_pri) {
    id_prior == id_pri;
    pendiente = false;
    proc_env = proc_rechazados = 0;
}

void Prioridad::add_job(Proceso p) {
    antique.push(p.consultar_ID());
    mjob.insert(make_pair(p.consultar_ID(),p));
    pendiente = true;
}

Proceso Prioridad::consultar_job_mas_antiguo() const {
    Proceso p;
    return p;
}

bool Prioridad::existe_job(int id) const {
    return (pendiente and mjob.find(id) != mjob.end());
    
}

bool Prioridad::en_espera() const {
    return pendiente;
}

void Prioridad::escribir_job() const {
    queue<int> c = antique;
    while (not c.empty()) {
        if (mjob.find(c.front()) != mjob.end()) mjob.at(c.front()).escribir();
        c.pop();
    }

}


void Prioridad::escribir_enviados() const {
    cout << proc_env;
}

void Prioridad::escribir_rechazados() const {
    cout << proc_rechazados;
}