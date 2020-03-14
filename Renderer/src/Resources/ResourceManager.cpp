#include <thread>
#include <Core/OBJLoader.h>
#include <Resources/ResourceManager.h>

void Resources::ResourceManager::ResourceManager::Load(const std::string& p_path, const std::string& p_name)
{
    //Instanciating Model
    m_models.emplace_back(std::make_shared<Resources::Model::Model>(p_name));
    m_models.back()->GetLoadedStatePromise() = m_models.back()->GetPromise().get_future();

    //Creating a thread that will load the model async
    std::thread createModel(OBJParser::OBJLoader::LoadObj, p_path, m_models.back());
    createModel.detach();
}

void Resources::ResourceManager::ResourceManager::Remove(const std::string& p_name)
{
    //Finding the model by name and deleting it
    for (int i = 0; i < m_models.size(); ++i)
        if (m_models[i]->GetName() == p_name)
            m_models.erase(m_models.begin() + i);
}

void Resources::ResourceManager::ResourceManager::CheckMeshLoading()
{
    try
    {
        for (int i = 0; i < m_models.size(); ++i)
        {
            if (m_models[i] == nullptr)
                throw std::string("Model INVALID\n");

            if (m_models[i]->GetLoadedStatePromise().valid())
            {
                if (m_models[i]->GetLoadedStatePromise()._Is_ready())
                    if (m_models[i]->GetLoadedStatePromise().get())
                    {
                        m_models[i]->GetLoadedState() = true;
                    }
            }            
        }
    }
    catch (const std::string str)
    {
        std::cout << str;
    }
}
