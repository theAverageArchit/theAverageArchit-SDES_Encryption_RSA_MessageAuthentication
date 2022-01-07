bin : main.o encrypt.o CBC.o CBC_MAC.o sDES.o sDES12.o RSA.o roundKeyGen.o
	gcc main.o encrypt.o CBC.o CBC_MAC.o sDES.o sDES12.o RSA.o roundKeyGen.o -o bin

main.o : main.c roundKeyGen.h sDES12.h RSA.h sDES.h CBC_MAC.h CBC.h encrypt.h
	gcc -c main.c

encrypt.o : encrypt.c roundKeyGen.h sDES12.h RSA.h sDES.h CBC_MAC.h CBC.h
	gcc -c encrypt.c

CBC.o : CBC.c roundKeyGen.h sDES12.h sDES.h
	gcc -c CBC.c

CBC_MAC.o : CBC_MAC.c roundKeyGen.h sDES12.h sDES.h
	gcc -c CBC_MAC.c

RSA.o : RSA.c
	gcc -c RSA.c

sDES.o : sDES.c roundKeyGen.h
	gcc -c sDES.c

sDES12.o : sDES12.c roundKeyGen.h
	gcc -c sDES12.c

roundKeyGen.o : roundKeyGen.c
	gcc -c roundKeyGen.c

clean : 
	rm *.o bin