#ifndef HITBOXCOMPONENT_H_
#define HITBOXCOMPONENT_H_

class HitboxComponent
{
  public:
    HitboxComponent(sf::Sprite& sprite, float& width, float& factor);
    virtual ~HitboxComponent();

    //Functions
    sf::CircleShape& GetHitbox();

    void Update();
    void Render(sf::RenderTarget& target);

  private:
    sf::Sprite&     sprite_;
    sf::CircleShape hitbox_;

    float factor_;
};

#endif // !HITBOXCOMPONENT_H_
