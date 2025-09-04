#ifdef ETC_DEBUG_PRINT
    #include <cstdio>
    #define DEBUG_PRINT(fmt, ...) std::printf("etc2comp: " fmt, __VA_ARGS__)
#else
    inline void __debug_sink(...) {} // Prevent unused arg warnings
    #define DEBUG_PRINT(fmt, ...) __debug_sink(__VA_ARGS__)
#endif
