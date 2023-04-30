/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

Proceso::Proceso() {

}

void Proceso::add_indice (int ind) {
    ind_mem.first = ind;
}

void Proceso::restar_tiempo(int t) {
    t_ejec -= t;
}

int Proceso::consultar_ID() const{
    return id;
}

int Proceso::consultar_MEM() const {
    return ind_mem.second;
}

int Proceso::consultar_ind() const {
    return ind_mem.first;
}

int Proceso::consultar_tiempo() const {
    return t_ejec;
}

void Proceso::leer() {
    cin >> id >> ind_mem.second >> t_ejec;    
}

void Proceso::escribir() const {
    cout << id << ' ' << ind_mem.second << ' ' << t_ejec << endl;
}