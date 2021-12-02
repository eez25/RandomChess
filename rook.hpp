#include "piece.hpp"

// making this a virtual class because it is one of two (this and Bishop) that
// are subclassed by the same child class (Queen)
class Rook : virtual public Piece 
{
    public:
        //constructor
        Rook(Team team, int r, col c) : Piece(PType::R, team, std::pair(r,(int)c)){}
        Rook() = default;

        std::vector<std::pair<int,int>> get_valid_moves();
};