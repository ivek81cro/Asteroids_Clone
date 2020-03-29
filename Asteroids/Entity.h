#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/Graphics.hpp>

class Entity
{
  public:
    virtual void update(sf::Time& elapsedTime, const sf::Event& event);
    virtual void onEvent(const sf::Event& event);

    bool        isAlive();
    void        draw(sf::RenderTarget& target, sf::RenderStates states) const;
    float       getRadius();
    int         getId();
    sf::Sprite& getSprite();

  protected:
    bool       is_alive;
    float      radius;
    int        id;
    int        mMoveRect    = 0;
    int        mElapsedTime = 0;
    sf::Sprite sprite;
};

#endif
