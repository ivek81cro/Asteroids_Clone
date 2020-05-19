#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Entity.h"

class Asteroid : public Entity
{
  public:
    Asteroid(const float& x, const float& y, const int& level, sf::Texture& texture_sheet,
             const float& scale_factor, const float& game_level);
    virtual ~Asteroid();

    Asteroid(const Asteroid&) = delete;
    void operator=(const Asteroid&) = delete;

    //Functions
    void                SetScale(const int& leve);
    void                SetAlive(const bool& is_alive);
    void                Update(const float& delta, const sf::Vector2u& window_size);
    const int&          GetLevel() const;
    const sf::Vector2f& Getposition() const;
    const int           GetPoints() const;

  private:
    //Variables
    int   level_;
    int   points_;
    float rescale_factor_;

    //Initializer functions
    void InitVariables();
    void InitComponents(sf::Texture& texture_sheet);
};

#endif
