#include <../include/Core/OBJLoader.h>

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <ctime>
#include <ctype.h>
#include <future>

using namespace Resources::Model::OBJParser;
using namespace Resources::Model;

void OBJLoader::CalculateTriangles(const char* filePath, std::vector<Vec3>& tmp_vertices)
{
    std::ifstream ObjFile(filePath);
    if (ObjFile.is_open() == false)
    {
        std::cout << "Can't Load " << filePath << " file, please check your filePath\n";
        return;
    }

    while (!ObjFile.eof())
    {
        std::string cs;
        ObjFile >> cs;

        if (cs == "v")
        {
            Vec3 vertex;
            ObjFile >> vertex.mf_x >> vertex.mf_y >> vertex.mf_z;
            tmp_vertices.emplace_back(vertex);
        }
    }
}

void OBJLoader::CalculateUV(const char* filePath, std::vector<Vec3>& o_uvs)
{
    std::ifstream ObjFile(filePath);
    std::string line;
    std::vector<Vec3> tmp_uvs;
    std::vector<GLuint> uv_indices;

    while (std::getline(ObjFile, line))
    {
        if (line[0] == 'v' && line[1] == 't')
        {
            Vec3 uv;
            uv.mf_x = uv.mf_y = uv.mf_z = 0;
            int i = sscanf_s(line.c_str(), "%*s %f %f", &uv.mf_x, &uv.mf_y);
            if (i == 3)
                tmp_uvs.emplace_back(uv);

        }

        if (line[0] == 'f')
        {
            int id1, id2, id3, id4 = 0;

            int k = sscanf_s(line.c_str(), "%*s %*d %*c %d %*c %*d %*d %*c %d %*c %*d %*d %*c %d %*c %*d %*d %*c %d %*c %*d", &id1, &id2, &id3, &id4);
            if (k == 3)
            {
                uv_indices.emplace_back(id1 - 1);
                uv_indices.emplace_back(id2 - 1);
                uv_indices.emplace_back(id3 - 1);
            }
            else if (k == 4)
            {
                uv_indices.emplace_back(id1 - 1);
                uv_indices.emplace_back(id2 - 1);
                uv_indices.emplace_back(id3 - 1);
                uv_indices.emplace_back(id4 - 1);
            }
        }

    }
    for (unsigned int i = 0; i < uv_indices.size(); ++i)
    {
        o_uvs.emplace_back(tmp_uvs[uv_indices[i]]);
    }
}

void OBJLoader::CalculateNormals(const char* filePath, std::vector<Vec3>& o_normals)
{
    std::vector<Vec3> tmp_normals;
    std::vector<GLuint> normalIndices;
    std::ifstream ObjFile(filePath);
    std::string line;


    while (std::getline(ObjFile, line))
    {
        if (line == "" || line[0] == '#')
            continue;


        if (line[0] == 'v' && line[1] == 'n')
        {
            Vec3 normal;
            int i = sscanf_s(line.c_str(), "%*s %f %f %f", &normal.mf_x, &normal.mf_y, &normal.mf_z);
            if (i == 3)
                tmp_normals.emplace_back(normal);

        }

        if (line[0] == 'f')
        {
            int id1, id2, id3, id4 = 0;

            int k = sscanf_s(line.c_str(), "%*s %*d %*c %*d %*c %d %*d %*c %*d %*c %d %*d %*c %*d %*c %d %*d %*c %*d %*c %d", &id1, &id2, &id3, &id4);
            if (k == 3)
            {
                normalIndices.emplace_back(id1 - 1);
                normalIndices.emplace_back(id2 - 1);
                normalIndices.emplace_back(id3 - 1);
            }
            else if (k == 4)
            {
                normalIndices.emplace_back(id1 - 1);
                normalIndices.emplace_back(id2 - 1);
                normalIndices.emplace_back(id3 - 1);
                normalIndices.emplace_back(id4 - 1);
            }
            else
            {
                int l = sscanf_s(line.c_str(), "%*s %*d %*c %*c %d %*d %*c %*c %d %*d %*c %*c %d %*d %*c %*c %d", &id1, &id2, &id3, &id4);
                if (l == 3)
                {
                    normalIndices.emplace_back(id1 - 1);
                    normalIndices.emplace_back(id2 - 1);
                    normalIndices.emplace_back(id3 - 1);
                }
                else if (l == 4)
                {
                    normalIndices.emplace_back(id1 - 1);
                    normalIndices.emplace_back(id2 - 1);
                    normalIndices.emplace_back(id3 - 1);
                    normalIndices.emplace_back(id4 - 1);
                }
            }
        }
    }

    for (int i = 0; i < normalIndices.size(); ++i)
    {
        o_normals.emplace_back(tmp_normals[normalIndices[i]]);    
    }
}

