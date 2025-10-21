#ifndef TRAY_TRANSFORM_H
#define TRAY_TRANSFORM_H

#include "flecs.h"
#include <JavaScriptCore/JavaScriptCore.h>
#include <raylib.h>

typedef Vector2 Position;
typedef Vector2 Velocity;

typedef JSValueRef JSPosition;
typedef JSValueRef JSVelocity;
typedef JSValueRef JSScale;
typedef JSValueRef JSRotation;

extern ECS_COMPONENT_DECLARE(JSPosition);
extern ECS_COMPONENT_DECLARE(JSScale);
extern ECS_COMPONENT_DECLARE(JSRotation);
extern ECS_COMPONENT_DECLARE(JSVelocity);

void TransformImport(ecs_world_t *world);

#endif
