#include "Procesador.hh"

Procesador::Procesador() {
    mem = 0;
}

Procesador::Procesador(string s, int m) {
    id_mem.first = s;
    id_mem.second = m;
    mem = 0;
}

void Procesador::search_mem_stack (int memo, int& ind) {
    map<int,pair<int, int> >::const_iterator it = mmem.begin();
    int a, b;
    if (mmem.size() == 1) {
        if ((*it).first == 0) ind = (*it).second.first;
        else if ((*it).first >= memo) ind = 0;
        else ind = (*it).first + (*it).second.first;
    }
    else {
        if ((*it).first == memo) ind = 0;
        else {
            bool found = false;
            b = a = 0;
            while (it != mmem.end() and not found) {
                a = (*it).first + (*it).second.first; //indice + espacio
                ++it;
                if (it != mmem.end()) b = (*it).first; //indice sig. elem.
                if (memo == b - a) {
                    ind = a;
                    found = true;
                }      
            }
            if (not found) ind = -1;
        }
    }
}

void Procesador::add_job(Proceso p) {
    int ind = 0;
    if (not mjob.empty()) { 
        int memo = p.consultar_MEM();
        bool found = false;
        while (not found) {
            search_mem_stack(memo, ind);
            if (ind == -1) ++memo;
            else found = true;
        }
        cout << "he salido" << endl;
    }
    mem += p.consultar_MEM();
    pair <int, int> par (p.consultar_MEM(), p.consultar_ID());
    mmem.insert(make_pair(ind, par));
    mjob.insert(make_pair(p.consultar_ID(),p));
}

void Procesador::eliminar_job(int id) {

}

void Procesador::compactar_mem() {

}

string Procesador::consultar_ID() const {
    return id_mem.first;
}

int Procesador::consultar_MEM_contigua() const {
    int a, b;
    map <int,pair<int,int> >::const_iterator it = mmem.begin();
    if (mem == 0) return id_mem.second;
    else if (mmem.size() == 1) {
        a = id_mem.second - (*it).second.first;
        b = (*it).first;
        if (a >= b) return a;
        return b;
    }
    int max_consec = 0;
    if ((*it).first != 0) max_consec = (*it).first + 1; //comença desde 0
    a = b = 0;
    while (it != mmem.end()) {
         a = (*it).first + (*it).second.first; //indice + espacio
        ++it;
        if (it != mmem.end()) b = (*it).first; //indice sig. elem.    
        if (max_consec < b - a) max_consec = b - a;
    }
    return max_consec;
}

bool Procesador::existe_job(int id) const {
    map <int, Proceso>::const_iterator it = mjob.find(id); 
    if (it == mjob.end()) return false;
    return true;
}

bool Procesador::en_curso() const {
    return not mjob.empty();
}

void Procesador::leer() {
    
}

void Procesador::escribir() const {
    map <int, pair <int,int> >::const_iterator it;
    for (it = mmem.begin(); it != mmem.end(); ++it) {
        cout << (*it).first << ' ' << (*it).second.second << ' ';
        cout << (*it).second.first << ' ';
        cout << mjob.at((*it).second.second).consultar_tiempo() << endl;
    }
}