#include "Game2D.h"
#include "TankExample.h"
//#include "fmod.h"  // c-context
#include "fmod.hpp"
#include <iostream>
#include <conio.h>

/*
fmod api documentation
https://www.fmod.com/resources/documentation-api
*/

using namespace std;

int main()
{
	//jm::MouseExample().init("This is my digital canvas!", 1000, 1000, false).run();

	FMOD::System     *system(nullptr);
	FMOD::Sound      *sound(nullptr);
	FMOD::Channel    *channel(nullptr);
	FMOD_RESULT       result;
	unsigned int      version;
	void             *extradriverdata(nullptr);

	result = FMOD::System_Create(&system);
	if (result != FMOD_OK) return -1;

	result = system->getVersion(&version);
	if (result != FMOD_OK) return -1;

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
	if (result != FMOD_OK) return -1;

	//result = system->createSound("singing.wav", FMOD_LOOP_NORMAL, 0, &sound);
	result = system->createSound("ost.wav", FMOD_LOOP_NORMAL, 0, &sound); // .mp3 files work!
	if (result != FMOD_OK) return -1;

	result = system->playSound(sound, 0, false, &channel);
	if (result != FMOD_OK) return -1;

	while (true)
	{
		result = system->update();
		if (result != FMOD_OK) return -1;

		if (channel)
		{
			bool playing = false;
			result = channel->isPlaying(&playing);
			if (!playing) break;
		}

		jm::TankExample().run();

		break;
	}

	system->release();

	return 0;
}