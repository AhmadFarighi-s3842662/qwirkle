#include <cctype>

#include "Tile.h"
#include "TileCodes.h"

Tile::Tile(Colour colour, Shape shape) :
    colour(std::toupper(colour)),
    shape(shape)
{}

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

bool Tile::equals(Tile t) {
    return t.getColour() == colour && t.getShape() == shape;
}

bool Tile::hasBlankValue() {
    return colour == NO_COLOUR || shape == NO_SHAPE;
}