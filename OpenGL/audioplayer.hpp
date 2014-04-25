#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <algorithm>
#include <Windows.h>

#include "include\FMOD_64-4.44.23\fmod.hpp"
#include "include\GLM-0.9.4.4\glm.hpp"
#include "include\GLM-0.9.4.4\gtc\quaternion.hpp"
#include "include\GLM-0.9.4.4\gtx\quaternion.hpp"
#include "include\GLM-0.9.4.4\gtc\matrix_transform.hpp"

class AudioPlayer
{
public:
	AudioPlayer();
	~AudioPlayer();

	void loadTrack(const char* songName);
	void setPaused(bool state);
	void updatePlayback();

	void create();
	void update();
	void kill();

	static glm::mat4 scaleMatrix;

private:
	char* songName;
	
	FMOD::Sound*	sound;
	FMOD::System*	system;
	FMOD::Channel*	channel;

private:
	void beatDetect();

	int	sampleSize;
	int	beatLastTick;
	
	float* spec;
	float* specLeft;
	float* specRight; 
};

#endif // AUDIO_HPP