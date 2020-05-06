#ifndef ENTITY_H_
#define ENTITY_H_

#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "MovementComponent.h"

class Entity
{
  public:
    Entity();
    virtual ~Entity();

    //Component functions
    void CreateMovementComponent(const float max_velocity, const float acceleration, const float deceleration,
                                 const float& angle);
    void CreateAnimationComponent(sf::Texture& texture_sheet);
    void CreateHitboxComponent(sf::Sprite& sprite, float width, float factor = 1.f);

    //Functions
    virtual void                   SetPosition(const float x, const float y);
    virtual void                   Move(const float dir_x, const float dir_y, const float& delta);
    virtual const bool             IsAlive();
    virtual void                   SetAlive(bool is_alive);
    virtual const bool             IsExploding();
    virtual const std::string      GetName();
    virtual const sf::CircleShape& GetHitbox() const;
    virtual const bool             CheckCollision(const sf::CircleShape& other);
    virtual const int&             GetLevel() const;
    virtual const sf::Vector2f&    Getposition() const;

    virtual void Update(const float& delta, const sf::Vector2u& window_size);
    virtual void Render(sf::RenderTarget& target);

  protected:
    //Variables
    sf::Sprite sprite_;

    HitboxComponent* hitbox_component_;

    std::string name_;
    std::string animation_name_;

    bool alive_;
    bool exploding_;

    int      asteroid_level_;
    float    scale_factor_;
    float    game_level_;
    float    max_velocity_;
    float    acceleration_;

    MovementComponent*  movement_component_;
    AnimationComponent* animation_component_;

  private:
    //Initializer functions
    void InitVariables();
};

#endif
