#pragma once

#include "GText.h"
#include <algorithm>
#include <sstream>
#include <iostream>

class Options
{
public:
    Options(std::string const& name, sf::RenderWindow& window, sf::Font * font,
                int selected = 1);
    ~Options();

    void    draw();

    template<typename T>
    void    addValue(T v)
    {
        std::stringstream stream;
        std::string str;
        stream << std::boolalpha << v;
        stream >> str;
        _values.push_back(str);
        _texts.push_back(new GText(str, _font));
    }
    template<typename T>
    void    addValues(std::vector<T> values)//set values
    {
        for (typename std::vector<T>::iterator it = values.begin(); it < values.end(); ++it)
            addValue(*it);
        selectedText()->select();
        validatedText()->validate();
    }
    
    //Setters
    void    setSelected(unsigned int i);
    void    selectLeft();
    void    selectRight();
    void    validate();
    void    focus();
    void    unfocus();
    void    setY(int y);

    //Getters
    inline std::string const&     name() const {
        return _name;
    }
    inline int     selected() const {
        return _selected;
    }
    template<typename T>
    T     selectedValue() const {
        assert(_values.size() > 0);
        assert((_selected - 1) >= 0 && (_selected - 1) < _values.size());
        return _values[_selected - 1];
    }
    template<typename T>
    T     validatedValue() const {
        assert(_values.size() > 0);
        assert((_validated - 1 ) >= 0 && (_validated - 1 ) < _values.size());

        std::stringstream stream;
        T v;
        stream << _values[_validated - 1];
        stream >> std::noboolalpha >> v;
        return v;
    }

private:
    std::string         _name;
    std::vector<std::string>      _values;
    unsigned int        _selected;
    unsigned int        _validated;
    sf::RenderWindow&   _window;
    std::vector<GText *>  _texts;
    sf::Font *            _font;

    GText*     selectedText() const;
    GText*     validatedText() const;
};
