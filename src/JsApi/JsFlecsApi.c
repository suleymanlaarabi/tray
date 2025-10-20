#include <flecs.h>
#include <stdio.h>
#include <tray.h>
#include <utils.h>
#include <JavaScriptCore/JavaScriptCore.h>
#include <JsApi.h>

JSValueRef js_ecs_new(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    UNUSED JSObjectRef thisObject,
    UNUSED size_t argumentCount,
    UNUSED const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {
    ecs_entity_t entity = ecs_new(world);

    if (argumentCount > 0) {
        JSValueRef value = *arguments;
        if (JSValueIsString(ctx, value)) {
            CStringFromJsValue(ctx, value, entity_name);
            ecs_set_name(world, entity, entity_name);
        }
    }
    return JSBigIntCreateWithUInt64(ctx, entity, NULL);
}

JSValueRef js_ecs_delete(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    UNUSED JSObjectRef thisObject,
    UNUSED size_t argumentCount,
    UNUSED const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {
    ecs_delete(world, JSValueToUInt64(ctx, arguments[0], NULL));
    return JSValueMakeUndefined(ctx);
}

JSValueRef js_ecs_add(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    UNUSED JSObjectRef thisObject,
    UNUSED size_t argumentCount,
    UNUSED const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {
    ecs_add_id(world, JSValueToUInt64(ctx, arguments[0], NULL), JSValueToUInt64(ctx, arguments[1], NULL));
    return JSValueMakeUndefined(ctx);
}

JSValueRef js_ecs_add_pair(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    UNUSED JSObjectRef thisObject,
    UNUSED size_t argumentCount,
    UNUSED const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {
    ecs_add_id(world, JSValueToUInt64(ctx, arguments[0], NULL), ecs_make_pair(JSValueToUInt64(ctx, arguments[1], NULL), JSValueToUInt64(ctx, arguments[2], NULL)));
    return JSValueMakeUndefined(ctx);
}

void js_api_register_flecs_functions(
    JSContextRef ctx,
    JSObjectRef global
)
{
    JSStringRef ecs_new_name = JSStringCreateWithUTF8CString("ecs_new");
    JSObjectRef ecs_new_obj = JSObjectMakeFunctionWithCallback(ctx, ecs_new_name, js_ecs_new);
    JSObjectSetProperty(ctx, global, ecs_new_name, ecs_new_obj, kJSPropertyAttributeNone, NULL);

    JSStringRef ecs_delete_name = JSStringCreateWithUTF8CString("ecs_delete");
    JSObjectRef ecs_delete_obj = JSObjectMakeFunctionWithCallback(ctx, ecs_delete_name, js_ecs_delete);
    JSObjectSetProperty(ctx, global, ecs_delete_name, ecs_delete_obj, kJSPropertyAttributeNone, NULL);

    JSStringRef ecs_add_name = JSStringCreateWithUTF8CString("ecs_add");
    JSObjectRef ecs_add_obj = JSObjectMakeFunctionWithCallback(ctx, ecs_add_name, js_ecs_add);
    JSObjectSetProperty(ctx, global, ecs_add_name, ecs_add_obj, kJSPropertyAttributeNone, NULL);

    JSStringRef ecs_add_pair_name = JSStringCreateWithUTF8CString("ecs_add_pair");
    JSObjectRef ecs_add_pair_obj = JSObjectMakeFunctionWithCallback(ctx, ecs_add_pair_name, js_ecs_add_pair);
    JSObjectSetProperty(ctx, global, ecs_add_pair_name, ecs_add_pair_obj, kJSPropertyAttributeNone, NULL);
}
