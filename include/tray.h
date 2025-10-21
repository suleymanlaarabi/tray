#ifndef TRAY_H
    #define TRAY_H
    #include <flecs.h>
    #include <JavaScriptCore/JavaScriptCore.h>

extern ecs_world_t *world;
extern JSStringRef name_str;
extern JSStringRef entity_str;
extern JSStringRef parent_str;
extern JSStringRef constructor_str;
extern JSStringRef childOf_str;
extern JSStringRef prototype_str;
extern JSStringRef x_str, y_str, r_str, g_str, b_str, a_str;
extern JSStringRef radius_str, width_str, height_str;

void JsImport(ecs_world_t *world);

typedef JSGlobalContextRef JSGlobalContext;
typedef JSObjectRef JSGlobalObject;
typedef JSObjectRef JSObject;
typedef JSObjectRef JSObjectThis;

extern ECS_COMPONENT_DECLARE(JSGlobalContext);
extern ECS_COMPONENT_DECLARE(JSGlobalObject);
extern ECS_COMPONENT_DECLARE(JSObject);
extern ECS_COMPONENT_DECLARE(JSObjectThis);

#endif
