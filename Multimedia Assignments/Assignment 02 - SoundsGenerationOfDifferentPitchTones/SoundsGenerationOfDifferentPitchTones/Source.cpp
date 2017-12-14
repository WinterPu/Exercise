#include "WAV_Lib.h"
#include "SoundGenerator.h"
using namespace std;


int main()
{
	WavFile test(294,100,5);
	test.CreateWavFile("D:/test.wav");

	WavFile test2(440, 100, 5);
	test2.CreateWavFile("D:/test2.wav");

	WavFile* test3 = SoundGenerator::Merge(&test, &test,1);
	test3->CreateWavFile("D:/test3.wav");



	SoundGenerator sound_generator;
	sound_generator.SynthesizeFromFile("C:/Users/Winter Pu/Desktop/Sound/music note.txt");

	WavFile* final_sound_ptr = sound_generator.GetFileLink();
	if (final_sound_ptr != NULL)
		final_sound_ptr->CreateWavFile("D:/final.wav");

	return 0;
}