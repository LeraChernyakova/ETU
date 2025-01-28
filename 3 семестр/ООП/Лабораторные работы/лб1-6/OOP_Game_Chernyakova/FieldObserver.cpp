#include <iostream>
#include "FieldObserver.h"
#include "Logger.h"
//#include "Field.h"

void FieldObserver::onCellEventChanged(int x, int y) {
    Logger::getInstance() << LogMessage{
        "On cell (" + std::to_string(x) + "," + std::to_string(y) + ") changed event",
        Logger::Trace };
}
void FieldObserver::onCellPatencyChanged(int x, int y, bool patency) {
    Logger::getInstance() << LogMessage{
        "Cell" + std::to_string(x) + "," + std::to_string(y) + "change patency on " + std::to_string(patency),
        Logger::Trace };
}
void FieldObserver::onCellActivityChanged(int x, int y, const Cell& cell) {
    if (_pf) {
        _pf->reprintCell(x, y, cell);
    }
}
void FieldObserver::setPrintField(PrintField* pf) {
    _pf = pf;

}