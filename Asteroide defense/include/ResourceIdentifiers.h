#ifndef RESOURCEIDENTIFIERS_H_INCLUDED
#define RESOURCEIDENTIFIERS_H_INCLUDED


// Conteneur "sf" est le conteneur d�finissant les classes de SFML
namespace sf
{
class Texture;
class Font;
class Shader;
class SoundBuffer;
class Image;
}

namespace Textures
{
enum ID
{
    Entities,
    Space,
    PresentationScreen,
    TitleScreen,
    Buttons,
    Explosion,
    Particle,
    FinishLine,
    Base,
    AsteroideUn,
};
}

namespace Shaders
{
enum ID
{
    BrightnessPass,
    DownSamplePass,
    GaussianBlurPass,
    AddPass,
};
}

// Pareil que pour "Textures" mais avec la classe Font de SFML
namespace Fonts
{
enum ID
{
    Main,
};
}

namespace SoundEffect
{
enum ID
{
    AlliedGunfire,
    EnemyGunfire,
    Explosion1,
    Explosion2,
    LaunchMissile,
    Button,
    LaunchAsteroideUn,
};
}

namespace Music
{
enum ID
{
    MenuTheme,
    MissionTheme,
};
}

namespace Image
{
enum ID
{
    Icon,
};
}


// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;
/*
    ResourceHolder<sf::Texture, Textures::ID> TextureHolder = Template de classe ResourceHolder d�finit
    en tant que conteneur des classes Texture de SFML et nomm� comme classe RessourceHolder.
    typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder = Pareil mais pour la classe Font de SFML
*/
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID> ShaderHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID> SoundBufferHolder;
typedef ResourceHolder<sf::Image, Image::ID> ImageHolder;

#endif // RESOURCEIDENTIFIERS_H_INCLUDED
