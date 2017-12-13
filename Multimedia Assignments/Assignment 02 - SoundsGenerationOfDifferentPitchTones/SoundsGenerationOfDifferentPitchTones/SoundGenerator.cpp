#include "SoundGenerator.h"

SoundGenerator::SoundGenerator()
{
	for (int i = 0; i < NUM_NOTE; i++) {

		std::pair<std::string, int> char_iterm;
		char_iterm.first = musical_notes_char[i];
		char_iterm.second = musical_note_list_tone2[i];
		map_char_tone2.insert(char_iterm);
		char_iterm.second = musical_note_list_tone4[i];
		map_char_tone4.insert(char_iterm);


		std::pair<int, int> number_iterm;
		number_iterm.first = musical_notes_int[i];
		number_iterm.second = musical_note_list_tone2[i];
		map_number_tone2.insert(number_iterm);
		number_iterm.second = musical_note_list_tone4[i];
		map_number_tone4.insert(number_iterm);
	}
	tone_duration = 0;
	delay_time = DEFAULT_DELAY_VALUE;
}


void SoundGenerator::ReadFromFile(std::string file_path)
{
	std::fstream stream_musical_notes(file_path);

	std::string str;
	while (stream_musical_notes >> str) {

		std::cout << "Original " << str << std::endl;
		if (str == "-")
		{
			MusicalNote tmp(REST_NOTE_FREQUENCY, REST_NOTE_DURATION);
			melody_tone2.push_back(tmp);
			melody_tone4.push_back(tmp);
			tone_duration++;
		}
		else if (isdigit(str[0]))
		{
			// 1,12,1-2,12-2
			std::map<int, int>::iterator iter;
			int number_note;
			float tmp_duration = DEFAULT_DURATION;
			if (str.size() == 1 || str.size() == 2)
				number_note = atoi(str.c_str());

			else if (str[1] == '-')
			{
				int number_note = str[0] - '0';
				tmp_duration = atoi(str.substr(2, str.size() - 2).c_str());
			}
			else {
				int number_note = atoi(str.substr(0, 2).c_str());
				tmp_duration = atoi(str.substr(3, str.size() - 3).c_str());
			}

			iter = map_number_tone2.find(number_note);
			if (iter != map_number_tone2.end())
			{
				MusicalNote tmp(iter->second, tmp_duration); melody_tone2.push_back(tmp);
				MusicalNote tmp2(map_number_tone4.find(number_note)->second, tmp_duration); 	melody_tone4.push_back(tmp2);
			}
			//cannot find: wait to be handled
			tone_duration+= tmp_duration;
		}
		else {
			//A ,A#,A-2,A#-2
			std::map<std::string, int>::iterator iter;
			std::string str_note;
			float tmp_duration = DEFAULT_DURATION;
			if (str.size() == 1 || str.size() == 2)
				str_note = str;

			else if (str[1] == '-')
			{
				str_note = toupper(str[0]); 
				tmp_duration = atoi(str.substr(2, str.size() - 2).c_str());
			}
			else {
				str_note = str.substr(0, 2); str_note[0] = toupper(str_note[0]);
				tmp_duration = atoi(str.substr(3, str.size() - 3).c_str());
			}

			iter = map_char_tone2.find(str_note);
			if (iter != map_char_tone2.end())
			{
				MusicalNote tmp(iter->second, tmp_duration); melody_tone2.push_back(tmp);
				MusicalNote tmp2(map_char_tone4.find(str_note)->second, tmp_duration); 	melody_tone4.push_back(tmp2);
			}
			//cannot find: wait to be handled
			tone_duration += tmp_duration;
		}
	}


}

void SoundGenerator::CreateSeperatePart()
{
	basso_wave = new WavFile(1,DEFAULT_VOLUME,tone_duration);
	alto_wave = new WavFile(1, DEFAULT_VOLUME, tone_duration);
	//share part (use basso)
	int num_notes = melody_tone2.size();
	long long length = basso_wave->WAVE_HEAD_LENGTH;

	for (int i = 0; i < num_notes; i++)
	{
		WavFile* tmp_wave_basso = new WavFile(melody_tone2[i].frequency, DEFAULT_VOLUME, melody_tone2[i].duration);
		WavFile* tmp_wave_alto = new WavFile(melody_tone4[i].frequency, DEFAULT_VOLUME, melody_tone4[i].duration);

		memcpy(basso_wave->GetDataLinker() + length, tmp_wave_basso->GetDataLinker() + tmp_wave_basso->WAVE_HEAD_LENGTH, tmp_wave_basso->GetDataLength());
		memcpy(alto_wave->GetDataLinker() + length, tmp_wave_alto->GetDataLinker() + tmp_wave_alto->WAVE_HEAD_LENGTH, tmp_wave_alto->GetDataLength());
		length += tmp_wave_basso->GetDataLength();

		delete tmp_wave_basso;
		delete tmp_wave_alto;
	}
}

void SoundGenerator::synthesize()
{
	//if file A 's length does not equal to B's
	//	...

	//else 
	final_sound = new WavFile(1,DEFAULT_VOLUME,delay_time + tone_duration);

	int header_length = basso_wave->WAVE_HEAD_LENGTH;

	WavFile* delayed_wave = new WavFile(1, DEFAULT_VOLUME, delay_time);
	WavFile* delayed_basso_wave = new WavFile(1, DEFAULT_VOLUME, delay_time + tone_duration);
	WavFile* delayed_alto_wave = new WavFile(1, DEFAULT_VOLUME, delay_time + tone_duration);

	memcpy(delayed_basso_wave->GetDataLinker() + header_length, basso_wave->GetDataLinker() + header_length, basso_wave->GetDataLength());
	memcpy(delayed_basso_wave->GetDataLinker() + header_length+ basso_wave->GetDataLength(), delayed_wave->GetDataLinker() + header_length, delayed_wave->GetDataLength());
	memcpy(delayed_alto_wave->GetDataLinker() + header_length,  delayed_wave->GetDataLinker() + header_length, delayed_wave->GetDataLength());
	memcpy(delayed_alto_wave->GetDataLinker() + header_length+ delayed_wave->GetDataLength(), alto_wave->GetDataLinker() + header_length, alto_wave->GetDataLength());


	for (int i = 0; i < final_sound->GetDataLength(); i++)
	{	

		*(final_sound->GetDataLinker() + header_length + i) = (*(delayed_basso_wave->GetDataLinker() + header_length + i) + *(delayed_alto_wave->GetDataLinker() + header_length + i)) / 2.0;
	}

	delete delayed_wave;
	delete delayed_alto_wave;
	delete delayed_basso_wave;
}
