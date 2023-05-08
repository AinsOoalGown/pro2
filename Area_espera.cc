/** @file Area_espera.cc
    @brief Código de la clase Area_espera
*/

#include "Area_espera.hh"
using namespace std;

Area_espera::Area_espera() {

}

void Area_espera::add_job(const Proceso& p, const string& id_prior) {
    map <string, Prioridad>::iterator it = mprior.find(id_prior);
    if (it == mprior.end()) cout << "error: no existe prioridad" << endl;
    else {
        if (it->second.existe_job(p.consultar_ID())) cout << "error: ya existe proceso" << endl;
        else it->second.add_job(p);
    }
    
}

void Area_espera::add_prior(const string& id_prior) {
    if (mprior.find(id_prior) == mprior.end()) {
        Prioridad p;
        mprior.insert(make_pair(id_prior, p));
    }
    else cout << "error: ya existe prioridad" << endl;
}

void Area_espera::eliminar_prior(const string& id_prior) {
    map<string,Prioridad>::iterator it = mprior.find(id_prior);
    if (it == mprior.end()) cout << "error: no existe prioridad" << endl;
    else {
        if (it->second.en_espera()) cout << "error: prioridad con procesos" << endl;
        else mprior.erase(it);
    }
    
}

void Area_espera::enviar_job_a_cluster() {  //no se usa
    mprior["proc12"].escribir_job();
}

bool Area_espera::pendiente_global() const {  //no se usa
    return false;
}

void Area_espera::leer() {
    int n;
    string s;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        Prioridad pri;
        mprior.insert(make_pair(s, pri));
    }
}

void Area_espera::escribir() const {
    for (map <string, Prioridad>::const_iterator it = mprior.begin(); it != mprior.end(); ++it) {
        cout << it->first << endl;    
        escribir_prior("*", it);
    }

}

void Area_espera::escribir_prior(const string& id_prior, map <string, Prioridad>::const_iterator& it) const {
    if (id_prior != "*") {
        it = mprior.find(id_prior);
        if (it == mprior.end()) cout << "error: no existe prioridad" << endl;
        else {
            if (it->second.en_espera()) it->second.escribir_job(); 
            it->second.escribir_env_rech();
        }
    }
    else {
        if (it->second.en_espera()) it->second.escribir_job(); 
        it->second.escribir_env_rech();
    }
}
