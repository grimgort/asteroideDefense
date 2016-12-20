#ifndef BASE_H
#define BASE_H

#include <Entity.h>
#include <Command.h>
#include <ResourceIdentifiers.h>
#include <Animation.h>
#include <TextNode.h>

#include <SFML/Graphics/Sprite.hpp>

/////////////////////////////////////////////////
/// \file Base.h
/// \brief Créer une base
/// \author Fred
/// \version 0.0
///
/// Les base hérite des Entity. C'est un objet immobile avec des PV.
///
/// Généralité : Pour Rajouter un objet qui hérites des entités,
/// Il faut compléter les fichier suivant : DataTable.h, DataTable.cpp,
/// RessourceIdentifier.h
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/// \class Base
/// \brief Classe representant les bases
///
/// La classe gère les bases. Se sont les objet immobile a défendre
/// pour le joueur ou à détruire pour l'équipe adverse.
/////////////////////////////////////////////////

class Base : public Entity
{
public:
    enum Type
    {
        BaseTypeUn,
        TypeCount
    };

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /// \param type : Type pouvant prendre la valeur BaseTypeUn ou TypeCount.
    /// Les type doivent être déclaré dans DataTable
    /// \param &textures : Référence de la texture de la base contenu
    /// dans TextureHolder.
    /// \param &fonts : Référence du type de font contenu
    /// dans FontHolder
    /////////////////////////////////////////////////
    Base (Type type, const TextureHolder &textures,
          const FontHolder &fonts);

    /////////////////////////////////////////////////
    /// \brief Retourne la catégorie de la base
    ///
    /// Retourne une catégorie Base. (Il faut certainement faire
    /// une catégorie base allié et ennemy... a corriger)
    /////////////////////////////////////////////////
    virtual unsigned int getCategory() const;

    /////////////////////////////////////////////////
    /// \brief Retourne la position global du sprite
    ///
    /// Retourne une catégorie Base. (Il faut certainement faire
    /// une catégorie base allié et ennemy... a corriger)
    /////////////////////////////////////////////////
    virtual sf::FloatRect getBoundingRect() const;

    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /// \brief Détruit le noeud base dans la mémoire
    ///
    /// Aprés son utilisation, cet objet n'existe plus.
    /////////////////////////////////////////////////
    virtual void remove();

    /////////////////////////////////////////////////
    /// \brief Dit si l'objet doit être détruit à cet frame
    ///
    /// \return Vrai si l'objet est détruit et l'explosion terminé
    /////////////////////////////////////////////////
    virtual bool isMarkedForRemoval() const;

private:
    /////////////////////////////////////////////////
    /// \brief Trace la texture de la base
    ///
    /// Vérifie si l'objet est détruit ou pas. Dans le premier cas,
    /// l'explosion est montré. Dans le deuxième, la base est montré.
    /////////////////////////////////////////////////
    virtual void drawCurrent (sf::RenderTarget & target
                              , sf::RenderStates states) const;
    virtual void updateCurrent (sf::Time dt, CommandQueue& commands);
    //    void updateTexts();

private:
    ///> Contient le type de la base (Base)
    Type m_type;

    ///> Contient le sprite de la base
    sf::Sprite m_sprite;

    ///> Vrai si l'animation explosion doit être montré
    bool m_showExplosion;

    ///> Vrai si l'animation explosion doit commencer
    bool m_explosionBegan;

    ///> Animation de l'explosion des bases
    Animation m_explosion;

};

#endif // BASE_H
