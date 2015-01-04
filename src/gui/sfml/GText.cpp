#include "GText.h"

GText::GText(std::string content, sf::Font * font, STYLE style, float x, float y)
: /*sf::Text(), */_font(font) {
    setString(content);
    setFont(*_font);
    setPosition(x, y);
    resetStyle(style);
}
GText::~GText() {
}

/*inline*/ void GText::_default() {
    setColor(sf::Color::White);
    setCharacterSize(24);
    setStyle(sf::Text::Regular);
}
/*inline*/ void GText::title() {
    setColor(sf::Color::Blue);
    setCharacterSize(32);
}
// inline void GText::untitle() {
//     setColor(sf::Color::White);
//     setCharacterSize(24);
// }
/*inline*/ void GText::subtitle() {
    setColor(sf::Color::Green);
    setCharacterSize(32);
}
// inline void GText::unsubtitle() {
//     setColor(sf::Color::White);
//     setCharacterSize(24);
// }
/*inline*/ void GText::validate() {
    setColor(sf::Color::Red);
}
/*inline*/ void GText::unvalidate() {
    setColor(sf::Color::White);
}
/*inline*/ void GText::select() {
    setStyle(sf::Text::Underlined);
}
/*inline*/ void GText::unselect() {
    setStyle(sf::Text::Regular);
}

void GText::resetStyle(STYLE newStyle) {
    _style = newStyle;
    _default();
    if (flagSetted(TITLE)) {
        title();
    } else if (flagSetted(SUBTITLE)) {
        subtitle();
    } else {
        flagSetted(SELECTED) ? select() : unselect();
        flagSetted(VALIDATED) ? validate() : unvalidate();
    }
}

// inline bool GText::flagSetted(int v, int flag) {
//     return ((v & flag) == flag);
// }
inline bool GText::flagSetted(int flag) {
    return ((_style & flag) == flag);
}

// inline void GText::applyStyle() {
//     if (flagSetted(TITLE) {
//         setCharacterSize(32);
//         setColor(sf::Color::Green);
//         setStyle(sf::Text::Bold);
//     }
//     if (flagSetted(SUBTITLE) {
//         setCharacterSize(24);
//         setColor(sf::Color::Green);
//         setStyle(sf::Text::Bold);
//     }
//     if (flagSetted(SELECTED) {
//         if (!(flagSetted(getStyle(), sf::Text::Underlined)))
//         setStyle(getStyle() | sf::Text::Underlined);//que se passe t il s'il est deja souligné ?
//     }
//     if (flagSetted(VALIDATED) {
//         setColor(sf::Color::Red);
//     }
// }

// inline void GText::title() {
//     _style = TITLE;
//     setCharacterSize(32);
//     setColor(sf::Color::Green);
//     setStyle(sf::Text::Bold | sf::Text::Underlined);
// }
// inline void GText::subtitle() {
//     _style = SUBTITLE;
//     setCharacterSize(24);
//     setColor(sf::Color::Green);
//     setStyle(sf::Text::Bold);
// }
// inline void GText::select() {
//     _style = SELECTED;
//     setCharacterSize(24);
//     setColor(sf::Color::Blue);
//     setStyle(sf::Text::Regular);
// }
// inline void GText::unselect() {
//     _style = UNSELECTED;
//     setCharacterSize(24);
//     setColor(sf::Color::White);
//     setStyle(sf::Text::Regular);
// }
// inline void GText::validate() {
//     _style = VALIDATED;
//     setCharacterSize(24);
//     setColor(sf::Color::Red);
//     setStyle(sf::Text::Underlined);
// }
