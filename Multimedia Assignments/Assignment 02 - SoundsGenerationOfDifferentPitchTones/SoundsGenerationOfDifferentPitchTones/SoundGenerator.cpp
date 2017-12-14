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


WavFile* SoundGenerator::Merge(WavFile* pre, WavFile* rear, int delay_time)
{
	if (pre == NULL || rear == NULL)
		return nullptr;

	WavFile * new_rear;
	WavFile * new_pre;
	if (delay_time > 0)
	{
		//do delaying
		WavFile* delayed_sound = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME, delay_time);
		new_rear = SoundGenerator::Combine(delayed_sound, rear);

		//do padding
		if (pre->GetDuration() > rear->GetDuration())
		{
			//pre > rear
			WavFile* delayed_sound_pre = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME, delay_time);
			WavFile* padding_rear = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME, pre->GetDuration() - rear->GetDuration());
			new_pre = SoundGenerator::Combine(pre, delayed_sound_pre);
			WavFile* garbage = new_rear;
			new_rear = SoundGenerator::Combine(rear,padding_rear);
			delete garbage;
		}
		else if (pre->GetDuration() < rear->GetDuration())
		{
			// pre < rear
			WavFile* delayed_sound_pre = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME, delay_time+ rear->GetDuration() - pre->GetDuration());
			new_pre = SoundGenerator::Combine(pre, delayed_sound_pre);
		}
		else {
			//pre == rear
			WavFile* delayed_sound = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME, delay_time);
			new_pre = SoundGenerator::Combine(pre, delayed_sound);

		}

	}
	else
	{
		//do padding
		if (pre->GetDuration() > rear->GetDuration())
		{
			//pre > rear
			WavFile* padding_part = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME, pre->GetDuration() - rear->GetDuration());
			new_rear = SoundGenerator::Combine(rear, padding_part);
			new_pre = pre;
		}
		else if (pre->GetDuration() < rear->GetDuration())
		{
			// pre < rear
			WavFile* padding_part = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME,  rear->GetDuration() - pre->GetDuration());
			new_pre = SoundGenerator::Combine(pre, padding_part);
			new_rear = rear;
		}
		else {
			// pre == rear
			new_pre = pre;
			new_rear = rear;
		}

	}

	int duration = new_pre->GetDuration();
	WavFile* merged_file = new WavFile(1,DEFAULT_VOLUME,duration);
	for (int i = 0; i < merged_file->GetDataLength(); i++)
	{
		*(merged_file->GetDataLinker() + merged_file->GetHeaderLength() + i) = Merge_Function((double)(*(pre->GetDataLinker() + pre->GetHeaderLength() + i)), (double)(*(rear->GetDataLinker() + rear->GetHeaderLength() + i)));
	}
	return merged_file;
}


WavFile * SoundGenerator::Combine(WavFile * pre, WavFile * rear)
{
	if (pre == NULL || rear == NULL)
		return nullptr;

	int total_durations = pre->GetDuration() + rear->GetDuration();

	WavFile* combined_file = new WavFile(1, DEFAULT_VOLUME, total_durations);


	for (int i = 0; i < pre->GetDataLength(); i++)
	{
		*(combined_file->GetDataLinker() + combined_file->GetHeaderLength() + i) = *(pre->GetDataLinker() + pre->GetHeaderLength() + i);
	}
	for (int i = pre->GetDataLength(); i <combined_file->GetDataLength(); i++)
	{
		*(combined_file->GetDataLinker() + combined_file->GetHeaderLength() + i) = *(rear->GetDataLinker() + rear->GetHeaderLength() + i - pre->GetDataLength());
	}

	return combined_file;
}

void SoundGenerator::CreateSeperatePart()
{
	basso_wave = new WavFile(1,DEFAULT_VOLUME,tone_duration);
	alto_wave = new WavFile(1, DEFAULT_VOLUME, tone_duration);
	//share part (use basso)
	int num_notes = melody_tone2.size();
	long long length = basso_wave->GetHeaderLength();

	for (int i = 0; i < num_notes; i++)
	{
		WavFile* tmp_wave_basso = new WavFile(melody_tone2[i].frequency, DEFAULT_VOLUME, melody_tone2[i].duration);
		WavFile* tmp_wave_alto = new WavFile(melody_tone4[i].frequency, DEFAULT_VOLUME, melody_tone4[i].duration);

		memcpy(basso_wave->GetDataLinker() + length, tmp_wave_basso->GetDataLinker() + tmp_wave_basso->GetHeaderLength(), tmp_wave_basso->GetDataLength());
		memcpy(alto_wave->GetDataLinker() + length, tmp_wave_alto->GetDataLinker() + tmp_wave_alto->GetHeaderLength(), tmp_wave_alto->GetDataLength());
		length += tmp_wave_basso->GetDataLength();
	}
}

void SoundGenerator::synthesize()
{
	//if file A 's length does not equal to B's
	//	...

	//else 
	final_sound = new WavFile(1,DEFAULT_VOLUME,delay_time + tone_duration);

	int header_length = basso_wave->GetHeaderLength();

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
}

SoundGenerator::~SoundGenerator()
{
	delete basso_wave;
	delete alto_wave;
	delete final_sound;
}

double Merge_Function(double a, double b)
{
	return (a+b)/2.0;
}
