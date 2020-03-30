#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/Graphics.hpp>

class Entity
{
  public:
    Entity()=default;
    Entity(int moveRect, float elapsedTime, int id, float radius, bool isAlive);

    virtual void Update(sf::Time& elapsedTime, const sf::Event& event);
    virtual void OnEvent(const sf::Event& event);

    bool        IsAlive();
    void        Draw(sf::RenderTarget& target, sf::RenderStates states) const;
    float       GetRadius();
    int         GetId();
    sf::Sprite& GetSprite();

  protected:
    bool       mAlive;
    float      mRadius;
    int        mId;
    int        mMoveRect;
    float      mElapsedTime;
    sf::Sprite mSprite;
};

#endif
