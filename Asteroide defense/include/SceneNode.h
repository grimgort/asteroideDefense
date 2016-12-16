#ifndef SCENENODE_H
#define SCENENODE_H

#include <Category.h>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <set>
#include <memory>
#include <utility>
#include <map>

/////////////////////////////////////////////////
/// \file SceneNode.h
/// \brief Créer un noeud de type scene
/// \author Fred
/// \version 0.0
///
/////////////////////////////////////////////////

struct Command;
class CommandQueue;

/*
Permet de définir les noeuds de la scéne (position des objets dans la fenêtre).
Chaque noeud est unique(nonCopyable), peuvent être dessiner(Drawable) et modifier(Transformable).
Les méthodes sont écrites en considérant le noeud manipulé comme le noeud parent
*/
/////////////////////////////////////////////////
/// \class SceneNode
/// \brief Classe representant le sceneNode
///
/// La classe gère les noeuds représantant l'ensemble des objets du jeux.
/// Par exemple, les avions, les projectiles, les pickup sont hérite des sceneNode
/// Les méthodes de cette classe permettent notamment de gérer la création et
/// la destruction des objets (ou noeud).
///
/// L'architecture des noeuds est un arbre. C'est à dire qu'il y a un noeud
/// principal qui posséde plusieurs branche avec d'autres noeud, etc...
///
/////////////////////////////////////////////////
//        *---*---*
//        |
// *------*   *---*
//        |   |
//        *---*---*
/////////////////////////////////////////////////
class SceneNode
    : public sf::Transformable
    , public sf::Drawable
    , private sf::NonCopyable
{
public:
    ///>Définit Ptr comme un pointeur unique de SceneNode
    typedef std::unique_ptr<SceneNode> Ptr;
    ///>Définit Pair comme une paire d'adresse de pointeur de SceneNode
    typedef std::pair<SceneNode*, SceneNode*> Pair;

public:
    /////////////////////////////////////////////////
    /// \brief Constructeur
    ///
    /// \param category : Type de catégorie (Aircraft, missile, etc...).
    /// De base, c'est une category de type None
    /// (qui n'est pas encore définit par héritage)
    /////////////////////////////////////////////////
    explicit SceneNode (Category::Type category =
                            Category::None);

    /////////////////////////////////////////////////
    /// \brief Rajoute un noeud enfant
    ///
    /// \param child : pointeur de l'enfant
    ///
    /// Permet de rajouter un noeud enfant à se sceneNode en completant
    /// le vecteur "m_children" avec le pointeur.
    /////////////////////////////////////////////////
    void attachChild (Ptr child);

    /////////////////////////////////////////////////
    /// \brief Détache un noeud de son père
    ///
    /// \param node : pointeur de l'enfant
    /// \return Renvoit le pointeur (objet) afin de le déplacer
    /// quelque part
    ///
    /// Permet de récupérer un pointeur (et ses enfants) en le détachant du noeud prére
    /////////////////////////////////////////////////
    Ptr detacheChild (const SceneNode& node);

    /////////////////////////////////////////////////
    /// \brief met à jour le noeud
    ///
    /// \param dt : pointeur de l'enfant
    /// \param commands : Comande dans la queue
    ///
    /////////////////////////////////////////////////
    void update (sf::Time dt, CommandQueue& commands);

     /////////////////////////////////////////////////
    /// \brief Retourne la position absolu du noeud dans le niveau
    ///
    /// \return Le vecteur 2D de la position
    ///
    /// Se base sur getWorldTransform qui récupére
    /// le "transform" de la scéne mère.
    /////////////////////////////////////////////////
    sf::Vector2f getWorldPosition() const;

    /////////////////////////////////////////////////
    /// \brief Retourne le transform du noeud mère (niveau)
    ///
    /// \return Retourne le transform du noeud mère (niveau)
    ///
    /////////////////////////////////////////////////
    sf::Transform getWorldTransform() const;


    void onCommand (const Command& command
                    , sf::Time dt);
    virtual unsigned int getCategory() const;

    virtual void checkNodePosition (const
                                    std::vector<sf::FloatRect>&virtualRectCollision
                                    , std::multimap<int, SceneNode*>&
                                    collisionListeToTest
                                    , sf::Int32 nbCutX
                                    , sf::Int32 nbCutY);

    void checkSceneCollision (
        std::multimap<int, SceneNode*>
        &collisionListeToTest
        , std::set<Pair> &collisionPairs);

    void removeWrecks();
    virtual sf::FloatRect getBoundingRect() const;
    virtual bool isMarkedForRemoval() const;
    virtual bool isDestroyed() const;
    virtual int getPositionCollision() const;

private:
    virtual void updateCurrent (sf::Time dt
                                , CommandQueue &commands);
    void updateChildren (sf::Time dt
                         , CommandQueue &commands);

    virtual void draw (sf::RenderTarget& target,
                       sf::RenderStates states) const;
    virtual void drawCurrent (sf::RenderTarget&
                              target, sf::RenderStates states) const;
    void drawChildren (sf::RenderTarget& target,
                       sf::RenderStates states) const;
    void drawBoundingRect (sf::RenderTarget& target,
                           sf::RenderStates states) const;

    bool matchesCategories (SceneNode& node1
                            , SceneNode& node2
                            , Category::Type type1
                            , Category::Type type2);

private:
    ///> Tableau contenant les pointeurs des noeuds enfants.
    std::vector<Ptr> m_children;
    ///> Adresse du noeud père.
    SceneNode* m_parent;
    Category::Type m_nodeCategory;

//protected:
//    int m_positionCollision;
};

bool collision (const SceneNode& lhs,
                const SceneNode& rhs);
float distance (const SceneNode& lhs,
                const SceneNode& rhs);


#endif // SCENENODE_H
