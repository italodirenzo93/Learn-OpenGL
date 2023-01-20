#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "CommonInclude.h"
#include "Shader.h"

class ShaderManager
{
public:
    static ShaderManager& instance()
    {
        if (_instance == nullptr)
        {
            _instance = new ShaderManager;
        }

        return *_instance;
    }

    ~ShaderManager()
    {
        delete _instance;
    }

    /**
     * Pre-compiles and caches all shaders
     */
    void preloadShaders();

    /**
     * Purges the shader cache of any currently unused shaders
     */
    void clearUnused();

    /**
     * Look up shader program by name
     */
    std::shared_ptr<Shader> get(const std::string& name);

private:
    ShaderManager() = default;
    static ShaderManager* _instance;

    std::map<std::string, std::shared_ptr<Shader>> _shaders;

    NON_COPYABLE_OR_MOVABLE_CLASS(ShaderManager)
};

#endif
