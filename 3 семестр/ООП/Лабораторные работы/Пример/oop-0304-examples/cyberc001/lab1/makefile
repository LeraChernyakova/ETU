GCPP = g++ -std=c++17 -g


lab1: field.o field_view.o cells/cell.o cells/cell_view.o cells/cell_entrance.o cells/cell_exit.o
	$(GCPP) main.cpp field.o field_view.o cells/cell.o cells/cell_view.o cells/cell_entrance.o cells/cell_exit.o -o lab1
clean:
	-rm -f *.o
	-rm -f cells/*.o


field.o: field.cpp field.h
	$(GCPP) -c $< -o $@
field_view.o: field_view.cpp field_view.h
	$(GCPP) -c $< -o $@
cells/cell.o: cells/cell.cpp cells/cell.h
	$(GCPP) -c $< -o $@
cells/cell_view.o: cells/cell_view.cpp cells/cell_view.h
	$(GCPP) -c $< -o $@
cells/cell_entrance.o: cells/cell_entrance.cpp cells/cell_entrance.h
	$(GCPP) -c $< -o $@
cells/cell_exit.o: cells/cell_exit.cpp cells/cell_exit.h
	$(GCPP) -c $< -o $@
