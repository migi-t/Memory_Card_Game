#ifndef CARD_HH
#define CARD_HH

/* Class: Card
 * ------------
 * Depicts one card in game
 */

const char HIDDEN_CHAR = '#';
const char EMPTY_CHAR = '.';
enum Visibility_type {OPEN, HIDDEN, EMPTY};

class Card
{
public:

    // Constructor: creates a hidden card with the given character.
    Card(const char c);

    // Destructor.
    ~Card();

    // Obvious setter and getter methods.
    void set_letter(const char c);
    void set_visibility(const Visibility_type visibility);
    char get_letter() const;
    Visibility_type get_visibility() const;

private:
    char letter_;
    Visibility_type visibility_;
};
#endif // CARD_HH
