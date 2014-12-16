#include "Options.h"

Options::Options(std::string const& name, sf::RenderWindow& window, sf::Font * font,
            int selected)
    : _name(name), _selected(selected), _validated(selected), _window(window), _font(font)
{
    _texts.push_back(new GText(name, _font, GText::SUBTITLE));
}
Options::~Options() {
    _texts.clear();
}
void Options::draw()
{
    std::for_each(_texts.begin(), _texts.end(), [&](GText * text){
        _window.draw(*text);
    });
}

void    Options::setSelected(unsigned int i)
{
    if (i >= 1 && i < _texts.size())
    {
        if (_texts[_selected]->style() != GText::VALIDATED)
            _texts[_selected]->unselect();
        _selected = i;
        if (_texts[_selected]->style() != GText::VALIDATED)
            _texts[_selected]->select();
    }
}
void    Options::selectLeft()
{
    setSelected(_selected - 1);
}
void    Options::selectRight()
{
    setSelected(_selected + 1);
}
void    Options::validate()
{
    unsigned int i = 0;
    std::for_each(_texts.begin(), _texts.end(), [&](GText * text){
        if (i != 0 && i != _selected)
            selectedText()->unselect();
    });
    _validated = _selected;
    selectedText()->validate();
}
void    Options::focus()
{
    selectedText()->select();
}
void    Options::unfocus()
{
    unsigned int i = 0;
    std::for_each(_texts.begin(), _texts.end(), [&](GText * text){
        if (i != 0 && text->style() != GText::VALIDATED)
            selectedText()->unselect();
    });
}
void    Options::setY(int y)
{
    unsigned int i = 0;
    std::for_each(_texts.begin(), _texts.end(), [&](GText * text){
        text->setPosition(_window.getSize().x * i++ / _texts.size(), y);
    });
}

GText*     Options::selectedText() const {
    assert(_texts.size() > 1);
    assert(_selected >= 1 && _selected < _texts.size());
    return _texts[_selected];
}
GText*     Options::validatedText() const {
    assert(_texts.size() > 1);
    assert(_validated >= 1 && _validated < _texts.size());
    return _texts[_validated];
}


template<>
bool     Options::selectedValue<>() const {
    assert(_values.size() > 0);
    assert((_selected - 1 ) >= 0 && (_selected - 1 ) < _values.size());
    return (_values[_selected - 1] == "true");
}
template<>
bool     Options::validatedValue<>() const {
    assert(_values.size() > 0);
    assert((_validated - 1 ) >= 0 && (_validated - 1 ) < _values.size());
    return (_values[_validated - 1] == "true");
}
