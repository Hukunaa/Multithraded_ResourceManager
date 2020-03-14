#pragma once

#include <../include/LowRenderer/Mesh.h>
#include <../include/Resources/Shader.h>
#include <../include/LowRenderer/Camera.h>
#include <../include/Resources/ResourceManager.h>

using namespace Resources::Shader;
using namespace LowRenderer::Camera;
using namespace LowRenderer::Mesh;

class Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;

    static void TryToRender(std::shared_ptr<Mesh> p_mesh, Shader& p_shader, Camera& p_camera, Resources::ResourceManager::ResourceManager& p_manager);
	static void Render(std::shared_ptr<Mesh> p_mesh, Shader& p_shader, Camera& p_camera);
};

