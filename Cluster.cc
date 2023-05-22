/** @file Cluster.cc
    @brief Código de la clase Cluster
*/

#include "Cluster.hh"
using namespace std;

Cluster::Cluster() {

}

bool Cluster::recibir_job(const Proceso& p) {   
    map<string, Procesador>::iterator it = mprc.end();
    bfs(it, Tprc, p.consultar_MEM(), p.consultar_ID());
    if (it == mprc.end()) return false;        //el proceso no cabia en ningun procesador
    it->second.add_job(p);
    return true;
}

void Cluster::bfs(map<string, Procesador>::iterator& it,const BinTree<string>& tree, int memo, int id) {
    queue<BinTree<string> > q;
    q.push(tree);       
    int hollow = -1;
    while (not q.empty()) {
        BinTree<string> plant (q.front());          //planta el árbol del frente de la cola
        map <string, Procesador>::iterator itm = mprc.find(plant.value());  //iterador que apunta al procesador con el id del primer nodo del árbol plantado
        int hueco;
        if (not itm->second.existe_job(id) and itm->second.hueco(memo, hueco)) {    //el id del proceso no existe en el procesador y cabe 
            if (it == mprc.end() or hueco < hollow) {   //el hueco del procesador actual esta más ajustado que el del procesador con hueco más ajustado (anteriormente) 
                it = itm;
                hollow = hueco;
            }
            else if (hueco == hollow and itm->second.MEM_libre() > it->second.MEM_libre()) it = itm;   //escoje el procesador con más memoria libre 
        }
        if (not plant.left().empty()) q.push(plant.left()); //si el subárbol izquierdo no esta vacio añadelo a la cola (preorden)
        if (not plant.right().empty()) q.push(plant.right());   //después el derecho
        q.pop();    //el primer nodo del árbol ya ha sido visitado por lo tanto se borra de la cola
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

void Cluster::compactar_prc(const string& id) {
    map<string,Procesador>::iterator it = mprc.find(id);
    if (it == mprc.end()) cout << "error: no existe procesador" << endl;
    else it->second.compactar_mem();
}

map<string, Procesador> Cluster::blend() const {
    return mprc;
}

void Cluster::añadir_cluster(Cluster& c, const string& id) { 
    map <string, Procesador>::iterator it = mprc.find(id);
    if (it == mprc.end()) cout << "error: no existe procesador" << endl;
    else {
        if (it->second.en_curso()) cout << "error: procesador con procesos" << endl;
        else if (modif_tree(id, Tprc, c)) {
            mprc.erase(it);
            map<string,Procesador> mix = c.blend();        //mix tiene el map del cluster auxiliar
            mprc.insert(mix.begin(), mix.end());           //unimos (blend) el map principal con el auxiliar
        }
    }
}

BinTree<string> Cluster::seed() const {
    return Tprc;
}

bool Cluster::modif_tree(const string& id, BinTree<string>& a, Cluster& c) {
    if (a.empty()) return false; 
    BinTree<string> l = a.left();
    BinTree<string> r = a.right();
    if (a.value() == id) {              //procesador con ID = id encontrado
        if (l.empty() and r.empty()) {  //no tiene hijos
            a = c.seed();               //planta el nuevo subárbol 
            return true; 
        } 
        else {
            cout << "error: procesador con auxiliares" << endl;
            return false; 
        }
    } 
    else {
        bool b = modif_tree(id, l, c);          //primero mirar en el subárbol izquierdo
        if (not b) b = modif_tree(id, r, c);   
        a = BinTree<string> (a.value(), l, r);
        return b;
    }
}

void Cluster::leer_arbol(BinTree<string>& a, map <string, Procesador>& mpr) {       //añadir nuevos parametros 
    BinTree<string> l, r;
    string s;
    cin >> s;
    if (s != "*") {
        int m;
        cin >> m;
        Procesador prc(s, m);           //constructora con parametros
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
        cout << it->first << endl;
        escribir_prc("*", it);
    }
}

 void Cluster::escribir_prc(const string& id, map<string,Procesador>::const_iterator& it) const { 
    if (id != "*") {        
        it = mprc.find(id);
        if (it == mprc.end()) cout << "error: no existe procesador" << endl;
        else if (it->second.en_curso()) it->second.escribir();  //si el procesador tiene procesos ejecutandose escribe sus atributos
    }
    else if (it->second.en_curso()) it->second.escribir(); 
 }