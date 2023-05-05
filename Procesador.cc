/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador() {
    id_mem.second = 0;
}

Procesador::Procesador(const string& s, int m) {
    id_mem.first = s;
    id_mem.second = m;
}

void Procesador::update_mem (const Proceso& p, map <int, set<int>>& mem, map<int, Proceso>& mp) {   //hay minimo 2 procesos
    pair <int,int> pr = p.consultar_hollow();
    map<int, Proceso>::iterator it = mp.find(p.consultar_ind());
    //gestion del espacio vacio del PROCESO ANTERIOR a este proceso
    if (pr.first != p.consultar_ind()) {   //hay un proceso anterior a este
        --it;
        pair<int,int> pr2 = it->second.consultar_hollow();
        it->second.mod_hollow2(pr2.second + p.consultar_MEM() + pr.second);
        ++it;
    }
    //gestion del espacio vacio del PROCESO POSTERIOR a este proceso
    ++it;
    if (it != mp.end()) {   //hay un proceso posterior a este
        pair<int,int> pr2 = it->second.consultar_hollow();
        it->second.mod_hollow1(pr2.first + p.consultar_MEM() + pr.first);
    }
    //gestion del mapa del memoria por huecos vacios
    //1.Crear hueco nuevo o añadir nuevo índice al hueco con mismo tamaño 
    map<int,set<int>>::iterator it2 = mem.find(p.consultar_MEM() + pr.first + pr.second);
    if (it2 == mem.end()) {     //no existe ese hueco
        set<int> s;
        s.insert(p.consultar_ind() - pr.first);
        mem.insert(make_pair(p.consultar_MEM() + pr.first + pr.second, s));
    }
    else {  //existe el mismo hueco
        mem[p.consultar_MEM() + pr.first + pr.second].insert(p.consultar_ind() - pr.first);     //añadimos nuevo indice al set
    }
    //2. Eliminar hueco derecho del proceso p 
    if (pr.second != 0)  {
        mem[pr.second].erase(p.consultar_ind() + p.consultar_MEM());
        if (mem[pr.second].empty()) mem.erase(pr.second);
    }
    //3. Eliminar hueco izquierdo del proceso p
    if (pr.first != 0) {
        mem[pr.first].erase(p.consultar_ind() - pr.first);
        if (mem[pr.first].empty()) mem.erase(pr.first);
    }
       
}

void Procesador::eliminar_job(int id, map <int,Proceso>::iterator& it) {
    if (id != -1) it = mjob.find(id);
    if (mjob.size() == 1) mmem.clear();     //solo quedaba 1 proceso 
    else update_mem(it->second, mmem, mpos); //habian mínimo 2 procesos
    mpos.erase(it->second.consultar_ind());
    it = mjob.erase(it);
}

void Procesador::add_job(Proceso& p, bool& added) { 
    int memo = p.consultar_MEM();   //memo = 3
    if (not mjob.empty()) {
        map <int,set<int>>::iterator it1 = mmem.lower_bound(memo); //hueco igual o mayor a la memoria del proceso
        if (it1 == mmem.end()) added = false;
        else {
            added = true;
            set<int>::const_iterator it2 = it1->second.begin(); //indice más pequeño con hueco más ajustado
            p.add_indice(*it2);
            int hueco = it1->first - memo; //hueco = hueco anterior - memoria del proceso p.e: h.an. = 4, m = 2 -> h.ac. = 2
            if (hueco > 0) {
                it1 = mmem.find(hueco);
                if (it1 == mmem.end()) {
                    set<int> s;
                    s.insert(*it2 + memo);      //ind del proceso + mem del proceso = ind del sig hueco
                    mmem.insert(make_pair(hueco, s));
                }
                else it1->second.insert(*it2 + memo);   //ind del proceso + mem del proceso = ind del sig hueco  
                p.add_hollow(0, hueco);
            }
            else p.add_hollow(0, 0);   //no se tiene que crear llave de mmem para hueco
            pair <map <int,Proceso>::iterator,bool> pair_it = mpos.insert(make_pair(*it2, p)); 
            map <int,Proceso>::iterator it = pair_it.first;
            mjob.insert(make_pair(p.consultar_ID(), p));
            int ind = *it2;
            it1->second.erase(*it2);
            if (it1->second.empty()) it1 = mmem.erase(it1);
            if (ind != 0) {         //update del hollow2 del proceso "anterior" a este
                --it;
                it->second.mod_hollow2(0);
                ++it;
            }
            ++it;
            if (it != mpos.end()) it->second.mod_hollow1(hueco); //update del hollow1 del proceso "posterior" a este  
        }
    }
    else if (id_mem.second >= p.consultar_MEM()){       //max mem >= mem del proceso
        added = true;
        p.add_indice(0);
        p.add_hollow(0, id_mem.second - memo);
        mpos.insert(make_pair(0, p));
        mjob.insert(make_pair(p.consultar_ID(), p));
        set<int> s;
        s.insert(memo);
        mmem.insert(make_pair(id_mem.second - memo, s));    //hueco = mem max - mem del proceso
    }
    else added = false;
}

void Procesador::compactar_mem() {  //no se usa
    mjob[78].escribir();
}

void Procesador::avanzar_tiempo(int t) {
    if (not mjob.empty()) {
        map <int, Proceso>::iterator it = mjob.begin();
        while (it != mjob.end()) {
            if (it->second.consultar_tiempo() <= t) eliminar_job(-1, it);  
            else {
                it->second.restar_tiempo(t);          
                ++it;
            }
        }
    }
}

string Procesador::consultar_ID() const {
    return id_mem.first;
}

bool Procesador::existe_job(int id) const {
    map <int, Proceso>::const_iterator it = mjob.find(id); 
    if (it == mjob.end()) return false;
    return true;
}

bool Procesador::en_curso() const {
    return not mjob.empty();
}

void Procesador::leer() {   //no se usa
    cin >> id_mem.first;
}

void Procesador::escribir() const {
    map <int, Proceso>::const_iterator it;
    for (it = mpos.begin(); it != mpos.end(); ++it) {
        cout << it->first << ' ';
        it->second.escribir();
    }
}