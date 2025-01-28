#include "observable.h"

void observable::setObserver(observer& ob){ this->ob = &ob; }
void observable::notifyObserver() { if(ob) ob->notify(); }
