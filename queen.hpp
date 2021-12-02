#include "rook.hpp"
#include "bishop.hpp"

// Multiclass inheritance
class Queen : public Rook, public Bishop
{
    public:
        //constructor
        Queen(Team team, int r, col c) : Piece(PType::Q, team, std::pair(r,(int)c)){}

        std::vector<std::pair<int,int>> get_valid_moves();
};