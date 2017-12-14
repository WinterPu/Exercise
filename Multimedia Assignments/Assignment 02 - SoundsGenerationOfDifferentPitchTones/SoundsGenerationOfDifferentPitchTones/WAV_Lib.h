#pragma once
//reference :http://blog.csdn.net/TQ1996/article/details/54913828
#ifndef WAV_LIB_H
#define WAV_LIB_H

#include <windows.h> 
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <fstream> 
#include <math.h>
#include <vector>


#define MATH_PI 3.1415

#define FM_FLAG 0
double GenerationFunc(int times, int rate, int freq, int amp, bool fm_flag);



//.wav文件的文件头结构 
typedef struct
{
	char chRIFF[4];
	DWORD dwRIFFLen;
	char chWAVE[4];
	char chFMT[4];
	DWORD dwFMTLen;
	PCMWAVEFORMAT pwf;
	char chDATA[4];
	DWORD dwDATALen;
	//UINT8* pBufer;
}WaveHeader;


class WavFile {

public :
	WavFile(int v_frequency, int v_volume, int v_durations);
	//samplefreq > 2 *frequency  according to the Nyquist - Shannon theorem
	WavFile(int v_samplefreq, int v_channels, int v_channelbits, int v_frequency, int v_volume, int v_durations);
	

	void CreateWaveHeader(WaveHeader*pHeader, char* pWaveBuffer);

	//void MakeWaveData(int rate, int freq, int amp, char* p, int len);
	void CalcSampleFrequency();
	void MakeWaveData(WaveHeader*pHeader, char* pWaveBuffer);
	int CreateWavFile(std::string file_path);


	int  GetDuration() { return durations; }
	std::vector<double>* GetDataLinker() { return &vec_sample_freq;}
	DWORD   GetDataLength() { return wav_data_length; }
	DWORD    GetHeaderLength() { return wave_header_length; }

	bool SetFMFlag() { fm_flag = ~fm_flag; vec_sample_freq.clear(); CalcSampleFrequency(); }
	bool SetFMFlag(bool value) { fm_flag = value; vec_sample_freq.clear(); CalcSampleFrequency(); }

	~WavFile() {};
private:
	bool fm_flag;

	int frequency; // sound frequency
	int volume;
	int durations;

	std::vector<double> vec_sample_freq;


	DWORD totalLen;
	DWORD wave_header_length;
	DWORD wav_data_length;

	int m_samplefreq; // sample rate
	int m_channels;
	int m_channelbits;
};





#endif