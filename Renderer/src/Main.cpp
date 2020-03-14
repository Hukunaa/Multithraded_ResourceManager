#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ctime>

#include <../include/Resources/Shader.h>
#include <../include/Resources/ResourceManager.h>

#include <../include/LowRenderer/Mesh.h>
#include <../include/LowRenderer/Camera.h>
#include <../include/LowRenderer/Renderer.h>

// !!! READ THE README.txt FIRST !!!

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    }
}

int main()
{
	//Creating Window and Initializing Glew/GLFW
    std::cout << "Initializing GLEW and GLFW...\n";
    GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1680, 1050, "Emini Renderer", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Error init GLEW\n";
    }

	std::cout << glGetString(GL_VERSION) << "\n";
    glfwSetKeyCallback(window, key_callback);

	Camera mainCamera;
    Resources::ResourceManager::ResourceManager Manager;

    //Loading models
    Manager.Load("res/OBJ/BarrocMiniTable.obj", "mini");
    Manager.Load("res/OBJ/BarrocTable.obj", "table");
    Manager.Load("res/OBJ/Cube.obj", "cube");
    Manager.Load("res/OBJ/dodge.obj", "dodge");
    Manager.Load("res/OBJ/Minion.obj", "minion");
    Manager.Load("res/OBJ/Monkey.obj", "monkey");
    Manager.Load("res/OBJ/Kindred.obj", "rift");

   
	//Creating GameObjects
    std::shared_ptr<Mesh> Tank(new Mesh("dodge"));
    std::shared_ptr<Mesh> Tank2(new Mesh("mini"));
    std::shared_ptr<Mesh> Tank3(new Mesh("table"));
    std::shared_ptr<Mesh> Tank4(new Mesh("cube"));
    std::shared_ptr<Mesh> Tank5(new Mesh("minion"));
    std::shared_ptr<Mesh> Tank6(new Mesh("rift"));
    std::shared_ptr<Mesh> Rift(new Mesh("rift"));

	//Creating Shader
	Shader BasicShader;
	BasicShader.GetColor() = { 0.8f, 0.8f, 1.0f };
	BasicShader.LoadRainBowShader();
	BasicShader.SetupRainBowShader();


	//Setup DrawMode
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

    //deltaTime
    clock_t deltaTimeOldC;
    clock_t deltaTimeC = 0;
    float angle {0};

	//Main Loop
	while (!glfwWindowShouldClose(window))
	{
        deltaTimeOldC = deltaTimeC;
        deltaTimeC = clock();
        float deltaTime = (deltaTimeC - deltaTimeOldC) * 0.001f;

		angle += 10 * deltaTime;

        //POSITION, ROTATION AND SCALE UPDATES
		Tank->UpdatePosition(0, 0, -6);
		Tank2->UpdatePosition(-20, 0, -6);
		Tank3->UpdatePosition(40, 0, -6);
		Tank4->UpdatePosition(-40, 0, -6);
		Tank5->UpdatePosition(30, -8, -6);
        Tank6->UpdatePosition(20, -8, -6);
        

        Rift->UpdateScale(0.2f);
        Tank->UpdateScale(2);
        Tank2->UpdateScale(0.1f);
        Tank6->UpdateScale(0.1f);

        Rift->UpdateRotation(angle, 0, 1, 0);
	    Tank->UpdateRotation(angle, 0, 1, 0);
	    Tank2->UpdateRotation(-angle, 0, 1, 0);
	    Tank3->UpdateRotation(angle, 0, 1, 0);
	    Tank4->UpdateRotation(-angle, 0, 1, 1);
	    Tank5->UpdateRotation(angle, 0, 1, 0);
	    Tank6->UpdateRotation(-angle, 1, 0, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        
        mainCamera.UpdatePositionWithKeyBoard(deltaTime * 10, window);

		//Renderering each GameObject
        Renderer::TryToRender(Tank, BasicShader, mainCamera, Manager);
        Renderer::TryToRender(Tank2, BasicShader, mainCamera, Manager);
        Renderer::TryToRender(Tank3, BasicShader, mainCamera, Manager);
        Renderer::TryToRender(Tank4, BasicShader, mainCamera, Manager);
        Renderer::TryToRender(Tank5, BasicShader, mainCamera, Manager);
        Renderer::TryToRender(Tank6, BasicShader, mainCamera, Manager);
        Renderer::TryToRender(Rift, BasicShader, mainCamera, Manager);
        
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
	return 0;
}