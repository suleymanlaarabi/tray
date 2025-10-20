#include "raylib.h"
#include "flecs.h"
#include "rayflecs.h"
#include "transform.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

ECS_COMPONENT_DECLARE(Rectangle);
ECS_COMPONENT_DECLARE(CircleShape);
ECS_COMPONENT_DECLARE(RectangleShape);
ECS_COMPONENT_DECLARE(Color);
ECS_COMPONENT_DECLARE(Cube);
ECS_COMPONENT_DECLARE(Camera3D);
ECS_TAG_DECLARE(NoRender);

void BeginDrawingSystem(ecs_iter_t *_) {
    if (WindowShouldClose()) {
        exit(0);
    }
    BeginDrawing();
    ClearBackground(BLACK);
}

void DrawCircleShapeSystem(ecs_iter_t *it) {
    CircleShape *shapes = ecs_field(it, CircleShape, 0);
    Position *positions = ecs_field(it, Position, 1);
    Color *colors = ecs_field(it, Color, 2);

    for (int i = 0; i < it->count; i++) {
        DrawCircleV(positions[i], shapes[i], colors[i]);
    }
}

void DrawRectangleShapeSystem(ecs_iter_t *it) {
    RectangleShape *rects = ecs_field(it, RectangleShape, 0);
    Position *positions = ecs_field(it, Position, 1);
    Color *colors = ecs_field(it, Color, 2);

    for (int i = 0; i < it->count; i++) {
        DrawRectangleV(positions[i], rects[i], colors[i]);
    }
}
void EndDrawingSystem(ecs_iter_t *_) {
    EndDrawing();
}

void RayflecsImport(ecs_world_t *world) {
    ECS_MODULE(world, Rayflecs);
    ECS_IMPORT(world, Transform);

    ECS_TAG_DEFINE(world, NoRender);

    ECS_COMPONENT_DEFINE(world, RectangleShape);
    ECS_COMPONENT_DEFINE(world, CircleShape);
    ECS_COMPONENT_DEFINE(world, Color);

    raystruct(world, RectangleShape,
        rayfield(width, f32),
        rayfield(height, f32)
    );
    raystruct(world, Color,
        rayfield(r, u8),
        rayfield(g, u8),
        rayfield(b, u8),
        rayfield(a, u8)
    );
    rayprimitive(world, CircleShape, f32);

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Game good");

    ECS_SYSTEM(world, BeginDrawingSystem, EcsPreFrame,);

    ECS_SYSTEM(world, DrawCircleShapeSystem, EcsOnUpdate,
        [in] CircleShape,
        [in] transform.Position,
        [in] Color
    );
    ECS_SYSTEM(world, DrawRectangleShapeSystem, EcsOnUpdate,
        [in] RectangleShape,
        [in] transform.Position,
        [in] Color
    );
    ECS_SYSTEM(world, EndDrawingSystem, EcsPostFrame,);
}
