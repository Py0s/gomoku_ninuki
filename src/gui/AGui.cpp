#include "AGui.h"

AGui::AGui(int map_size_y, int map_size_x, enum E_SCENE scene)
: _map_size_y(map_size_y), _map_size_x(map_size_x), _curs(), _scene(scene) {

}

AGui::~AGui() {

}

// Getters
const  Cursor& AGui::getCursor() const {
    return _curs;
}

enum AGui::E_SCENE AGui::getScene() const {
    return _scene;
}