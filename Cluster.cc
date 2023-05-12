/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"
using namespace std;

Cluster::Cluster() {

}

bool Cluster::recibir_job(const Proceso& p) {   
    int mem = p.consultar_MEM();
    int id = p.consultar_ID();
    map<string, Procesador>::iterator it = mprc.begin();
    int tight = it->second.hueco(mem);
    int free_mem = it->second.MEM_libre();
    pair<int,int> pr = it->second.height_left();
    map<string, Procesador>::iterator it2 = it;
    ++it;
    while (it != mprc.end()) {
        int hueco = it->second.hueco(mem);
        int fmem = it->second.MEM_libre();
        pair<int,int> pr2 = it->second.height_left();
        if ((tight == -1 or (tight > hueco and hueco != -1)) and not it->second.existe_job(id)) {
            tight = hueco;
            free_mem = fmem;
            pr = pr2;
            it2 = it;
        }
        else if (tight == hueco) {
            if (fmem > free_mem) {
                free_mem = fmem;
                pr = pr2;
                it2 = it;
            }
            else if (fmem == free_mem) {
                if (pr.first > pr2.first) {
                    pr = pr2;
                    it2 = it;
                }
                else if (pr.first == pr2.first) {
                    if (pr.second < pr2.second) {
                        pr.second = pr2.second;
                        it2 = it;
                    }
                }
            }

        }
        ++it;
    }
    if (tight == -1) return false;
    else {
        it2->second.add_job(p);
        return true;
    }
}

void Cluster::add_job_prc(const string& idprc, Proceso& p) {
    map<string, Procesador>::iterator it = mprc.find(idprc);
    if (it == mprc.end()) cout << "error: no existe procesador" << endl;
    else {
        if (it->second.existe_job(p.consultar_ID())) cout << "error: ya existe proceso" << endl;
        else it->second.add_job(p);
    }
}

void Cluster::eliminar_job_prc(const string& idprc, int idjob) {
   map<string, Procesador>::iterator it = mprc.find(idprc);
   if (it == mprc.end()) cout << "error: no existe procesador" << endl;
   else {
        map <int,Proceso>::iterator it1;
        it->second.eliminar_job(idjob, it1);
   }
}

void Cluster::avanzar_tiempo_prc(int t) {
    map <string, Procesador>::iterator it;
    for (it = mprc.begin(); it != mprc.end(); ++it) {
        it->second.avanzar_tiempo(t);
    }
}

void Cluster::compactar() { 
    map<string,Procesador>::iterator it = mprc.begin();
    while (it != mprc.end()) {
        it->second.compactar_mem();
        ++it;
    }
}

map<string, Procesador> Cluster::bundle() const {
    return mprc;
}

void Cluster::añadir_cluster(Cluster& c, const string& id) { 
    map <string, Procesador>::iterator it = mprc.find(id);
    if (it == mprc.end()) cout << "error: no existe procesador" << endl;
    else {
        if (it->second.en_curso()) cout << "error: procesador con procesos" << endl;
        else if (modif_tree(id, Tprc, c)) {
            pair<int,int> pr = it->second.height_left();
            c.update_tree(pr.first, pr.second, c.seed());      //nuevas posiciones de altura y grado de izquierda
            mprc.erase(it);
            map<string,Procesador> mix = c.bundle();
            mprc.insert(mix.begin(), mix.end());
        }
    }
}

void Cluster::update_tree(int alt, int izq, const BinTree<string>& a) {
    BinTree<string> l, r;
    if (a.empty()) return;
    else {
        mprc[a.value()].añadir_alt_izq(alt, izq);
        l = a.left();
        r = a.right();
        update_tree(alt + 1, izq + 1, l);
        update_tree(alt + 1, izq - 1, r);
    }
}

BinTree<string> Cluster::seed() const {
    return Tprc;
}

bool Cluster::modif_tree(const string& id, BinTree<string>& a, Cluster& c) {
    if (a.empty()) return false; 
    BinTree<string> l = a.left();
    BinTree<string> r = a.right();
    if (a.value() == id) {
        if (l.empty() and r.empty()) {
            a = c.seed();
            return true; 
        } 
        else {
            cout << "error: procesador con auxiliares" << endl;
            return false; 
        }
    } 
    else {
        bool b = modif_tree(id, l, c);
        if (not b) b = modif_tree(id, r, c);
        a = BinTree<string> (a.value(), l, r);
        return b;
    }
}


void Cluster::leer_arbol(BinTree<string>& a, map <string, Procesador>& mpr, int alt, int izq) {       //añadir nuevos parametros 
    BinTree<string> l, r;
    string s;
    cin >> s;
    if (s != "*") {
        int m;
        cin >> m;
        Procesador prc(s, m, alt, izq);           //añadir nuevos valores para los nuevos atributos
        mpr.insert(make_pair(s, prc));
        leer_arbol(l, mpr, alt + 1, izq + 1);
        leer_arbol(r, mpr, alt + 1, izq - 1);      
        a = BinTree<string>(s, l, r);
    }
    else a = BinTree<string>();
    
}

void Cluster::leer() {
 mprc.clear();
 int alt = 0;
 int izq = 0;
 leer_arbol(Tprc, mprc, alt, izq);
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
        cout << it->first << endl;
        escribir_prc("*", it);
    }
}

 void Cluster::escribir_prc(const string& id, map<string,Procesador>::const_iterator& it) const { 
    if (id != "*") { 
        it = mprc.find(id);
        if (it == mprc.end()) cout << "error: no existe procesador" << endl;
        else if (it->second.en_curso()) it->second.escribir();
    }
    else if (it->second.en_curso()) it->second.escribir();
 }