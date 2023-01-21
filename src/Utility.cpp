#include "Utility.h"

using namespace std;
namespace fs = std::filesystem;

namespace util
{
    void clear(bool color, bool depth, bool stencil, int stencilValue, float r, float g, float b, float a)
    {
        unsigned int flags = 0;

        if (color)
        {
            glClearColor(r, g, b, a);
            flags |= GL_COLOR_BUFFER_BIT;
        }

        if (depth)
        {
            flags |= GL_DEPTH_BUFFER_BIT;
        }

        if (stencil)
        {
            glClearStencil(stencilValue);
            flags |= GL_STENCIL_BUFFER_BIT;
        }

        glClear(flags);
    }

    void createCube(VertexArrayLayout& vertexArray, VertexBuffer<float> &vertexBuffer, IndexBuffer &indexBuffer)
    {
		vertexArray.clearBindings();
		vertexArray.addBinding({ POSITION, 3, GL_FLOAT, false })
			.addBinding({ NORMAL, 3, GL_FLOAT, false })
			.addBinding({ TEXCOORD, 2, GL_FLOAT, false });

        vertexBuffer.setData({
             1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
             1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
             -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
             -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
             -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
             1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
             1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
             1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
             1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
             1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
             -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
             -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
             -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
             -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
             -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
             -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
             1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
             1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
             -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
             -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        });

		vertexArray.mapToBuffer<float, 8>(vertexBuffer);

        indexBuffer.setData({
            0, 1, 2,
            0, 2, 3,
            4, 5, 6,
            4, 6, 7,
            8, 9, 10,
            8, 10, 11,
            12, 13, 14,
            12, 14, 15,
            16, 17, 18,
            16, 18, 19,
            20, 21, 22,
            20, 22, 23
        });
    }

	void createSkybox(VertexArrayLayout& vertexArray, VertexBuffer<float>& vertexBuffer)
    {
		vertexBuffer.setData({
			// positions          
		   -1.0f,  1.0f, -1.0f,
		   -1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
		   -1.0f,  1.0f, -1.0f,

		   -1.0f, -1.0f,  1.0f,
		   -1.0f, -1.0f, -1.0f,
		   -1.0f,  1.0f, -1.0f,
		   -1.0f,  1.0f, -1.0f,
		   -1.0f,  1.0f,  1.0f,
		   -1.0f, -1.0f,  1.0f,

			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,

		   -1.0f, -1.0f,  1.0f,
		   -1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f, -1.0f,  1.0f,
		   -1.0f, -1.0f,  1.0f,

		   -1.0f,  1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
		   -1.0f,  1.0f,  1.0f,
		   -1.0f,  1.0f, -1.0f,

		   -1.0f, -1.0f, -1.0f,
		   -1.0f, -1.0f,  1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
		   -1.0f, -1.0f,  1.0f,
			1.0f, -1.0f,  1.0f
		});

		vertexArray.clearBindings();
		vertexArray.addBinding({ POSITION, 3, GL_FLOAT, false });
		vertexArray.mapToBuffer<float, 3>(vertexBuffer);
    }

	unsigned int loadCubemap(const std::string& textureDir)
	{
		unsigned int cubemapID = 0;

		static const vector<string> texture_faces{
			"right.jpg",
			"left.jpg",
			"top.jpg",
			"bottom.jpg",
			"front.jpg",
			"back.jpg"
		};

		glGenTextures(1, &cubemapID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		// Cubemaps in OpenGL use a left-handed co-ordinate system while the rest of the API uses a right-handed
		// co-ordinate system.... because reasons
		stbi_set_flip_vertically_on_load(false);

		int width, height, nChannels;
		for (uint32_t i = 0; i < texture_faces.size(); i++)
		{
			unsigned char* data = stbi_load((textureDir + texture_faces[i]).c_str(), &width, &height, &nChannels, STBI_default);

			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				cout << "Failed to load cubemap texture " << texture_faces[i] << endl;
			}

			stbi_image_free(data);
		}

		stbi_set_flip_vertically_on_load(true);

		return cubemapID;
	}
}
