#include <flecs.h>
#include <sys/cdefs.h>
#include "transform.h"

ECS_COMPONENT_DECLARE(JSPosition);
ECS_COMPONENT_DECLARE(JSVelocity);
ECS_COMPONENT_DECLARE(JSRotation);
ECS_COMPONENT_DECLARE(JSScale);

void TransformImport(ecs_world_t *world) {
    ECS_MODULE(world, Transform);

    ECS_COMPONENT_DEFINE(world, JSRotation);
    ECS_COMPONENT_DEFINE(world, JSPosition);
    ECS_COMPONENT_DEFINE(world, JSVelocity);
    ECS_COMPONENT_DEFINE(world, JSScale);
}
