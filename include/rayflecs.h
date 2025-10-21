#ifndef TRAY_RAYFLECS_H
#define TRAY_RAYFLECS_H

#include "flecs.h"
#include <stdint.h>
#include <raylib.h>
#include <JavaScriptCore/JavaScriptCore.h>

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

typedef struct {
    float radius;
} CircleShape;

typedef struct {
    float width;
    float height;
} RectangleShape;

typedef JSValueRef JSCircleShape;
typedef JSValueRef JSRectangleShape;
typedef JSValueRef JSColor;

extern ECS_COMPONENT_DECLARE(JSCircleShape);
extern ECS_COMPONENT_DECLARE(JSRectangleShape);
extern ECS_COMPONENT_DECLARE(JSColor);

void RayflecsImport(ecs_world_t *world);

#endif
