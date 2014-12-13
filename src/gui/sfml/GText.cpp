#include "GText.h"

GText::GText(std::string content, sf::Font * font, STYLE style, float x, float y)
: /*sf::Text(), */_font(font) {
    setString(content);
    setFont(*_font);
    setPosition(x, y);
    switch (style)
    {
        case TITLE: title(); break;
        case SUBTITLE: subtitle(); break;
        case SELECTED: select(); break;
        case UNSELECTED: unselect(); break;
        case VALIDATED: validate(); break;
    }
}
GText::~GText() {
}

inline void GText::title() {
    _style = TITLE;
    setCharacterSize(32);
    setColor(sf::Color::Green);
    setStyle(sf::Text::Bold | sf::Text::Underlined);
}
inline void GText::subtitle() {
    _style = SUBTITLE;
    setCharacterSize(24);
    setColor(sf::Color::Green);
    setStyle(sf::Text::Bold);
}
inline void GText::select() {
    _style = SELECTED;
    setCharacterSize(24);
    setColor(sf::Color::Blue);
    setStyle(sf::Text::Regular);
}
inline void GText::unselect() {
    _style = UNSELECTED;
    setCharacterSize(24);
    setColor(sf::Color::White);
    setStyle(sf::Text::Regular);
}
inline void GText::validate() {
    _style = VALIDATED;
    setCharacterSize(24);
    setColor(sf::Color::Red);
    setStyle(sf::Text::Underlined);
}
