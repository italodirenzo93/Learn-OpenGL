#include "Material.h"

void Material::apply(const Shader &program, const std::string &uniformName) const
{
    {
        auto texture = diffuse.lock();
        if (texture)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture->getID());

            program.setInt(uniformName + ".diffuse", 0);
        }
    }
    {
        auto texture = specular.lock();
        if (texture)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture->getID());

            program.setInt(uniformName + ".specular", 1);
        }
    }

	program.setFloat(uniformName + ".shininess", shininess);
}
