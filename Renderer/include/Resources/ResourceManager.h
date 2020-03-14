#pragma once

#include <vector>
#include <Resources/Model.h>

namespace Resources::ResourceManager
{
    class ResourceManager
    {
    public:
        ResourceManager() = default;
        ~ResourceManager() = default;

        void Load(const std::string& p_path, const std::string& p_name);
        void Remove(const std::string& p_name);
        void CheckMeshLoading();

        std::shared_ptr<Resources::Model::Model> GetMesh(const std::string& p_name)
        {
            for(int i = 0; i < m_models.size(); ++i)
                if(m_models[i]->GetName() == p_name)
                    return m_models[i];

            std::cout << "No models found with name: " << p_name << "\n";
            return nullptr;
        }

    private:
        
        std::vector<std::shared_ptr<Resources::Model::Model>> m_models;
        
    };
}
