Slab's Quests Underground Into Dungeons, Goring Enemies
(name is tentative.)


To build, you need:
* cmake
* SDL
* SDL_image
* boost

On OS X this is pretty easy with homebrew:
  brew install sdl sdl_image boost cmake

Haven't worked on Windows yet.


I've been building with:
   cd build
   cmake ..
   make

On Windows you should do this from a Windows SDK/Visual Studio command
prompt, and use 'nmake' instead of 'make'.
(I don't know what to do about dependencies. Sorry.)
