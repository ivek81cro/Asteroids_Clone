#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"
#include <SFML/Graphics.hpp>

class Bullet : public Entity
{
    static bool        init_done;
    static const float lifetime;
    static const float speed;
    static sf::Texture tBullet;

  public:
    Bullet(sf::Vector2f position, float angle);
    ~Bullet();

    void        Kill();
    void        Update(sf::Time& elapsed_time);
    static bool Init(const std::string& image_file);

  private:
    float        mRemainingLife;
    sf::Vector2f mDirection;
};

#endif
