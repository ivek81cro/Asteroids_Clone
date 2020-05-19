#include "stdafx.h"
#include "Entity.h"


/**
    Base class for entities
 */
//Constructors / Destrustors
Entity::Entity()
        : asteroid_level_(0)
        , game_level_(1)
{
    InitVariables();
}

Entity::~Entity()
{
}

//Initializer functions
void Entity::InitVariables()
{
    hitbox_component_    = nullptr;
    movement_component_  = nullptr;
    animation_component_ = nullptr;
    alive_               = true;
    exploding_           = false;
}

//Component functions
void Entity::CreateMovementComponent(const float max_velocity, const float acceleration, const float deceleration,
                                     const float& angle)
{
    movement_component_ = std::unique_ptr<MovementComponent>(
        new MovementComponent(sprite_, max_velocity, acceleration, deceleration, angle, movement_name_));
}

void Entity::CreateAnimationComponent(sf::Texture& texture_sheet)
{
    animation_component_ = std::unique_ptr<AnimationComponent>(new AnimationComponent(sprite_, texture_sheet));
}

void Entity::CreateHitboxComponent(sf::Sprite& sprite, float width, float factor)
{
    hitbox_component_ = std::unique_ptr<HitboxComponent>(new HitboxComponent(sprite, width, factor));
}

//Functions
void Entity::SetPosition(const float& x, const float& y)
{
    sprite_.setPosition(x, y);
}

void Entity::Move(const float& dir_x, const float& dir_y, const float& delta)
{
    if (movement_component_ && !exploding_)
        movement_component_->Move(dir_x, dir_y, delta); //Sets velocity
}

const bool Entity::GetAlive() const
{
    return alive_;
}

void Entity::SetAlive(const bool& is_alive)
{
    alive_ = is_alive;
}

const bool Entity::IsExploding() const
{
    return exploding_;
}

const EntityName_e Entity::GetName() const
{
    return name_;
}

const sf::CircleShape& Entity::GetHitbox() const
{
    return hitbox_component_->GetHitbox();
}

/**
    Check collision between two entities via hitbox
 */
const bool Entity::CheckCollision(const sf::CircleShape& other)
{
    float ax = hitbox_component_->GetHitbox().getPosition().x;
    float ay = hitbox_component_->GetHitbox().getPosition().y;

    float px = other.getPosition().x;
    float py = other.getPosition().y;

    float sqrDistance = sqrt((ax - px) * (ax - px) + (ay - py) * (ay - py));
    float sqrRadius   = hitbox_component_->GetHitbox().getRadius() + other.getRadius();

    return (sqrDistance <= sqrRadius);
}

const int& Entity::GetLevel() const
{
    return asteroid_level_;
}

const sf::Vector2f& Entity::GetPosition() const
{
    return sprite_.getPosition();
}

void Entity::ResetAnimationName()
{
}


/**
    Update components of entity
 */
void Entity::Update(const float& delta, const sf::Vector2u& window_size)
{
    if (movement_component_ && alive_)
        movement_component_->Update(delta, window_size);

    if (animation_component_ && alive_)
        animation_component_->Play(animation_name_, delta);

    if (hitbox_component_ && alive_)
        hitbox_component_->Update();
}


/**
    Draw entity
 */
void Entity::Render(sf::RenderTarget& target)
{
    target.draw(sprite_);

    if (hitbox_component_)
        hitbox_component_->Render(target);
}

const bool Entity::ShieldsUp() const
{
    return shields_;
}

float Entity::GetAngle() const
{
    return 0.0f;
}

const int Entity::GetPoints() const
{
    return 0;
}
