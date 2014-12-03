
#include "Stone.h"
#include "Referee.h"
#include "ExcOutOfBound.h"

const enum Stone::E_COLOR Referee::OP_COLOR[] = { Stone::WHITE, Stone::BLACK };

Referee::Referee() {

}

Referee::~Referee() {

}

Referee::E_STATE Referee::check(const Stone& s, Map& map, APlayer* player) const {
    Tile& tile = map[s.y()][s.x()];

    if (tile.getColor() != Stone::E_COLOR::NONE)
        return INVALID;

    map.placeStone(s);

    // if RULE
    if (checkDoubleThree(map, tile, s.color()))
    {
        map.removeStone(tile);
        std::cout << "DOUBLE TROIS" << std::endl;
        return E_STATE::INVALID;
    }

    checkCapture(tile, map, player);

    E_STATE ret = checkAlign(tile, map);

    // map.displayDebug();
    return ret;
}

bool Referee::alignOne(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    Map::PTR ptr = map.go[dir];
    Tile& inter_tile = (map.*ptr)(tile, 1);

    if (inter_tile.getIntValue(color, dir % 4) == 3)
        return true;
    return false;   
}

bool Referee::XFactorextrem(Map& map, Tile& tile, Stone::E_COLOR color, int dir, int first_value, int second_value) const
{
    Map::PTR ptr = map.go[dir];
    Tile& inter_tile = (map.*ptr)(tile, first_value);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;

    ptr = map.go[Map::OP_DIR[dir]];
    inter_tile = (map.*ptr)(tile, second_value);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;
    return true;
}

/*bool Referee::extremOne(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    Map::PTR ptr = map.go[dir];
    Tile& inter_tile = (map.*ptr)(tile, 4);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;

    ptr = map.go[Map::OP_DIR[dir]];
    inter_tile = (map.*ptr)(tile, 1);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;
    return true;
}
*/
bool Referee::alignTwo(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    Map::PTR ptr = map.go[dir];
    Tile& inter_tile = (map.*ptr)(tile, tile.getValue(color, dir) + 1);

    if (inter_tile.getIntValue(color, dir) == 3)
        return true;
    return false;
}

/*bool Referee::extremTwo(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    Map::PTR ptr = map.go[dir];
    Tile& inter_tile = (map.*ptr)(tile, tile.getValue(color, dir) + 3);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;

    ptr = map.go[Map::OP_DIR[dir]];
    inter_tile = (map.*ptr)(tile, tile.getValue(color, Map::OP_DIR[dir]) + 1);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;
    return true;
}
*/
bool Referee::alignThree(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    return true;
}

/*bool Referee::extremThree(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    Map::PTR ptr = map.go[dir];
    Tile& inter_tile = (map.*ptr)(tile, tile.getValue(color, dir) + 1);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;

    ptr = map.go[Map::OP_DIR[dir]];
    inter_tile = (map.*ptr)(tile, tile.getValue(color, Map::OP_DIR[dir]) + 1);

    if (inter_tile.getColor() != Stone::E_COLOR::NONE)
        return false;
    return true;
}
*/
bool Referee::checkFreeThreeConfig(Map& map, Tile& tile, Stone::E_COLOR color, int dir) const
{
    try
    {
        switch (tile.getIntValue(color, dir))
        {
            case 1:
                if (alignOne(map, tile, color, dir)
                    && /*extremOne(map, tile, color, dir))*/  XFactorextrem(map, tile, color, dir, 4, 1))
                {
                    std::cout << "Cas 1 align" << std::endl;
                    return true;
                }
                break;
            case 2:
                if (alignTwo(map, tile, color, dir)
                    && /*extremTwo(map, tile, color, dir))*/ XFactorextrem(map, tile, color, dir, tile.getValue(color, dir) + 3, tile.getValue(color, Map::OP_DIR[dir]) + 1))
                {
                    std::cout << "Cas 2 align" << std::endl;
                    return true;
                }
                break;
            case 3:
                if (alignThree(map, tile, color, dir)
                    && /*extremThree(map, tile, color, dir))*/ XFactorextrem(map, tile, color, dir, tile.getValue(color, dir) + 1, tile.getValue(color, Map::OP_DIR[dir]) + 1)) // TODO : OPTI POUR NE PAS CHECKER DEUX FOIS LA MEME CHOSE
                {
                    std::cout << "Cas 3 align" << std::endl;
                    return true;
                }
                break;
            default:
                break;
        }
    }
    catch (const ExcOutOfBound& e) {
        return false;
    }
    return false;
}

