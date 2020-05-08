#ifndef ENEMYUFO_H_
#define ENEMYUFO_H_

#include "Entity.h"
#include "Bullet.h"

class EnemyUfo : public Entity
{
  public:
    EnemyUfo(float x, float y, sf::Texture& texture_sheet, float scale);
    virtual ~EnemyUfo();

    void Update(const float& delta, const sf::Vector2u& window_size);

    const bool   GetArriving() const;
    const float& GetFireCooldown() const;
    void         ResetFireCooldown();
    void         SetLifeTime(const float& delta);

  private:
    //Variables
    bool  arriving_;
    bool  away_;
    float fire_cooldown_;
    float lifetime_;

    //Functions
    void InitComponents(sf::Texture& texture_sheet);



};
#endif