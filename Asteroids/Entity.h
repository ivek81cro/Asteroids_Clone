#ifndef ENTITY_H_
#define ENTITY_H_

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

class Entity
{
  public:
    Entity();
    virtual ~Entity();

    //Component functions
    void CreateSprite(sf::Texture* texture);

    //Functions
    virtual void SetPosition(const float x, const float y);
    virtual void SetTextureRect(const int x, const int y, const int height, const int width);
    virtual void Move(const float& delta, const float x, const float y);

    virtual void Update(const float& delta);
    virtual void Render(sf::RenderTarget* target);

  protected:
    sf::Texture* texture_;
    sf::Sprite*  sprite_;

    float movement_speed_;

  private:
    //Initializer functions
    void InitVariables();
};

#endif
