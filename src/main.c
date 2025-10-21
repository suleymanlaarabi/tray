#include <rayflecs.h>
#include <tray.h>
#include <transform.h>
#include <JavaScriptCore/JavaScriptCore.h>
#include <stdio.h>
#include <string.h>
#include <flecs.h>
#include <JsApi.h>

#define tray_assert(cond, msg, ...) if (!(cond)) { fprintf(stderr, msg, __VA_ARGS__); }
#define JS_DEFINE_CONST(ctx, global, name, value) \
    { \
        JSStringRef js_name = JSStringCreateWithUTF8CString(name); \
        JSValueRef js_val = JSBigIntCreateWithUInt64(ctx, value, NULL); \
        JSObjectSetProperty(ctx, global, js_name, js_val, kJSPropertyAttributeNone, NULL); \
        JSStringRelease(js_name); \
    }

ecs_world_t *world = NULL;
JSStringRef name_str = NULL;
JSStringRef childOf_str = NULL;
JSStringRef parent_str = NULL;
JSStringRef entity_str = NULL;
JSStringRef constructor_str = NULL;
JSStringRef prototype_str = NULL;
JSStringRef x_str, y_str, r_str, g_str, b_str, a_str = NULL;
JSStringRef radius_str, width_str, height_str = NULL;

void evaluate_script(const char *script_path, JSContextRef ctx) {
    FILE *file = fopen(script_path, "r");
    tray_assert(file, "Failed to open script file: %s\n", script_path);

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    size_t read = fread(buffer, 1, length, file);
    buffer[read] = '\0';
    fclose(file);

    JSStringRef script = JSStringCreateWithUTF8CString(buffer);
    JSEvaluateScript(ctx, script, NULL, NULL, 0, NULL);
    JSStringRelease(script);
    free(buffer);
}

int onInit(ecs_world_t *world) {
    puts("Flecs devtool: https://www.flecs.dev/explorer/?host=localhost");
    ecs_shrink(world);
    return 0;
}

int main(void) {
    world = ecs_init();
    ECS_IMPORT(world, Js);
    ECS_IMPORT(world, Rayflecs);
    ECS_IMPORT(world, Transform);

    JSGlobalContextRef ctx = *ecs_singleton_get(world, JSGlobalContext);
    JSObjectRef global = *ecs_singleton_get(world, JSGlobalObject);

    name_str = JSStringCreateWithUTF8CString("name");
    entity_str = JSStringCreateWithUTF8CString("entity");
    constructor_str = JSStringCreateWithUTF8CString("constructor");
    prototype_str = JSStringCreateWithUTF8CString("prototype");
    x_str = JSStringCreateWithUTF8CString("x");
    y_str = JSStringCreateWithUTF8CString("y");
    r_str = JSStringCreateWithUTF8CString("r");
    g_str = JSStringCreateWithUTF8CString("g");
    b_str = JSStringCreateWithUTF8CString("b");
    a_str = JSStringCreateWithUTF8CString("a");
    radius_str = JSStringCreateWithUTF8CString("radius");
    width_str = JSStringCreateWithUTF8CString("width");
    height_str = JSStringCreateWithUTF8CString("height");
    childOf_str = JSStringCreateWithUTF8CString("childOf");
    parent_str = JSStringCreateWithUTF8CString("parent");

    js_api_register_debug_functions(ctx, global);
    js_api_register_flecs_functions(ctx, global);

    JS_DEFINE_CONST(ctx, global, "ChildOf", EcsChildOf);
    JS_DEFINE_CONST(ctx, global, "OnUpdate", EcsOnUpdate);
    JS_DEFINE_CONST(ctx, global, "OnStart", EcsOnStart);
    JS_DEFINE_CONST(ctx, global, "PositionEntity", ecs_id(JSPosition));
    JS_DEFINE_CONST(ctx, global, "VelocityEntity", ecs_id(JSVelocity));
    JS_DEFINE_CONST(ctx, global, "ColorEntity", ecs_id(JSColor));
    JS_DEFINE_CONST(ctx, global, "CircleShapeEntity", ecs_id(JSCircleShape));
    JS_DEFINE_CONST(ctx, global, "RectangleShapeEntity", ecs_id(JSRectangleShape));

    evaluate_script("./build/main.js", ctx);

    ecs_app_run(world, &(ecs_app_desc_t) {
        .enable_rest = true,
        .enable_stats = true,
        .target_fps = 120,
        .init = onInit,
        .threads = 4
    });
}
