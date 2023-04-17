#include "Cluster.hh"
#include <utility>
#include <iostream>
using namespace std;

Cluster::Cluster() {

}

void Cluster::add_job_prc(string id, Proceso p) {
    mprc[id].add_job(p);
}

void Cluster::avanzar_tiempo(int t) {

}

void Cluster::añadir_cluster(const Cluster& c, string id) {

}

void Cluster::compactar() {

}

bool Cluster::existe_prc(string id) const {
    map <string,Procesador>::const_iterator it = mprc.find(id);
    if (it == mprc.end()) return false;
    return true;
}

Procesador Cluster::consultar_prc(string id) const {
    return mprc.at(id);
}

bool Cluster::existe_aux(string id) const {
    return false;
}

void Cluster::leer_arbol(BinTree<string>& a) {
    BinTree<string> l, r;
    string s;
    cin >> s;
    if (s != "*") {
        int m;
        cin >> m;
        Procesador prc(s, m);
        mprc.insert(make_pair(s, prc));
        leer_arbol(l);
        leer_arbol(r);
        a = BinTree<string>(s, l, r);
    }
    else a = BinTree<string>();
    
}

void Cluster::leer() {
 leer_arbol(Tprc);
}

void Cluster::escribir_arbol(const BinTree<string>& a) const {
    if (not a.empty()) {
        cout << '(';
        cout << a.value();
        escribir_arbol(a.left());
        escribir_arbol(a.right());
    }
    else cout << ')';
}

void Cluster::escribir_est() const {
    escribir_arbol(Tprc);
    cout << ')' << endl;
}

void Cluster::escribir_todos() const {
    for (map <string,Procesador>::const_iterator it = mprc.begin(); it != mprc.end(); ++it) {
        cout << (*it).first << endl;
        escribir_prc((*it).first);
    }
}

 void Cluster::escribir_prc(string id) const { 
    if (mprc.at(id).en_curso()) {
        mprc.at(id).escribir();
    }
 }