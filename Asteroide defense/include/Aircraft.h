#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <Entity.h>
#include <Command.h>
#include <ResourceIdentifiers.h>
#include <Projectile.h>
#include <Asteroide.h>
#include <TextNode.h>
#include <Animation.h>

#include <SFML/Graphics/Sprite.hpp>

/*
    Aircraft est la classe associée aux textures d'avions Eagle et raptor. Elle hérite de la class Entity
    qui définit la position et vitesse de l'image. Elle permet donc de spécifier des méthodes particulière aux Aircraft,
    et nottament si l'avion est le joueur ou l'ennemi.
*/
/////////////////////////////////////////////////
/// \file Aircraft.h
/// \brief Creer un element de type Avion
/// \author Fred
/// \version 0.0
///
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/// \class Aircraft
/// \brief Classe des avions (aircraft)
///
/// Permet de creer les objets de type avions. Ils peuvent être joueur ou PNJ.
/// Les statistiques des avions sont contenues dans une database
///
/////////////////////////////////////////////////
class Aircraft : public Entity
{
public:
/////////////////////////////////////////////////
/// \brief Types de aircraft
///
/// Enumére les differents type de aircraft
/// Les statistiques des avions sont contenues dans une Datatable(DataTables.cpp)
///
/////////////////////////////////////////////////
    enum Type
    {
        Eagle,
        Raptor,
        Avenger,
        TypeCount
    };

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /// \param type : Type de l'avion définit dans l'enum Type
    /// \param &textures : Référence du conteneur de texture de l'avion
    /// \param &fonts : Référence du conteneur de fonts(texte) de l'avion
    ///
    /////////////////////////////////////////////////
    Aircraft (Type type, const TextureHolder &textures,
              const FontHolder &fonts);
    /////////////////////////////////////////////////
    /// \return Retourne la catégorie de l'avion
    /////////////////////////////////////////////////
    virtual unsigned int getCategory() const;
    /////////////////////////////////////////////////
    /// \return Retourne la position global de l'avion
    /////////////////////////////////////////////////
    virtual sf::FloatRect getBoundingRect() const;
    /////////////////////////////////////////////////
    /// \brief
    /// \param
    /// \return
    /////////////////////////////////////////////////
    virtual void remove();
    /////////////////////////////////////////////////
    /// \brief
    /// \param
    /// \return
    /////////////////////////////////////////////////
    virtual bool isMarkedForRemoval() const;
    /////////////////////////////////////////////////
    /// \brief Dit si l'avion est allié ou pas
    /// \param
    /// \return True si l'avion est de type Eagle.
    /////////////////////////////////////////////////
    bool isAllied() const;
    /////////////////////////////////////////////////
    /// \brief Recupere la vitesse de l'avion
    /// \return Retourne la vitesse de l'avion
    /////////////////////////////////////////////////
    float getMaxSpeed() const;
    /////////////////////////////////////////////////
    /// \brief Desactive les pickups
    /// \return False for m_pickupsEnabled attribute
    /////////////////////////////////////////////////
    void disablePickups();
    /////////////////////////////////////////////////
    /// \brief Increase one level of speed fire
    /////////////////////////////////////////////////
    void increaseFireRate();
    /////////////////////////////////////////////////
    /// \brief Increase number of spread
    /////////////////////////////////////////////////
    void increaseSpread();
    /////////////////////////////////////////////////
    /// \brief Collect pickup with missile ammo
    /////////////////////////////////////////////////
    void collectMissiles (unsigned int count);
    /////////////////////////////////////////////////
    /// \brief Say if the aircraft firing.
    /// \param count : number of ammo to give at aircraft
    ///
    /// When aircraft firing it can't fire again
    /////////////////////////////////////////////////
    void fire();
    /////////////////////////////////////////////////
    /// \brief Commande to launch Missile
    /// It's impossible to launch missile before amount of time
    /////////////////////////////////////////////////
    void launchMissile();
    /////////////////////////////////////////////////
    /// \brief Say to launch Asteroid of type one
    /////////////////////////////////////////////////
    void launchAsteroideUn();
    /////////////////////////////////////////////////
    /// \brief Play sound localize on aircraft position
    /// \param command : Command Queue who store command to play
    /// \param effect : Sound effect to play
    /////////////////////////////////////////////////
    void playLocalSound (CommandQueue& commands, SoundEffect::ID effect);
    /////////////////////////////////////////////////
    /// \brief Get aircraft identifier
    /// \return Aircraft identifier
    /////////////////////////////////////////////////
    int getIdentifier();
    /////////////////////////////////////////////////
    /// \brief Set aircraft identifier
    /// \param aircraft identifier
    /////////////////////////////////////////////////
    void setIdentifier (int identifier);
    /////////////////////////////////////////////////
    /// \brief
    /// \param
    /// \return
    /////////////////////////////////////////////////
    int getMissileAmmo() const;
    /////////////////////////////////////////////////
    /// \brief
    /// \param
    /// \return
    /////////////////////////////////////////////////
    void setMissileAmmo (int ammo);

private:
    /*
        Dessine la texture de l'avion sur la fenêtre target(RenderTarget) avec les éventuel transformation de "RenderStates".
    */
    virtual void drawCurrent (sf::RenderTarget& target,
                              sf::RenderStates states) const;
    virtual void updateCurrent (sf::Time dt, CommandQueue& commands);
    void updateMovementPattern (sf::Time dt);
    void checkPickupDrop (CommandQueue& commands);
    void checkProjectileLaunch (sf::Time dt, CommandQueue& commands);

