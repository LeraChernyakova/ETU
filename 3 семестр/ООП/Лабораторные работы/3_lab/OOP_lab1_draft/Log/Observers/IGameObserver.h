#include "../Log.h"

class IGameObserver {
public:
    virtual void gameStarted(Log &log) = 0;
    virtual void gameEnded(Log &log) = 0;
    virtual void invalidFieldHeight(Log &log) = 0;
    virtual void invalidFieldWidth(Log &log) = 0;
    virtual ~IGameObserver() = default;
};
