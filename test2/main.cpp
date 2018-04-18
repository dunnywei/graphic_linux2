#include <stdio.h>
#include <stdlib.h>



#include <GL/glew.h>



#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;


int main( void )
{





    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Modified tutorials", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize 
    glewExperimental = GL_TRUE;//Most imporotant

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    printf("after glewInit() \n");
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);


    

    GLuint VertexArrayID;
    glGenVertexArrays(1,&VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    static const GLfloat verts[]={
        
        +0.0f, +0.0f, //0
        +1.0f,+0.0f,+0.0f, //For 0 vertex's color in RGB lec 9
        +1.0f,+1.0f,//1
        +1.0f,+0.0f,+0.0f, //For 1 vertex's color in RGB lec 9
        -1.0f,+1.0f,  //2
        +1.0f,+0.0f,+0.0f, //For 2 vertex's color in RGB lec 9
        -1.0f,-1.0f,//3
        +1.0f,+0.0f,+0.0f, //For 3 vertex's color in RGB lec 9  
        +1.0f,-1.0f,//4
        +1.0f,+0.0f,+0.0f, //For 4 vertex's color in RGB lec 9
        
        
    };

    GLuint vertexBufferID;
    glGenBuffers(1,&vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_STATIC_DRAW);

    GLushort indices[]= {0,1,2,0,3,4};
    GLuint indexBufferID;
    glGenBuffers(1,&indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW );

    


    do{
        glClear( GL_COLOR_BUFFER_BIT );

                
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferID);
        
        glVertexAttribPointer(0, 
                          2, //Two floating points make one vetrices 
                          GL_FLOAT,
                          GL_FALSE,//normalized
                          sizeof(float)*5,//strides->distance. of the 0 vertex to 1 vertex 
                          (void*)0);

        glEnableVertexAttribArray(1);//second attribute, color lecture 9(6:13)
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float)*5,(char*)(sizeof(float)*2));//->Lecture 9(6:44)

        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);

        glDisableVertexAttribArray(0);
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
    

    glDeleteBuffers(1,&vertexBufferID);
    glDeleteBuffers(1,&indexBufferID);
    glDeleteVertexArrays(1,&VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();


    return 0;


}

