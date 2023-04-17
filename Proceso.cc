#include "Proceso.hh"

Proceso::Proceso() {

}

int Proceso::consultar_ID() const{
    return id;
}

int Proceso::consultar_MEM() const {
    return ind_mem.second;
}

int Proceso::consultar_tiempo() const {
    return t_ejec;
}

void Proceso::leer() {
    cin >> id >> ind_mem.second >> t_ejec;    
}

void Proceso::escribir() const {

}