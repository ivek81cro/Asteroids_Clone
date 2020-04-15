#ifndef HITBOXCOMPONENT_H_
#define HITBOXCOMPONENT_H_

#include "SFML/Graphics.hpp"

class HitboxComponent
{
  public:
    HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    virtual ~HitboxComponent();

    //Functions
    bool CheckIntersect(const sf::FloatRect& frect);

    void Update();
    void Render(sf::RenderTarget& target);

  private:
    sf::Sprite&        sprite_;
    sf::RectangleShape hitbox_;

    float offset_x_;
    float offset_y_;
};

#endif // !HITBOXCOMPONENT_H_
