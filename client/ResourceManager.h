#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <boost/utility.hpp>
#include <map>
#include <string>
#include "client/Texture.h"

namespace squidge {
namespace client {

class ResourceManager : boost::noncopyable
{
public:
   // There's a singleton ResourceManager.
   // ... not sure how I feel about this, but it's okay for now.
   static ResourceManager& get();

   boost::shared_ptr<Texture> getTexture(const std::string& name);

private:
   ResourceManager();
   ~ResourceManager();

   boost::shared_ptr<Texture> _loadTexture(const std::string& name);

   boost::filesystem::path _resourceDir;
   std::map< std::string, boost::shared_ptr<Texture> > _loadedTextures;
};

} // namespace client
} // namespace squidge
