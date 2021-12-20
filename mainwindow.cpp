#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "player.hh"
#include "card.hh"

#include <QPoint>
#include <QCursor>
#include <QGraphicsView>
#include <QPalette>
#include <QString>
#include <QPixmap>
#include <QSize>

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <fstream>
#include <set>
#include <random>

//Methods/functions for mainwindow of the program

//Images for cards universal backside and 26 images for each letter
const std::vector<std::string> images = {
    "pictures/card_backside.png", "A.png", "B.png", "C.png", "D.png", "E.png",
    "F.png", "G.png", "H.png", "I.png", "J.png", "K.png", "L.png", "M.png",
    "N.png", "O.png", "P.png", "Q.png", "R.png", "S.png", "T.png", "U.png",
    "V.png", "W.png", "X.png", "Y.png", "Z.png"

};

//Rules to be displayed in the ui
const QString rules_str = "RULES: Choose between 16-52 cards, 2-6 players and "
"give individual name for everyone, leave one space between each entered name. "
"  When clicking <PLAY!>, the game starts and ends when all"
" cards are picked up by players or when pressed <RESTART>, which"
" resets the game totally. After turning two different cards, player in turn "
"must press <SWITCH TURN> to give turn to next player.";

//String of letters for generating cards
const std::string LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Changes colors of some ui components
    QPalette pal = palette();
    pal.setColor(QPalette::Button, Qt::green)
            ;ui->playButton->setAutoFillBackground(true)
            ;ui->playButton->setPalette(pal);ui->playButton->update();

    pal.setColor(QPalette::Button, Qt::red)
            ;ui->restartButton->setAutoFillBackground(true)
            ;ui->restartButton->setPalette(pal);ui->restartButton->update();

    pal.setColor(QPalette::Window, Qt::black)
            ;ui->lcdNumberMin->setAutoFillBackground(true)
            ;ui->lcdNumberMin->setPalette(pal);ui->lcdNumberMin->update();

    ui->lcdNumberSec->setAutoFillBackground(true)
                ;ui->lcdNumberSec->setPalette(pal);ui->lcdNumberSec->update();

    //Changes min/max values of some ui components
    ui->spinBoxCards->setMinimum(16);
    ui->spinBoxCards->setMaximum(52);
    ui->spinBoxCards->setSingleStep(2);

    ui->spinBoxPlayers->setMinimum(2);
    ui->spinBoxPlayers->setMaximum(6);

    ui->rulesBrowser->setText(rules_str);

    //Sets timer
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update_timer()));

    //Setting a graphics view to put buttons inside them, 4:3 relation
    QGraphicsView* view_ = new QGraphicsView(this);
    view_->setGeometry(10, 160, 600, 450);
    view_->show();

    //Area for card stacks
    scene_ = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene_);

    //Disables some buttons by default, these buttons are enabled when they are
    //needed
    ui->newturnButton->setDisabled(true);
    ui->restartButton->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;

    //Destructs all players
    for (unsigned int i=0;i<player_objects_.size();++i) {
        delete player_objects_.at(i);
    }

    //Deletes timer
    delete timer;

    //Deletes scene
    delete scene_;

    //Destructs all buttons and cards
    for (unsigned int i=0;i<cards_buttons_.size();++i) {

        for (unsigned int j=0;j<cards_buttons_.at(i).size();++j) {

            delete cards_buttons_.at(i).at(j);
            delete card_matrix_.at(i).at(j);

        }
    }

    //Deletes name labels
    for (unsigned int i=0;i<name_labels_.size();++i) {
        delete name_labels_.at(i);
    }

    //Deletes the card stack labels from each player
    auto iter = stack_labels.begin();
    while (iter != stack_labels.end()) {

        std::vector<QLabel*> to_delete = iter->second;
        for (unsigned int i=0;i<to_delete.size();++i){
            delete to_delete.at(i);
        }

        ++iter;
    }
}

