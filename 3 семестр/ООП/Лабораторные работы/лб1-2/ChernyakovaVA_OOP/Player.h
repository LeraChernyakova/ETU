#pragma once

class Player {
private:
    int health;
    int food;
    int score;
    int resource;
    bool winner;
    bool dead;
    bool open_exit;
public:
    Player();
    ~Player();

    int getHealth() const;
    int getFood() const;
    int getScore() const;
    int getResource() const;
    bool getWinner() const;
    bool getDead() const;
    bool getOpenExit() const;
    
    void addHealth(int health_);
    void addFood(int food_);
    void addScore(int score_);
    void addResource(int resource_);

    void cutHealth(int health_);
    void cutFood(int food_);
    void cutScore(int score_);

    void setWinner();
    void setDead();
    void setOpenExit();
};