/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador() {
    
}

Procesador::Procesador(const string& s, int m) {
    id_mem.first = s;
    id_mem.second = m;
    mmem[id_mem.second].insert(0);
}

void Procesador::eliminar_job(int id, map <int,Proceso>::iterator& it) {
    if (id != -1) it = mpos.find(mjob[id]);
    mjob.erase(it->second.consultar_ID());
    if (mjob.empty()) {     //solo habia 1 proceso
        mmem.clear();
        mmem[id_mem.second].insert(0);
    }
    else {  //habia mas de 1 proceso
        int ind = it->first;
        int mem = it->second.consultar_MEM() + ind;
        int ind_ant;
        int ind_sig;
        if (it != mpos.begin()) {
            --it;
            ind_ant = it->first + it->second.consultar_MEM();
            if (ind != ind_ant) {
                mmem[ind - ind_ant].erase(ind_ant);         
                if (mmem[ind - ind_ant].empty()) mmem.erase(ind - ind_ant);
            }
            ++it;
        }
        else {
            ind_ant = 0;
            if (ind != 0) {
                mmem[ind].erase(0);
                if (mmem[ind].empty()) mmem.erase(ind);   
            }
        }
        ++it;
        if (it != mpos.end()) {
            ind_sig = it->first;
            if (ind_sig != mem) {
                mmem[ind_sig - mem].erase(mem);
                if (mmem[ind_sig - mem].empty()) mmem.erase(ind_sig - mem);
            }
        }
        else ind_sig = id_mem.second;            
        --it;
        mmem[ind_sig - ind_ant].insert(ind_ant);

    }
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

void Procesador::add_job(const Proceso& p) { 
    int memo = p.consultar_MEM();
    map <int,set<int>>::iterator it1 = mmem.lower_bound(memo); //hueco igual o mayor a la memoria del proceso
    if (it1 == mmem.end()) cout << "error: no cabe proceso" << endl; 
    else {
        set<int>::const_iterator it2 = it1->second.begin(); //indice más pequeño con hueco más ajustado 
        int hueco = it1->first - memo; //hueco = hueco anterior - memoria del proceso p.e: h.an. = 4, m = 2 -> h.ac. = 2
        if (hueco > 0) mmem[hueco].insert(*it2 + memo);     
        mpos.insert(make_pair(*it2, p));
        mjob.insert(make_pair(p.consultar_ID(), *it2));

        //Actualizar mapa de memoria
        it1->second.erase(*it2);
        if (it1->second.empty()) it1 = mmem.erase(it1);   
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