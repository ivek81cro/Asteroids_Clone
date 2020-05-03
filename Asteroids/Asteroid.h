#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Entity.h"

class Asteroid : public Entity
{
  public:
    Asteroid(float x, float y, int level, sf::Texture& texture_sheet, float scale_factor);
    virtual ~Asteroid();

    Asteroid(const Asteroid&) = delete;
    void operator=(const Asteroid&) = delete;

    //Functions
    void                SetScale(const int& leve);
    void                SetAlive(bool is_alive);
    void                Update(const float& delta, const sf::Vector2u& window_size);
    const int&          GetLevel() const;
    const sf::Vector2f& Getposition() const;
    const int           GetPoints() const;

  private:
    //Variables
    int   level_;
    int   points_;
    float rescale_factor_;
    float max_velocity_asteroid_;

    //Initializer functions
    void InitVariables();
    void InitComponents();
};

#endif
