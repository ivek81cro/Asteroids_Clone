#ifndef DROPLIFE_H_
#define DROPLIFE_H_

#include "Entity.h"

class DropLife : public Entity
{
  public:
      //Functions
    DropLife(float x, float y, sf::Texture& texture_sheet, float scale);
    virtual ~DropLife();

    void Update(const float& delta, const sf::Vector2u& window_size);

  private:
      //Variables
    float lifetime_;
      //Functions
    void InitComponents(sf::Texture& texture_sheet);
};

#endif