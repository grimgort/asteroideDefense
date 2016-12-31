#ifndef STATESTACK_H
#define STATESTACK_H


#include <State.h>
#include <StateIdentifiers.h>
#include <ResourceIdentifiers.h>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

namespace sf
{
class Event;
class RenderWindow;
}

class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear,
    };
public:
    explicit StateStack(State::Context context);

    template<typename T>
    void registerState(States::ID stateID);
    template<typename T, typename Param1>
    void registerState(States::ID stateID, Param1 arg1);

    void update(sf::Time dt);
    void draw();
    void handleEvent(const sf::Event& event);

    void pushState(States::ID stateID);
    void popState();
    void clearStates();

    bool isEmpty() const;

private:
    State::Ptr createState(States::ID stateID);
    void applyPendingChanges();

private:
    struct PendingChange
    {
        explicit PendingChange(Action action,  States::ID stateID = States::None);
        Action action;
        States::ID stateID;
    };

private:
    std::vector<State::Ptr> m_stack; //pointeur des classes state
    std::vector<PendingChange> m_pendingList;
    State::Context m_context;
    //Contient l'ensemble des �tats possible
    std::map<States::ID, std::function<State::Ptr()>> m_factories;
};

template <typename T>
void StateStack::registerState(States::ID stateID)
{
    m_factories[stateID] = [this] ()
    {
        return State::Ptr(new T(*this, m_context));
    };
}


template <typename T, typename Param1>
void StateStack::registerState(States::ID stateID, Param1 arg1)
{
    m_factories[stateID] = [this, arg1] ()
    {
        return State::Ptr(new T(*this, m_context, arg1));
    };
}

#endif // STATESTACK_H
