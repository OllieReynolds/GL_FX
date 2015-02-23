#include "shader_manager.hpp"

ShaderManager::ShaderManager() {
	shaderDir dir;
	dir.vertex = "shader/cubefield.vert";
	dir.fragment = "shader/cubefield.frag";
	registerShader("Cubefield", dir);
	
	dir.vertex = "shader/skybox.vert";
	dir.fragment = "shader/skybox.frag";
	registerShader("Skybox", dir);

	dir.vertex = "shader/panel.vert";
	dir.fragment = "shader/panel.frag";
	registerShader("Panel", dir);

	dir.vertex = "shader/plane.vert";
	dir.fragment = "shader/plane.frag";
	registerShader("Plane", dir);

	dir.vertex = "shader/cam.vert";
	dir.fragment = "shader/cam.frag";
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