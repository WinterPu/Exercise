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


#define MATH_PI 3.1415

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
	

	void CreateWaveHeader();

	~WavFile();
	
	//void MakeWaveData(int rate, int freq, int amp, char* p, int len);
	void MakeWaveData(int rate, int freq, int amp, char * p, int len);
	int CreateWavFile(std::string path, std::string file_name);


	int  GetDuration() { return durations; }
	char* GetDataLinker() { return pWaveBuffer;}
	int   GetDataLength() { return wav_data_length; }
	int   GetHeaderLength() { return wave_header_length; }
private:
	int frequency;
	int volume;
	int durations;

	WaveHeader * pHeader;
	DWORD totalLen;
	char* pWaveBuffer;
	int wave_header_length;
	int wav_data_length;


	int m_samplefreq;
	int m_channels;
	int m_channelbits;
};



#define FM_FLAG 0
double GenerationFunc(int times,int rate, int freq, int amp, bool fm_flag);

#endif