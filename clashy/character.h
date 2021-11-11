#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include"BaseCharacter.h"
class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos()override;
    Rectangle getWeaponCollisionRec() {return weaponColisionRec;}
    float getHealth() const { return health;}
    void takeDamage(float damage);
private:
int windowWidth{}; 
int windowHight{};
Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
Rectangle weaponColisionRec{};
float health{100.f};
};
#endif