#pragma once

// Platform detection code from:
// http://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
#if _WIN64
   #define SQUIDGE_PLATFORM_WINDOWS
   #define SQUIDGE_PLATFORM_WIN64
#elif _WIN32
   #define SQUIDGE_PLATFORM_WINDOWS
   #define SQUIDGE_PLATFORM_WIN32
#elif __APPLE__
   #include "TargetConditionals.h"
   #define SQUIDGE_PLATFORM_APPLE
   #if TARGET_OS_IPHONE
      #define SQUIDGE_PLATFORM_IPHONE
   #elif TARGET_OS_MAC
      #define SQUIDGE_PLATFORM_MACOSX
   #else
      #error Unknown Apple platform!
   #endif
#elif __linux
   #define SQUIDGE_PLATFORM_LINUX
#else
   #error Unknown platform!
#endif
