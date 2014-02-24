Install
-------

- You need a correctly prepared multitouch hardware for it to work.
- It should work with the mouse but it is not recommended.
- Just running attractouch.exe is enough

Level editing
-------------

For the launcher, the direction is an angle in degrees.
Zero is oriented full right and positive angles are counter-clockwise.

All positions are according to a 1280x1024 screen but are adapted
according to the current resolution.

The radius for launcher is the activation radius for the finger,
for receiver it is the radius of attraction of particles.

The rate of the level should not be modified for the sound to be
in a good rythm.

The next level should not be set for the last level, it will then
return to the menu. The name of a level consists of the base name
of the XML file : for yahoo.xml, its name is "yahoo".

The name of the first level is inside constants.xml and can be
modified.

The XSD files should not be modified.


Keyboard shortcuts
------------------

R - reload current level
N - next level (or menu if last level)
D - debug mode
Space - start/stop simulation of particles
S - do one step of the simulation
Q - quit
Space (on video) - skip video


Using the mouse as fingers
--------------------------

Left button - temporary finger
	follows the mouse as long as you keep the button pressed
Right button - sticky finger
	stays in place but can be removed by right clicking on its center
	can be moved using the left button on its center