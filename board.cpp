#include "board.hpp"

bool same_type_team(Piece* p, PType pt, Team t)
{
    return *p == std::pair(pt,t);
}

bool same_type(Piece* p, PType pt, Team t)
{
    return p->get_type() == pt;
}

bool same_team(Piece* p, PType pt, Team t)
{
    return p->get_team() == t;
}

//uses function pointers to above boolean methods
std::vector<Piece*> check_pieces(bool (*check_same)(Piece*,PType,Team), std::vector<Piece*> vec, PType pt, Team t)
{
    std::vector<Piece*> ret;
    for (Piece* p : vec)
    {
        if (check_same(p,pt,t))
        {
            ret.push_back(p);
        }
    }
    return ret;
}

//passes function pointer as parameter
std::vector<Piece*> Board::get_pieces(std::vector<Piece*> vec, PType pt, Team t)
{
    return check_pieces(same_type_team, vec, pt, t);
}

//passes function pointer as parameter
std::vector<Piece*> Board::get_pieces(std::vector<Piece*> vec, PType pt)
{
    return check_pieces(same_type, vec, pt, Team::Empty);
}

//passes function pointer as parameter
std::vector<Piece*> Board::get_pieces(std::vector<Piece*> vec, Team t)
{
    return check_pieces(same_team, vec, PType::Empty, t);
}


bool Board::has_checkmate(Team t)
{
    // get opposing king
    Piece* king = get_pieces(active_pieces, King, Piece::opposite(t))[0];

    // true if he has no moves and is_threatened AND TODO CANNOT BE PROTECTED
    return king->get_valid_moves().size() == 0 && has_check(t);
}

bool Board::has_check(Team t)
{
    // get team t's active pieces and the opposing king
    std::vector<Piece*> pieces = get_pieces(active_pieces, t);
    Piece* king = get_pieces(active_pieces,King,Piece::opposite(t))[0];

    // if any of these pieces are threatening the opposing king, return true
    for (Piece* p : pieces)
    {
        if (p->is_threatening(king->get_position())) return true;
    }
    return false;
}

//removes an element from remove_from and adds it to add_to; returns false if it is not in remove_from
bool switch_vecs(std::vector<Piece*> add_to, std::vector<Piece*> remove_from, Piece* element)
{
    //STL algorithm
    std::vector<Piece*>::iterator found_el = std::find(remove_from.begin(),remove_from.end(),element);

    //return false if the piece is already not there (so find returned the last element instead)
    if (found_el[0] != element) return true;
    
    //if the piece is in the vector we want to remove it from
    remove_from.erase(found_el);
    add_to.push_back(element);
    return false;
}

bool Board::remove_piece(Piece* p)
{
    // attempt to move p from removed to active and return false if not possible
    bool already_gone = switch_vecs(removed_pieces,active_pieces,p);
    if (already_gone) return false;

    // set the piece at this board space to be empty
    board[p->get_position().first][p->get_position().second] = Piece::get_empty();

    return true;
}

bool Board::replace_piece(Piece* p, std::pair<int,int> pos)
{
    // attempt to move p from removed to active and return false if not possible
    bool already_gone = switch_vecs(active_pieces,removed_pieces,p);
    if (already_gone) return false;

    // set this piece to its proper place on the board
    board[p->get_position().first][p->get_position().second] = p;
    
    return true;
}

void Board::move(Piece* p, std::pair<int,int> pos)
{
    Piece* old = board[pos.first][pos.second];

    // remove the old piece if there is one
    if (old != Piece::get_empty()) remove_piece(old);

    // move this piece to the new place
    board[pos.first][pos.second] = p;

    // put nothing in the place this piece used to occupy
    board[p->get_position().first][p->get_position().second] = Piece::get_empty();
    
    // update the position attribute to be the new location
    p->set_position(pos);
}