void CalculateIndices(const char* filePath, std::vector<GLuint>& o_indices, std::atomic<bool>& hasQuads)
{
    std::vector<GLuint> vertexIndices, uvIndices;
    std::ifstream ObjFile(filePath);
    std::string line;
    while (std::getline(ObjFile, line))
    {

        if (line[0] == 'f')
        {
            int id1, id2, id3, id4 = 0;

            int k = sscanf_s(line.c_str(), "%*s %d %*c %*d %*c %*d %d %*c %*d %*c %*d %d %*c %*d %*c %*d %d %*c %*d %*c %*d", &id1, &id2, &id3, &id4);
            if (k == 3)
            {
                hasQuads = false;
                vertexIndices.emplace_back(id1 - 1);
                vertexIndices.emplace_back(id2 - 1);
                vertexIndices.emplace_back(id3 - 1);
            }
            else if (k == 4)
            {
                hasQuads = true;
                vertexIndices.emplace_back(id1 - 1);
                vertexIndices.emplace_back(id2 - 1);
                vertexIndices.emplace_back(id3 - 1);
                vertexIndices.emplace_back(id4 - 1);
            }
            else
            {
                int l = sscanf_s(line.c_str(), "%*s %d %*c %*c %*d %d %*c %*c %*d %d %*c %*c %*d %d %*c %*c %*d", &id1, &id2, &id3, &id4);
                if (l == 3)
                {
                    hasQuads = false;
                    vertexIndices.emplace_back(id1 - 1);
                    vertexIndices.emplace_back(id2 - 1);
                    vertexIndices.emplace_back(id3 - 1);
                }
                else if (l == 4)
                {
                    hasQuads = true;
                    vertexIndices.emplace_back(id1 - 1);
                    vertexIndices.emplace_back(id2 - 1);
                    vertexIndices.emplace_back(id3 - 1);
                    vertexIndices.emplace_back(id4 - 1);
                }
            }
        }
    }
    //Putting indices Data in output vectors
    for (int i = 0; i < vertexIndices.size(); ++i)
    {
        o_indices.emplace_back(vertexIndices[i]);
    }
}

void CalculateFinalVertices(std::vector<Vec3>& vertices, std::vector<Vec3>& finalVertices, std::vector<GLuint>& indices)
{
    for (int i = 0; i < indices.size(); ++i)
    {
        finalVertices.emplace_back(vertices[indices[i]]);
    }
}


void OBJLoader::LoadObj(const std::string& path, std::shared_ptr<Resources::Model::Model> p_model)
{

    //CLOCK FOR BENCHMARKING
    clock_t begin = clock();
	const char* filePath = path.c_str();
	std::cout << "Loading OBJ file...\n";

    std::vector<Vec3> vertices;

    //STARTING THREADS THAT WILL PROCESS THE FILE
    std::thread vertex(CalculateTriangles, filePath, std::ref(vertices));
    std::thread normals(CalculateNormals, filePath, std::ref(p_model->GetNormals()));
    std::thread indices(CalculateIndices, filePath, std::ref(p_model->GetIndices()), std::ref(p_model->GetQuadsState()));

    vertex.join();
    normals.join();
    indices.join();

    CalculateFinalVertices(vertices, p_model->GetVertices(), p_model->GetIndices());

    clock_t end = clock();
    clock_t duration = (end - begin);
    p_model->GetPromise().set_value(true);

    std::cout << "Loaded .obj file in " << duration << " ms\n";
}
