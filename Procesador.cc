/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador() {
    mem = 0;
    id_mem.second = 0;
}

Procesador::Procesador(const string& s, int m) {
    id_mem.first = s;
    id_mem.second = m;
    mem = 0;
}

int Procesador::search_mem_stack (int memo, int mem_max, const map <int, pair<int, int> >& mem) {
    map<int,pair<int, int> >::const_iterator it = mem.begin();
    if (it->first == memo) return 0;
    //Caso 1: hay un exactamente un proceso
    if (mem.size() == 1) {
        int size = it->first + it->second.first;
        if (it->first == 0) {
            if (mem_max - size < memo) return -1;
            return it->second.first;
        }
        if (it->first < memo) {
            if (size == mem_max) return -1;
            if (mem_max - size < memo) return -1;
            return size;
        }
        return 0;
    }
    //Caso 2: hay dos o más procesos
    else {
        int a, b, min_size;
        int ind = -1;
        if (memo < it->first) {
            min_size = it->first;
            ind = 0;
        }
        else min_size = mem_max;
        b = a = 0;
        while (it != mem.end()) {
            a = it->first + it->second.first; //indice + espacio
            ++it;
            if (it != mem.end()) {
                b = it->first; //indice sig. elem.
                if (memo == b - a) return a;
                else if (b - a < min_size and b - a > memo) {
                    min_size = b - a;
                    ind = a;
                } 
            }
            else if (mem_max - a >= memo) {
                if (mem_max - a == memo or mem_max - a < min_size) return a;
            }           
        }
        return ind;
    }
}

void Procesador::add_job(Proceso& p, bool& added) {
    int ind = 0;
    int memo = p.consultar_MEM();
    if (not mjob.empty()) {
        ind = search_mem_stack(memo, id_mem.second, mmem);   
    }
    if (ind == -1 or id_mem.second < memo) added = false;
    else {
        added = true;
        mem += p.consultar_MEM();
        pair <int, int> par (p.consultar_MEM(), p.consultar_ID());
        mmem.insert(make_pair(ind, par));
        p.add_indice(ind);
        mjob.insert(make_pair(p.consultar_ID(), p));
    }
}

void Procesador::eliminar_job(int id, map <int,Proceso>::iterator& it) {
    if (id != -1) it = mjob.find(id);
    mem -= it->second.consultar_MEM();
    int ind = it->second.consultar_ind();
    it = mjob.erase(it);
    mmem.erase(mmem.find(ind));
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
    map <int, pair <int,int> >::const_iterator it;
    for (it = mmem.begin(); it != mmem.end(); ++it) {
        cout << it->first << ' ';
        mjob.at(it->second.second).escribir();
    }
}