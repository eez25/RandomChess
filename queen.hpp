#include "rook.hpp"
#include "bishop.hpp"

// Multiclass inheritance
class Queen : public Rook, public Bishop
{
    //constructor
    Queen(Team team, std::pair<int,int> pos) : Piece(PType::Queen, team, pos){}

    std::vector<std::pair<int,int>> get_valid_moves();
};