#include "shader_manager.hpp"

ShaderManager::ShaderManager() {
	shaderDir dir;
	dir.vertex = "shader/cubefield.vs";
	dir.fragment = "shader/default.fs";
	registerShader("Cubefield", dir);
	
	dir.vertex = "shader/skybox.vs";
	dir.fragment = "shader/skybox.fs";
	registerShader("Skybox", dir);

	dir.vertex = "shader/panel.vs";
	dir.fragment = "shader/panel.fs";
	registerShader("Panel", dir);

	dir.vertex = "shader/plane.vs";
	dir.fragment = "shader/panel.fs";
	registerShader("Plane", dir);

	dir.vertex = "shader/cam.vs";
	dir.fragment = "shader/cam.fs";
	registerShader("Camera", dir);
}

ShaderManager::~ShaderManager() {
	for (auto it = shaderTable.begin(); it != shaderTable.end(); ++it) {
		delete it->second;
		shaderTable.erase(it);
	}

	shaderTable.clear();
}

int ShaderManager::registerShader(const std::string& name, const shaderDir& dir) {
	Shader* s = new Shader();

	if (s->create(dir) == -1) {
		delete s;
		cout << "Failed to register: " + name + " program" << endl; 
		return -1;
	} else {
		shaderTable[name] = s;
		return 0;
	}
}

Shader* ShaderManager::getShader(const std::string& name) {
	Shader* s = shaderTable[name];
	s->use();
	return s;
}