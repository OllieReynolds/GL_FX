#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include <string>
#include <unordered_map>

#include "shader.hpp"

class ShaderManager 
{
public:
	ShaderManager();
	~ShaderManager();

	int registerShader(const std::string& name, const shaderDir& dir);
	Shader* getShader(const std::string& name);

private:
	std::unordered_map<std::string, Shader*> shaderTable;
};

#endif // SHADERMANAGER_HPP