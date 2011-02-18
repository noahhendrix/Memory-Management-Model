main:main.o
	g++ -g main.o -o main

main.o:main.cpp job_manager.o
	g++ -c -g main.cpp

job_manager.o:models/JobManager.h list.o
	g++ -c -g models/JobManager.h

list.o:lib/List.h
	g++ -c -g lib/List.h

clean:
	rm -f *.o *~ main
