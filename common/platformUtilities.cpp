#include "common/platformUtilities.h"
#include "common/platform.h"

namespace squidge {

#if defined(SQUIDGE_PLATFORM_MACOSX)
   #include <mach-o/dyld.h>
#elif defined(SQUIDGE_PLATFORM_WINDOWS)
   #ifndef WIN32_LEAN_AND_MEAN
      #define WIN32_LEAN_AND_MEAN
   #endif
   #include <windows.h>
#endif

void getExecutablePath(boost::filesystem::path& path)
{

#if defined(SQUIDGE_PLATFORM_MACOSX)

   std::vector<char> executablePath;
   uint32_t size = 0;
   // Call to get size.
   _NSGetExecutablePath(&executablePath[0], &size);
   executablePath.resize(size);
   // Now call to get data.
   _NSGetExecutablePath(&executablePath[0], &size);
   path = &executablePath[0];

#elif defined(SQUIDGE_PLATFORM_WINDOWS)

   // Should this use the unicode version?
   // This'll have to do a std::wstring on Windows then...
   std::vector<char> executablePath;
   DWORD size = GetModuleFileNameA(NULL, &executablePath[0], 0);
   executablePath.resize(size);
   GetModuleFileNameA(NULL, &executablePath[0], size);
   path = &executablePath[0];

#else

   #error No impl of getExecutablePath on this platform!

#endif

}

void getResourceDirPath(boost::filesystem::path& path)
{

#if defined(SQUIDGE_PLATFORM_MACOSX)
   // Executable location is at 'Squidge.app/Contents/MacOS/Squidge'
   // Resource directory is at 'Squidge.app/Contents/Resources'

   getExecutablePath(path);
   path = path.parent_path().parent_path();
   path /= "Resources";

#elif defined(SQUIDGE_PLATFORM_WINDOWS)
   // Executable location is at '.../Squidge.exe'
   // Resource directory is at '.../Resources'

   getExecutablePath(path);
   path = path.parent_path();
   path /= "Resources";

#else

   #error No impl of getResourceDirPath on this platform!

#endif

}

} // namespace squidge
