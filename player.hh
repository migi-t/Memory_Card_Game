#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>
#include "card.hh"
#include <vector>

/* Class: Player
 * ------------
 * Depicts one player in program
 */

class Player
{
public:

    // Constructor: creates a player with the given name.
    Player(const std::string& name);

    // Destructor.
    ~Player();

    // Returns the name of the player.
    std::string get_name();

    // Returns the number of pairs collected by the player so far.
    std::vector <char> get_pairs() const;

    // Moves the given card from the game board for the player,
    // i.e. inserts it to the collected cards of the player and
    // removes it from the game board.
    void add_card(char letter);

private:
    std::string name_;
    std::vector <char> pairs_ = { };
};

#endif // PLAYER_HH
