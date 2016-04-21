#include "Window.h"

const char* window_title = "GLFW Starter Project";

int Window::width;
int Window::height;
const char * filename = "bunny.obj";
//const char * file;
OBJObject * object = new OBJObject(filename);

//OBJObjects
OBJObject  * bunny = new OBJObject("bunny.obj");
OBJObject * dragon = new OBJObject("dragon.obj");
OBJObject * bear = new OBJObject("bear.obj");

bool toggle = true;

double lastTime = glfwGetTime();

void Window::clean_up()
{
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

    //ADDED
    glfwGetFramebufferSize(window, &width, &height);
    
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
	Window::width = width;
	Window::height = height;
	// Set the viewport size
	glViewport(0, 0, width, height);
	// Set the matrix mode to GL_PROJECTION to determine the proper camera properties
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the perspective of the projection viewing frustum
	gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0);
	// Move camera back 20 units so that it looks at the origin (or else it's in the origin)
	glTranslatef(0, 0, -20);
}

//correct spot
//multiply matrices to move
//trans, scale, trans back 
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
   // double currentTime = glfwGetTime();
  //  float deltaTime = float(currentTime - lastTime);
    
    
    // Check for a key press
    if (action == GLFW_PRESS)
    {
        // Check if escape was pressed
        if (key == GLFW_KEY_ESCAPE)
        {
            // Close the window. This causes the program to also terminate.
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        else if(key == GLFW_KEY_F1){
            object = bunny;
            //object->Drawable("bunny.obj", object);
        }
       
        else if(key == GLFW_KEY_F2){
            object = dragon;
           // object->Drawable("bear.obj", object);
        }
        
        else if(key == GLFW_KEY_F3){
            object = bear;
            //object->Drawable("dragon.obj", object);
        }
       
        //move right: pos. x
        else if(key == GLFW_KEY_X && mods == GLFW_MOD_SHIFT){
            
            object-> toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f , 0.0f))*object->toWorld;

        }
        
        else if (key == GLFW_KEY_X && mods != GLFW_MOD_SHIFT){
            object-> toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f , 0.0f))*object->toWorld;
   
        }
        
        //move pos. y
        else if (key == GLFW_KEY_Y && mods == GLFW_MOD_SHIFT){
            object-> toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f , 0.0f))*object->toWorld;
        }
        
        else if (key == GLFW_KEY_Y && mods != GLFW_MOD_SHIFT){
            object-> toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f , 0.0f))*object->toWorld;
            
        }
        //move pos. z
        else if (key == GLFW_KEY_Z && mods == GLFW_MOD_SHIFT){
            object-> toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f , -1.0f))*object->toWorld;
        }
        
        else if (key == GLFW_KEY_Z && mods != GLFW_MOD_SHIFT){
            object-> toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f , 1.0f))*object->toWorld;
        }
        //o/O doesn't work
        else if (key == GLFW_KEY_O && mods == GLFW_MOD_SHIFT){
            object-> toWorld = glm::rotate(glm::mat4(1.0f), -0.3f, glm::vec3(0.0f,0.0f,1.0f)) * object->toWorld;
        }
        else if (key == GLFW_KEY_O && mods != GLFW_MOD_SHIFT){
            object-> toWorld = glm::rotate(glm::mat4(1.0f), 0.3f, glm::vec3(0.0f,0.0f,1.0f))* object->toWorld;
        
        }
        else if (key == GLFW_KEY_S && mods == GLFW_MOD_SHIFT){
            object-> toWorld = object->toWorld * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
        }
        else if (key == GLFW_KEY_S && mods != GLFW_MOD_SHIFT){
            object-> toWorld = object->toWorld * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.5f));
        }
        else if (key == GLFW_KEY_R){
            object->toWorld = glm::mat4(1.0f);
        }
        else if (key == GLFW_KEY_P && mods == GLFW_MOD_SHIFT){
            //point p : make global
            glPointSize(10.0f);
        }
        else if (key == GLFW_KEY_P && mods != GLFW_MOD_SHIFT){
            glPointSize(0.5f);
        }
        //FIXME

        else if (key == GLFW_KEY_T  && mods != GLFW_MOD_SHIFT){
            toggle = true;
            
        }
        else if (key == GLFW_KEY_T && mods == GLFW_MOD_SHIFT){
            toggle = false;
        }
        
    }
    
}


void Window::initialize_objects()
{
    
}

void Window::idle_callback(){
	// Perform any updates as necessary. Here, we will spin the cube slightly.
    object->update();
}

void Window::display_callback(GLFWwindow* window){
	// Clear the color and depth buffers
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Set the matrix mode to GL_MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	// Load the identity matrix
	glLoadIdentity();
	
	// Render objects -- right
    object->draw();

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}