//Handles showing time spent on one game
void MainWindow::update_timer()
{
    if (seconds_ == 60) {
        seconds_ =0;
        minutes_ += 1;

    } else {
        seconds_ += 1;
    }

    ui->lcdNumberSec->display(seconds_);
    ui->lcdNumberMin->display(minutes_);
}

//Handles card clicks and advances game when user has found pairs
void MainWindow::handle_card_click()
{

    // Counting local cursor position, i.e. decreasing
    // Main Window's location from the global one
    QPoint global_click_position = QCursor::pos();
    int local_x = global_click_position.x() - geometry().x();
    int local_y = global_click_position.y() - geometry().y();
    QPoint local_click_position = QPoint(local_x, local_y);

    //Search the matrises for button clicked and the corresponding card object
    for (unsigned int i=0;i<cards_buttons_.size();++i) {

        std::vector <QPushButton*> row = cards_buttons_.at(i);

        for (unsigned int j=0;j<row.size();++j) {

            if (cards_buttons_.at(i).at(j)->geometry()
                    .contains(local_click_position) and
                    cards_clicked_in_turn < 2) {

                //Modifies the states of the wanted button and card object
                Card* atm_card = card_matrix_.at(i).at(j);
                atm_card->set_visibility(OPEN);

                QString letter = "";
                std::string letter_str(1, atm_card->get_letter());
                letter += atm_card->get_letter();

                QPushButton* atm_button = cards_buttons_.at(i).at(j);

                //At index 1 is the latest clicked/revealed card.
                //Makes sure user cant reveal same card two times
                if (latest_two_buttons_.at(1) == atm_button) {
                    return;
                }

                //Updates the latest two activated cards/buttons
                latest_two_buttons_.erase(latest_two_buttons_.begin());
                latest_two_buttons_.push_back(atm_button);

                latest_two_cards_.erase(latest_two_cards_.begin());
                latest_two_cards_.push_back(atm_card);

                cards_clicked_in_turn += 1;

                //Turns clicked card to show correct frontside picture on it
                std::string filename = "pictures/";
                filename += std::string(1, atm_card->get_letter()) + ".png";
                QPixmap img(QString::fromStdString(filename));
                QPixmap scaled = img.scaled(QSize(atm_button->width(),
                                atm_button->height()), Qt::IgnoreAspectRatio,
                                            Qt::SmoothTransformation);
                atm_button->setIcon(scaled);
                atm_button->setIconSize(QSize(atm_button->width(),
                                              atm_button->height()));

                //Checks if two cards are revealed, enables switching turn
                //and informs user about possible found pairs
                if (cards_clicked_in_turn == 2) {

                    ui->newturnButton->setEnabled(true);

                    if (latest_two_cards_.at(0)->get_letter() ==
                            latest_two_cards_.at(1)->get_letter()) {
                        std::string info = "";

                        info += ("Pairs! Player " + in_turn->get_name() +
                                 " earned card " + letter_str);

                        ui->roundInfoBrowser->setText(QString::fromStdString(info));
                        in_turn->add_card(latest_two_cards_.at(0)->get_letter());

                    } else {
                        ui->roundInfoBrowser->setText("Not pairs!");
                    }
                }
                return;
            }
        }
    }
}

//Splits a string with parameters character and returns result in vector
std::vector <std::string> split_string(std::string str, char delim)
{

    std::vector<std::string> result = {""};
    bool cont = false;
    for ( auto cha : str )
    {
        if ( cha == '"' )
        {
            cont = not cont;
        }
        else if ( cha == delim and not cont)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(cha);
        }
    }
    if ( result.back() == "" )
    {
        result.erase(--result.end());
    }
    return result;
}

