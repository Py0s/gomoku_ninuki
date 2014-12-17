#pragma once

#include <SFML/Graphics.hpp>
#include <assert.h>

class GText : public sf::Text
{
public:
    enum STYLE {
        DEFAULT = 0,
        TITLE = 1,
        SUBTITLE = 2,
        SELECTED = 4,
        VALIDATED = 8,
    };

    GText(std::string content, sf::Font * font, STYLE style = DEFAULT, float x = 0, float y = 0);
    ~GText();

    void title();
    // void untitle();
    void subtitle();
    // void unsubtitle();
    void select();
    void unselect();
    void validate();
    void unvalidate();
    void resetStyle(STYLE newStyle);

private:
    sf::Font *   _font;
    STYLE       _style;

    bool flagSetted(int flag);
    void _default();
};