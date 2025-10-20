#include <rayflecs.h>
#include <tray.h>
#include <JavaScriptCore/JavaScriptCore.h>
#include <stdio.h>
#include <string.h>
#include <flecs.h>
#include <JsApi.h>

#define tray_assert(cond, msg, ...) if (!file) { fprintf(stderr, msg, __VA_ARGS__); }

ecs_world_t *world = NULL;
JSStringRef name_str = NULL;
JSStringRef info_str = NULL;
JSStringRef entity_str = NULL;

void evaluate_script(const char *script_path, JSContextRef ctx) {
    FILE *file = fopen(script_path, "r");
    tray_assert(!file, "Failed to open script file: %s\n", script_path);

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

int onInit(ecs_world_t *_) {
    puts("Flecs devtool: https://www.flecs.dev/explorer/?host=localhost");
    return 0;
}

int main(void) {
    world = ecs_init();
    ECS_IMPORT(world, Js);
    ECS_IMPORT(world, Rayflecs);

    JSGlobalContextRef ctx = *ecs_singleton_get(world, JSGlobalContext);
    JSObjectRef global = *ecs_singleton_get(world, JSGlobalObject);

    name_str = JSStringCreateWithUTF8CString("name");
    info_str = JSStringCreateWithUTF8CString("info");
    entity_str = JSStringCreateWithUTF8CString("entity");

    js_api_register_debug_functions(ctx, global);
    js_api_register_flecs_functions(ctx, global);

    JSStringRef child_of_name = JSStringCreateWithUTF8CString("ChildOf");
    JSValueRef child_of_value = JSBigIntCreateWithUInt64(ctx, EcsChildOf, NULL);
    JSObjectSetProperty(ctx, global, child_of_name, child_of_value, kJSPropertyAttributeNone, NULL);

    evaluate_script("./build/main.js", ctx);

    ecs_app_run(world, &(ecs_app_desc_t) {
        .enable_rest = true,
        .enable_stats = true,
        .target_fps = 120,
        .init = onInit
    });
}
