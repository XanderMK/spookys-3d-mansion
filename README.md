# A very in-progress remake of Spooky's Jumpscare Mansion in C++ for the Nintendo 3DS.

https://github.com/user-attachments/assets/8b0e91c2-43e4-46ef-84f6-e72c00aa6546

^ a vid of the game streaming from real hardware

![pic](https://github.com/user-attachments/assets/04530574-b4e4-4e61-b603-65d5f8fe95b0)

### This is a remake of the indie game Spooky's Jumpscare Mansion, now on Nintendo 3DS! It supports 3D as well (though it runs kinda slow, I need to optimize the rendering)

To run this game, either use an emulator (I recommend Lime3DS) or put it on the SD card of a modded 3DS.

EMULATOR:
- Download .3dsx file
- Drag and drop file onto emulator (or open File>Load File and select the .3dsx)

CONSOLE:
- Download .3dsx file
- Take SD card out of 3DS, insert into computer, and drag .3dsx file into the /3ds folder (or use FTP client to do the same)
- Put SD card back in 3DS, open Homebrew Launcher, and open the game (If downloaded .cia, open FBI and install the file from there, then run it from the home screen)

CONTROLS:
- Circle pad to move
- C stick to look (I believe you can also use the Circle Pad Pro on the original 3DS)
- R to run
- A to open doors
- Start to exit

TO BUILD:
- Install devkitPro, devkitARM, and all 3DS-specific addons (https://devkitpro.org/wiki/Getting_Started)
  - Note: I think there were some bulid libraries that were not installed automatically from devkitARM. If there are errors about files not being found, you can find the corresponding tools online and move them into the tools folder.
- Open the folder with source and run "make all"