//Checks that all input fields in game are filled correctly, return True if so
bool MainWindow::check_input()
{

    if (amount_cards_ % 2 != 0) {
        ui->roundInfoBrowser->setText("Amount of cards must be even!");
        return false;
    }

    unsigned int max_name_length = 15;
    QString names_qstr = ui->lineEditPlayerNames->text();
    std::string name_str = names_qstr.toStdString();

    std::vector <std::string> names = split_string(name_str, ' ');

    if (names.size() != amount_players_) {
        ui->roundInfoBrowser->setText("Invalid amount of entered player names! "
                                        "Read Rules on how to enter names.");
        return false;
    }

    for (unsigned int i=0; i<names.size();++i) {

        if (names.at(i).size() > max_name_length) {
            ui->roundInfoBrowser->setText("Some player name(s) are too long! "
                                           "Max length of name is 15 letters.");
            return false;
        }
    }
    return true;
}

//Fill the existing empty matrises of cards & buttons with real cards & buttons
void MainWindow::fill_board()
{

    //Creates a string of alphabets based on amount of cards and shuffles it
    unsigned int letters = amount_cards_ / 2;
    std::string randomize_letters = "";
    unsigned int index=0;

    while (index < letters) {

        std::string atm_char = std::string(1, LETTERS.at(index));

        std::string one_part = "";
        one_part.append(atm_char);
        one_part.append(atm_char);

        randomize_letters.append(one_part);

        ++index;

    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(randomize_letters.begin(), randomize_letters.end(),std::default_random_engine(seed));
    //std::random_shuffle(randomize_letters.begin(), randomize_letters.end());

    //Used for picking letter from randomize_letters
    int letter_position = 0;

    //Replaces the nullpointers in card&button matrises with real cards&buttons
    for (unsigned int i=0;i<card_matrix_.size();++i) {

        //Adjusts y position of buttons after first row
        gboard_y_coord_ += Y_MARGIN;

        for (unsigned int j=0; j < cards_buttons_.at(i).size() ;++j) {

            char letter_to_cast = randomize_letters.at(letter_position);

            //Create new card and place it in matrix
            card_matrix_.at(i).at(j) = new  Card(letter_to_cast);

            card_matrix_[i][j]->set_letter(letter_to_cast);
            card_matrix_[i][j]->set_visibility(HIDDEN);

            //Creates new button and places it inside view_(gameboard area)
            QPushButton* pushButton = new QPushButton("", this);
            pushButton->setGeometry(2 * X_MARGIN + j * (BUTTON_WIDTH +
                                    X_MARGIN), i*BUTTON_HEIGTH +
                                    gboard_y_coord_, BUTTON_WIDTH,
                                    BUTTON_HEIGTH);

            //Inits every button with backside image(hidden)
            QPixmap img("pictures/card_backside.png");
            QPixmap scaled = img.scaled( QSize( pushButton->width(),
                             pushButton->height() ), Qt::IgnoreAspectRatio ,
                                         Qt::SmoothTransformation);
            pushButton->setIcon(scaled);
            pushButton->setIconSize(QSize(pushButton->width(),
                                          pushButton->height()));

            //Connects the new button
            connect(pushButton, &QPushButton::clicked,
                    this, &MainWindow::handle_card_click);

            cards_buttons_.at(i).at(j) = pushButton;
            pushButton->show();

            ++letter_position;

        }
    }
}

//Inits the matrix of cards and buttons with nullpointers
void MainWindow::init_empty_board()
{

    cards_buttons_.clear();
    card_matrix_.clear();

    //Calculates amount of rows and colums for both matrises
    unsigned int rows = 0;
    unsigned int columns = 0;
    calculate_factors_and_sizes(rows, columns);

    //Counts amount of cards pushed to board so that no more than needed
    //placeholding nullpointers are created
    unsigned int created_cards = 0;
    for (unsigned int i=0;i<rows;++i) {

        std::vector <QPushButton*> row_buttons = { };
        std::vector <Card*> row_cards = { };

        for (unsigned int j=0;(j<columns) and (created_cards < amount_cards_);
             ++j) {

            QPushButton* button = nullptr;
            row_buttons.push_back(button);

            Card* card = nullptr;
            row_cards.push_back(card);

            ++created_cards;

        }

        cards_buttons_.push_back(row_buttons);
        card_matrix_.push_back(row_cards);
    }
}

//Calculates amount of rows and colums based on amount of cards on board. Also
//calculates sizes for buttons, tries to make buttons 4:3 in size
void MainWindow::calculate_factors_and_sizes(unsigned int &rows,
                                             unsigned int &columns)
{

    float sqrt_of_cards = sqrt(amount_cards_);
    rows = sqrt_of_cards;

    //Check if amount of cards is n*n
    if (rows*rows == amount_cards_) {
        columns = rows;
    } else {
        columns = sqrt_of_cards + 1;
    }

    remainder_ = amount_cards_ - rows*columns;

    //If all cards do not fit into calculated row*columns, adds
    //new row for remainder cards
    if (remainder_ > 0) {
        rows += 1;
    }
    //Calculates button width and heigth using 4:3 ratio
    BUTTON_WIDTH = (gboard_width_ - (columns+1)*X_MARGIN) / columns;
    BUTTON_HEIGTH = float(0.75) * BUTTON_WIDTH;

    //Calculates space left between buttons vertically
    Y_MARGIN = (gboard_height_ - rows*BUTTON_HEIGTH) / (rows)+1 + 0.5;
}

//Checks if all card pairs have been found, returns True if so
bool MainWindow::is_board_empty()
{

    for (unsigned int i=0; i < card_matrix_.size() ;++i){
        for (unsigned int j=0; j <card_matrix_.at(i).size() ;++j){

            Card* atm_card = card_matrix_.at(i).at(j);
            if (atm_card->get_visibility() == HIDDEN) {
                return false;
            }
        }
    }
    return true;
}

//Announces winner and shows info about players stats
void MainWindow::announce_winner()
{

    std::map <Player*, int> points = { };
    unsigned int max_points = 0;

    //Saves players points to a map
    for (unsigned long int luku=0;luku< player_objects_.size();++luku)
    {

        points.insert({player_objects_.at(luku),
                       player_objects_.at(luku)->get_pairs().size()});

        //Saves biggest score
        if (player_objects_.at(luku)->get_pairs().size() > max_points) {

            max_points = player_objects_.at(luku)->get_pairs().size();

        }

    }

    //Calculates amount of winners and saves winner(s) to vector
    std::vector <Player*> winners = { };
    auto iter = points.begin();
    while (iter != points.end()) {
        if (iter->second == int(max_points)) {
            winners.push_back(iter->first);
        }
        ++iter;
    }

    //Announces winner(s)
    std::string announce_str = "Game over!\n";
    if (winners.size() == 1) {

        announce_str += (winners.at(0)->get_name() +
                         " has won with " +
                         std::to_string(max_points));

    } else {

        announce_str += ("Tie of " +
                         std::to_string(winners.size()) +
                         " players with " +
                         std::to_string(max_points));

    }

    announce_str += " pairs.\nClick RESTART for new game.";
    ui->roundInfoBrowser->setText(QString::fromStdString(announce_str));

    //Prints all scores to results browser
    QString all_info = "";

    auto iter_2 = points.begin();
    while (iter_2 != points.end()) {

        std::string player_info = "";
        player_info += (std::string(iter_2->first->get_name()) + " got " +
                        std::to_string(iter_2->second) + " points\n" +
                        "Cards: ");

        //Makes string showing all individual cards held in players stack at the
        //end of the game
        std::string players_cards = "";
        for (unsigned int i=0; i < iter_2->first->get_pairs().size() ;++i) {
            std::string letter_str(1, iter_2->first->get_pairs().at(i));

            if (i == iter_2->first->get_pairs().size() - 1){
                players_cards += letter_str;
            } else {
                players_cards += (letter_str + ", ");
            }

        }

        player_info += players_cards;
        all_info += (QString::fromStdString(player_info) + "\n" + "\n");

        ++iter_2;
    }
    ui->resultsBrowser->setText(all_info);
    ui->resultsBrowser->update();

    //Prints top 5 scores of all time from file, which only holds max 20 lines
    //print_scores_from_file("scores.txt");
}

//Calculates players visual card stack positions/sizes based on player amount
void MainWindow::calculate_stack()
{

    int amount_of_stacks = player_objects_.size();

    //Calculates stack heigth so that is has room to grow upwards when needed
    unsigned int max_stack_height = stack_view_height_ - (4*10);

    //Cards height will be 7/4 * width and vice versa
    stack_width_ = (stack_view_width_ - (amount_of_stacks * 10))
            / amount_of_stacks;

    //Relations for stacks width and height
    float relation_1 = float(7)/float(4);
    float relation_2 = float(4)/float(7);

    stack_height_ = relation_1 * stack_width_;

    //Limits stack width if heigth*7/4 would overflow the max height
    if (stack_height_ > max_stack_height) {
        stack_height_ = max_stack_height;
        stack_width_ = relation_2 * stack_height_;
    }

    //Space which will be between stacks and view edge
    dst_from_x_side_ = (stack_view_width_ - ((amount_of_stacks)*stack_width_))
                        / (amount_players_ +1) ;

    //calculates custom dst from upper edge, if there are > 3 players
    if (amount_of_stacks > 3) {

        dst_from_y_side_ = (stack_view_height_ - stack_height_) / 2;

    }

    //Places each players names on top of his/her card stack
    //Calculates label positions to match card stacks x-coord wise
    for  (unsigned int i=0;i<player_objects_.size();++i) {

        QString name_for_label = QString::fromStdString(player_objects_.
                                                        at(i)->get_name());
        QLabel* new_label = new QLabel(name_for_label, this);
        QFont font = new_label->font();
        font.setBold(true);
        new_label->setFont(font);

        //Calculate starting x-coordinates
        unsigned int x_point = 640 + dst_from_x_side_ +
                (float(stack_width_) / float(3)) +
                (i*(stack_width_ + dst_from_x_side_));

        new_label->setGeometry(x_point, 142, stack_width_, 16);
        new_label->show();

        name_labels_.at(i) = new_label;
    }
}

//Creates labels and shows pictures of cards on them imitating a card stack
void MainWindow::paint_stacks(char letter)
{

    //Finds atm players position in vector and decides the start point from
    //where the rectangle will be painted
    unsigned int player_position = 0;
    for (unsigned int i=0; i < player_objects_.size() ;++i) {

        if (in_turn == player_objects_.at(i)) {
            i = 10;
        } else {
            player_position += 1;
        }
    }

    //Equal space left between horizontal edges of graphicsview and stacks
    unsigned int x_place = (player_position +1) * dst_from_x_side_ +
                            (player_position*stack_width_);

    //First card is at the lowest possible point of the view
    //each new card after first will be placed 4px higher, causes 3d-effect
    unsigned int y_place = 3*10;

    //Filename for picture
    std::string letter_str = std::string(1, letter);
    QString pic_name = "pictures/" + QString::fromStdString(letter_str)
            + ".png";

    if(amount_players_ > 3) {

        //Calculates space left outside height and view edges,
        //then divides it by 4, leaves 3/4 above stack
        y_place = 3*((stack_view_height_ - stack_height_) / 4);
    }

    //Check if this is players first card in stack
    if (in_turn->get_pairs().size() == 1){

       //Makes new label and displays cards image on it
        QLabel* new_label = new QLabel("", this);
        new_label->setGeometry(x_place + stack_x_coords_, y_place +
                               stack_y_coords_, stack_width_, stack_height_);

        QPixmap pic(pic_name);
        QPixmap scaled = pic.scaled(QSize(stack_width_, stack_height_),
                                    Qt::IgnoreAspectRatio,
                                    Qt::SmoothTransformation );
        new_label->setPixmap(scaled);
        new_label->show();

        stack_labels[in_turn->get_name()].push_back(new_label);



    } else {

        //Cheks if atm top cards upper border would overflow
        //the container(graphicsview)
        //If so, starts painting new cards straight on top of the
        //most top/latest card
        unsigned int y_start_coord = y_place-((in_turn->get_pairs().
                                               size() -1) * 5);

        if (y_start_coord <= 0) {

            QLabel* new_label = new QLabel("", this);
            new_label->setGeometry(x_place + stack_x_coords_, 5 + stack_y_coords_,
                                   stack_width_, stack_height_);
            QPixmap pic(pic_name);
            QPixmap scaled = pic.scaled(QSize(stack_width_, stack_height_),
                                        Qt::IgnoreAspectRatio,
                                        Qt::SmoothTransformation );

            new_label->setPixmap(scaled);
            new_label->show();

            stack_labels[in_turn->get_name()].push_back(new_label);

        } else {

            QLabel* new_label = new QLabel("", this);
            new_label->setGeometry(x_place + stack_x_coords_, y_place -
                       ((in_turn->get_pairs().size() -1) * 5) + stack_y_coords_,
                                   stack_width_, stack_height_);
            QPixmap pic(pic_name);
            QPixmap scaled = pic.scaled(QSize(stack_width_, stack_height_),
                                        Qt::IgnoreAspectRatio,
                                        Qt::SmoothTransformation );

            new_label->setPixmap(scaled);
            new_label->show();

            stack_labels[in_turn->get_name()].push_back(new_label);

        }
    }
}

//Adds last rounds scores to file and prints all scores (top20) from file
//Writes only top 20 points to back to file
void MainWindow::print_scores_from_file(std::string file_name)
{

    //Saves points&players names to map
    std::map <std::string, int> scores = { };
    std::ifstream file_object(file_name);

    std::string row;
    int row_index = 0;

    if ( not file_object ) {

        std::string file_error_info = "Error! The file " + file_name +
                " cannot be opened.\n";
        ui->top5playersBrowser->setText(QString::fromStdString(file_error_info));
        return;

    } else {

        //Info in file is stored in format of Player_1;score
        //The number at the end of name will be automatically generated for
        //everyone, when showing results it isnt shown
        while ( getline(file_object, row) ) {

            std::vector <std::string> row_content = { };
            row_content = split_string(row, ';');
            int player_score = std::stoi(row_content.at(1));

            std::string player_name = row_content.at(0);

            scores.insert({player_name, player_score});

            row_index += 1;

        }
        file_object.close();
    }

    //Inserts this games players to map, modifies names
    for (unsigned int i=0;i<player_objects_.size();++i) {
        int number = row_index + (i+1);
        std::string fixed_name = player_objects_.at(i)->get_name() + "_" + std::to_string(number);
        scores.insert({fixed_name, player_objects_.at(i)->get_pairs().size()});
    }

    //This is filled with rows of info, player name and score, descending order
    std::string info = "";

    //Code below sorts the map scores by its values in descending order
    typedef std::function<bool(std::pair<std::string, int>, std::pair<std::string, int>)> Comparator;
    // Defining a lambda function to compare two pairs. It will compare two pairs using second field
    Comparator compFunctor =
            [](std::pair<std::string, int> elem1 ,std::pair<std::string, int> elem2)
            {
                return elem1.second > elem2.second;
            };
    // Declaring a set that will store the pairs using above comparision logic
    std::set<std::pair<std::string, int>, Comparator> setOfWords(
            scores.begin(), scores.end(), compFunctor);
    //Iterate over a set using range base for loop. Store to string info
    for (std::pair<std::string, int> element : setOfWords)
        info += (" - " + element.first.substr(0, element.first.size()-2)  +
                 " : " + std::to_string(element.second)  + "\n");

    ui->top5playersBrowser->setText(QString::fromStdString(info));

    //Now rewrites first 20 value pairs from sorted map of info back to the file
    std::ofstream updated_file_object(file_name);
    std::string new_row;
    int row_amount = 0;
    auto iter_2 = scores.begin();

    while ((iter_2 != scores.end()) and (row_amount < 20)) {

        std::string row_to_save = iter_2->first + ";" +
                std::to_string(iter_2->second) + "\n";
        updated_file_object << row_to_save;

        ++row_amount;
        ++iter_2;

    }
    updated_file_object.close();
}

//Starts the flow of the game
void MainWindow::on_playButton_clicked()
{

    //Checks if input fields are filled correctly and changes few things
    //based on it
    if (check_input()) {

        playing_ = true;
        ui->playButton->setDisabled(true);
        ui->roundInfoBrowser->setText("");

        timer->start(1000);

    } else {
        return;
    }

    //Disables some ui components
    ui->lineEditPlayerNames->setDisabled(true);
    ui->spinBoxCards->setDisabled(true);
    ui->spinBoxPlayers->setDisabled(true);

    //Creates player objects
    std::vector <std::string> names = split_string(ui->lineEditPlayerNames->
                                                    text().toStdString(), ' ');

    for (unsigned int i=0;i<names.size();++i) {
        Player* new_player = new Player(names.at(i));
        player_objects_.push_back(new_player);
        //Inits label vector
        name_labels_.push_back(nullptr);

        //Inits map for players card stack
        std::vector<QLabel*> helper = { };
        stack_labels.insert({names.at(i), helper});

    }

    //Calculates card stack positons/sizes based on player amount
    calculate_stack();

    //Init gameboards data structures with empty cards and empty buttons
    init_empty_board();

    //Init with real cards and buttons
    fill_board();

    //Starts the first round, in turn is first player whose name was entered.
    //After this, turns are changed manually by players clicking
    //<SWITCH TURN> button
    in_turn = player_objects_.at(0);
    std::string name_in_turn = in_turn->get_name();
    ui->turnBrowser->setText(QString::fromStdString(name_in_turn));
    ui->restartButton->setEnabled(true);
}

void MainWindow::on_spinBoxCards_editingFinished()
{
    amount_cards_ = ui->spinBoxCards->value();
}

void MainWindow::on_spinBoxPlayers_editingFinished()
{
    amount_players_ = ui->spinBoxPlayers->value();
}

//When clicked, checks amount of revealed cards and changes turn while
//modifying some variables used in tracking the state of the game
void MainWindow::on_newturnButton_clicked()
{

    ui->newturnButton->setDisabled(true);

    //Checks that two individual cards are revealed
    if (cards_clicked_in_turn < 2) {

        ui->roundInfoBrowser->setText("ERROR: Turn 2 cards!");

    } else if(cards_clicked_in_turn==2){

        ui->roundInfoBrowser->setText("");

        //No pairs found by player
        if (latest_two_cards_.at(0)->get_letter() != latest_two_cards_.at(1)->
                get_letter()) {

            //update two latest card's icon to show backside
            for (unsigned int i=0; i < 2;++i){

                QPixmap img("pictures/card_backside.png");
                QPixmap scaled = img.scaled(QSize(latest_two_buttons_.at(i)
                            ->width(), latest_two_buttons_.at(i)->height()
                            ), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

                latest_two_buttons_.at(i)->setIcon(scaled);
                latest_two_buttons_.at(i)->
                        setIconSize(QSize(latest_two_buttons_.at(i)->width(),
                                          latest_two_buttons_.at(i)->height()));


            }

            //Resets revealed cards and buttons to be hidden and clickable
            latest_two_cards_.at(0)->set_visibility(HIDDEN);
            latest_two_cards_.at(1)->set_visibility(HIDDEN);

            latest_two_buttons_.at(0)->setEnabled(true);
            latest_two_buttons_.at(1)->setEnabled(true);

        //Pairs, deletes two latest cards and hides the buttons
        } else {

            //Adds card to players stack of cards
            paint_stacks(latest_two_cards_.at(0)->get_letter());

            latest_two_buttons_.at(0)->hide();
            latest_two_buttons_.at(1)->hide();

            latest_two_cards_.at(0)->set_visibility(EMPTY);
            latest_two_cards_.at(1)->set_visibility(EMPTY);

        }

        //Decides who is next in turn by searching current players index in
        //vector of players
        unsigned int index = 0;
        for (unsigned int i = 0;i<player_objects_.size();++i) {

            if (player_objects_.at(i) == in_turn) {
                i = player_objects_.size();
            } else {
                index += 1;
            }
        }

        //Checks if player atm in turn is the last one in the vector
        int next_index = 0;
        if (index == player_objects_.size()-1) {
            in_turn = player_objects_.at(0);
        } else {
            next_index = index+1;
            in_turn = player_objects_.at(next_index);
        }

        latest_two_buttons_ = {nullptr, nullptr };
        cards_clicked_in_turn = 0;

        std::string name_in_turn = in_turn->get_name();
        ui->turnBrowser->setText(QString::fromStdString(name_in_turn));

    }

    //Checks if gameboard is empty after current turn
    //and if it is ends game and shows points etc
    if (is_board_empty()) {

        //Announces winner and ends current game
        announce_winner();
        ui->newturnButton->setDisabled(true);
        timer->stop();
    }
}

//Restores everything to default values and deletes pointers/objects
void MainWindow::on_restartButton_clicked()
{
    //Resets mainwindow.hh attributes
    playing_ = false;
    in_turn = nullptr;
    amount_players_ = 2;
    amount_cards_ = 16;
    cards_clicked_in_turn = 0;
    remainder_ = 0;

    //Updates ui components back to defaults
    ui->spinBoxCards->setValue(amount_cards_);
    ui->spinBoxPlayers->setValue(amount_players_);
    ui->lineEditPlayerNames->setText("");
    ui->turnBrowser->setText("");
    ui->roundInfoBrowser->setText("");
    ui->resultsBrowser->setText("");
    ui->top5playersBrowser->setText("");

    //Clears graphicsview scene of stacks
    scene_->clear();
    scene_->update();

    //Enables/disables some components
    ui->lineEditPlayerNames->setEnabled(true);
    ui->spinBoxCards->setEnabled(true);
    ui->spinBoxPlayers->setEnabled(true);
    ui->playButton->setEnabled(true);

    ui->newturnButton->setDisabled(true);
    ui->restartButton->setDisabled(true);

    //Resets timer
    timer->stop();
    minutes_ = 0;
    seconds_ = 0;
    ui->lcdNumberSec->display(seconds_);
    ui->lcdNumberMin->display(minutes_);

    //Resets button sizes
    BUTTON_WIDTH = 0;
    BUTTON_HEIGTH = 0;
    gboard_y_coord_ = 160;
    Y_MARGIN = 7;

    //Reset card stack sizes
    stack_width_ = 0;
    stack_height_ = 0;

    //Deletes button objects from gameboard and clears cards_buttons_
    for (unsigned int i=0;i<cards_buttons_.size();++i) {
        for (unsigned int j=0;j<cards_buttons_.at(i).size();++j) {

            delete cards_buttons_.at(i).at(j);

            delete card_matrix_.at(i).at(j);

        }
    }
    cards_buttons_.clear();
    card_matrix_.clear();

    //Deletes player objects, clears player_objects_
    for (unsigned int luku=0;luku<player_objects_.size();++luku) {
        delete player_objects_.at(luku);
    }
    player_objects_.clear();

    //Deletes name label components
    for (unsigned int i=0;i<name_labels_.size();++i) {
        delete name_labels_.at(i);
    }
    name_labels_.clear();

    //Deletes the card stack labels from each player
    auto iter = stack_labels.begin();
    while (iter != stack_labels.end()) {

        std::vector<QLabel*> to_delete = iter->second;
        for (unsigned int i=0;i<to_delete.size();++i){
            delete to_delete.at(i);
        }

        ++iter;
    }
    stack_labels.clear();

}
