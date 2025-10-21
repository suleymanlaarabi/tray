#include "raylib.h"
#include "flecs.h"
#include "rayflecs.h"
#include "transform.h"
#include "tray.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

ECS_COMPONENT_DECLARE(JSRectangle);
ECS_COMPONENT_DECLARE(JSCircleShape);
ECS_COMPONENT_DECLARE(JSRectangleShape);
ECS_COMPONENT_DECLARE(JSColor);
ECS_TAG_DECLARE(NoRender);

void BeginDrawingSystem(ecs_iter_t *_) {
    if (WindowShouldClose()) {
        exit(0);
    }
    BeginDrawing();
    ClearBackground(BLACK);
}

void DrawCircleShapeSystem(ecs_iter_t *it) {
    JSPosition *positions = ecs_field(it, JSPosition, 0);
    JSCircleShape *shapes = ecs_field(it, JSCircleShape, 1);
    JSColor *colors = ecs_field(it, JSColor, 2);
    JSGlobalContext ctx = *ecs_singleton_get(world, JSGlobalContext);

    for (int i = 0; i < it->count; i++) {
        JSObjectRef posObj = (JSObjectRef)positions[i];
        JSObjectRef shapeObj = (JSObjectRef)shapes[i];
        JSObjectRef colorObj = (JSObjectRef)colors[i];

        Position p = {
            .x = (float)JSValueToNumber(ctx, JSObjectGetProperty(ctx, posObj, x_str, NULL), NULL),
            .y = (float)JSValueToNumber(ctx, JSObjectGetProperty(ctx, posObj, y_str, NULL), NULL),
        };

        CircleShape s = {
            .radius = (float)JSValueToNumber(ctx, JSObjectGetProperty(ctx, shapeObj, radius_str, NULL), NULL),
        };

        Color c = {
            .r = (unsigned char)JSValueToNumber(ctx, JSObjectGetProperty(ctx, colorObj, r_str, NULL), NULL),
            .g = (unsigned char)JSValueToNumber(ctx, JSObjectGetProperty(ctx, colorObj, g_str, NULL), NULL),
            .b = (unsigned char)JSValueToNumber(ctx, JSObjectGetProperty(ctx, colorObj, b_str, NULL), NULL),
            .a = (unsigned char)JSValueToNumber(ctx, JSObjectGetProperty(ctx, colorObj, a_str, NULL), NULL),
        };

        DrawCircleV(p, s.radius, c);
    }
}

void DrawRectangleShapeSystem(ecs_iter_t *it) {
    JSPosition *positions = ecs_field(it, JSPosition, 0);
    JSRectangleShape *shapes = ecs_field(it, JSRectangleShape, 1);
    JSColor *colors = ecs_field(it, JSColor, 2);
    JSGlobalContext ctx = *ecs_singleton_get(world, JSGlobalContext);

    for (int i = 0; i < it->count; i++) {
        JSObjectRef posObj = (JSObjectRef)positions[i];
        JSObjectRef shapeObj = (JSObjectRef)shapes[i];
        JSObjectRef colorObj = (JSObjectRef)colors[i];

        Position p = {
            .x = (float)JSValueToNumber(ctx, JSObjectGetProperty(ctx, posObj, x_str, NULL), NULL),
            .y = (float)JSValueToNumber(ctx, JSObjectGetProperty(ctx, posObj, y_str, NULL), NULL),
        };

        RectangleShape s = {
            .width  = (float)JSValueToNumber(ctx, JSObjectGetProperty(ctx, shapeObj, width_str, NULL), NULL),
            .height = (float)JSValueToNumber(ctx, JSObjectGetProperty(ctx, shapeObj, height_str, NULL), NULL),
        };

        Color c = {
            .r = (unsigned char)JSValueToNumber(ctx, JSObjectGetProperty(ctx, colorObj, r_str, NULL), NULL),
            .g = (unsigned char)JSValueToNumber(ctx, JSObjectGetProperty(ctx, colorObj, g_str, NULL), NULL),
            .b = (unsigned char)JSValueToNumber(ctx, JSObjectGetProperty(ctx, colorObj, b_str, NULL), NULL),
            .a = (unsigned char)JSValueToNumber(ctx, JSObjectGetProperty(ctx, colorObj, a_str, NULL), NULL),
        };

        DrawRectangleV(p, (Vector2){s.width, s.height}, c);
    }
}


void EndDrawingSystem(ecs_iter_t *_) {
    EndDrawing();
}

void RayflecsImport(ecs_world_t *world) {
    ECS_MODULE(world, Rayflecs);
    ECS_IMPORT(world, Transform);

    ECS_TAG_DEFINE(world, NoRender);

    ECS_COMPONENT_DEFINE(world, JSRectangleShape);
    ECS_COMPONENT_DEFINE(world, JSCircleShape);
    ECS_COMPONENT_DEFINE(world, JSColor);

    const int screenWidth = 800;
    const int screenHeight = 450;
    SetTraceLogLevel(LOG_ERROR);

    InitWindow(screenWidth, screenHeight, "Game good");
    SetTargetFPS(0);
    ECS_SYSTEM(world, BeginDrawingSystem, EcsPreFrame,);

    ECS_SYSTEM(world, DrawCircleShapeSystem, EcsOnUpdate,
        [in] transform.JSPosition,
        [in] JSCircleShape,
        [in] JSColor
    );
    ECS_SYSTEM(world, DrawRectangleShapeSystem, EcsOnUpdate,
        [in] transform.JSPosition,
        [in] JSRectangleShape,
        [in] JSColor
    );
    ECS_SYSTEM(world, EndDrawingSystem, EcsPostFrame,);
}
