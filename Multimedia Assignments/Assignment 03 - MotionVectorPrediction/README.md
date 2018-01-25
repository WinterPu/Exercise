# Assignment 03 Motion Vector Prediction
## Introduction:
### 1.Two Algorithm:
#1 Sequential Search

#2 2D Logarithm Search

### 2.Understanding Parameters:

**N**: num of macroblock pixels

Ps: the origin (x,y) of the macroblock is at the upper-left corner [in materials]

**P**: search windows size:(2P-1, 2P+1)

Ps: the origin (x,y) is the center of the search windows


#### For example:
**M** is the origin pixel of the macroblock: [image.at(x,y)]

Maybe the macroblock's size is out of the search windows' boundary, it's OK.

**(2P-1,2P+1)** means:

M can move :  

up -- for p pixels , down -- for p pixels 

left -- for p pixels, right -- for p pixels

if P =1, the search windows can show:

@   |   @

--  M   --

@   |   @

(M is the macroblock's origin,  **@, |, --** is the other pixel in the search windows, **|, ---** just want to show it can move towards this four directions.)

### 3. Note:
+ Ref / Tar Image: the macroblocks start from (0,0)
+ Each mage has its motion vector
+ In search windows, each movement is 1 pixel ( not 1 macroblocks (not N))
+ If (x+i,y+j) is out of the boundary, or the macroblock ( whose origin is on (x+i,y+j)) will excceed the image boundary.
**Turn to the next (i,j) displacement value** 

## Result Image：
### Reference Image:
![Reference Image](https://github.com/WinterPu/Exercise/blob/master/Multimedia%20Assignments/Assignment%2003%20-%20MotionVectorPrediction/--%20Result%20Images%20--/Reference%20Image.png?raw=true)
### Target Image:
![Target Image](https://github.com/WinterPu/Exercise/blob/master/Multimedia%20Assignments/Assignment%2003%20-%20MotionVectorPrediction/--%20Result%20Images%20--/Target%20Image.png?raw=true)
### Predicted Image [ Sequential Search ]
![Sequential Search](https://github.com/WinterPu/Exercise/blob/master/Multimedia%20Assignments/Assignment%2003%20-%20MotionVectorPrediction/--%20Result%20Images%20--/Sequential%20Search%20Image.png?raw=true)
### Reference Image [ 2D Logarithm Search ]
![2D Logarithm Search Image](https://github.com/WinterPu/Exercise/blob/master/Multimedia%20Assignments/Assignment%2003%20-%20MotionVectorPrediction/--%20Result%20Images%20--/2D%20Logarithm%20Search%20Image.png?raw=true)

### Speed & SNR
#### Result Image
![Evaluation](https://github.com/WinterPu/Exercise/blob/master/Multimedia%20Assignments/Assignment%2003%20-%20MotionVectorPrediction/--%20Result%20Images%20--/Evaluation.png?raw=true)

#### Sequential Search
Consuming Time： 20691 ms

SNR Value: 183.002
#### 2D Logarithm Search
Consuming Time： 871 ms

SNR Value: 106.033

## Experience:
+ The program architecture needs to be improved.

(Please respect the right of portraits. Image source comes from the course)
