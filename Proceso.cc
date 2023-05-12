/** @file Proceso.cc
    @brief Código de la clase Proceso
*/

#include "Proceso.hh"

Proceso::Proceso() {

}

void Proceso::restar_tiempo(int t) {
    t_ejec -= t;
}

int Proceso::consultar_ID() const{
    return id;
}

int Proceso::consultar_MEM() const {
    return mem;
}

int Proceso::consultar_tiempo() const {
    return t_ejec;
}

void Proceso::leer() {
    cin >> id >> mem >> t_ejec;    
}

void Proceso::escribir() const {
    cout << id << ' ' << mem << ' ' << t_ejec << endl;
}