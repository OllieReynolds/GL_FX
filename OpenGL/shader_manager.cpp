#include "shader_manager.hpp"

ShaderManager::ShaderManager() {
	shaderDir dir;
	dir.vertex = "shader/cubefield_vs.glsl";
	dir.fragment = "shader/cubefield_fs.glsl";
	registerShader("Cubefield", dir);
	
	dir.vertex = "shader/skybox_vs.glsl";
	dir.fragment = "shader/skybox_fs.glsl";
	registerShader("Skybox", dir);

	dir.vertex = "shader/panel_vs.glsl";
	dir.fragment = "shader/panel_fs.glsl";
	registerShader("Panel", dir);

	dir.vertex = "shader/plane_vs.glsl";
	dir.fragment = "shader/plane_fs.glsl";
	registerShader("Plane", dir);

	dir.vertex = "shader/cam_vs.glsl";
	dir.fragment = "shader/cam_fs.glsl";
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