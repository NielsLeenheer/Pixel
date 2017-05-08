<h1>
<img src=https://raw.githubusercontent.com/NielsLeenheer/Pixel/master/source/PixelServer/data/web/icon2x.png width=36 height=36 align="absmiddle"> Pixel
</h1>

A pixel art display for displaying monsters and notifications. But mostly monsters. Created using a NodeMCU and a 8x8 LED matrix, some code and a lot of hacks.
This project was created just to have some fun and experiment with the NodeMCU to create a connected pixel art display.

![Pixel](https://raw.githubusercontent.com/NielsLeenheer/Pixel/master/photos/main.jpg)

When assembled, it sets up a custom WiFi hotspot with captive portal, which you can use to configure the Pixel. It can connect
to any other WiFi network and has an API which can be used to display notifications. For example, I use Domoticz to track
when my mailbox is full and it sends a nice picture of a mailbox to Pixel. When connected to the WiFi network, it also has a 
webserver that contains a mobile web app. That app allows you to draw monsters on the display using your phone and save them in Flash memory.

More info about this project can be found in my talk "Monsters, mailboxes and other non-sense":
https://speakerdeck.com/nielsleenheer/monsters-brievenbussen-en-andere-onzin-at-amsterdam-university-of-applied-sciences?slide=56


What you need to build this is:
- NodeMCU
- 8x8 LED matrix, like the Adafruit NeoPixel Matrix
- 10kΩ Resistor
- Photoresistor 
- 1000μF Electrolytic capacitor
- Active buzzer

And of course a housing to put it in. A 3D printed diffuser grid. And some wires, a breadboard, or maybe a custom PCB.


## The first prototype

![First prototype](https://raw.githubusercontent.com/NielsLeenheer/Pixel/master/photos/prototype-1.jpg)

The first prototype is basically just a ceilinglamp which I bought in a DIY store. I ripped out all the existing stuff, 
so I am left with just the bare housing. On the back I glued a breadboard on which I placed the components and behind the
glass I placed the LED matrix. Initially I placed the matrix directly behind the glass which caused the pixels to be round 
not connected. Later I printed a custom diffuser grid on a 3D printer that clips on the LED matrix, which makes sure the pixels will be square.

## The second prototype

![Second prototype](https://raw.githubusercontent.com/NielsLeenheer/Pixel/master/photos/prototype-2.jpg)

I'm currently working on a second prototype, still based on a ceilinglamp housing. The second prototype uses a custom 
designed PCB based on the latest configuration of the first prototype. The PCB will be much smaller than the breadboard,
so it will fit better in the housing. Also because there a less random wires sticking out, it will look less like a bomb. Also I've replaced the 3D printed diffuser and replaced it with a laser-cut one that fits snugly in the housing. 

## Stuff to work on

- An even smaller PCB that is not larger than the NodeMCU (design is done, currently at the fab). 
- Improve the laser-cut diffuser, by using thicker, black plexiglas. And optionally place matte transparent plexiglas windows in the holes of the diffuser.
- Maybe build a custom housing using lasercutting.
