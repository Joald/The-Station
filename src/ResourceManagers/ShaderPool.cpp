#include <fstream>
#include <Filesystem/Filesystem.h>
#include "ShaderPool.h"
#include "Exceptions/ResourceNotFoundError.h"
#include "Globals/Globals.h"


ShaderPool::storage_t::iterator ShaderPool::loadResource(std::string_view id) {
    using namespace Globals;

    auto it = storage.emplace(id, std::make_shared<sf::Shader>()).first;
    auto filePath = STEngine::Filesystem::pathToResource(resolveFolderName(FolderName::Shaders), id);
    // TODO make options for both shader types
    if (!it->second->loadFromFile(filePath, sf::Shader::Fragment)) {
        throw ResourceNotFoundError(concat({"Shader ", filePath, " could not be loaded."}));
    }
    return it;
}

ShaderPool& shaderPool() {
    static ShaderPool pool;
    return pool;
}
