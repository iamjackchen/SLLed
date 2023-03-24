# SLLed

A decorative lighting piece I designed and built for Valentine's day. The project is called "SLLed" because the intended recipient had supposedly caught me talking about singly-linked lists in my sleep.

Inspired by https://www.instructables.com/DIY-LED-heart/. 

</br>

## Hardware

I first started by building a schematic in KiCAD. Some design considerations:

 - I was at uni and didn't have access to my usual soldering equipment, so I had to get my PCB assembled by its manufacturer. This meant that my component selection was restricted to what the manufacturer had available. 

 - I also didn't have access to any mcu programming tools, so I wanted this module to be USB-programmable for ease of development. USB-C because, c'mon guys, it's 2023.

For the MCU I settled for the ATMega16U2, which is from the family of microcontrollers used in the classic Arduino line (the commonly-used 32U4 was out of stock). 

I added a 16MHZ crystal should I choose to implement some form of USB connectivity with a host device in the future (for which the 16U2's internal crystal would be insufficient).

I also designed a very simple MOSFET-based power-switching circuit so that this module can be powered both via battery and USB.
 
The final schematic may be found [here](https://github.com/iamjackchen/SLLed/blob/master/Hardware/schematic.pdf).


![](https://raw.githubusercontent.com/iamjackchen/SLLed/master/Screenshots/Schematic.png)

<br/>

I then assigned footprints to components and build a quick layout. Some design considerations:

 - For reasons of aesthetic purity, everything visible on the front-side of the PCB must be part of the heart. No vias outside of the heart!

 - Added a small hole to the top of the PCB, so you could thread a string through it and hang the module on somewhere

The geometry of the heart took some time to get right, but it turned out ok.



![](https://raw.githubusercontent.com/iamjackchen/SLLed/master/Screenshots/PCBEditor.png)

<br/>

I exported the Gerber files and BOM, and sent it off to JLCPCB for manufacture. Here are some renders: 

<p align="center">
  <img align="center" src="https://raw.githubusercontent.com/iamjackchen/SLLed/master/Screenshots/PCBFrontRender1.png" width="49%"/>
  <img align="center" src="https://raw.githubusercontent.com/iamjackchen/SLLed/master/Screenshots/PCBBackRender1.png" width="49%"/> 
</p>

<br/>


## Software

In my humble opinion, using Arduino as a university student in _computer science_ is akin to intellectual cowardice. It is a sign that one lacks to bravery to face the almighty datasheet. /s

I programmed this in AVR C because I wanted to learn more about how microcontrollers worked at a lower level. Implementing I/O functions and interrupts by directly interacting with registers was a fun challenge and made the end result all the more rewarding. 

The [code](https://github.com/iamjackchen/SLLed/blob/master/Software/code.c) is structured as such:

 - I have system of decoding arrays so that the corresponding bits at the corresponding registers for each LED can be easily accessed via an index, where 0 is the top LED and the index moves through the heart clockwise.

 - The program runs on an infinite loop, which relies on a frame counter that increments and resets periodically. For each lighting mode, I have done some rudimentary maths to map the frame counter to the indices of the LEDs that need to be turned on or off.

 - An interrupt service routine is defined such that whenever the push-button (connected to Pin C2) is pressed, the loop resets and and the lighting mode changes.

There are currently 5 lighting modes built into the program : twinkle, heartbeat, vertical sweep, snake, and solid (hopefully these names are all self-explanatory).

<br/>

## Gallery



<p align="center">
 <img align="center" src="https://raw.githubusercontent.com/iamjackchen/SLLed/master/Screenshots/wall.jpg" width="32.3%" />
<img align="center" src="https://raw.githubusercontent.com/iamjackchen/SLLed/master/Screenshots/display.jpg" width="32.3%" />
<img align="center" src="https://raw.githubusercontent.com/iamjackchen/SLLed/master/Screenshots/dark.jpg" width="32.3%" />
</p>

<p align="center">
 <img align="center" src="https://raw.githubusercontent.com/iamjackchen/SLLed/master/Screenshots/snake.gif" width="49%" />
<img align="center" src="https://raw.githubusercontent.com/iamjackchen/SLLed/master/Screenshots/vsweep.gif" width="49%" />
</p>


