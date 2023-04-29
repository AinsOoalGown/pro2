/** @file Area_espera.cc
    @brief Código de la clase Area_espera
*/

#include "Area_espera.hh"
using namespace std;

Area_espera::Area_espera() {

}

void Area_espera::add_job(Proceso p, string id_prior) {
    mprior[id_prior].add_job(p);
}

void Area_espera::add_prior(string id_prior) {
    Prioridad p (id_prior);
    mprior.insert(make_pair(id_prior, p));
}

void Area_espera::eliminar_prior(string id_prior) {
    mprior.erase(id_prior);
}

void Area_espera::enviar_job_a_cluster() {  //no se usa
    mprior["proc12"].escribir_job();
}

bool Area_espera::pendiente_global() const {  //no se usa
    return false;
}

bool Area_espera::id_prior_pendiente (string id_prior) const {
    return mprior.at(id_prior).en_espera();
}

bool Area_espera::existe_prior(string id_prior) const {
    return (mprior.find(id_prior) != mprior.end());
}

bool Area_espera::existe_prior_job(string id_prior, int id) const {
   return mprior.at(id_prior).existe_job(id);
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
        cout << (*it).first << endl;    
        escribir_prior((*it).first);
    }

}

void Area_espera::escribir_prior(string id_prior) const {
    Prioridad p = mprior.at(id_prior);
    if (p.en_espera()) p.escribir_job(); 
    p.escribir_env_rech();
}
