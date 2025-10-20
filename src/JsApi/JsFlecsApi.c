#include <stdlib.h>
#include <string.h>
#include <flecs.h>
#include <stdio.h>
#include <tray.h>
#include <utils.h>
#include <JavaScriptCore/JavaScriptCore.h>
#include <JsApi.h>

#define EntityToJSValue(ctx, entity) JSBigIntCreateWithUInt64(ctx, entity, NULL)

JSValueRef js_ecs_new(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    UNUSED JSObjectRef thisObject,
    size_t argumentCount,
    const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {
    ecs_entity_t entity = ecs_new(world);

    if (argumentCount > 0 && JSValueIsString(ctx, *arguments)) {
        CStringFromJsValue(ctx, *arguments, entity_name);
        ecs_set_name(world, entity, entity_name);
    }
    return EntityToJSValue(ctx, entity);
}

JSValueRef js_ecs_delete(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    UNUSED JSObjectRef thisObject,
    UNUSED size_t argumentCount,
    const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {
    ecs_delete(world, JSValueToUInt64(ctx, *arguments, NULL));
    return JSValueMakeUndefined(ctx);
}

JSValueRef js_ecs_add(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    UNUSED JSObjectRef thisObject,
    UNUSED size_t argumentCount,
    const JSValueRef arguments[],
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
    const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {
    ecs_add_id(world, JSValueToUInt64(ctx, arguments[0], NULL), ecs_make_pair(JSValueToUInt64(ctx, arguments[1], NULL), JSValueToUInt64(ctx, arguments[2], NULL)));
    return JSValueMakeUndefined(ctx);
}


JSValueRef js_ecs_set_name(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    UNUSED JSObjectRef thisObject,
    UNUSED size_t argumentCount,
    const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {
    CStringFromJsValue(ctx, arguments[1], name);
    ecs_set_name(world, JSValueToUInt64(ctx, arguments[0], NULL), name);
    return JSValueMakeUndefined(ctx);
}

void EcsRunJsSystem(ecs_iter_t *it) {
    JSGlobalContext ctx = *ecs_singleton_get(world, JSGlobalContext);
    JSObjectRef function = *ecs_get(world, it->system, JSObject);
    JSObjectRef this = *ecs_get(world, it->system, JSObjectThis);
    JSValueRef *elements = malloc(sizeof(JSValueRef) * it->count);

    for (int i = 0; i < it->count; i++) {
        elements[i] = JSBigIntCreateWithUInt64(ctx, it->entities[i], NULL);
    }

    JSValueRef array = JSObjectMakeArray(ctx, it->count, elements, NULL);


    JSObjectCallAsFunction(ctx, function, this, 1, &array, NULL);
}

JSValueRef js_ecs_system(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    JSObjectRef thisObject,
    UNUSED size_t argumentCount,
    const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {
    CStringFromJsValue(ctx, arguments[0], query);

    JSObjectRef js_function = JSValueToObject(ctx, arguments[1], NULL);

    JSValueRef js_function_name = JSObjectGetProperty(ctx, js_function, name_str, NULL);

    CStringFromJsValue(ctx, js_function_name, function_name);


    ecs_entity_t entity = ecs_entity(world, {
        .name = strdup(function_name),
        .add = ecs_ids(ecs_dependson(EcsOnUpdate))
    });

    ecs_system_init(world, &(ecs_system_desc_t) {
        .entity = entity,
        .query.expr = strdup(query),
        .callback = EcsRunJsSystem
    });

    ecs_set(world, entity, JSObject, {js_function});
    ecs_set(world, entity, JSObjectThis, {thisObject});

    return EntityToJSValue(ctx, entity);
}

static ecs_entity_t ecs_register_js_component(ecs_world_t *world, const char *name) {
    ecs_entity_t entity = ecs_lookup(world, name);
    if (entity) {
        return entity;
    }

    ecs_entity_desc_t edesc = {0};
    edesc.name = name;
    edesc.symbol = name;
    edesc.use_low_id = true;

    ecs_component_desc_t cdesc = {0};
    cdesc.entity = ecs_entity_init(world, &edesc);
    cdesc.type.size = ECS_SIZEOF(void *);
    cdesc.type.alignment = ECS_ALIGNOF(void *);
    ecs_entity_t component = ecs_component_init(world, &cdesc);
    return component;
}

JSValueRef js_ecs_component(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    UNUSED JSObjectRef thisObject,
    UNUSED size_t argumentCount,
    const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {

    CStringFromJsValue(ctx, arguments[0], name);
    ecs_entity_t entity = ecs_register_js_component(world, strdup(name));

    return EntityToJSValue(ctx, entity);
}

ecs_entity_t component_from_js_constructor(
    JSContextRef ctx,
    JSValueRef value
) {
    JSObjectRef obj = JSValueToObject(ctx, value, NULL);

    JSValueRef name_value = JSObjectGetProperty(ctx, obj, name_str, NULL);
    CStringFromJsValue(ctx, name_value, name)
    ecs_entity_t component = ecs_lookup(world, name);

    return component;
}

JSValueRef js_ecs_set(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    UNUSED JSObjectRef thisObject,
    UNUSED size_t argumentCount,
    const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {
    ecs_entity_t entity = JSValueToUInt64(ctx, arguments[0], NULL);
    ecs_entity_t component = 0;
    JSValueRef value = NULL;

    if (JSValueIsBigInt(ctx, arguments[1])) {
        component = JSValueToUInt64(ctx, arguments[1], NULL);
        value = arguments[2];
    } else {
        JSObjectRef obj = JSValueToObject(ctx, arguments[1], NULL);
        JSObjectRef info = JSValueToObject(ctx, JSObjectGetProperty(ctx, obj, info_str, NULL), NULL);
        component = JSValueToUInt64(ctx, JSObjectGetProperty(ctx, info, entity_str, NULL), NULL);
        value = arguments[1];
    }

    JSValueProtect(ctx, value);
    ecs_set_id(world, entity, component, sizeof(void *), &value);
    return JSValueMakeUndefined(ctx);
}

JSValueRef js_ecs_get(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    UNUSED JSObjectRef thisObject,
    UNUSED size_t argumentCount,
    const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {
    ecs_entity_t entity = JSValueToUInt64(ctx, arguments[0], NULL);
    ecs_entity_t component = component_from_js_constructor(ctx, arguments[1]);

    return *((JSValueRef *) ecs_get_id(world, entity, component));
}

static void register_js_function(
    JSContextRef ctx,
    JSObjectRef global,
    const char *name,
    JSObjectCallAsFunctionCallback callback
) {
    JSStringRef js_name = JSStringCreateWithUTF8CString(name);
    JSObjectRef js_func = JSObjectMakeFunctionWithCallback(ctx, js_name, callback);
    JSObjectSetProperty(ctx, global, js_name, js_func, kJSPropertyAttributeNone, NULL);
    JSStringRelease(js_name);
}

void js_api_register_flecs_functions(JSContextRef ctx, JSObjectRef global) {
    register_js_function(ctx, global, "ecs_new", js_ecs_new);
    register_js_function(ctx, global, "ecs_delete", js_ecs_delete);
    register_js_function(ctx, global, "ecs_add", js_ecs_add);
    register_js_function(ctx, global, "ecs_add_pair", js_ecs_add_pair);
    register_js_function(ctx, global, "ecs_set_name", js_ecs_set_name);
    register_js_function(ctx, global, "ecs_system", js_ecs_system);
    register_js_function(ctx, global, "ecs_component", js_ecs_component);
    register_js_function(ctx, global, "ecs_set", js_ecs_set);
    register_js_function(ctx, global, "ecs_get", js_ecs_get);

}
