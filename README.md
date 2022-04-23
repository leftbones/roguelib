# Roguelib

I started making a game in a psuedo terminal-style way, using ASCII graphics (code page 437) drawn from a texture, similar to how Dwarf Fortress handles graphics. After getting everything up and working, I decided to instead make a sort of "library" for others to use alongside raylib for quickly laying the groundwork for making classic roguelike games. I'm writing this in C but I've been doing all of my testing using C++, so it should work with both languages just fine.

This library is dependent on raylib. The only other thing required is a tileset. If you don't know where to get one, try here: https://dwarffortresswiki.org/index.php/Tileset_repository

Just put the headers somewhere in your project directory, include `roguelib.h`, and you're good to go!

*Roguelib is a codename and may be subject to change in the future.*
