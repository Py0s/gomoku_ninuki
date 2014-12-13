#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>

class GText : public sf::Text
{
public:
    enum STYLE {
        TITLE = 0,
        SUBTITLE,
        SELECTED,
        UNSELECTED,
        VALIDATED
    };

    GText(std::string content, sf::Font * font, STYLE style = UNSELECTED, float x = 0, float y = 0);
    ~GText();

    void title();
    void subtitle();
    void select();
    void unselect();
    void validate();

    inline STYLE style() const {
        return _style;
    }

private:
    sf::Font *   _font;
    STYLE       _style;
};