#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

#include"Shader.h"
#include"renderer.h"
#include"Texture.h"

#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"VertexBufferLayout.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Shader shader);

float mix_value = 0.2f;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MY WINDOW", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "COULD NOT CREATE A WINDOW!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "COULD NOT INITIALIZE GLAD!" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);        //investigate
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float tex_vertices[] = {
        -0.5f, -0.5f, 0.0f,               // vertex    
         1.0f,  0.0f, 0.0f,                // color
         0.0f,  0.0f,                      // texture   //bottom left  0
        -0.5f,  0.5f, 0.0f, 
         0.0f, 1.0f, 0.0f, 
         0.0f, 4.0f,                                   //top left     1
         0.5f, 0.5f, 0.0f, 
         0.0f, 0.0f, 1.0f, 
         4.0f, 4.0f,                                   //top right    2
         0.5f, -0.5f, 0.0f, 
         1.0f, 1.0f, 0.0f, 
         2.0f, 0.0f                                    //bottom right 3
    };

    unsigned int tex_indices[] = {
       0, 1, 3, 3, 2, 1
    };
 
    VertexArray va;
    
    vertexBuffer boxVertices(tex_vertices, sizeof(tex_vertices));
    indexBuffer boxIndices(tex_indices, 6);
    
    VertexBufferLayout myLayout;
    myLayout.Push<float>(3);
    myLayout.Push<float>(3);
    myLayout.Push<float>(2);
    
    va.AddBuffer(boxVertices, myLayout);
 
    va.UnBind();
    boxVertices.UnBind();
    boxIndices.UnBind();
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // GL_LINE or GL_FILL
	
    Shader shader("VertexShader.glsl", "FragmentShader.glsl");
    shader.use();
    
    shader.setInt("ourTexture", 0);
    shader.setInt("ourTexture2", 1);

    Texture myText("awesomeface.png");
    Texture myText2("container.jpg");

    myText.setParam(GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    myText.setParam(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    myText2.setParam(GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    myText2.setParam(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    myText.Bind(0);
    myText2.Bind(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window))
	{
		processInput(window, shader);

		glClearColor(0.2f, 0.3f, 0.6f, 0.8f);
		glClear(GL_COLOR_BUFFER_BIT);
        
        va.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);  //glfwswapinterval for framerate
		glfwPollEvents();
	} 
	
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, Shader shader)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (mix_value < 1.0f)
            mix_value += 0.05f;
        shader.setFloat("mix_value", mix_value);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (mix_value > 0.0f)
            mix_value -= 0.05f;
        shader.setFloat("mix_value", mix_value);
    }
}
