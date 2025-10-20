#ifndef TRAY_UTILS_H
    #define TRAY_UTILS_H
    #include <JavaScriptCore/JavaScriptCore.h>
    #define UNUSED __attribute((unused))
    #define U64_AS_DOUBLE(x) \
        ((union { uint64_t u; double d; }){ .u = (x) }).d
    #define DOUBLE_AS_U64(x) \
        ((union { uint64_t u; double d; }){ .u = (x) }).u

    #define CStringFromJsValue(ctx, value, name) \
        JSStringRef _name__##str = JSValueToStringCopy(ctx, value, NULL); \
        size_t _name__##size = JSStringGetMaximumUTF8CStringSize(_name__##str); \
        char name[_name__##size]; \
        JSStringGetUTF8CString(_name__##str, name, _name__##size);

#endif
