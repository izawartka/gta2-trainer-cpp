# gta2-trainer-cpp

## About
A tool for GTA2 allowing you to manipulate gameplay in real time (without exiting the game or loading saves). 
Some of the main features are:
- Controlling your character's stats e.g. health, ammo, appearance, walking speed, wanted level, respect
- Teleporting
- Spawning any cars
- Spawning any objects (power-ups etc.)
- Playing vocals
- Giving yourself any weapons (including secret ones)
- Giving yourself any car weapons
- Using some of the built-in cheats without entering any cheat codes

## Fast install
If you just want to play it, go to the [Releases tab](https://github.com/izawartka/gta2-trainer-cpp/releases) and download
the latest gta2-trainer-x.xx.zip. Then copy its contents to your game root folder. Now you just need to run (in windowed mode)
gta-trainer.exe file instead of gta.exe and you should see the trainer window under the GTA2 window.

If you're having problems with running the game make sure your system has [all needed VC++ Redistributables](https://www.techpowerup.com/download/visual-c-redistributable-runtime-package-all-in-one/) installed.

## Playing with the code
If you want to build it on your own, there is a VS solution included in the repo.

Before you'll try to compile it for the first time, you have to change some settings though
1. Change the configuration to Release x86
2. Configuration Settings > General > Output directory <-- change it to the GTA2 root folder path
3. Configuration Settings > Debugging > Program <-- change it to the GTA2-trainer.exe path
4. Configuration Settings > Debugging > Working directory <-- change it to the GTA2 root folder path
5. Go to the Visual Studio Command Line
6. Type cd Detours
7. Type nmake
8. Wait ...
9. Done!

## Authors
h0x91b,
masuo (aka. izawartka)

And if you want to add something more to it, you're free to do it but it would be nice if you mentioned us somewhere.

## Links
Some of my GTA2 videos on YT:
https://www.youtube.com/playlist?list=PLKAXxj2_FYzeFLyv6GPP8g58Z9kq6_rQU

h0x91b's Discord channel:
https://discord.gg/H7tBftD
