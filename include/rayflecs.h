#ifndef TRAY_RAYFLECS_H
#define TRAY_RAYFLECS_H

#include "flecs.h"
#include <stdint.h>
#include <raylib.h>

#define MAP_f32 F32
#define MAP_i32 I32
#define MAP_u32 U32
#define MAP_f64 F64
#define MAP_i64 I64

#define CAT(a,b) a##b
#define EXPAND_CAT(a,b) CAT(a,b)

#define raystruct(world, component, ...) ecs_struct(world, { .entity = ecs_id(component), .members = { __VA_ARGS__ } })
#define rayfield(field_name, field_type) { .name = #field_name, .type = ecs_id(ecs_##field_type##_t) }
#define raynested(field_name, component) { .name = #field_name, .type = ecs_id(component) }

#define rayprimitive(world, component, type) ecs_primitive(world, { .entity = ecs_id(component), .kind = EXPAND_CAT(Ecs, MAP_##type) })

typedef float CircleShape;
typedef Vector2 RectangleShape;

extern ECS_COMPONENT_DECLARE(Rectangle);
extern ECS_COMPONENT_DECLARE(CircleShape);
extern ECS_COMPONENT_DECLARE(RectangleShape);
extern ECS_COMPONENT_DECLARE(Color);
extern ECS_COMPONENT_DECLARE(Camera3D);

typedef Vector3 Cube;

extern ECS_COMPONENT_DECLARE(Cube);

void RayflecsImport(ecs_world_t *world);

#endif
