# playerandai-prototype
<h1>Only Makefiles/Makefile.linux-g++, Makefiles/Makefile.linux.libtcod-g++ Makefiles/Makefile.msys Makefiles/Makefile.msys-libtcod (32 bit ) Makefiles/Makefile.freebsd ( gcc9 ) and Makefiles/Makefile.freebsd.libtcod-g++ ( gcc9 ) will build currently, but you can take a look at it and make other platforms compile</h1> <br />
To run a makefile (Debian 9 example): <br />
make -f Makefiles/Makefile.linux-g++ <br />
<br />
To run a makefile (Openbsd example): <br />
gmake -f Makefiles/Makefile.openbsd <br />
<br />
For windows you will need msys2 or visual studio 2017.  To run the compiled program from the msys2 and visual studio.  You will have to use cmd.  Msys2 terminal can't run the game properly.  In msys2 launching from shortcut mingw64.exe in the msys2 install directory: <br />
git <br />
ncurses <br />
openssl-devel (needed, because if you want to choose a seed 'example from cmd: .\playerandai1.exe "This is better now"') <br />
mingw-w64-x86_64-toolchain <br />
base-devel <br />
pkg-config <br />
<br />
For windows in msys2 you can install them using: <br />
pacman -S ncurses-devel mingw-w64-x86_64-ncurses openssl-devel mingw-w64-x86_64-toolchain base-devel pkg-config <br />
<br />
For Ubuntu you will need: <br />
git <br />
libncurses-dev <br />
libssl-dev (needed, because if you want to choose a seed 'example from bash: ./playerandai1 "This is better now"') <br />
build-essential <br />
pkg-config <br />
<br />
For Ubuntu you can install them using: <br />
sudo apt-get install git libncurses-dev libssl-dev build-essential pkg-config <br />
<br />
To compile with visual studio 2017 you will need pdcurses and openssl development includes and libs. You can get openssl from http://slproweb.com/products/Win32OpenSSL.html The preprocessor need the options 
_CRT_SECURE_NO_WARNINGS;INITWINDOWSNOW;INITNCURSESNOW;FREEBSD;INITWINDOWSNCURSES;INITOPENSSL; and keep the options there already for the preprocessor. <br />
<br />
To enable 2 player support (you can replace none with a different word): <br />
Linux: <br />
./playerandai1 "none" 1 <br />
Windows: <br />
.\playerandai1.exe "none" 1 <br />
<br />
