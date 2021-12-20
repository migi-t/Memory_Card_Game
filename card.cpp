#include "card.hh"
#include <string>
#include <iostream>

//Methods for Card class
Card::Card(const char c):
    letter_(c), visibility_(HIDDEN)
{
}

Card::~Card()
{
}

void Card::set_letter(const char c)
{
    letter_ = c;
}

void Card::set_visibility(const Visibility_type visibility)
{
    visibility_ = visibility;
}

char Card::get_letter() const
{
    return letter_;
}

Visibility_type Card::get_visibility() const
{
    return visibility_;
}
