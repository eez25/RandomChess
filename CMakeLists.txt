project(RandomChess)
set(CMAKE_CXX_STANDARD 20)

add_executable(RandomChess 
	main.cpp 
	board.hpp board.cpp 
	piece.hpp piece.cpp 
	printer.hpp printer.cpp 
	bishop.hpp bishop.cpp 
	king.hpp king.cpp 
	knight.hpp knight.cpp 
	pawn.hpp pawn.cpp 
	queen.hpp queen.cpp 
	rook.hpp rook.cpp 
	move.hpp move.cpp)