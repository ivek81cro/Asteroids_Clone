#ifndef SHIP_H_
#define SHIP_H_

#include "Entity.h"

class Ship : public Entity
{
  public:
    Ship(float x, float y, sf::Texture& texture_sheet, float scale);
    virtual ~Ship();

    Ship(const Ship&) = delete;
    void operator=(const Ship&) = delete;

    //Functions
    void  ResetAnimationName();
    void  Update(const float& delta, const sf::Vector2u& window_size);
    void  Move(const float dir_x, const float dir_y, const float& delta);
    void  SetAlive(bool is_alive);
    float GetAngle() const;

  private:
    //Variables
    float shield_timer_;
    int   lives_;

    //Initializer functions
    void InitVariables();
    void InitComponents(sf::Texture& texture_sheet);
};

#endif
