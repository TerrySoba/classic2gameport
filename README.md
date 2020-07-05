Classic2Gameport
================

About
-----
Classic2Gameport is an adapter that allows to connect up to two [Nintendo Wii Classic Controllers](https://en.wikipedia.org/wiki/Classic_Controller) to [PC Gameports](https://en.wikipedia.org/wiki/Game_port).
The adapter acts like a Gravis Gamepad.

Supported Devices
-----------------

The following Nintendo controllers are supported:
 * Classic Controller
 * Classic Controler Pro
 * SNES Mini Controller

The PC needs to have a Gameport to use this adapter.


Adapter Modes
-------------

| Mode | Combination | Description |
|------|-------------|--|
| Normal Mode | SELECT + DOWN | Button B -> 1<br>Button Y -> 2<br>Button A -> 3<br>Button X -> 4 |
| Two Player Mode | (connect two controllers) | Button B1 -> 1<br>Button Y1 -> 2<br>Button B2 -> 3<br>Button Y2 -> 4<br>
| Jump'n'Run Mode | SELECT + UP | Button Y -> 1<br>Button A -> 2<br>Button B -> Up |

Building Instructions
---------------------

Here are some images of the assembled adapter:

![pcb v4 front](images/finished_adapter.jpg "The finished adapter")
![pcb v4 front](images/pcb_v4_front.jpg "PCB Version 4 Front")
![pcb v4 back](images/pcb_v4_back.jpg "PCB Version 4 Back")

The Kicad files of the PCB can be found in the pcb directory of the repository.

The firmware for the ST STM32G071KxT microcontroller can be found in the firmware directory.