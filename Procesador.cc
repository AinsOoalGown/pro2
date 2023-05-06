/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador() {
    id_mem.second = 0;
    mmem.insert(make_pair(id_mem.second, set<int>{0}));
    
}

Procesador::Procesador(const string& s, int m) {
    id_mem.first = s;
    id_mem.second = m;
    mmem.insert(make_pair(id_mem.second, set<int>{0}));
}

void Procesador::update_mem (const Proceso& p, map <int, set<int>>& mem, map<int, Proceso>& mp) { 
    pair <int,int> pr = p.consultar_hollow();
    map<int, Proceso>::iterator it = mp.find(p.consultar_ind());
    //gestion del espacio vacio del PROCESO ANTERIOR a este proceso
    if (it != mp.begin()) {   //hay un proceso anterior a este
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
    //gestion del mapa de memoria por huecos vacios
    //1.Crear hueco nuevo o añadir nuevo índice al hueco con mismo tamaño 
    mem[p.consultar_MEM() + pr.first + pr.second].insert(p.consultar_ind() - pr.first);

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
    if (id != -1) it = mpos.find(mjob[id]);
    update_mem(it->second, mmem, mpos);
    mjob.erase(it->second.consultar_ID());
    it = mpos.erase(it);
}

void Procesador::avanzar_tiempo(int t) {
    if (not mjob.empty()) {
        map <int, Proceso>::iterator it = mpos.begin();
        while (it != mpos.end()) {
            if (it->second.consultar_tiempo() <= t) eliminar_job(-1, it);  
            else {
                it->second.restar_tiempo(t);         
                ++it;
            }
        }
    }   
}

void Procesador::add_job(Proceso& p) { 
    int memo = p.consultar_MEM();
    map <int,set<int>>::iterator it1 = mmem.lower_bound(memo); //hueco igual o mayor a la memoria del proceso
    if (it1 == mmem.end()) cout << "error: no cabe proceso" << endl; 
    else {
        set<int>::const_iterator it2 = it1->second.begin(); //indice más pequeño con hueco más ajustado 
        p.add_indice(*it2);
        int hueco = it1->first - memo; //hueco = hueco anterior - memoria del proceso p.e: h.an. = 4, m = 2 -> h.ac. = 2
        if (hueco > 0) mmem[hueco].insert(*it2 + memo);     
        p.add_hollow(0, hueco);  
        mpos.insert(make_pair(*it2, p));
        mjob.insert(make_pair(p.consultar_ID(), *it2));
        int ind = *it2;
        //Actualizar mapa de memoria
        map <int, Proceso>::iterator it = mpos.find(*it2);
        it1->second.erase(*it2); //
        if (it1->second.empty()) it1 = mmem.erase(it1); //
        if (ind != 0) {         //update del hollow2 del proceso "anterior" a este
            --it;
            it->second.mod_hollow2(0);
            ++it;
        }
        ++it;
        if (it != mpos.end()) it->second.mod_hollow1(hueco); //update del hollow1 del proceso "posterior" a este  
    }
}


void Procesador::compactar_mem() {  //no se usa
    cout << mjob[78] << endl;
}

string Procesador::consultar_ID() const {
    return id_mem.first;
}

bool Procesador::existe_job(int id) const {
    return (mjob.find(id) != mjob.end());
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