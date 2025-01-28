all: main.o class_images.o reflection.o paint_pentogram.o paint_rectangle.o paint_hexagon.o is_error.o
	g++ main.o class_images.o reflection.o paint_pentogram.o paint_rectangle.o paint_hexagon.o is_error.o -lpng

main.o: main.cpp class_images.h
	g++ -c main.cpp

class_images.o: class_images.cpp class_images.h
	g++ -c class_images.cpp

reflection.o: reflection.cpp class_images.h
	g++ -c reflection.cpp

paint_pentogram.o: paint_pentogram.cpp class_images.h
	g++ -c paint_pentogram.cpp

paint_rectangle.o: paint_rectangle.cpp class_images.h
	g++ -c paint_rectangle.cpp

paint_hexagon.o: paint_hexagon.cpp class_images.h
	g++ -c paint_hexagon.cpp

is_error.o: is_error.cpp class_images.h
	g++ -c is_error.cpp

clean:
	rm *.o a.out
