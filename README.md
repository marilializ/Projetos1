Trilha sonora 
===
_Board game designed for visually impaired people_

A board game designed to provide the same experience for both visually impaired and sighted players. 

This respositorie contain all codes used in this project, including The source code to move the arduino servos and the code for the minigames.

Wiring
===

This can be a little confusing, so make it slowly and calmly.

![Trilha Sonora Conections](extras/Trilha_sonora.png?raw=true "Trilha Sonora Conections")

You can use the [Fritzing](http://fritzing.org/home/)(_.fzz_) files inside [extras](https://github.com/marilializ/Projetos1/tree/main/extras) to see it more closely and to draw your own prototype.

How to use 
===

1. **install**

    - if you haven't already got, install the [Arduino IDE](https://www.arduino.cc/en/software/)
    - install the files from the repository

2. **Configure**

    With arduino ide open:

    - Click in ```File  > Open```;
    - Search in your Pc for the folder of the project;
    - Open the ```Geral.ino```
    - Select ```OK```

    This will create a new folder for the Geral file;

    - Move the other Files in the main folder to the Geral folder;

3. **aply**

    With all the other things ok, just upload the code to your arduino.

4. **audio**

    With a MicroSd with 32gb or less, formatted in FAT32:
    
    - Cacth all the folders in the audio folders of the main and move to the Microsd.
    
    - insert the microsd in the DFRobot module.

5. **Done**

    Thats it, press the reset button in the arduino and it's done.