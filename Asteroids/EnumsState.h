#ifndef ENUMS_STATE_H_
#define ENUMS_STATE_H_

enum class Textures
{
    Player_ship,
    Asteroid,
    Bullet,
    Bullet_enemy,
    Background_texture,
    Enemy_ufo,
    Life
};

enum class Settings
{
    Resolution,
    Fullscreen,
    V_sync,
    Antialiasing,
    Keys_config
};

enum class SupportedKeys
{
    Up,
    Down,
    Left,
    Right,
    Escape,
    Space,
    W,
    A,
    S,
    D,
    Unsupported
};

enum class Keybinds
{
    Close,
    Fire,
    Move_up,
    Move_down,
    Move_left,
    Move_right,
    Unknown
};
#endif // !ENUMS_STATE_H_
