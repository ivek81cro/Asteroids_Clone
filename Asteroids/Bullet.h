#ifndef _BULLET_H_
#define _BULLET_H_

#include <SFML/Graphics.hpp>


class Bullet : public sf::Drawable, sf::Transformable
{
	static bool init_done;
	static const float lifetime;
	static const float speed;
	
	static sf::Texture tBullet;
	sf::Sprite sBullet;

public:
	Bullet(sf::Vector2f position, float angle);
	~Bullet();

	bool isAlive();
	void kill();
	void update(float frametime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	static bool Init(const std::string& ImageFile)
	{
		init_done = true;
		return tBullet.loadFromFile(ImageFile);
	}

private:
	bool is_alive;
	float remaning_life;
	sf::Vector2f direction;
};

#endif