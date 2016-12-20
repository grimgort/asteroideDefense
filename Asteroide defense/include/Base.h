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
/// \brief Cr�er une base
/// \author Fred
/// \version 0.0
///
/// Les base h�rite des Entity. C'est un objet immobile avec des PV.
///
/// G�n�ralit� : Pour Rajouter un objet qui h�rites des entit�s,
/// Il faut compl�ter les fichier suivant : DataTable.h, DataTable.cpp,
/// RessourceIdentifier.h
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/// \class Base
/// \brief Classe representant les bases
///
/// La classe g�re les bases. Se sont les objet immobile a d�fendre
/// pour le joueur ou � d�truire pour l'�quipe adverse.
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
    /// Les type doivent �tre d�clar� dans DataTable
    /// \param &textures : R�f�rence de la texture de la base contenu
    /// dans TextureHolder.
    /// \param &fonts : R�f�rence du type de font contenu
    /// dans FontHolder
    /////////////////////////////////////////////////
    Base (Type type, const TextureHolder &textures,
          const FontHolder &fonts);

    /////////////////////////////////////////////////
    /// \brief Retourne la cat�gorie de la base
    ///
    /// Retourne une cat�gorie Base. (Il faut certainement faire
    /// une cat�gorie base alli� et ennemy... a corriger)
    /////////////////////////////////////////////////
    virtual unsigned int getCategory() const;

    /////////////////////////////////////////////////
    /// \brief Retourne la position global du sprite
    ///
    /// Retourne une cat�gorie Base. (Il faut certainement faire
    /// une cat�gorie base alli� et ennemy... a corriger)
    /////////////////////////////////////////////////
    virtual sf::FloatRect getBoundingRect() const;

    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /// \brief D�truit le noeud base dans la m�moire
    ///
    /// Apr�s son utilisation, cet objet n'existe plus.
    /////////////////////////////////////////////////
    virtual void remove();

    /////////////////////////////////////////////////
    /// \brief Dit si l'objet doit �tre d�truit � cet frame
    ///
    /// \return Vrai si l'objet est d�truit et l'explosion termin�
    /////////////////////////////////////////////////
    virtual bool isMarkedForRemoval() const;

private:
    /////////////////////////////////////////////////
    /// \brief Trace la texture de la base
    ///
    /// V�rifie si l'objet est d�truit ou pas. Dans le premier cas,
    /// l'explosion est montr�. Dans le deuxi�me, la base est montr�.
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

    ///> Vrai si l'animation explosion doit �tre montr�
    bool m_showExplosion;

    ///> Vrai si l'animation explosion doit commencer
    bool m_explosionBegan;

    ///> Animation de l'explosion des bases
    Animation m_explosion;

};

#endif // BASE_H
