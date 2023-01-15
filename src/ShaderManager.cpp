//
// Created by Italo on 1/13/2023.
//

#include "ShaderManager.h"

#include <fstream>
using namespace std;


ShaderManager* ShaderManager::_instance = nullptr;


static const vector<string> ShaderNames {"basic", "lit", "mesh", "single_color"};
static const string shaderDirectory = "./resources/shaders/";


void ShaderManager::preloadShaders()
{
    for (auto& shader : ShaderNames)
    {
        // Check to see if we already compiled this shader program
        if (_shaders.find(shader) != _shaders.cend())
        {
            // if so, skip it
            continue;
        }

        string vertexPath = shaderDirectory + shader + ".vert";
        string fragmentPath = shaderDirectory + shader + ".frag";

        ifstream ifs;

        ifs.open(vertexPath);
        if (!ifs.is_open())
        {
            cout << "Missing vertex shader for " << shader << " program" << endl;
            continue;
        }

        ifs.close();

        ifs.open(fragmentPath);
        if (!ifs.is_open())
        {
            cout << "Missing fragment shader for " << shader << " program" << endl;
            continue;
        }

        ifs.close();

        _shaders.emplace(shader, make_shared<Shader>(vertexPath.c_str(), fragmentPath.c_str()));
    }
}

shared_ptr<Shader> ShaderManager::get(const string& name)
{
    auto shader = _shaders[name];

    if (!shader)
    {
        auto vertexPath = shaderDirectory + name + ".vert";
        auto fragmentPath = shaderDirectory + name + ".frag";
        shader = make_shared<Shader>(vertexPath.c_str(), fragmentPath.c_str());

        if (shader)
        {
            _shaders[name] = shader;
        }
        else
        {
            cout << "No shader found named " << name << endl;
            return nullptr;
        }
    }

    return shader;
}
