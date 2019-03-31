#include "Gold.h"
#include "Utility.h"

Gold::Gold(int value, const FontHolder& fonts)
{
    m_value = value ;
//    sf::Font& font = fonts->get (Fonts::Main);

    std::unique_ptr<TextNode> goldDisplay (new TextNode (fonts, ""));
    m_goldDisplay = goldDisplay.get();

    updateTexts();
}

void Gold::soustractValue(int value)
{
    m_value -= value ;
}

void Gold::addValue(int value)
{
    m_value += value ;
}

int Gold::getValue()
{
    return m_value ;
}

void Gold::updateTexts()
{
    m_goldDisplay->setString (toString (getValue()) + " Gold");

    m_goldDisplay->setPosition (500.f, 500.f);

}
