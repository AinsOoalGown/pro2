/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"
using namespace std;

Cluster::Cluster() {

}

void Cluster::add_job_prc(string id, Proceso p, bool& added) {
    mprc[id].add_job(p, added);
}

void Cluster::eliminar_job_prc(string idprc, int idjob) {
    mprc[idprc].eliminar_job(idjob);
}

void Cluster::avanzar_tiempo_prc(int t) {
    map <string, Procesador>::iterator it;
    for (it = mprc.begin(); it != mprc.end(); ++it) {
        (*it).second.avanzar_tiempo(t);
    }
}

void Cluster::añadir_cluster(const Cluster& c, string id) { //no se usa
    c.leer_arbol(Tprc, mprc);
    mprc[id].avanzar_tiempo(7);

}

void Cluster::compactar() { //no se usa
    mprc["proc12"].avanzar_tiempo(7);
}

bool Cluster::existe_prc(string id) const {
    map <string,Procesador>::const_iterator it = mprc.find(id);
    if (it == mprc.end()) return false;
    return true;
}

Procesador Cluster::consultar_prc(string id) const {
    return mprc.at(id);
}

bool Cluster::existe_aux(string id) const { // no se usa
   return mprc.at(id).en_curso();
}

void Cluster::leer_arbol(BinTree<string>& a, map <string, Procesador>& mpr) {
    BinTree<string> l, r;
    string s;
    cin >> s;
    if (s != "*") {
        int m;
        cin >> m;
        Procesador prc(s, m);
        mpr.insert(make_pair(s, prc));
        leer_arbol(l, mpr);
        leer_arbol(r, mpr);
        a = BinTree<string>(s, l, r);
    }
    else a = BinTree<string>();
    
}

void Cluster::leer() {
 mprc.clear();
 leer_arbol(Tprc, mprc);
}

void Cluster::escribir_arbol(const BinTree<string>& a) {
    if (not a.empty()) {
        cout << '(';
        cout << a.value();
        escribir_arbol(a.left());
        escribir_arbol(a.right());
        cout << ')';
    }
    else cout << ' ';
}

void Cluster::escribir_est() const {
    escribir_arbol(Tprc);
    cout << endl;
}

void Cluster::escribir_todos() const {
    for (map <string,Procesador>::const_iterator it = mprc.begin(); it != mprc.end(); ++it) {
        cout << (*it).first << endl;
        escribir_prc((*it).first);
    }
}

 void Cluster::escribir_prc(string id) const { 
    if (mprc.at(id).en_curso()) mprc.at(id).escribir();
 }