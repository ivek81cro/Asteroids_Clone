#ifndef ENEMYUFO_H_
#define ENEMYUFO_H_

#include "Entity.h"
#include "Bullet.h"

class EnemyUfo : public Entity
{
  public:
    EnemyUfo(const float& x, const float& y, sf::Texture& texture_sheet, const float& scale, const int& game_level);
    virtual ~EnemyUfo();

    void Update(const float& delta, const sf::Vector2u& window_size);

    void         SetLifeTime(const float& delta);
    const int    GetPoints() const;
    void         SetAlive(const bool& is_alive);

  private:
    //Variables
    int   points_;
    bool  away_;
    float lifetime_;


    //Functions
    void InitComponents(sf::Texture& texture_sheet);
    void InitVariables();



};
#endif