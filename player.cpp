#include "player.hh"
#include <string>

//Methods for Player class
Player::Player(const std::string& name):name_(name)
{
}

Player::~Player()
{
}

std::string Player::get_name()
{
    return name_;
}

std::vector<char> Player::get_pairs() const
{
    return pairs_;
}


void Player::add_card(char letter)
{
    pairs_.push_back(letter);
}
