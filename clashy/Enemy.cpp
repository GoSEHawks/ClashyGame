#include "Enemy.h"
#include"raymath.h"

Enemy::Enemy(Vector2 Pos, Texture2D idle_tex, Texture2D run_tex) 

{
   worldPos = Pos;
   texture = idle_tex;
   idle = idle_tex;
   run = run_tex;

   width = texture.width / maxFrames;
   hight = texture.height;
   speed = 2.5f;
}
void Enemy::tick(float deltaTime)
{
   if(!getAlive()) return;
   // get  totarget
   velocity = Vector2Subtract(target->getScreenPos(),getScreenPos());
   if (Vector2Length(velocity) < radius) velocity = {};
   BaseCharacter::tick(deltaTime);
   if (CheckCollisionRecs(target->GetCollisionRec(),GetCollisionRec()))
   {
      target -> takeDamage(damagePerSec * deltaTime);
   }
}
Vector2 Enemy::getScreenPos()
{
   return Vector2Subtract(worldPos, target -> getWorldPos());
}

