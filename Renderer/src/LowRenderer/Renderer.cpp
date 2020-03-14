#include <../include/LowRenderer/Renderer.h>

void Renderer::TryToRender(std::shared_ptr<Mesh> p_mesh, Shader& p_shader, Camera& p_camera, Resources::ResourceManager::ResourceManager& p_manager)
{
    try
    {
        p_manager.CheckMeshLoading();

        if (p_mesh == nullptr)
            throw p_mesh;

        if (p_manager.GetMesh(p_mesh->m_modelName) == nullptr)
            throw std::string("Mesh Getter INVALID\n");


        if (p_manager.GetMesh(p_mesh->m_modelName)->GetLoadedState() && p_mesh->GetInitStatus())
        {
            std::cout << "Mesh Init...\n";
            p_mesh->m_model = p_manager.GetMesh(p_mesh->m_modelName);
            p_mesh->Init();
            p_mesh->SetInitStatus(false);

        }

        if (p_mesh->GetLoadedStatus())
        {
            Render(p_mesh, p_shader, p_camera);
        }
    }
    catch (Mesh* meshError)
    {
        std::cout << "Mesh is INVALID with adress : " << &meshError << "\n";
    }
    catch (const std::string str)
    {
        std::cout << str;
    }
}

void Renderer::Render(std::shared_ptr<Mesh> p_mesh, Shader& p_shader, Camera& p_camera)
{
    GLfloat camTransform[16];
    Mat4::MatrixToShader(p_camera.m_transform, camTransform);
    GLfloat* cam = camTransform;

    GLfloat meshTransform[16];
    Mat4::MatrixToShader(p_mesh->GetTransform(), meshTransform);
    GLfloat* mesh = meshTransform;

    GLfloat perspectiveMat[16];
    Mat4::MatrixToShader(Mat4::CreatePerspectiveMatrix(75.0f, 1680.0f / 1050.0f, 0.5f, 1000.0f), perspectiveMat);
    GLfloat* perspective = perspectiveMat;

    p_shader.m_time += 0.001f;

	glUseProgram(p_shader.GetShaderID());

	glUniform3f(p_shader.m_shaderData[1], p_camera.m_position.mf_x, p_camera.m_position.mf_y, p_camera.m_position.mf_z);
	glUniform3f(p_shader.m_shaderData[5], p_shader.GetColor().mf_x, p_shader.GetColor().mf_y, p_shader.GetColor().mf_z);
	glUniform1f(p_shader.m_shaderData[6], p_shader.m_time);
	glUniformMatrix4fv(p_shader.m_shaderData[2], 1, GL_FALSE, mesh);
	glUniformMatrix4fv(p_shader.m_shaderData[3], 1, GL_FALSE, camTransform);
	glUniformMatrix4fv(p_shader.m_shaderData[4], 1, GL_FALSE, perspective);

	glBindVertexArray(p_mesh->VAO);

	if(!p_mesh->m_model->GetQuadsState())
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(p_mesh->m_model->GetIndices().size()), GL_UNSIGNED_INT, nullptr);
    else
		glDrawElements(GL_QUADS, static_cast<GLsizei>(p_mesh->m_model->GetIndices().size()), GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
}
