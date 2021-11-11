#include "BaseCharacter.h"
#include"raymath.h"

BaseCharacter::BaseCharacter()
{
    
}
void BaseCharacter ::undoMovement()
{
    worldPos = worldPosLastFrame;
}
Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        hight * scale
    };
}

void BaseCharacter:: tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
      //update animation frame
    runningTime += deltaTime;
    if (runningTime >= updDateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }
        if (Vector2Length(velocity) != 0.0)
    {

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};
    Rectangle source{frame * width, 0.f, rightLeft * width, hight};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * hight};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}