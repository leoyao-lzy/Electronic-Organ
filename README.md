In the autumn of 2021, I began my third year in MED@THU. This semester, I had a pretty interesting course named "Fundamentals of computer hardware technology". In this course, I tried to program on MSP430G2553, which is a kind of microcontroller produced by Texas Instruments(TI). My course project is to design a simple electronic organ which can implement some of the specified functions like strumming or playing. I use CCS as my IDE.

------

### What is MSP430?

The MSP430 is a mixed-signal microcontroller family from Texas Instruments,  first introduced on  14  February 1992. Built  around a 16-bit CPU, the MSP430 is designed for low cost and,  specifically,  low power consumption embedded applications.You can click https://www.ti.com/microcontrollers-mcus-processors/microcontrollers/msp430-microcontrollers/overview.html for more information.

### What is Code Composer Studio(CCS)?

Code Composer Studio is an integrated development environment to develop applications for Texas Instruments embedded processors. Texas Instruments embedded processors include TMS320 DSPs, OMAP system-on-a-chip, DaVinci system-on-a-chip, Sitara applications processors, Hercules microcontrollers, Simplelink MCUs, MSP430 and Tiva/Stellaris microcontrollers. It also enables debugging on several subsystems such as Ducati, IVA Accelerator and PRU-ICSS.

### About this project

- #### Purpose

Synthesizing the theory and experimental content of "Fundamentals of computer hardware technology", through the hardware, software design and debugging of a microcontroller application system, the development ability of computer software and hardware is improved.

- #### ==Contents==

Design and implement a simple electronic keyboard, the functional requirements are as follows.
##### Basic Functions

1. Implement the function of playing the electronic keyboard.
2. Implement the music playback function of the electronic keyboard: at least three different pieces of music can be played.
3. With the function of switching between two modes(strumming and playing), you can use LEDs or digital tubes to display which song is playing.
  ##### Improved Functions

The function of the phone Bluetooth controlling.

- #### Project design and debugging

It is necessary to investigate, design and program the project outside the classroom, including the hardware system circuit design of the project, the overall design of the software (including the module division of the software, the overall flow chart of the software and the flow chart of each module), the design of human-computer interaction operation, etc.

- #### ==Reference scheme(significant!)==

##### Implement the control of each tone
1. Learn the timer TA of the msp430g2553 and master the method of using the TA to output the PWM waveform with adjustable frequency and duty cycle on the pin.

2. Programming the buzzer to emit 3 pitches of different notes in 1, 2, 3, 4, 5, 6, 7, etc. Square wave signals of different frequencies are completed with the PWM output of the microcontroller timer.

##### Implement song playback function
In the Flash ROM, in the form of a table to store a song or music score, including the tone and beat information of each tone, programming the stored score through the control of the timer PWM output, so that the buzzer to complete the music playback function, and with the LED to display which song is playing, and can be added buttons to control the playback process, pause, resume, or replay.
##### Implement the playing function
1. Add the control of the key, when the single key in K1 ~ K7 is pressed, the buzzer emits the corresponding tone of the call name 1, 2, 3, 4, 5, 6, 7.
2. When K8 is pressed, and then any of the keys in K1~K7 are pressed, the buzzer emits the corresponding tone of the treble name 1, 2, 3, 4, 5, 6, 7, such as pressing K8 and then pressing the K1 key to issue a treble 1, at which time K8 is used as a treble control key.
3. Add an off-board independent button K. When the K key is pressed, and then any of the keys in K1 to K7 are pressed, the buzzer emits the corresponding tones of the bass called 1, 2, 3, 4, 5, 6, and 7, respectively, and K is used as the bass control key.
##### Adds a toggle control button for playback and playing functions

The switching function can be done with another off-board independent key, and each time this off-board key is pressed, it switches from one mode to another.
##### Bluetooth functions
1. Set up an electronic keyboard password lock, enter the correct password through the Bluetooth terminal of the mobile phone, and then turn on the electronic keyboard.

2. When music is playing, the phone displays the name of the song being played.

3. You can control the playback of songs on your phone using bluetooth.

------

### Other information about this repository

1. In the "Music-Play" folder, there are C files that play the songs "Little Stars" and "Shinning Days" separately.

2. ==I'm just getting started with C programming, it's my first time working on a project on my own, and my level of programming is still improving, so the implementation code for this project doesn't look concise enough, and there's plenty of room for debugging and modifying. If you have any questions or suggestions, you are more than welcome to comment or contact me directly.==

3. Will be updated continuously... 

   ​                                                                                                                Edition1. December 29, 2021 at Ye Jiaxuan Library, Tsinghua University.





