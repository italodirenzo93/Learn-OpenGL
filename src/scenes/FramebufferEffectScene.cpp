#include "FramebufferEffectScene.h"
#include "ShaderManager.h"

using namespace std;

FramebufferEffectScene::FramebufferEffectScene(const Camera& camera) : _camera(camera)
{
	// Create framebuffer
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Create texture to render to
	{
		glGenTextures(1, &renderTexture);
		glBindTexture(GL_TEXTURE_2D, renderTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	{
		glGenTextures(1, &depthTexture);
		glBindTexture(GL_TEXTURE_2D, depthTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 1024, 720, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "Error building framebuffer..." << endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	quadVertices.setData({
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top right

		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top right
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
	});

	// Create VAO
	quadVertices.bind();
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	quadVertices.unbind();
}

void FramebufferEffectScene::render(float deltaTime)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto shader = ShaderManager::instance().get("basic");
	shader->activate();

	_camera.project(*shader);

	// Draw some stuff

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	_camera.unproject(*shader);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->setMat4("uMatModel", glm::identity<glm::mat4>());

	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderTexture);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
