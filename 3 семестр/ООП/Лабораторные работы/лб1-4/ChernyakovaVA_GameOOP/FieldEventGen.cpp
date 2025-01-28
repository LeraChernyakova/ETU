#include "FieldEventGen.h"

Event* FieldEventGen::generate() {
	return new FieldNoWalls(field);
}