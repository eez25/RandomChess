# RandomChess
By Enya Zimecka

Overview:
This is a simple model of a chess game.  It is playable at the command line and has a built-in opponent who moves uniformly at random.

Compiling:
 - Download folder
 - Open folder in Visual Studio C++ IDE
 - Ensure you have CMake extensions
 - Select x64-Release in the configuration drop-down
 - Select RandomChess.exe in the debug target drop-down to the right
 - Run that configuration

Simplifications:
 - Movement rules do not include castling
 - Movement rules do not restrict that you cannot open up your king to being checked
 - Game strategy is decided by randomly moving pieces

Current known bugs to fix:
 - Movement rules do not recognize that a king can move out of the way when threatened
