#ifndef SOKOL_TRACY_INCLUDED
#define SOKOL_TRACY_INCLUDED
/*
    sokol_tracy.h -- optional Tracy profiler zones inside the sokol headers
    (nothke/sokol-zig fork, not part of upstream sokol).

    Enabled by defining SOKOL_TRACY (the `with_tracy` build option). The
    Tracy client (TracyClient.cpp built with TRACY_ENABLE) must then be
    linked into the final executable; the few C-API functions used here are
    declared by hand (matching public/tracy/TracyC.h, Tracy v0.14), so no
    Tracy include path is needed. Without SOKOL_TRACY the macros are empty.

    Usage inside a function:

        _SOKOL_TRACY_ZONE(zone, "sapp: create window");
        ...
        _SOKOL_TRACY_ZONE_END(zone);
*/
#if defined(SOKOL_TRACY)
#include <stdint.h>

struct ___tracy_source_location_data {
    const char* name;
    const char* function;
    const char* file;
    uint32_t line;
    uint32_t color;
};

struct ___tracy_c_zone_context {
    uint32_t id;
    int32_t active;
};

#if defined(__cplusplus)
extern "C" {
#endif
struct ___tracy_c_zone_context ___tracy_emit_zone_begin(const struct ___tracy_source_location_data* srcloc, int32_t active);
void ___tracy_emit_zone_end(struct ___tracy_c_zone_context ctx);
#if defined(__cplusplus)
}
#endif

#define _SOKOL_TRACY_ZONE(ctx, name) \
    static const struct ___tracy_source_location_data ctx##_srcloc = { name, __func__, __FILE__, (uint32_t)__LINE__, 0 }; \
    struct ___tracy_c_zone_context ctx = ___tracy_emit_zone_begin(&ctx##_srcloc, 1)
#define _SOKOL_TRACY_ZONE_END(ctx) ___tracy_emit_zone_end(ctx)

#else

#define _SOKOL_TRACY_ZONE(ctx, name)
#define _SOKOL_TRACY_ZONE_END(ctx)

#endif // SOKOL_TRACY
#endif // SOKOL_TRACY_INCLUDED
