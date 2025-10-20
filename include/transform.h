#ifndef TRAY_TRANSFORM_H
#define TRAY_TRANSFORM_H

#include "flecs.h"
#include <raylib.h>

typedef Vector2 Position;
typedef Vector3 Position3;
typedef Vector2 Velocity;
typedef Vector2 Size;
typedef Vector2 Scale;
typedef float Rotation;

extern ECS_COMPONENT_DECLARE(Position);
extern ECS_COMPONENT_DECLARE(Position3);
extern ECS_COMPONENT_DECLARE(Vector3);
extern ECS_COMPONENT_DECLARE(Size);
extern ECS_COMPONENT_DECLARE(Scale);
extern ECS_COMPONENT_DECLARE(Rotation);

void TransformImport(ecs_world_t *world);

#endif
