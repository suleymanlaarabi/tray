#include <flecs.h>
#include <sys/cdefs.h>
#include "transform.h"
#include "rayflecs.h"

ECS_COMPONENT_DECLARE(Position);
ECS_COMPONENT_DECLARE(Rotation);
ECS_COMPONENT_DECLARE(Scale);
ECS_COMPONENT_DECLARE(Size);
ECS_COMPONENT_DECLARE(Position3);
ECS_COMPONENT_DECLARE(Vector3);

#define REGISTER_VECTOR2_COMPONENT(world, component) ecs_struct(world, { \
        .entity = ecs_id(component), \
        .members = { \
            { .name = "x", .type = ecs_id(ecs_f32_t) }, \
            { .name = "y", .type = ecs_id(ecs_f32_t) } \
        } \
    });


void PositionCtor(void *ptr, __unused int _, __unused const ecs_type_info_t *_info) {
    Position *p = ptr;
    p->x = 0.0f;
    p->y = 0.0f;
}

void TransformImport(ecs_world_t *world) {
    ECS_MODULE(world, Transform);

    ECS_COMPONENT_DEFINE(world, Rotation);
    ECS_COMPONENT_DEFINE(world, Position);
    ECS_COMPONENT_DEFINE(world, Scale);
    ECS_COMPONENT_DEFINE(world, Size);
    ECS_COMPONENT_DEFINE(world, Position3);
    ECS_COMPONENT_DEFINE(world, Vector3);

    REGISTER_VECTOR2_COMPONENT(world, Position);
    REGISTER_VECTOR2_COMPONENT(world, Scale);
    REGISTER_VECTOR2_COMPONENT(world, Size);

    raystruct(world, Position3,
        rayfield(x, f32),
        rayfield(y, f32),
        rayfield(z, f32)
    );
    raystruct(world, Vector3,
        rayfield(x, f32),
        rayfield(y, f32),
        rayfield(z, f32)
    );

    ecs_set_hooks(world, Position, {
        .ctor = PositionCtor,
    });

    ecs_primitive(world, {
        .entity = ecs_id(Rotation),
        .kind = ecs_id(ecs_f32_t)
    });
}
