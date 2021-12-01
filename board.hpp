#include <vector>
#include <string>

#include "piece.hpp"

const int BOARD_LENGTH = 8;
const std::vector<Piece> all_pieces;

class Board
{ 
    public:
        //holds the pieces active on the board in their appropriate spaces
        std::vector<std::vector<Piece*>> board;

        //holds the pieces who no longer occupy spaces on the board
        std::vector<Piece*> removed_pieces;

        //holds the pieces who occupy spaces on the board
        std::vector<Piece*> active_pieces;

        //retrieves the pieces in the given vector who meet the criteria passed in
        std::vector<Piece*> get_pieces(std::vector<Piece*> vec, PType pt, Team t);
        std::vector<Piece*> get_pieces(std::vector<Piece*> vec, PType pt);
        std::vector<Piece*> get_pieces(std::vector<Piece*> vec, Team t);

        //determines if the team given has checkmated the other team
        bool has_checkmate(Team t);

        //determines if the team given has checked the other team
        bool has_check(Team t);

        //removes a piece from the board and makes it inactive; returns false if the piece is already off the board
        bool remove_piece(Piece* p);

        //replaces a piece on the board and makes it active; returns false if the piece is already on the board
        bool replace_piece(Piece* p, std::pair<int,int> pos);

        // moves Piece p to board space pos and handles chain reactions such as removing pieces that were captured
        void move(Piece* p, std::pair<int,int> pos);
};