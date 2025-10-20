#ifndef TRAY_JS_API_H
    #define TRAY_JS_API_H
    #include <JavaScriptCore/JavaScriptCore.h>

void js_api_register_debug_functions(
    JSContextRef ctx,
    JSObjectRef global
);
void js_api_register_flecs_functions(
    JSContextRef ctx,
    JSObjectRef global
);

#endif
