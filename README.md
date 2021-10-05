# NeoPixel PSI

This is the code for the NeoPixelPSI boards for an R2D2. Just a simple strand of PSI in a disc pattern

5x5 Matrix
```
    0  1  2
 3  4  5  6  7
 8  9 10 11 12
13 14 15 16 17
   18 19 20
```
7x7 Matrix
```
       2  1  0
    7  6  5  4  3
14 13 12 11 10  9  8
21 20 19 18 17 16 15
28 27 26 25 24 23 22
   33 32 31 39 29
      36 35 34
```

8x8 Matrix
```
       3  2  1  0
    9  8  7  6  5  4
17 16 15 14 13 12 11 10
25 24 23 22 21 20 19 18
33 32 31 30 29 28 27 26
41 40 39 38 37 36 35 34
   47 46 45 44 43 42
      51 50 49 48
```



## Installation

Download the zip of this repository and uncompress in your arduino libraries directory, or clone the repo directly into that directory. Then when you fire up the arudino 
IDE you can go to File->examples->NeoPixelPSI and select an example piece of code, or just include the library and write your own.

## Examples

### Standalone

This version of the code will run on most arduino boards, tested mainly on a nano and Mega. I have also done a simple breakout board for an Arduino Pro Mini

### FlthyHP

Use an existing FlthyMcNasty HP board's spare pins and combine the system. PSIs are defined at around line 572, with the colour for the second one set at line 629.

## ReelTwo

Also available in the ReelTwo library for R2. https://github.com/reeltwo/Reeltwo

## More info:

https://r2djp.co.uk/category/electronics/neopixel-psi/
