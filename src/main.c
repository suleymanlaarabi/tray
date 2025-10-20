#include <JavaScriptCore/JavaScriptCore.h>
#include <stdio.h>
#include <string.h>
#include <flecs.h>
#include <JsApi.h>

#define tray_assert(cond, msg, ...) if (!file) { fprintf(stderr, msg, __VA_ARGS__); }

ecs_world_t *world = NULL;

void evaluate_script(const char *script_path, JSGlobalContextRef ctx) {
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

int main(void) {
    world = ecs_init();

    JSGlobalContextRef ctx = JSGlobalContextCreate(NULL);
    JSObjectRef global = JSContextGetGlobalObject(ctx);

    js_api_register_debug_functions(ctx, global);
    js_api_register_flecs_functions(ctx, global);

    JSStringRef child_of_name = JSStringCreateWithUTF8CString("ChildOf");
    JSValueRef child_of_value = JSBigIntCreateWithUInt64(ctx, EcsChildOf, NULL);
    JSObjectSetProperty(ctx, global, child_of_name, child_of_value, kJSPropertyAttributeNone, NULL);

    evaluate_script("./build/main.js", ctx);

    ecs_app_run(world, &(ecs_app_desc_t) {
        .enable_rest = true,
        .enable_stats = true,
        .target_fps = 120
    });
}
