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

}

Proceso Prioridad::consultar_job_mas_antiguo() const {
    Proceso p;
    return p;
}

bool Prioridad::existe_job(int id) {
    return false;
}

bool Prioridad::en_espera() const {
    return pendiente;
}

void Prioridad::escribir_job() const {

}


void Prioridad::escribir_enviados() const {
    cout << proc_env;
}

void Prioridad::escribir_rechazados() const {
    cout << proc_rechazados;
}