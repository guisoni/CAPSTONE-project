# CPPND: Capstone Solar System Simulation

This is my repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213)
My project is a simulation of a Solar System using Newton Laws to calculate the motion of the planets. The planets are in scale in relation one to another and in relation to the distances between them. The planets also rotate around its own axes, except for the Sun. 

There are the following bodies in the simulation: Sun, Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto. Yes Pluto, I am old school.

## Assumptions: 
* Newton Laws holds, no special relativity or general relativity used.
* The Sun is in the center of mass of the Solar System, although not stricly true, since it is really massive compared to the rest of bodies it is a good approximation.
* All orbits happen in the same plane but with their original size, Except for pluto, I changed the orbit of Pluto, because it would hit Neptune since they are in the same plane and in reality they are not.
* The initial position of all bodies are generated randomically in their orbits, except for the Sun wich is in the origin and does not move, the Earth and the Moon wich start in a pre-determined configuration. 

## Resources:
The references I used for learning SDL were [Lazy Foo website] (https://lazyfoo.net/tutorials/SDL/index.php), and [MadsyCode](https://www.youtube.com/watch?v=1KD4Ae0tX0g&list=PL-K0viiuJ2RctP5nlJlqmHGeh66-GOZR_) youtube channel. Great resources! I learned static classes from MadsyCode, and the use of textures with Lazy Foo. And lastly but not least, the [SDL Wiki](https://wiki.libsdl.org/) page where I could read about the commands taughts in other tutorials.


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


## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SolarSystem`.

The program was originally created for Linux, in a 64bit machine therefore it is configured to run in that. I have never tested it on 
Windows or Mac. The #include "SDL2/SDL.h" and #include "SDL2/SDL_image.h" only works for Linux. You should remove the "SDL2/" part if you are
running in other operating systems. In windows the process need a bit more steps. [click here for Lazy Foo tips](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php).

## Program Instructions
* Keys 1,2,3,4,5,6,7,8,9,0,s: changes the reference body on center of screen in the following orther 1-Mercury, 2-Venus, 3-Earth, 4-Moon,5-Mars, 6-Jupiter, 7-Saturn, 8-Uranus, 9-Neptune, 0-Pluto, s-Sun. Resets the positon of screen to the center of a body.
* Key l: Alternatively locks and unlocks to the planet rotation on its on axis. The program starts on Earth.
* Keys z,x: Zooms in and zooms out respectively
* Up, Down, Left, Right arrows: moves the center of screen away from the reference planet. If you want to move the screen through the solar system.
* Keys j, m: increases and decreases the number of pixels you move at each press to the arrows. If you zoom in and out it seems to be faster since one pixel is still one pixel. The program starts with dislacement of 1 pixel.
* Key q: Quits the application. Use it if the x window button goes out of screen. It is configured for a screen size of 1820x780. If it does not fit your screen you an change that in Core.h file screen_width_ and screen_height members. 
* Keys: t, g: increases or decreases the increment of time used in the calculations. It increases or decreases the speed you see the bodies moving. The small time interval of 0.01666s is really smal for the machine to do all the calculations and there is lag depending on the machine, the maximum time step is equivalent to Earth complete rotation around the sun in 1 minute. Program starts with maximum time step.

## Program Ilustrations.
All the ilustrations were made by me in Krita, a professional FREE and open source painting program. [Krita website](https://krita.org/en/).

## File Structure

### Folder src:

* main.h and main.cpp - contains a few comands to start the simulation and stop the simulation an free all the memory.

* Body.h and body.cpp - it contains a class called Body that represents the Body subjected to the forces of other Bodies. The members are
basically position_, velocity_, acceleration_, angular_position_, angular_velocity_, mass_, mass_moment_Inertia_, bodyName_, Perihelion_,Aphelion_, diameter_, image_pos_scale_. The last one holds the offset position and scale factors of the images that will be rendered. The methods are basically the Getters of each member and  basic newtomia physics: GravityForcePerMass(), UpdateAcceleration(), UpdateVelocity(), UpdatePosition(), UpdateAngularPosition(), PrintBody().

* SolarSystem - This static class is a wraper for all the bodies. It keeps all the bodies in a vector. And has some complementary methods to calculate the movement of the bodies. It is a static class making it easier to be used everiwere. It is through this class that Core and the Body classes interchange information. The members are SolarSystem, bodies_, is_start_, position_, totalMass_, is_imported_. The methods are
GetSolarSystem(), ImportData(), AddBody(), Update(), PrintBody(), TotalMass(), CenterOfMass(), GetTotalMass(), GetPosition(), GetIsImported, GetNumberOfBodies, GetBody, BodyName, InitialConditions. SolarSystem class is a friend of Body class and can access all its private members.
ImportData() impots the data from planets.txt file.

* planets.txt - a text file with the bodies data that is imported to the application. The data has no units since it has been divided by the Sun diameter, or the Sun Mass. The only units are pixels and radians/sec for the angular velocities. 

* PixelMath.h - Contains one function to convert a position to a position on the screen screen ConvertPositionToPixel(). 

* Core.h and Core.cpp - This static class controls the application. It calls the functios to open or close the main window, load the textures,
control the user inputs, and control the entire configutation. The members of this class are: core_, success_, sdl_window_, sdl_renderer_, Textexture_, screen_width_, screen_height_, framesPerSecond_, msPerFrame_, timeRatio_, cameraId_, scale_factor_, displ_, delta_, minBodySize_, isLocked_, minimumScaleFactor_, maximumScaleFactor_, maximum_time_interval, minimum_time_interval, dt_factor_, dt_.
The methods are GetCore(), FreeCore(), Start(), RunGame(), EndGraphics(), Renderer(), GetStatus(), GetRenderer(), ClearRenderer(), EventHandler(), multiplyDelta(). RunGame() is the main method that controls everithing. It also manages time as referenced in
[Snake Game repo](https://github.com/udacity/CppND-Capstone-Snake-Game).

* Textures.h and Textures.cpp - This static class is a wraper for all the textures of all the bodies. The members are textures_, rectangle_, texture_, scale_texture_, bool success_. texture_ is a vector containing all textures and scale_texture a vector containing the scale factors to apply in each texture. The methods are GetTextures(), FreeTextures(), AddTexture(), AddScaleFactor(), TextureFromImageLoad(), EndTexture(), Draw(), GetTextureSize(), GetScaleFactor(), mostly to use SDL texture structure, or to control the scaling of the images.

* Vector2Elm.h Vector2Elm.cpp - contains basic math functions and basic 2D vector algebra. AuxMath is a namespace with radians(), degrees(), and sign() functions. Vector2Elm is a class with public members x_ and y_ and many vector operations mostly through operator overloading.
Addition, subtraction, multiplication and division by a scalar, scalar product, vectorial product and modulus of vector.  


### image folder

 Contains all the images to render in .png fomat from SUN to PLUTO.


### main folder

Contains this README.md and CMakeLists.txt file.

### cmake folder

Contains findSDL2_image.make. Form the original [Snake Game repo](https://github.com/udacity/CppND-Capstone-Snake-Game).

## Rubric Addressed Criteria

1- The project reads data from a file and process the data, or the program writes data to a file: SolarSystem::ImportData() reads file
planets.txt and import the bodies data to the program. The method starts in line 12 of SolarSystem.cpp file.

2- The project accepts input from a user as part of the necessary operation of the program: The project accepts inputs from the user as mentioned in *Program Instructions* above. The Core::EventHandler() method handle all the keyboard events mentioned. The method starts in line 216 of Core.cpp file.  

3- The project uses Object Oriented Programming techniques. The project uses classes Vector2Elm, Body, SolarSystem, Core, Textures, ImgPosScale. They are found in the files with the same name plus .h and .cpp except for ImgPosScale that is inside Body.h file because a member of Body is ImgPosScale type.  

4-The project makes use of references in function declarations. It is used a lot in the project. Examples are in Texture.h line 14 
void AddScaleFactor(const int &refmeasure, const double &Diam) and line 15 void TextureFromImageLoad(const int &index, const std::string &filename) but it can be found in many other places.

5-Classes use appropriate access specifiers for class members. Vector2Elm.h line 32 public. Textures.h line 10 public, line 21 private.
SolarSystem.h line 16 public, line 45 private. Core.h line 13 public, line 34 private. Body.h ImgPosScale class line 15 public, 23 private. Class Body, line 31 public, line 71 private.


## Final Comments

Thanks to all the Udacity team for this great course.












