#include "PresentationState.h"
#include "utility"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

PresentationState::PresentationState(StateStack& stack, Context context)
    : State (stack, context)
{
    m_backgroundSprite.setTexture (context.textures->get (
                                       Textures::PresentationScreen));
}

void PresentationState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.draw (m_backgroundSprite);
}

bool PresentationState::update (sf::Time)
{
    return true;
}

bool PresentationState::handleEvent (const sf::Event& event)
{
    sf::Clock m_spriteClock;
    float Timer=2.;
    m_spriteClock.restart();
    //Lorsque le compteur est à 2, on passe à l'état Titre
    while (m_spriteClock.getElapsedTime().asSeconds()<Timer)
    {
    }
    requestStackPop();
    requestStackPush (States::Title);


    return true;
}
