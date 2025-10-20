#ifndef TRAY_H
    #define TRAY_H
    #include <flecs.h>
    #include <JavaScriptCore/JavaScriptCore.h>

extern ecs_world_t *world;
extern JSStringRef name_str;
extern JSStringRef info_str;
extern JSStringRef entity_str;

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
