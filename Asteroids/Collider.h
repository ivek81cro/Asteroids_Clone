#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "Entity.h"
#include <SFML/Graphics.hpp>

class Collider
{
  public:
    bool isCollide(Entity& obj1, Entity& obj2);

  private:
};

#endif // _COLLIDER_H_
