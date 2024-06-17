#include <iostream>
// Base class representing a generic game piece
class Piece {
protected:
    int owner; // Identifier of the piece's owner

public:
    // Constructors
    Piece() : owner(0) {};
    Piece(int owner) : owner(owner) {}
    // Destructor
    virtual ~Piece() = default;
    // Pure virtual function for getting the type of the piece
    virtual std::string getType() const = 0; 
    // Accessor method for retrieving the owner of the piece
    int getOwner() const { return owner; }
    // Mutator method for setting the owner of the piece
    void setOwner(int newOwner) { owner = newOwner; }
     // Pure virtual function for displaying information about the piece
    virtual void display() const = 0; // פונקציה וירטואלית טהורה להציג מידע על החלק
};
// Class representing a road piece, inheriting from Piece
class Road : public Piece {
public:
    // Constructor
    Road(int owner) : Piece(owner) {}
    // Displays information about the road piece
    void display() const override {
        std::cout << "Road owned by player " << owner << std::endl;
    }
    // Returns the type of the road piece
     std::string getType() const override{
        return "ROAD";
    }
};
// Class representing a settlement piece, inheriting from Piece
class Settlement : public Piece {
public:
    // Constructor
    Settlement(int owner) : Piece(owner) {}
    ~Settlement(){};
    // Returns the type of the settlement piece
    std::string getType() const override { return "SETTLEMENT"; }

    // Displays information about the settlement piece
    void display() const override {
        std::cout << "Settlement owned by player " << owner << std::endl;
    }
};
// Class representing a city piece, inheriting from Piece
class City : public Piece {
public:
    // Constructor
    City(int owner) : Piece(owner) {}

    // Returns the type of the city piece
    std::string getType() const override { return "CITY"; }

    // Displays information about the city piece
    void display() const override {
        std::cout << "City owned by player " << owner << std::endl;
    }
};
