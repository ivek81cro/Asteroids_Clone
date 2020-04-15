#include "Entity.h"

//Constructors / Destrustors
Entity::Entity()
{
    InitVariables();
}

Entity::~Entity()
{
    delete movement_component_;
    delete animation_component_;
    delete hitbox_component_;
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
    movement_component_ = new MovementComponent(sprite_, max_velocity, acceleration, deceleration, angle, name_);
}

void Entity::CreateAnimationComponent(sf::Texture& texture_sheet)
{
    animation_component_ = new AnimationComponent(sprite_, texture_sheet);
}

void Entity::CreateHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width)
{
    hitbox_component_ =
        new HitboxComponent(sprite, offset_x, offset_y, width);
}

//Functions
void Entity::SetPosition(const float x, const float y)
{
    sprite_.setPosition(x, y);
}

void Entity::Move(const float dir_x, const float dir_y, const float& delta)
{
    if (movement_component_ && !exploding_)
        movement_component_->Move(dir_x, dir_y, delta); //Sets velocity

    //Ship animation preset based on movement
    if (name_ == "ship")
    {
        if (dir_x > 0)
            animation_name_ = "ship_r";
        else if (dir_x < 0)
            animation_name_ = "ship_l";
        else
            animation_name_ = name_;
    }
}

bool Entity::IsAlive()
{
    return alive_;
}

void Entity::SetAlive(bool is_alive)
{
    alive_ = is_alive;
}

std::string Entity::GetName()
{
    return name_;
}

void Entity::Update(const float& delta, const sf::Vector2u& window_size)
{
    if (movement_component_)
        movement_component_->Update(delta, window_size);

    if (animation_component_)
    {
        if (name_ == "ship" && exploding_)
            animation_name_ = "ship_explode";
        animation_component_->Play(animation_name_, delta);
    }

    if (hitbox_component_)
        hitbox_component_->Update();
}

void Entity::Render(sf::RenderTarget& target)
{
    target.draw(sprite_);

    if (hitbox_component_)
        hitbox_component_->Render(target);
}
