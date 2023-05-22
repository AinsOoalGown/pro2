/** @file Procesador.cc
    @brief Código de la clase Procesador
*/

#include "Procesador.hh"

Procesador::Procesador() {
    
}

Procesador::Procesador(const string& s, int m) {
    id = s;
    free_max.second = m;
    free_max.first = 0;
    mmem[free_max.second].insert(0);
}

void Procesador::eliminar_job(int id, map <int,Proceso>::iterator& it) {
    bool borrar = true;         
    if (id != -1) {
        map<int,int>::iterator it1 = mjob.find(id);
        if (it1 == mjob.end()) {
            cout << "error: no existe proceso" << endl;
            borrar = false;             //no hay proceso que borrar
        }
        else {
            it = mpos.find(it1->second);        //iterador que apunta al proceso a eliminar del map de indices
            free_max.first -= it->second.consultar_MEM();   //libera la memoria ocupada
        }
    }
    if (borrar) {
        mjob.erase(it->second.consultar_ID());
        if (mjob.empty()) {     //solo habia 1 proceso
            mmem.clear();
            mmem[free_max.second].insert(0);
        }
        else {                  //habia mas de 1 proceso
            int ind = it->first;  
            int mem = it->second.consultar_MEM() + ind;
            int ind_ant, ind_sig;
            if (it != mpos.begin()) {       //el proceso NO esta al inicio de la memoria
                --it;
                ind_ant = it->first + it->second.consultar_MEM();   
                if (ind != ind_ant) {
                    mmem[ind - ind_ant].erase(ind_ant);         
                    if (mmem[ind - ind_ant].empty()) mmem.erase(ind - ind_ant);
                }
                ++it;
            }
            else {                          //el proceso esta al inicio de la memoria
                ind_ant = 0;
                if (ind != 0) {
                    mmem[ind].erase(0);
                    if (mmem[ind].empty()) mmem.erase(ind);   
                }
            }
            ++it;   
            if (it != mpos.end()) {         //el proceso a eliminar NO es el último de la memoria
                ind_sig = it->first;
                if (ind_sig != mem) {
                    mmem[ind_sig - mem].erase(mem);
                    if (mmem[ind_sig - mem].empty()) mmem.erase(ind_sig - mem);
                }
            }
            else {                          //el proceso a eliminar es el último de la memoria
                ind_sig = free_max.second;
                if (mem != free_max.second){
                    mmem[free_max.second - mem].erase(mem);
                    if (mmem[free_max.second - mem].empty()) mmem.erase(free_max.second - mem);
                }
            }        
            --it;
            mmem[ind_sig - ind_ant].insert(ind_ant);

        }
        it = mpos.erase(it);
    }
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

int Procesador::MEM_libre() const {
    return free_max.second - free_max.first;
}

bool Procesador::hueco(int mem, int& hueco) {
    map<int,set<int> >::const_iterator it = mmem.lower_bound(mem);
    if (it == mmem.end()) return false;
    hueco = it->first;
    return true;
}

void Procesador::add_job(const Proceso& p) {
    int memo = p.consultar_MEM();
    map <int,set<int>>::iterator it1 = mmem.lower_bound(memo);  //hueco igual o mayor a la memoria del proceso
    if (it1 == mmem.end()) cout << "error: no cabe proceso" << endl; 
    else {
        free_max.first += memo;                             //actualiza memoria ocupada del procesador
        set<int>::const_iterator it2 = it1->second.begin(); //indice más pequeño con hueco más ajustado 
        int hueco = it1->first - memo;                      //hueco = hueco anterior - memoria del proceso p.e: h.an. = 4, m = 2 -> hueco = 2
        if (hueco > 0) mmem[hueco].insert(*it2 + memo);     
        mpos.insert(make_pair(*it2, p));
        mjob.insert(make_pair(p.consultar_ID(), *it2));

        //Actualizar mapa de memoria
        it1->second.erase(*it2);
        if (it1->second.empty()) it1 = mmem.erase(it1);   
    }
}


void Procesador::compactar_mem() {  
    if (not mjob.empty()) {
        mmem.clear();
        map <int, Proceso>::iterator it = mpos.begin();     //it del map <indice,proceso>
        int length = 0;                                    //acumula el tamaño de los procesos
        while (it != mpos.end()) {
            if (it->first != length) {
                mpos.insert(it, make_pair(length, it->second)); //insert detras del elemento a eliminar
                mjob[it->second.consultar_ID()] = length;      //actualizamos mjob map
                length += it->second.consultar_MEM();         //siguiente indice al que se tiene que mover (tamaño total de todos los procesos anteriores)
                it = mpos.erase(it);                         //avanzas al siguiente 
            }
            else {
                length += it->second.consultar_MEM();
                ++it;
            }
        }
        mmem[free_max.second - length].insert(length);      //actualizamos map de huecos con un solo hueco 
    }
}

string Procesador::consultar_ID() const {
    return id;
}

bool Procesador::existe_job(int id) const {
    return (mjob.find(id) != mjob.end());
}

bool Procesador::en_curso() const {
    return not mjob.empty();
}

void Procesador::escribir() const {
    map <int, Proceso>::const_iterator it;
    for (it = mpos.begin(); it != mpos.end(); ++it) {
        cout << it->first << ' ';       //escribe el indice
        it->second.escribir();          //escribe atributos del proceso
    }
}