#ifdef _WIN32
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      #define WINDOWS
   #else
      #define WINDOWS
   #endif
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
        #define APPLE
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    // linux
    #define LINUX
#elif __unix__ // all unices not caught above
    // Unix
    #define LINUX
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif