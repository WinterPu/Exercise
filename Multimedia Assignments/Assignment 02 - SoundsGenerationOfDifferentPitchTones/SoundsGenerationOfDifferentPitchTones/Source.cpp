#include "WAV_Lib.h"
#include "SoundGenerator.h"
using namespace std;



int main()
{
	SoundGenerator sound_generator;
	sound_generator.ReadFromFile("C:/Users/Winter Pu/Desktop/Sound/music note.txt");
	sound_generator.CreateSeperatePart();
	sound_generator.synthesize();

	WavFile* final_sound_ptr = sound_generator.GetFileLink();
	if (final_sound_ptr != NULL)
		final_sound_ptr->CreateWavFile("D:/","final.wav");

	return 0;
}