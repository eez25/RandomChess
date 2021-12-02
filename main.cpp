#include "board.hpp"
#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "printer.hpp"
#include "queen.hpp"
#include "rook.hpp"

Board B;

int main()
{
    printer::print_board(B);
    return 0;
}