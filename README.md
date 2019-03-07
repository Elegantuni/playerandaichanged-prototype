# playerandai-prototype
To run a makefile (Debian 9 example): <br />
make -f Makefile.linux <br />
<br />
For windows you will need in msys2 launching from shortcut mingw64.exe in the msys2 install directory: <br />
git <br />
ncurses <br />
openssl-devel (needed, because if you want to choose a seed 'example from cmd: .\playerandai1.exe "This is better now"') <br />
mingw-w64-x8__64-toolchain <br />
base-devel <br />
pkg-config <br />
<br />
For windows in msys2 you can install them using: <br />
pacman -S ncurses openssl-devel mingw-w64-x86_64-toolchain base-devel pkg-config <br />
<br />
For Ubuntu you will need: <br />
git <br />
libncurses-dev <br />
libssl-dev (needed, because if you want to choose a seed 'example from bash: ./playerandai1 "This is better now"') <br />
build-essential <br />
pkg-config <br />
<br />
For Ubuntu you can install them using: <br />
sudo apt-get install git libncurses-dev libssl-dev build-essential clang pkg-config <br />
<br />
To compile with visual studio 2017 you will need pdcurses and openssl development includes and libs. You can get openssl from http://slproweb.com/products/Win32OpenSSL.html The preprocessor need the options 
_CRT_SECURE_NO_WARNINGS;INITWINDOWSNOW;INITNCURSESNOW;FREEBSD;INITWINDOWSNCURSES;INITOPENSSL; and keep the options there already for the preprocessor. <br />
