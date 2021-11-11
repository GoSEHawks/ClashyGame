#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowWidth{384};
    const int windwoHight{384};
    InitWindow(windowWidth, windwoHight, " CLASHY! ");

    Texture2D mainmap = LoadTexture("nature_tileset/worldmap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0};

    Character knigth{windowWidth, windwoHight};

    Prop Props[2]{
        Prop{Vector2{450.f, 100.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{850.f, 450.f}, LoadTexture("nature_tileset/Log.png")}

    };
    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};
    Enemy *enemies[]{
        &goblin,
        &slime};
    for (auto enemy : enemies)
    {
        enemy->setTarget(&knigth);
    }
    goblin.setTarget(&knigth);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knigth.getWorldPos(), -1.f);

        //draw the map
        DrawTextureEx(mainmap, mapPos, 0.0, mapScale, WHITE);

        // draw more props
        for (auto Prop : Props)
        {
            Prop.Render(knigth.getWorldPos());
        }
        if (!knigth.getAlive())
        {
            DrawText("GAME OVER!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knigth.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knigth.tick(GetFrameTime());
        // chack map bounds
        if (knigth.getWorldPos().x < 0.f ||
            knigth.getWorldPos().y < 0.f ||
            knigth.getWorldPos().x + windowWidth > mainmap.width * mapScale ||
            knigth.getWorldPos().y + windwoHight > mainmap.height * mapScale)
        {
            knigth.undoMovement();
        }
        //check prop collisons
        for (auto Prop : Props)
        {
            if (CheckCollisionRecs(Prop.GetCollisionRec(knigth.getWorldPos()), knigth.GetCollisionRec()))
            {
                knigth.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {

                if (CheckCollisionRecs(enemy ->GetCollisionRec(), knigth.GetCollisionRec()))
                {
                    enemy-> setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    CloseWindow();
}
