#ifndef ENEMYUFO_H_
#define ENEMYUFO_H_

#include "Entity.h"
#include "Bullet.h"

class EnemyUfo : public Entity
{
  public:
    EnemyUfo(float x, float y, sf::Texture& texture_sheet, float scale, int& game_level);
    virtual ~EnemyUfo();

    void Update(const float& delta, const sf::Vector2u& window_size);

    const bool   GetInvoulnerability() const;
    const float& GetFireCooldown() const;
    void         ResetFireCooldown();
    void         SetLifeTime(const float& delta);
    const int    GetPoints() const;
    void         SetAlive(bool is_alive);

  private:
    //Variables
    int   points_;
    bool  invoulnerability_;
    bool  away_;
    float fire_cooldown_;
    float lifetime_;


    //Functions
    void InitComponents(sf::Texture& texture_sheet);



};
#endif