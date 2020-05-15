#ifndef MOVEMENTCOMPONENT_H_
#define MOVEMENTCOMPONENT_H_

enum class Movement_e
{
    Ship,
    Asteroid,
    Enemy_ufo,
    Bullet,
    Life
};

class MovementComponent
{
  public:
    MovementComponent(sf::Sprite& sprite, const float& max_velocity, const float& acceleration,
                      const float& deceleration, const float& angle, const Movement_e& name);
    virtual ~MovementComponent();

    //Accessors
    const float& GetMaxVelocity() const;
    const sf::Vector2f& GetVelocity() const;

    //Functions
    void Move(const float x, const float y, const float& delta);
    void CheckMaxVelocity(const float& delta);
    void CheckPosition(const sf::Vector2u& window_size);
    void Update(const float& delta, const sf::Vector2u& window_size);

  private:
    sf::Sprite&  sprite_;
    sf::Vector2f direction_;
    Movement_e  name_;

    float max_velocity_;
    float acceleration_;
    float deceleration_;
    float angle_;

    sf::Vector2f velocity_;

    //Initializer functions
};
#endif
