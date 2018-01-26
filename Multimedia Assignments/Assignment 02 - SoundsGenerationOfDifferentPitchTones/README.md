# Assignment 02 Sounds Generation Of Different PitchTones
## The format you design for the input text file of musical notes.



### Each Musical Note:

You can type musical notes with both format in your file:

```
character： C  C# D D# E F F# G G# A A# B

number:     1  12  2  22  3  4  42  5  52   6 62   7

(use 12 to represent C# )
```



if you want to denote 2 beats, you can use: -2

all in all,  for each musical note :

```
number: 1,12, 1-2, 12-2

character: C, C# , C-2, C#-2
```


### Overall:

use whitespace-character to seperate two musical notes.

### for example:

`5  4-2 6 7 22-2 12`



## The ﬂowchart of your program

<img src="https://github.com/WinterPu/Exercise/blob/master/Multimedia%20Assignments/Assignment%2002%20-%20SoundsGenerationOfDifferentPitchTones/README_IMAGE/Flowchart.png?raw=true" height="600" alt="flow chart">


## The way to set up and run your program,
 
![UI](https://github.com/WinterPu/Exercise/blob/master/Multimedia%20Assignments/Assignment%2002%20-%20SoundsGenerationOfDifferentPitchTones/README_IMAGE/UI.png?raw=true)

you can use following command:

>**createwav [frequency value] [volume value] [duration value]**
>- to create wav file with specified - frequency , volume, duration
><br></br>etc: createwav 350 100 3

>**createsound**
>- to read your musical notes in your own file to generate the sound ( mix with two tones: basso & alto)

>**setfm**
>- to enable simple fm function 

>**settone**
>- to set tone for basso & alto in [ sound generation ] process

>**help**
>- to show the commands

>**end**
>- to end the program




Qt Version GUI：
![Qt_GUI](https://github.com/WinterPu/Exercise/blob/master/Multimedia%20Assignments/Assignment%2002%20-%20SoundsGenerationOfDifferentPitchTones/README_IMAGE/Qt%20Version%20GUI.png?raw=true)

Download Qt Version: https://github.com/WinterPu/Exercise/releases
## The illustrations or figures to demonstrate the results produced by your program.

Small Bee 
![Small Bee Result](https://github.com/WinterPu/Exercise/blob/master/Multimedia%20Assignments/Assignment%2002%20-%20SoundsGenerationOfDifferentPitchTones/README_IMAGE/SmallBee.PNG?raw=true)

Small Bee with simple FM using the same frequency

![Small Bee FM Result](https://github.com/WinterPu/Exercise/blob/master/Multimedia%20Assignments/Assignment%2002%20-%20SoundsGenerationOfDifferentPitchTones/README_IMAGE/SmallBee_FM_Using%20The%20Same%20Frequency.PNG?raw=true)


you can check the result files in the following link:
https://github.com/WinterPu/Exercise/tree/master/Multimedia%20Assignments/Assignment%2002%20-%20SoundsGenerationOfDifferentPitchTones/Experiment%20Input%20Sample%20and%20Results

## The problem(s) encountered and the way you solve it(them), if any.



It is a little troublesome to deal with wav file's data part at first.





## The discussions/summaries on your results, and what you have learned in this assignment

It can generate some sounds according to the musical notes.

- learn a simple method to synthesize music
- learn some about WAV format


When Designing:
need to try to keep the complete data. (wav->data part  : you can save as double vector)
the lossy transformation can be in the output process. (output process: double -> 16bit or 8bit)
