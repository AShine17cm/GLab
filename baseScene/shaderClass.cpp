#include "shaderClass.h"

//�� һ���ı��ļ�
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());

		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmnetFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmnetFile);
	const char* vertexSrc = vertexCode.c_str();
	const char* fragSrc = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSrc, NULL);
	glCompileShader(vertexShader);

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSrc, NULL);
	glCompileShader(fragShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragShader);
	//�����е� shader ���ӵ�һ��
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}
void Shader::Delete()
{
	glDeleteProgram(ID);
}