bool Referee::checkDoubleThreeSecondPart(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const
{
    for (int second_dir = 0; second_dir < 8; ++second_dir)
    {
        if (first_dir != second_dir
            && Map::OP_DIR[first_dir] != second_dir)
        {
            // std::cout << "On va checker si 2e trois libre:" << second_dir << std::endl;
            if (checkFreeThreeConfig(map, tile, color, second_dir))
                return true;
        }
    }
    return false;
}

bool Referee::checkDoubleThreeFirstPart(Map& map, Tile& tile, Stone::E_COLOR color, int first_dir) const
{
    if (checkFreeThreeConfig(map, tile, color, first_dir))
    {
        std::cout << "Premier trois libre" << std::endl;
        // PARCOURIR TOUTES LES PIERRES DE L ALIGNEMENT
        {
            if (checkDoubleThreeSecondPart(map, tile, color, first_dir))
                return true;
        }
    }
    return false;
}

bool Referee::checkDoubleThree(Map& map, Tile& tile, Stone::E_COLOR color) const 
{
    for (int first_dir = 0; first_dir < 8; ++first_dir)
    {
        if (checkDoubleThreeFirstPart(map, tile, color, first_dir))
            return true;
    }
    return false;
}


void Referee::checkCapture(Tile& tile, Map& map, APlayer* player) const {
    Stone::E_COLOR color = tile.getColor();

    for (int dir = 0; dir < 8; ++dir)
    {
        if (map[tile.Y][tile.X].getValue(Referee::OP_COLOR[color], dir) == 2)
        {
            try
            {
                Map::Map::PTR ptr = map.go[dir];
                Tile& tile_for_capture = (map.*ptr)(tile, 3);

                if (tile_for_capture.getColor() == color)
                {
                    player->captureStones();

                    Tile& first_captured_stone = (map.*ptr)(tile, 1);
                    Tile& second_captured_stone = (map.*ptr)(tile, 2);

                    map.removeStone(first_captured_stone);
                    map.removeStone(second_captured_stone);
                }
            }
            catch (const ExcOutOfBound& e) {
            }
        }
    }
}

Referee::E_STATE Referee::checkAlign(Tile& t, Map& m) const {
    // TODO: need to make a function from E_Dir to direction

    if (t.getIntValue(t.getColor(), Map::N) >= 5)
        // Mets toi ici avec if (is_beakable() == true) put_in_list(t) else ...
        return this->winner(t.getColor());
    if (t.getIntValue(t.getColor(), Map::W) >= 5)
        // Mets toi ici avec if (is_beakable() == true) put_in_list() else ...
        return this->winner(t.getColor());
    if (t.getIntValue(t.getColor(), Map::NW) >= 5)
        // Mets toi ici avec if (is_beakable() == true) put_in_list() else ...
        return this->winner(t.getColor());
    if (t.getIntValue(t.getColor(), Map::NE) >= 5)
        // Mets toi ici avec if (is_beakable() == true) put_in_list() else ...
        return this->winner(t.getColor());
    return VALID;
}

inline Referee::E_STATE Referee::winner(const Stone::E_COLOR color) const {
    if (color == Stone::BLACK)
        return END_BLACK;
    return END_WHITE;
}