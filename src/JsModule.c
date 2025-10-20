#include <tray.h>

ECS_COMPONENT_DECLARE(JSContext);
ECS_COMPONENT_DECLARE(JSGlobalContext);
ECS_COMPONENT_DECLARE(JSGlobalObject);
ECS_COMPONENT_DECLARE(JSObject);
ECS_COMPONENT_DECLARE(JSObjectThis);

void JsImport(ecs_world_t *world) {
    ECS_MODULE(world, Js);

    ECS_COMPONENT_DEFINE(world, JSGlobalContext);
    ECS_COMPONENT_DEFINE(world, JSGlobalObject);
    ECS_COMPONENT_DEFINE(world, JSObject);
    ECS_COMPONENT_DEFINE(world, JSObjectThis);

    JSGlobalContextRef ctx = JSGlobalContextCreate(NULL);
    JSObjectRef global = JSContextGetGlobalObject(ctx);

    ecs_singleton_set(world, JSGlobalContext, {ctx});
    ecs_singleton_set(world, JSGlobalObject, {global});
}
