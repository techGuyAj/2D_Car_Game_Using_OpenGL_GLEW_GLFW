#include "Utility_Class.h"

 GLuint Utility_Class::createShaderProgram(string vertexShader, string fragmentShader)
{
     unsigned int program;
     program = glCreateProgram();

     string vShader = readFromFile(vertexShader);
     string fShader = readFromFile(fragmentShader);
     cout << "vshadder " << vShader << endl;
     cout << "fShader " << fShader << endl;
     unsigned int vs = compileShader(vShader, GL_VERTEX_SHADER);
     unsigned int fs = compileShader(fShader, GL_FRAGMENT_SHADER);
     glAttachShader(program, vs);
     glAttachShader(program, fs);
     glLinkProgram(program);
     glValidateProgram(program);

     glDeleteShader(vs);
     glDeleteShader(fs);

     return program;
}
  GLuint  Utility_Class::compileShader(string ShaderSource, GLuint type)
 {
      unsigned int vs = glCreateShader(type);
      const char* src = ShaderSource.c_str();
      glShaderSource(vs, 1, &src, nullptr);
      glCompileShader(vs);
      //Add error handling code
      int result;
      glGetShaderiv(vs, GL_COMPILE_STATUS, &result);

      if (result == GL_FALSE)
      {
          int length;
          glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
          char* message = (char*)alloca(length * sizeof(char));

          glGetShaderInfoLog(vs, length, &length, message);

          cout << "FAILED  TO COMPIILE " << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << endl;

          cout << "Error log : " << message << endl;
          glDeleteShader(vs);
          return 0;
      }

      return vs;
 }
   string Utility_Class::readFromFile(string filePath)
  {
       filePath = "./Shaders/" + filePath;
       string shader_str = "";
       ifstream infile;
      // string path = "D:/Ajay/OpenGL/Opengl/Opengl/Shaders/" + filePath;
       infile.open(filePath);
       cout << filePath << endl;
       ostringstream ss;
       ss << infile.rdbuf();
       shader_str = ss.str();
       infile.close();
       cout <<"shader_str "<< shader_str << endl;
       return shader_str;
  }
   Utility_Class::shaderProgramSource Utility_Class::parseShader(string filePath)
   {
       enum class Shader_Type {
           None = -1,
           Vertex = 0,
           fragment = 1,
       };

       //string path = "D:/Ajay/OpenGL/Opengl/Opengl/Shaders/" + filePath;
       fstream stream(filePath);
       stringstream ss[2];
       string line;
       Shader_Type type = Shader_Type::None;
       while (getline(stream, line))
       {
           if (line.find("#shader") != string::npos)
           {

               if (line.find("vertex") != string::npos)
               {
                   type = Shader_Type::Vertex;
                   //change mode to vertex
               }

               if (line.find("fragment") != string::npos)
               {
                   //change mode to fragment
                   type = Shader_Type::fragment;
               }
           }
           else
           {
               ss[(int)type] << line << "\n";;
           }

       }
       return { ss[0].str(),ss[1].str() };
   }
   GLuint  Utility_Class::buildTexture_PNG(string filePath)
   {
       filePath = "./Assets/Images/" + filePath;
       GLuint id;
       unsigned char* buffer = nullptr;
       int width = 0, height = 0;
       int channels = 4;

       stbi_set_flip_vertically_on_load(1);
       buffer = stbi_load(filePath.c_str(), &width, &height, &channels, 4);
       glGenTextures(1, &id);
       glBindTexture(GL_TEXTURE_2D, id);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
       glBindTexture(GL_TEXTURE_2D, 0);

       if (buffer)
           stbi_image_free(buffer);

       return id;
   }