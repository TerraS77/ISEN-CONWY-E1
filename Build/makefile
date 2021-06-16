S_GFX = ../Source/GfxLib
B_GFX = ./GfxLib

S_CE = ../Source/ConwayEngine
B_CE = ./ConwayEngine

conwayApp: $(B_CE)/ConwayEngine.o $(B_GFX)/libisentlib.a
	mv ConwayEngine.o $(B_CE)/
	gcc -Wall $(B_CE)/ConwayEngine.o -o conwayApp $(B_GFX)/libisentlib.a -lm -lglut -lGL -lX11

$(B_CE)/ConwayEngine.o: $(S_CE)/ConwayEngine.c $(S_GFX)/GfxLib.h $(S_GFX)/BmpLib.h $(S_GFX)/ESLib.h
	gcc -Wall -c $(S_CE)/ConwayEngine.c

$(B_GFX)/libisentlib.a: $(B_GFX)/BmpLib.o $(B_GFX)/ErreurLib.o $(B_GFX)/ESLib.o $(B_GFX)/GfxLib.o $(B_GFX)/OutilsLib.o $(B_GFX)/VectorLib.o
	mv BmpLib.o $(B_GFX)/
	mv ESLib.o $(B_GFX)/
	mv ErreurLib.o $(B_GFX)/
	mv GfxLib.o $(B_GFX)/
	mv OutilsLib.o $(B_GFX)/
	mv VectorLib.o $(B_GFX)/
	ar r $(B_GFX)/libisentlib.a $(B_GFX)/BmpLib.o $(B_GFX)/ErreurLib.o $(B_GFX)/ESLib.o $(B_GFX)/GfxLib.o $(B_GFX)/OutilsLib.o $(B_GFX)/VectorLib.o
	ranlib $(B_GFX)/libisentlib.a

$(B_GFX)/BmpLib.o: $(S_GFX)/BmpLib.c $(S_GFX)/BmpLib.h $(S_GFX)/OutilsLib.h
	gcc -Wall -O2 -c $(S_GFX)/BmpLib.c

$(B_GFX)/ESLib.o: $(S_GFX)/ESLib.c $(S_GFX)/ESLib.h $(S_GFX)/ErreurLib.h
	gcc -Wall -O2 -c $(S_GFX)/ESLib.c
	
$(B_GFX)/ErreurLib.o: $(S_GFX)/ErreurLib.c $(S_GFX)/ErreurLib.h
	gcc -Wall -O2 -c $(S_GFX)/ErreurLib.c

$(B_GFX)/GfxLib.o: $(S_GFX)/GfxLib.c $(S_GFX)/GfxLib.h $(S_GFX)/ESLib.h
	gcc -Wall -O2 -c $(S_GFX)/GfxLib.c -I/usr/include/GL
	
$(B_GFX)/OutilsLib.o: $(S_GFX)/OutilsLib.c $(S_GFX)/OutilsLib.h
	gcc -Wall -O2 -c $(S_GFX)/OutilsLib.c
	
$(B_GFX)/VectorLib.o: $(S_GFX)/VectorLib.c $(S_GFX)/VectorLib.h
	gcc -Wall -O2 -c $(S_GFX)/VectorLib.c -msse3

# Sous MacOSX, commenter la ligne de commande ci-dessus (en mettant un # au debut)
# et de-commenter la ligne de commande ci-apres :
#	gcc -Wall -O2 -c WavLib.c

#zip:
#	tar -cvzf libisentlib.tgz *.[ch] *.bmp *.pdf makefile

clean:
#	rm -f *~ *.o

deepclean:
	rm -f conwayApp
	rm -f ./ConwayEngine/*
	rm -f ./GfxLib/*
	rm -f ./SmartGrid/*
	rm -f ./SmartUI/*