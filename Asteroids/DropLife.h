#ifndef DROPLIFE_H_
#define DROPLIFE_H_

#include "Entity.h"

class DropLife : public Entity
{
  public:
      //Functions
    DropLife(const float& x, const float& y, sf::Texture& texture_sheet, const float& scale);
    virtual ~DropLife();

    void Update(const float& delta, const sf::Vector2u& window_size);

  private:
      //Variables
    float lifetime_;
      //Functions
    void InitComponents(sf::Texture& texture_sheet);
};

#endif