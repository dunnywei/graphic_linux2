#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>

#include "shader.h"

using namespace  std;

GLuint LoadShaders(const char *vertex_file_path,const char *fragment_file_path)
{
   GLuint VertexShaderID=glCreateShader(GL_VERTEX_SHADER);
   GLuint FragmentShaderID=glCreateShader(GL_FRAGMENT_SHADER);
   //starts reading vertex Shader codes
   std::string VertexShaderCode;
   std::ifstream VertexShaderStream(vertex_file_path,std::ios::in);
   if(VertexShaderStream.is_open())
   {
      std::string line="";
      while(getline(VertexShaderStream,line))
      {
         VertexShaderCode+="\n"+line;
      }
      VertexShaderStream.close();
   }else
   {
      printf("Can't read file from %s \n", vertex_file_path);
      getchar();
      return 0;
   }

   //reading fragment shader code
   std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
		{
			FragmentShaderCode += "\n" + Line;
		}
		FragmentShaderStream.close();
	}else
    {
      printf("Can't read file from %s \n", fragment_file_path);
      getchar();
      return 0;
    }

    GLint Result = GL_FALSE;
	int InfoLogLength;
    //Starts compileing the vertex shader

    printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	//verify the vertex shader
    glGetShaderiv(VertexShaderID,GL_COMPILE_STATUS,&Result);
    glGetShaderiv(VertexShaderID,GL_INFO_LOG_LENGTH,&InfoLogLength);
    
    if(InfoLogLength>0)
    {
    	std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
    	glGetShaderInfoLog(VertexShaderID,InfoLogLength,NULL,&VertexShaderErrorMessage[0]);
    	printf("%s\n", &VertexShaderErrorMessage[0]);

    }
    
    //Starts compieling the framgent shading
    printf("Compiling shader : %s\n", fragment_file_path);

	char const * FragmentSourcePointer = FragmentShaderCode.c_str();

	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);
	// Verify Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}


    // Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
    


}



