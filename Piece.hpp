#include <iostream>

class Piece {
protected:
    int owner; // מזהה של הבעלים של החלק

public:
    Piece() : owner(0) {};
    Piece(int owner) : owner(owner) {}

    virtual ~Piece() = default;
    virtual std::string getType() const = 0; // Pure virtual function for piece type
    int getOwner() const { return owner; }
    void setOwner(int newOwner) { owner = newOwner; }

    virtual void display() const = 0; // פונקציה וירטואלית טהורה להציג מידע על החלק
};
class Road : public Piece {
public:
    Road(int owner) : Piece(owner) {}

    void display() const override {
        std::cout << "Road owned by player " << owner << std::endl;
    }
     std::string getType() const override{
        return "ROAD";
    }
};
class Settlement : public Piece {
public:
    Settlement(int owner) : Piece(owner) {}

    void display() const override {
        std::cout << "Settlement owned by player " << owner << std::endl;
    }
    std::string getType() const override{
        return "SETTLEMENT";
    }
};
class City : public Piece {
public:
    City(int owner) : Piece(owner) {}

    void display() const override {
        std::cout << "City owned by player " << owner << std::endl;
    }
    std::string getType() const override{
        return "CITY";
    }
};
