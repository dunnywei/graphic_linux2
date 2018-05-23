#include <stdio.h>
#include <stdlib.h>
#include  <string>


#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <fstream>

using namespace glm;
using namespace std;

GLFWwindow* window;


//extern const std::string vertexShaderCode;
//extern const std::string fragmentShaderCode;

//extern const char* vertexShaderCode;
//extern const char* fragmentShaderCode;

std::string readShaderCode(const char* fileName)
{
   cout<<"file name is "<<fileName<<" starts "<<std::endl;
   ifstream meInput(fileName);
   if(!meInput.good())
   {
     std::cout<<"load file fail"<<fileName<<std::endl; //Lecture 16->03:21
     exit(1);
   }
   
   return std::string(
      std::istreambuf_iterator<char>(meInput),
      std::istreambuf_iterator<char>());//Lecture 16->06:53
}

bool checkShaderStatus(GLuint shaderID)
{
    //start of lecture 16
    GLint compileStatus;
    glGetShaderiv(shaderID,GL_COMPILE_STATUS,&compileStatus);
    //it means that the last argument could be the index vector as compileStatus[10];(4:15)
    //when we talk about array in OpenGL->it means list of sequence of int (4:21)
    if(compileStatus!=GL_TRUE)//4:51
    {
        GLint infologLength;
        glGetShaderiv(shaderID,GL_INFO_LOG_LENGTH,&infologLength); //lecture 16->6:25
        GLchar *buffer=new GLchar[infologLength];

        GLsizei buffersize;
        glGetShaderInfoLog(shaderID,infologLength,&buffersize,buffer);//Lecture 16->8:51
        std::cout<<"buffer is"<<buffer<<std::endl;//Lecture 16->9:48

        delete [] buffer;
        return false;
    }
    return true;
    //end of lecture 16
}

bool checkProgramStatus(GLuint programID)
{
    //start of lecture 17
    GLint linkStatus;
    glGetProgramiv(programID,GL_LINK_STATUS,&linkStatus);

    //it means that the last argument could be the index vector as linkStatus[10];(4:15)
    //when we talk about array in OpenGL->it means list of sequence of int (4:21)
    if(linkStatus!=GL_TRUE)//4:51
    {
        GLint infologLength;
        glGetProgramiv(programID,GL_INFO_LOG_LENGTH,&infologLength); //lecture 16->6:25
        GLchar *buffer=new GLchar[infologLength];
        //GLchar *buffer=new GLchar[50];
        GLsizei buffersize;
        glGetProgramInfoLog(programID,infologLength,&buffersize,buffer);//Lecture 16->8:51
        std::cout<<"@checkProgramStatus,buffer is"<<buffer<<endl;//Lecture 16->9:48

        delete [] buffer;
        return false;
    }
    return true;
    //end of lecture 17
    //return checkStatus(shaderID,glGetProgramiv,glGetProgramInfoLog,GL_LINK_STATUS);

}
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
        +0.0f, +1.0f, //0
        +1.0f,+0.0f,+0.0f, //For 0 vertex's color in RGB lec 9
        -1.0f,-1.0f,//1
        +0.0f,+1.0f,+0.0f, //For 3 vertex's color in RGB lec 9  
        +1.0f,-1.0f,//2
        +0.0f,+0.0f,+1.0f, //For 4 vertex's color in RGB lec 9        
    };

    GLuint vertexBufferID;
    glGenBuffers(1,&vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_STATIC_DRAW);

    GLushort indices[]= {0,1,2};
    GLuint indexBufferID;
    glGenBuffers(1,&indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW );

    
    GLuint vertexShaderID=glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID=glCreateShader(GL_FRAGMENT_SHADER);

    

    const GLchar* adapter[1];

    


    //Lecture 17->starts here


    //adapter[0]=(const GLchar *)vertexShaderCode;

    std::string temp=readShaderCode("VertexShaderCode.glsl");
    adapter[0]=temp.c_str();//Lecture 16->05:00->starts here


    glShaderSource(vertexShaderID,1,adapter,0);

    //adapter=(const GLchar *)fragmentShaderCode.c_str();

    //adapter[0]=(const GLchar *)fragmentShaderCode;

    temp=readShaderCode("FragmentShaderCode.glsl");
    adapter[0]=temp.c_str();

    glShaderSource(fragmentShaderID,1,adapter,0);

    glCompileShader(vertexShaderID);
    glCompileShader(fragmentShaderID);

    if(!checkShaderStatus(vertexShaderID)||!checkShaderStatus(fragmentShaderID))
    {
        return -1;
    }

    GLuint programID=glCreateProgram();
    glAttachShader(programID,vertexShaderID);
    glAttachShader(programID,fragmentShaderID);
    glLinkProgram(programID);

    if(!checkProgramStatus(programID)) //Lecture 17->2:07
    {
        return -1;
    }


    do{
        glClear( GL_COLOR_BUFFER_BIT );

        
        glUseProgram(programID);

                
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

        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_SHORT,0);


        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
    
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();


    return 0;


}

