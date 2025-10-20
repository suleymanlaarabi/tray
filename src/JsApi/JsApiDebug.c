#include "utils.h"
#include <JavaScriptCore/JavaScriptCore.h>

static JSValueRef js_print(
    JSContextRef ctx,
    UNUSED JSObjectRef function,
    UNUSED JSObjectRef thisObject,
    size_t argumentCount,
    const JSValueRef arguments[],
    UNUSED JSValueRef* exception
) {
    for (size_t i = 0; i < argumentCount; i++) {
        JSStringRef str = JSValueToStringCopy(ctx, arguments[i], NULL);
        size_t size = JSStringGetMaximumUTF8CStringSize(str);
        char buffer[size];
        JSStringGetUTF8CString(str, buffer, size);
        printf("%s%s", buffer, i + 1 < argumentCount ? " " : "\n");
        JSStringRelease(str);
    }
    return JSValueMakeUndefined(ctx);
}


void js_api_register_debug_functions(
    JSContextRef ctx,
    JSObjectRef global
)
{
    JSStringRef function_name = JSStringCreateWithUTF8CString("print");
    JSObjectRef function_obj = JSObjectMakeFunctionWithCallback(ctx, function_name, js_print);
    JSObjectSetProperty(ctx, global, function_name, function_obj, kJSPropertyAttributeNone, NULL);
}
