#include <cctype>

#include "Tile.h"
#include "TileCodes.h"

Tile::Tile(Colour colour, Shape shape) :
    colour(std::toupper(colour)),
    shape(shape)
{}

// This is a stupid bodge
Tile::Tile(std::string tileSTR)
{
    colour = tileSTR.at(0);
    shape = std::stoi(tileSTR.substr(1,1));
}

Tile::Tile(Tile& other) :
    colour(other.colour),
    shape(other.shape)
{}

Tile::Tile(Tile&& other) :
    colour(other.colour),
    shape(other.shape)
{}

Tile::~Tile() {
    // No manual deletes necessary
}

Colour Tile::getColour() {
    return colour;
}

void Tile::setColour(Colour newColour) {
    colour = std::toupper(newColour);
}

Shape Tile::getShape() {
    return shape;
}

void Tile::setShape(Shape newShape)  {
    shape = newShape;
}

std::string Tile::toString() {
    std::string stringRepr = colour + std::to_string(shape);
    return stringRepr;
}

// Get ANSI colour coded string representation of tile
std::string Tile::toColouredString() {
    std::string str = toString();
    if (colour == RED) {
        str = "\033[;31m" + str + "\033[0m";
    } else if (colour == ORANGE) {
        str = "\033[38;5;208m" + str + "\033[0m";
    } else if (colour == YELLOW) {
        str = "\033[;33m" + str + "\033[0m";
    } else if (colour == GREEN) {
        str = "\033[;32m" + str + "\033[0m";
    } else if (colour == BLUE) {
        str = "\033[38;5;39m" + str + "\033[0m";
    } else if (colour == PURPLE) {
        str = "\033[38;5;135m" + str + "\033[0m";
    }
    return str;
}

bool Tile::equals(Tile t) {
    return t.getColour() == colour && t.getShape() == shape;
}

bool Tile::hasBlankValue() {
    return colour == NO_COLOUR || shape == NO_SHAPE;
}