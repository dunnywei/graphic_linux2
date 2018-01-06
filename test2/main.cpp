// Include standard headers
#include <stdio.h>
#include <stdlib.h>



// Include GLEW
#include <GL/glew.h>
//#include <GL/glut.h>


// Include GLFW

#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
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
    window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
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
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


    //add for tutorial 2
    GLuint VertexArrayID;
    glGenVertexArrays(1,&VertexArrayID);
    glBindVertexArray(VertexArrayID);
    //end of add for tutorial 2

    static const GLfloat g_vertex_buffer_data[]={
        /*
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        */
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    GLuint vertexbuffer;
    glGenBuffers(1,&vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);





    do{
        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear( GL_COLOR_BUFFER_BIT );

        // Draw nothing, see you in tutorial 2 !
        //adding for tutorial 2
        
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );

        glDrawArrays(GL_TRIANGLES,0,3);
        glDisableVertexAttribArray(0);
        
        //end of adding for tutorial 2
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
    

    glDeleteBuffers(1,&vertexbuffer);
    glDeleteVertexArrays(1,&VertexArrayID);
    // Close OpenGL window and terminate GLFW
    glfwTerminate();


    return 0;


}





/*
#include "test2_oglwidget.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>

class TriangleWindow : public OpenGLWindow
{
public:
    TriangleWindow();

    void initialize() override;
    void render() override;

private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
};

TriangleWindow::TriangleWindow()
    : m_program(0)
    , m_frame(0)
{
}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();
}

static const char *vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "attribute lowp vec4 colAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying lowp vec4 col;\n"
    "void main() {\n"
    "   gl_FragColor = col;\n"
    "}\n";

void TriangleWindow::initialize()
{

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");




}

void TriangleWindow::render()
{

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    GLfloat vertices[] = {
        0.0f, 0.707f,
        -0.5f, -0.5f,
        0.5f, -0.5f
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    m_program->release();

    ++m_frame;


}

*/
