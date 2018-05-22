#include <stdio.h>
#include <math.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

//Como compilar: g++ main.cpp -o main -lopenal -lalut -fpermissive -w
//OpenAL: sudo apt-get install libopenal0a libopenal-dev
//ALUT: sudo apt-get install libalut0 libalut-dev

// Maximum data buffers we will need.
#define NUM_BUFFERS 4

// Maximum emissions we will need.
#define NUM_SOURCES 4

// These index the buffers and sources.
#define START 0
#define MOVERY  1
#define MOVERN  2
#define VENCEU  3

// Buffers hold sound data.
ALuint Buffers[NUM_BUFFERS];

// Sources are points of emitting sound.
ALuint Sources[NUM_SOURCES];

// Position of the source sounds.
ALfloat SourcesPos[NUM_SOURCES][3];

// Velocity of the source sounds.
ALfloat SourcesVel[NUM_SOURCES][3];

// Position of the listener.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

// Velocity of the listener.
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

/*
 * ALboolean LoadALData()
 *
 *	This function will load our sample data from the disk using the alut
 *	utility and send the data into OpenAL as a buffer. A source is then
 *	also created to play that buffer.
 */
ALboolean LoadALData(){
	// Variables to load into.
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	// Load wav data into buffers.
	alGenBuffers(NUM_BUFFERS, Buffers);

	if(alGetError() != AL_NO_ERROR)	return AL_FALSE;

	alutLoadWAVFile("click1.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[MOVERY], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile("click2.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[MOVERN], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile("start.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[START], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile("congratulations.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[VENCEU], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	// Bind buffers into audio sources.
	alGenSources(NUM_SOURCES, Sources);

	if(alGetError() != AL_NO_ERROR) return AL_FALSE;

	alSourcei (Sources[START], AL_BUFFER,   Buffers[START]   );
	alSourcef (Sources[START], AL_PITCH,    1.0f              );
	alSourcef (Sources[START], AL_GAIN,     1.0f              );
	alSourcefv(Sources[START], AL_POSITION, SourcesPos[START]);
	alSourcefv(Sources[START], AL_VELOCITY, SourcesVel[START]);
	alSourcei (Sources[START], AL_LOOPING,  AL_FALSE          );

	alSourcei (Sources[MOVERY], AL_BUFFER,   Buffers[MOVERY]   );
	alSourcef (Sources[MOVERY], AL_PITCH,    1.0f            );
	alSourcef (Sources[MOVERY], AL_GAIN,     1.0f            );
	alSourcefv(Sources[MOVERY], AL_POSITION, SourcesPos[MOVERY]);
	alSourcefv(Sources[MOVERY], AL_VELOCITY, SourcesVel[MOVERY]);
	alSourcei (Sources[MOVERY], AL_LOOPING,  AL_FALSE        );

	alSourcei (Sources[MOVERN], AL_BUFFER,   Buffers[MOVERN]   );
	alSourcef (Sources[MOVERN], AL_PITCH,    1.0f            );
	alSourcef (Sources[MOVERN], AL_GAIN,     1.0f            );
	alSourcefv(Sources[MOVERN], AL_POSITION, SourcesPos[MOVERN]);
	alSourcefv(Sources[MOVERN], AL_VELOCITY, SourcesVel[MOVERN]);
	alSourcei (Sources[MOVERN], AL_LOOPING,  AL_FALSE        );
	

	alSourcei (Sources[VENCEU], AL_BUFFER,   Buffers[VENCEU]   );
	alSourcef (Sources[VENCEU], AL_PITCH,    1.0f            );
	alSourcef (Sources[VENCEU], AL_GAIN,     1.0f            );
	alSourcefv(Sources[VENCEU], AL_POSITION, SourcesPos[VENCEU]);
	alSourcefv(Sources[VENCEU], AL_VELOCITY, SourcesVel[VENCEU]);
	alSourcei (Sources[VENCEU], AL_LOOPING,  AL_FALSE        );

	// Do another error check and return.
	if(alGetError() != AL_NO_ERROR) return AL_FALSE;

	return AL_TRUE;
}

/*
 * void SetListenerValues()
 *
 *	We already defined certain values for the listener, but we need
 *	to tell OpenAL to use that data. This function does just that.
 */
void SetListenerValues(){
	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}

/*
 * void KillALData()
 *
 *	We have allocated memory for our buffers and sources which needs
 *	to be returned to the system. This function frees that memory.
 */
void KillALData(){
	alDeleteBuffers(NUM_BUFFERS, Buffers);
	alDeleteSources(NUM_SOURCES, Sources);
	alutExit();
}
