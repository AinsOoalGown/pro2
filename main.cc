/**
 * @mainpage Práctica: Simulación del rendimiento de procesadores interconectados.
 
En esta práctica se construye un programa modular que simula el funcionamiento de una arquitectura multiprocesador. Se introducen las clases <em>Procesador</em>, <em>Proceso</em>, <em>Cluster</em>, <em>Area_espera</em>. <em>Prioridad</em>.

Sólo se documentan los elementos públicos.
*/

/** @file main.cc
    @brief Programa principal para el proyecto <em>Simulación del rendimiento de procesadores interconectados</em>
 
*/

#include "Procesador.hh"
#include "Proceso.hh"
#include "Cluster.hh"
#include "Area_espera.hh"
#include "Prioridad.hh"

using namespace std;

/** @brief Programa principal para el proyecto <em>Simulación del rendimiento de procesadores interconectados</em>
*/
int main() {
    Cluster c;
    c.leer();
    Area_espera ae;
    ae.leer();
    string comando;
    cin >> comando;
    while (comando != "fin") {
        if (comando == "cc" or comando == "configurar_cluster") c.leer();  //1
        else if (comando == "mc" or comando == "modificar_cluster") {        //2
            string id;
            cin >> id;
            Cluster c2;
            c2.leer();
            if (c.existe_prc(id) and not c.consultar_prc(id).en_curso()
            and not c.existe_aux(id)) c.añadir_cluster(c2, id);
            else cout << "error" << endl;  
        }

        else if (comando == "ap" or comando == "alta_prioridad") {         //3
            string id_prior;
            cin >> id_prior;
            if (not ae.existe_prior(id_prior)) ae.add_prior(id_prior);
            else cout << "error: ya existe prioridad" << endl;
        }

        else if (comando == "bp" or comando == "baja_prioridad") {         //4
            string id_prior;
            cin >> id_prior;
            if (ae.existe_prior(id_prior)) {
                if (not ae.id_prior_pendiente(id_prior)) ae.eliminar_prior(id_prior);
                else cout << "error: prioridad con procesos" << endl;
            }
            else cout << "error: no existe prioridad" << endl;
        }
        
        else if (comando == "ape" or comando == "alta_proceso_espera") {       //5
            string id_prior;
            cin >> id_prior;
            Proceso p;
            p.leer();
            if (ae.existe_prior(id_prior)) {
                if (not ae.existe_prior_job(id_prior, p.consultar_ID())) {
                    ae.add_job(p, id_prior);
                }
                else cout << "error: ya existe proceso" << endl;
            }
            else cout << "error: no existe prioridad" << endl;
        }

        else if (comando == "app" or comando == "alta_proceso_procesador") {        //6
            string id;
            cin >> id;
            Proceso p;
            p.leer();
            if (c.existe_prc(id)) {
                if (not c.consultar_prc(id).existe_job(p.consultar_ID())) {
                    if (p.consultar_MEM() <= c.consultar_prc(id).consultar_MEM_contigua())
                    c.add_job_prc(id, p);
                    else cout << "error: no cabe proceso" << endl;
                }
                else cout << "error: ya existe proceso" << endl;
            }
            else cout << "error: no existe procesador" << endl;
        }

        else if (comando == "bpp" or comando == "baja_proceso_procesador") {        //7
            string idprc; //id procesador
            int idjob;     //id proceso
            cin >> idprc >> idjob;
            if (c.existe_prc(idprc)) { 
                if (c.consultar_prc(idprc).existe_job(idjob)) c.eliminar_job_prc(idprc,idjob); 
                else cout << "error: no existe proceso" << endl;
            }
            else cout << "error: no existe procesador" << endl;

        }

        else if (comando == "epc" or comando == "enviar_procesos_cluster") {        //8
            int n;
            cin >> n;
            bool salir = false;
            while (n >= 0 and not salir) {
                if (ae.pendiente_global()) {
                    ae.enviar_job_a_cluster();
                    --n;
                }
                else salir = true;
            }
        }

        else if (comando == "at" or comando == "avanzar_tiempo") {     //9
            int t;
            cin >> t;
            c.avanzar_tiempo_prc(t);
        }

        else if (comando == "ipri" or comando == "imprimir_prioridad") {   //10
            string id_prior;
            cin >> id_prior;
            if (ae.existe_prior(id_prior)) ae.escribir_prior(id_prior);
            else cout << "error: no existe prioridad" << endl;
        }

        else if (comando == "iae" or comando == "imprimir_area_espera") ae.escribir();  //11
        else if (comando == "ipro" or comando == "imprimir_procesador") {   //12
            string id;
            cin >> id;
            if (c.existe_prc(id)) c.escribir_prc(id);     
            else cout << "error: no existe procesador" << endl;
        }
        
        else if (comando == "ipc" or comando == "imprimir_procesadores_cluster") c.escribir_todos();   //13
        else if (comando == "iec" or comando == "imprimir_estructura_cluster") c.escribir_est(); //14
        else if (comando == "cmp" or comando == "compactar_memoria_procesador") {    //15
            string id;
            cin >> id;          //MAL!! NO USAR CONSULTAR PARA MODIFICAR
            if (c.existe_prc(id)) c.consultar_prc(id).compactar_mem(); 
            else cout << "error:" << endl;
        }
    
        else if (comando == "cmc" or comando == "compactar_memoria_cluster") c.compactar();   //16
        cin >> comando;
    }
}
