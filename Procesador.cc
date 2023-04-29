/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador() {
    mem = 0;
    id_mem.second = 0;
}

Procesador::Procesador(string s, int m) {
    id_mem.first = s;
    id_mem.second = m;
    mem = 0;
}

int Procesador::search_mem_stack (int memo, int mem_max, const map <int, pair<int, int> > mem) {
    map<int,pair<int, int> >::const_iterator it = mem.begin();
    if ((*it).first == memo) return 0;
    //Caso 1: hay un exactamente un proceso
    if (mem.size() == 1) {
        int size = (*it).first + (*it).second.first;
        //el proceso esta en índice 0
        if ((*it).first == 0) return (*it).second.first;
        //el proceso esta al final de la memoria
        else if (size == mem_max) return 0;
        //el índice del proceso != 0 y ind + esp != mem_max (esta en "medio")
        else if ((*it).first <= mem_max - size and (*it).first >= memo) return 0;
        return size;
    }
    //Caso 2: hay dos o más procesos
    else {
        int a, b, min_size;
        int ind = 0;
        if (memo < (*it).first) min_size = (*it).first;
        else min_size = mem_max;
        b = a = 0;
        while (it != mem.end()) {
            a = (*it).first + (*it).second.first; //indice + espacio
            ++it;
            if (it != mem.end()) {
                b = (*it).first; //indice sig. elem.
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

void Procesador::add_job(Proceso p) {
    int ind = 0;
    if (not mjob.empty()) {
        int memo = p.consultar_MEM();
        ind = search_mem_stack(memo, id_mem.second, mmem);    
    }
    mem += p.consultar_MEM();
    pair <int, int> par (p.consultar_MEM(), p.consultar_ID());
    mmem.insert(make_pair(ind, par));
    p.add_indice(ind);
    mjob.insert(make_pair(p.consultar_ID(), p));
}

void Procesador::eliminar_job(int id) {
    mem -= mjob[id].consultar_MEM();
    int ind = mjob[id].consultar_ind();
    mjob.erase(mjob.find(id));
    mmem.erase(mmem.find(ind));
}

void Procesador::compactar_mem() {  //no se usa
    mjob[78].escribir();
}

void Procesador::avanzar_tiempo(int t) {
    if (not mjob.empty()) {
        map <int, Proceso>::iterator it = mjob.begin();
        queue <int> q;
        while (it != mjob.end()) {
            if ((*it).second.consultar_tiempo() <= t) {
                int id = (*it).second.consultar_ID();
                q.push(id);
            }
            else (*it).second.restar_tiempo(t);          
            ++it;
        }
        while (not q.empty()) {
            eliminar_job(q.front());
            q.pop();
        }
    }
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
    if ((*it).first != 0) max_consec = (*it).first; //comença desde 0
    a = b = 0;
    while (it != mmem.end()) {
         a = (*it).first + (*it).second.first; //indice + espacio
        ++it;
        if (it != mmem.end()) {
            b = (*it).first; //indice sig. elem.
            if (max_consec < b - a) max_consec = b - a;
        }
        else if (id_mem.second - a > max_consec) max_consec = id_mem.second - a;
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

void Procesador::leer() {   //no se usa
    cin >> id_mem.first;
}

void Procesador::escribir() const {
    map <int, pair <int,int> >::const_iterator it;
    for (it = mmem.begin(); it != mmem.end(); ++it) {
        cout << (*it).first << ' ';
        mjob.at((*it).second.second).escribir();
    }
}