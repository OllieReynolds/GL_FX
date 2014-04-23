#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include <string>

class ShaderManager 
{
	ShaderManager();
	~ShaderManager();

	int registerShader(const std::string& name);
	int setActiveShader(const std::string& name);
};

#endif // SHADERMANAGER_HPP