Camera Controls:

- WASD to move Forward, Backward, Left and Right
- LeftShift to move Up
- LeftControl to move Down

To load a resource:
ResourceManager.Load("filePath", "name you choose for the resource");


!!! IMPORTANT !!!
-The resources need to be .obj files
-The file needs to be all triangles, or all quads. Not both mixed up. 
Else, your resource might not load properly, or in bad cases might crash the program.


To create a gameobject:
std::shared_ptr<Mesh> GameObject(new Mesh("Name of the resource you want"));

Then in main Loop:
Renderer::TryToRender(GameObject, Shader, Camera, ResourceManager);

And BOOM, magic, you got your mesh rendered !