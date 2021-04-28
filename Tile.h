#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
    // Constructors & destructor
    Tile(Colour colour, Shape shape);
    Tile(Tile& other);
    Tile(Tile&& other);
    ~Tile();

    // Alternate constructor to parse colour & shape from a string
    Tile(std::string tileString);

    // Getters & setters
    Colour getColour();
    void setColour(Colour newColour);
    Shape getShape();
    void setShape(Shape newShape);

    // Get tile in [letter][number] string format
    std::string toString();

private:
   Colour colour;
   Shape  shape;
};

#endif // ASSIGN2_TILE_H
