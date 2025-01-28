#pragma once

class Applications;
class GameObserver {
public:
    explicit GameObserver(Applications* application);
    void stop();
private:
    Applications* application;
};
