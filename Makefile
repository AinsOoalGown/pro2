

main.x: main.o Cluster.o Area_espera.o Prioridad.o Proceso.o Procesador.o
	g++ -o main.x main.o Area_espera.o Cluster.o Prioridad.o Procesador.o Proceso.o
Cluster.o: Area_espera.hh Procesador.hh Prioridad.hh Proceso.hh
	g++ -c Cluster.cc -I $(INCLUSIONS)
Area_espera.o: Prioridad.hh Proceso.hh Cluster.hh
	g++ -c Area_espera.cc -I $(INCLUSIONS)
Prioridad.o: Proceso.hh
	g++ -c Prioridad.cc
Proceso.o: 
	g++ -c Proceso.cc
Procesador.o: Proceso.hh 
	g++ -c Procesador.cc
main.o: main.cc Procesador.hh Proceso.hh Prioridad.hh Cluster.hh Area_espera.hh
	g++ -c main.cc -I $(INCLUSIONS)


clean:
	rm *.o
	rm *.x
