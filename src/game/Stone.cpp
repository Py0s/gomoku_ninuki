#include "Stone.h"
#include "Tile.h"

Stone::Stone(int y, int x, Stone::E_COLOR const& color)
    : _y(y), _x(x), _color(color) {
}
Stone::Stone(Tile const& tile)
    : _y(tile.Y), _x(tile.X), _color(tile.getColor()) {
}
Stone::Stone(Tile const& tile, Stone::E_COLOR const& color)
    : _y(tile.Y), _x(tile.X), _color(color) {
}

Stone::~Stone() {
}
