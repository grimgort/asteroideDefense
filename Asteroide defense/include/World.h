#ifndef WORLD_H
#define WORLD_H

#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.h>
#include <SceneNode.h>
#include <SpriteNode.h>
#include <Aircraft.h>
#include <CommandQueue.h>
#include <Command.h>
#include <Pickup.h>
#include <BloomEffect.h>
#include <SoundPlayer.h>
#include <NetworkProtocol.h>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>



#include <array>
#include <queue>
// Forward declaration
namespace sf
{
class RenderTarget;
}

class NetworkNode;


class World : private sf::NonCopyable
{
public:
    explicit World (sf::RenderTarget& outputTarget, FontHolder& fonts,
                    SoundPlayer& sounds, bool networked = false);
    void update (sf::Time dt);
    void draw();

    sf::FloatRect getViewBounds() const;
    sf::FloatRect getViewBoundsTeam2() const;

    CommandQueue& getCommandQueue();

    /////////////////////////////////////////////////
    /// \brief Ajoute un avion de type joueur
    ///
    /// Crer un pointeur unique d'un avion joueur et d�fini sa position,
    /// son identifiant et son noeud p�re.
    /////////////////////////////////////////////////
    Aircraft* addAircraft (int identifier);

    void removeAircraft (int identifier);
    void setCurrentBattleFieldPosition (float lineY);
    void setWorldHeight (float height);

    void addEnemy (Aircraft::Type type, float relX, float relY);
    void sortEnemies();

    bool hasAlivePlayer() const;
    bool hasPlayerReachedEnd() const;

    void setWorldScrollCompensation (float compensation);

    Aircraft* getAircraft (int identifier) const;
    sf::FloatRect getBattlefieldBounds() const;
    sf::FloatRect getWorldBounds() const;

    void createPickup (sf::Vector2f position, Pickup::Type type);
    bool pollGameAction (GameActions::Action& out);

private:
    void loadTextures();
    void adaptPlayerPosition();
    void adaptPlayerVelocity();

    /////////////////////////////////////////////////
    /// \brief Calcul la grille de collision
    ///
    /// Calcul les dimensions des rectangles en fonction du nombre
    /// de coupe en X(m_nbCutX) et Y(m_nbCutY) d�finit par le d�velloper.
    /// La m�thode compl�te donc le vecteur m_grilleDeCollision qui
    /// contient l'ensemble des rectangle de la grille de collision.
    ///
    /////////////////////////////////////////////////
    void grilleDeCollision();

    /////////////////////////////////////////////////
    /// \brief D�clenche le calcul des collision
    ///
    /// R�cup�re la grille de collision et demande la position des
    /// noeud dans la grille, regarde si les noeud rentre en collision
    /// et applique l'effet des collision.
    ///
    /// Id�e : Il est peut �ter int�rr�ssant d'en faire une classe (h�ritant
    /// du world???)
    ///
    /////////////////////////////////////////////////
    void handleCollisions();
    void updateSounds();

    /////////////////////////////////////////////////
    /// \brief Construit les objet de la scene � l'�tat initial
    ///
    /// Permet de construire l'ensemble des objet de la scene � l'�tat
    /// initial. C'est donc ici qu'il faut rajouter les objets qui doivent
    /// �tre construit au d�but de la scene. Elle est donc invoquer
    /// dans le constructeur de la classe World.
    /////////////////////////////////////////////////
    void buildScene();
    void addEnemies();
    void spawnEnemies();
    void destroyEntitiesOutsideWorld();
    void guideMissiles();

private:
    enum Layer
    {
        background,
        LowerAir,
        UpperAir,
        LayerCount
    };

    struct SpawnPoint
    {
        SpawnPoint (Aircraft::Type type, float x, float y) :
            type (type),
            x (x),
            y (y)
        {
        }

        Aircraft::Type type;
        float x;
        float y;
    };


private:
    sf::RenderTarget& m_target;
    sf::RenderTexture m_sceneTexture;

    sf::View m_worldView;
    sf::View m_viewTeam2;

    TextureHolder m_textures;
    FontHolder& m_fonts;
    SoundPlayer& m_sounds;

    SceneNode m_sceneGraph;
    //m_sceneLayers est un conteneur compos� de sceneNode associ� � un layer count.
    //Ici, il y a donc un sceneNode pour background, un autre pour Air, etc...
    std::array<SceneNode*, LayerCount> m_sceneLayers;
    CommandQueue m_commandQueue;

    sf::FloatRect m_worldBounds;
    sf::Vector2f m_spawnPosition;
    float m_scrollSpeed;
    float m_scrollSpeedCompensation;
    std::vector<Aircraft*>  m_playerAircrafts;

    std::vector<SpawnPoint> m_enemySpawnPoints;
    std::vector<Aircraft*> m_activeEnemies;

    BloomEffect m_bloomEffect;

    bool m_networkedWorld;
    NetworkNode* m_networkNode;
    SpriteNode* m_finishSprite;

    ///> Vector contenant l'ensemble des rectangles composant la grille
    ///> de collision.
    std::vector<sf::FloatRect> m_grilleDeCollision;

    ///> Nombre de case de collision en Y
    sf::Int32 m_nbCutY;
    ///> Nombre de case de collision en X
    sf::Int32 m_nbCutX;

};

#endif // WORLD_H
