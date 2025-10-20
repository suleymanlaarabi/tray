#ifndef TRAY_UTILS_H
    #define TRAY_UTILS_H
    #include <JavaScriptCore/JavaScriptCore.h>
    #define UNUSED __attribute((unused))
    #define U64_AS_DOUBLE(x) \
        ((union { uint64_t u; double d; }){ .u = (x) }).d
    #define DOUBLE_AS_U64(x) \
        ((union { uint64_t u; double d; }){ .u = (x) }).u

    #define CStringFromJsValue(ctx, value, name) \
        JSStringRef __name__##name = JSValueToStringCopy(ctx, value, NULL); \
        size_t __size__##name = JSStringGetMaximumUTF8CStringSize(__name__##name); \
        char name[__size__##name]; \
        JSStringGetUTF8CString(__name__##name, name, __size__##name);

#endif
