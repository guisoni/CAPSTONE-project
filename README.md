# CPPND: Capstone Solar System Simulation

This is my repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213)
My project is a simulation of a Solar System using Newton Laws to calculate the motion of the planets. The planets are in scale in relation one to another and in relation to the distances between them. The planets also rotate around its own axes, except for the Sun. 

There are the following bodies in the simulation: Sun, Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto. Yes Pluto, I am old school.

## Assumptions: 
* Newton Laws holds, no special relativity or general relativity used.
* The Sun is in the center of mass of the Solar System, although not stricly true, since it is really massive compared to the rest of bodies it is a good approximation.
* All orbits happen in the same plane but with their original size, Except for pluto, I changed the orbit of Pluto, because it would hit Neptune since they are in the same plane and in reality they are not.
* The initial position of all bodies are generated randomically in their orbits, except for the Sun wich is in the center and does not move, the Earth and the Moon wich start in a pre-determined configuration. 

## Resources:
The references I used for learning SDL were [Lazy Foo website] (https://lazyfoo.net/tutorials/SDL/index.php), and [MadsyCode](https://www.youtube.com/watch?v=1KD4Ae0tX0g&list=PL-K0viiuJ2RctP5nlJlqmHGeh66-GOZR_) youtube channel. Great resources! I learned static classes from Madsy code, and the use of textures with Lazy Foo. And lastly but not least, the [SDL Wiki](https://wiki.libsdl.org/) page where I could read about the commands taughts in other tutorials.


<img src="snake_game.gif"/>


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL_image developers package = 2.0.5 [click here SDL_Image website](https://www.libsdl.org/projects/SDL_image/#source)
  * Linux: Use commands apt-cache search libsdl2-image, apt-get install libsdl2-image-dev 
  * Mac: [instalation packages can be found here](https://www.libsdl.org/projects/SDL_image/#source)
  * Windows: [instalation packages can be found here](https://www.libsdl.org/projects/SDL_image/#source)

The program was originally created for Linux, in a 64bit machine therefore it is configured to run in that. I have never tested it on 
Windows or Mac. The #include "SDL2/SDL.h" and #include "SDL2/SDL_image.h" only works for Linux. You should remove the "SDL2/" part if you are
running in other operating systems. 

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SolarSystem`.

## Program Instructions
* Keys 1,2,3,4,5,6,7,8,9,0,s: changes the reference body on center of screen in the following orther 1-Mercury, 2-Venus, 3-Earth, 4-Moon,5-Mars, 6-Jupiter, 7-Saturn, 8-Uranus, 9-Neptune, 0-Pluto, s-Sun. Resets the positon of screen to the center of a body.
* Key l: Alternatively locks and unlocks to the planet rotation on its on axis.
* Kely z,x: Zoom in and zoom out respectively
* Up, Down, Left, Right arrows: move the center of screen away from the reference planet. If you want to move the screen through the solar system.
* j, m: increase and decrease the number of pixels you move at each press to the arrows. If you zoom in and out it seem to be faster since one pixel is still one pixel.
* q: Quits the application. Use it if the x window button goes out of screen. It is configured for a screen size of 1820x780. If it does not fit your screen you an change that in Core.h file screen_width_ and screen_height members. 