    void createBullets (SceneNode& node,
                        const TextureHolder& textures) const;
    void createProjectile (SceneNode& node, Projectile::Type type,
                           float XOffset, float yOffset, const TextureHolder& textures) const;
    void createPickup (SceneNode& node,
                       const TextureHolder& textures) const;
    void createAsteroideUn (SceneNode& node, Projectile::Type type,
                            float XOffset, float yOffset, const TextureHolder& textures) const;

    void updateTexts();
    void updateRollAnimation();

private:
    ///> Type de l'avion contenue dans l'enume Type
    Type m_type;
    ///> Image(Sprite) de l'avion
    sf::Sprite m_sprite;
    ///> Animation de l'explosion des avions à la destruction
    Animation m_explosion;
    ///> Commande pour l'action "tirer Balle"
    Command m_fireCommand;
    ///> Commande pour l'action "tirer Missile"
    Command m_missileCommand;
    ///> Commande pour l'action "tirer Asteroide"
    Command m_asteroideUnCommand;
    ///> Temps entre chaque tire de Balle
    sf::Time m_fireCountDown;
    ///> True si l'avion ne peut pas tirer une autre balle (déjà entrain de tirer)
    bool m_isFiring;
    ///> True si l'avion ne peut pas tirer un autre missile (déjà entrain de tirer)
    bool m_isLaunchingMissile;
    ///> True si l'avion ne peut pas tirer une autre astéroide (déjà entrain de tirer)
    bool m_isLaunchingAsteroideUn;
    ///> True si l'animation de l'explosion de l'avion est en cours d'execution.
    bool m_showExplosion;
    ///> True si l'animation de l'explosion  viens de commencer (permet de jouer les sons,ect...)
    bool m_explosionBegan;
    ///> True si l'avion loot un item bonus
    bool m_spawnedPickup;
    ///> True si l'avions peut lacher un item bonus
    bool m_pickupsEnabled;
    ///> Niveau de la vitesse de tir
    int m_fireRateLevel;
    ///> Niveau du nombre de tir
    int m_spreadLevel;
    ///> Nombre de munition
    int m_missileAmmo;
    ///> Commmande pour lacher un intem bonus
    Command m_dropPickupCommand;
    ///> Distance parcourue pas les balles
    float m_travelledDistance;
    ///> direction des balles
    std::size_t m_directionIndex;
    ///> affichage de la vie de l'avion
    TextNode* m_healthDisplay;
    ///> Affichage du nombre de missile
    TextNode* m_missileDisplay;
    ///> identifiant de l'avion
    int m_identifier;
};

#endif // AIRCRAFT_H
