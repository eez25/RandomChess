#include "pawn.hpp"

#include "board.hpp"

extern Board B;

std::vector<std::pair<int,int>> Pawn::get_valid_moves()
{
    std::vector<std::pair<int,int>> moves;
    int f = forward();
    std::pair<int,int> pos = get_position();
    int r = pos.first, c = pos.second;

    // if there is no Piece directly in front of the Pawn, it can move there
    if(B.board[r][c+f] == Piece::get_empty()) 
        moves.emplace_back(r,c+f);

    // if there is an enemy Piece diagonal to the right, it can move there
    if(r-1 > 0 && B.board[r-1][c+f]->get_team() == opposite(get_team()))
        moves.emplace_back(r-1,c+f);

    // if there is a Piece diagonal to the left, it can move there
    if(r+1 < BOARD_LENGTH && B.board[r+1][c+f]->get_team() == opposite(get_team()))
        moves.emplace_back(r+1,c+f);

    // if this Pawn is in the second row of its forward direction
    // and that space is unoccupied, it can move forward
    if(f == 1? (r == 2*f) : (r == BOARD_LENGTH+(2*f)-1) & B.board[r][c+(2*f)] == Piece::get_empty())
        moves.emplace_back(r,c+(2*f));

    return moves;
}