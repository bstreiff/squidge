#include "client/ResourceManager.h"
#include "common/platformUtilities.h"

namespace squidge {
namespace client {

ResourceManager& ResourceManager::get()
{
   static ResourceManager r;
   return r;
}

ResourceManager::ResourceManager() :
   _resourceDir(),
   _loadedTextures()
{
   getResourceDirPath(_resourceDir);
}

ResourceManager::~ResourceManager()
{ }

boost::shared_ptr<Texture> ResourceManager::getTexture(const std::string& name)
{
   std::map< std::string, boost::shared_ptr<Texture> >::const_iterator itr = _loadedTextures.find(name);
   if (itr == _loadedTextures.end())
   {
      // Not present, we have to load it.
      return _loadTexture(name);
   }

   // We found it.
   return itr->second;
}

boost::shared_ptr<Texture> ResourceManager::_loadTexture(const std::string& name)
{
   // TODO: Security concern: name can contain things like '..'.
   boost::filesystem::path filename = _resourceDir / name;

   // TODO: Should I move the texture-loading code from Texture ctor into here?
   // Texture then just becomes a holder for id/w/h...

   boost::shared_ptr<Texture> newTexture(new Texture(filename));

   _loadedTextures[name] = newTexture;
   
   return newTexture;
}

} // namespace client
} // namespace squidge
