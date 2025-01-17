# gta2-trainer-cpp

[Video showcase](https://www.youtube.com/watch?v=uAMWq2xMrv0)

## About
A tool for GTA2 allowing you to manipulate gameplay in real time (without exiting the game or loading saves). 
Some of the main features are:
- Controlling your character's stats e.g. health, ammo, appearance, walking speed, wanted level, respect
- Teleporting peds and cars
- Spawning vehicles
- Quicksaving the game
- Customizing your vehicle (color, emblems, damage, physics, invulnerability)
- Spawning objects (football, generator, tank turret, power-ups etc.)
- Spawning characters and setting up their AIs, appearance etc.
- Playing vocals
- Obtaining weapons (including secret ones)
- Obtaining car weapons
- Getting unlimited ammo, no reload delays
- Using some of the built-in cheats without entering any cheat codes
- Obtaining power-ups (invisibility, get outta jail free card, etc.)
- Freely moving in-game camera, freezing its height and zoom
- A customizable table showing info about all peds and vehicles in real time
- Hijacking trains:)

## Fast install
If you just want to play it, go to the [Releases tab](https://github.com/izawartka/gta2-trainer-cpp/releases) and download
the latest gta2-trainer-x.xx.zip. Then copy its contents to your game root folder. Now you just need to run (in windowed mode)
gta-trainer.exe file instead of gta.exe and you should see the trainer window under the GTA2 window.

If you're having problems with running the game make sure your system has [all needed VC++ Redistributables](https://www.techpowerup.com/download/visual-c-redistributable-runtime-package-all-in-one/) installed and you are using [GTA2 v11.44](https://gtamp.com/gta2/) without WideScreenFix or any other mods.

## Key bindings
- `ALT + W` - Get all weapons
- `ALT + G` - Spawn GT24640
- `ALT + T` - Spawn a tank
- `ALT + J` - Spawn a jeep
- `ALT + E` - Explode all nearby cars
- `ALT + P` - Teleport all peds to the player
- `ALT + O` - Spawn the last spawned object
- `ALT + C` - Spawn the last spawned car
- `ALT + H` - Hijack a train
- `ALT + N` - Watch the next ped (when watching peds)
- `ALT + B` - Show big text
- `ALT + D` - Call the debug function (no effect)
- `ALT + Q` - Save the game

## Building
If you want to build it on your own, there is a VS solution included in the repo.

Before you'll try to compile it for the first time, you have to change some settings though
1. Change the configuration to Release x86
2. Configuration Settings > General > Output directory <-- change it to the GTA2 root folder path
3. Configuration Settings > Debugging > Program <-- change it to the GTA2-trainer.exe path
4. Configuration Settings > Debugging > Working directory <-- change it to the GTA2 root folder path
5. Compile!

## Authors
- masuo (aka. izawartka)
- h0x91b

## Knowledge sources
- Own research using Ghidra, Cheat Engine and x64dbg
- [Official scripting documentation](https://gtamp.com/GTA2/gta2script.7z)
- [.MIS decompiler by T.M.](https://gtamp.com/forum/viewtopic.php?f=4&t=447)
- [Memory addresses list by BeepBoop](https://gtamp.com/forum/viewtopic.php?t=1123)

If you want to add something more to the software, you're free to do it but please mention us in your project.

## Links
Some of my GTA2 videos on YT:
https://www.youtube.com/playlist?list=PLKAXxj2_FYzeFLyv6GPP8g58Z9kq6_rQU

h0x91b's Discord server:
https://discord.gg/H7tBftD
