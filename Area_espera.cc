#include "Area_espera.hh"
#include <string>
#include <iostream>
using namespace std;

Area_espera::Area_espera() {

}

void Area_espera::add_job(Proceso p, string id_prior) {

}

void Area_espera::add_prior(string id_prior) {

}

void Area_espera::eliminar_prior(string id_prior) {

}

void Area_espera::enviar_job_a_cluster() {

}

bool Area_espera::pendiente_global() const {
    return false;
}

bool Area_espera::id_prior_pendiente (string id_prior) const {
    return false;
}

bool Area_espera::existe_prior(string id_prior) const {
    return false;
}

bool Area_espera::existe_prior_job(string id_prior, int id) const {
    return false;
}

void Area_espera::leer() {
    int n;
    string s;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        Prioridad pri(s);
        mprior.insert(make_pair(s, pri));
    }
}

void Area_espera::escribir() const {
    for (map <string, Prioridad>::const_iterator it = mprior.begin(); it != mprior.end(); ++it) {
        escribir_prior((*it).first);
    }

}

void Area_espera::escribir_prior(string id_prior) const {
    cout << id_prior;
    Prioridad p = mprior.at(id_prior);
    if (p.en_espera()) p.escribir_job();   
    cout << endl; 
    p.escribir_enviados();
    cout << ' ';
    p.escribir_rechazados();
    cout << endl;
}

void Area_espera::escribir_intentos(string id_prior) const {

}