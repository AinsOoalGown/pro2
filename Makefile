OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

main.x: main.o Cluster.o Area_espera.o Prioridad.o Proceso.o Procesador.o
	g++ -o program.exe *.o
Cluster.o: Area_espera.hh Procesador.hh Prioridad.hh Proceso.hh
	g++ -c Cluster.cc $(OPCIONS) -I $(INCLUSIONS) 
Area_espera.o: Prioridad.hh Proceso.hh Cluster.hh
	g++ -c Area_espera.cc $(OPCIONS) -I $(INCLUSIONS)
Prioridad.o: Proceso.hh
	g++ -c Prioridad.cc $(OPCIONS)
Proceso.o: 
	g++ -c Proceso.cc $(OPCIONS)
Procesador.o: Proceso.hh 
	g++ -c Procesador.cc $(OPCIONS)
main.o: program.cc Procesador.hh Proceso.hh Prioridad.hh Cluster.hh Area_espera.hh
	g++ -c program.cc $(OPCIONS) -I $(INCLUSIONS)


clean:
	rm *.o
	rm *.x
	rm *.tar

practica.tar:
	tar -cvf practica.tar *.cc *.hh Makefile