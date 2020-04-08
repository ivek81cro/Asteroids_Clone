#ifndef MOVEMENTCOMPONENT_H_
#define MOVEMENTCOMPONENT_H_

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

class MovementComponent
{
  public:
    MovementComponent(float max_velocity);
    virtual ~MovementComponent();

    //Accessors
    const sf::Vector2f& GetVelocity() const;

    //Functions
    void Move(const float x, const float y);
    void Update(const float& delta);

  private:
    float        max_velocity_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;
    sf::Vector2f deceleration_;

    //Initializer functions
};
#endif
