#include "audioplayer.hpp"
#include <iostream>

glm::mat4 AudioPlayer::scaleMatrix;

AudioPlayer::AudioPlayer() {
	FMOD::System_Create(&system);
	system->init(100, FMOD_INIT_NORMAL, 0);

	sampleSize = 128;
	beatLastTick = 0;
}

AudioPlayer::~AudioPlayer() {
	sound->release();
	system->close();
	system->release();
}

void AudioPlayer::setPaused(bool state) {
	channel->setPaused(state);
}

void AudioPlayer::loadTrack(const char* songName) {
	system->createStream(songName, FMOD_HARDWARE, 0, &sound);
	system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
}

void AudioPlayer::updatePlayback() {
	system->update();

	spec		= new float[sampleSize];
	specLeft	= new float[sampleSize];
	specRight	= new float[sampleSize];

	channel->getSpectrum(specLeft, sampleSize, 0, FMOD_DSP_FFT_WINDOW_RECT);
	channel->getSpectrum(specRight, sampleSize, 1, FMOD_DSP_FFT_WINDOW_RECT);

	for (int i = 0; i < sampleSize; i++)
		spec[i] = (specLeft[i] + specRight[i]) / 2;

	beatDetect();

	delete [] spec;
	delete [] specRight;
	delete [] specLeft;
}

void AudioPlayer::beatDetect()
{
	bool beatDetected = false;

	int beatThresholdBar		= 0;
	unsigned int beatPostIgnore	= 100;
	float beatThresholdVolume	= 0.25f;
	
	if (spec[beatThresholdBar] >= beatThresholdVolume && beatLastTick == 0) {
		beatLastTick = GetTickCount64();
		beatDetected = true;
	}

	if (beatDetected) {
		scaleMatrix *= glm::rotate(glm::mat4(1.0), 15.f, glm::vec3(0, 0, 1));
	} 

	if (GetTickCount64() - beatLastTick >= beatPostIgnore)
		beatLastTick = 0;
}