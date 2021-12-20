#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QLabel>

#include "card.hh"
#include "player.hh"
#include <vector>
#include <map>

/* Class: Mainwindow
 * ------------
 * Programs mainwindow, it's attributes and methods
*/

using Game_board_type = std::vector<std::vector<Card>>;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTimer* timer;

    bool check_input();

    void create_players();

    void init_empty_board();

    void fill_board();

    void calculate_factors_and_sizes(unsigned int &rows, unsigned int &columns);

    bool is_board_empty();

    void announce_winner();

    void calculate_stack();

    void paint_stacks(char letter);

    void print_scores_from_file(std::string file_name);

private slots:

    void on_playButton_clicked();

    void on_spinBoxCards_editingFinished();

    void on_spinBoxPlayers_editingFinished();

    void on_restartButton_clicked();

    void update_timer();

    void handle_card_click();

    void on_newturnButton_clicked();

private:
    Ui::MainWindow *ui;

    //Some obvious attributes
    bool playing_ = false;
    Player* in_turn = nullptr;
    int cards_clicked_in_turn = 0;
    int minutes_ = 0;
    int seconds_ = 0;

    //Used as help in creating card/button matrises
    int remainder_ = 0;

    //Area for card stacks
    QGraphicsScene* scene_;
    QGraphicsRectItem* rect_;

    //Minimum values set automatically
    unsigned int amount_players_ = 2;
    unsigned int amount_cards_ = 16;

    //placeholders for two cards opened in ones turn
    std::vector <Card*> latest_two_cards_ = {nullptr, nullptr };

    //placeholder for latest two clicked buttons
    std::vector<QPushButton*> latest_two_buttons_ = {nullptr, nullptr };

    //vector for player objects
    std::vector<Player*> player_objects_ = { };

    //matrix for generated buttons for each card
    std::vector<std::vector<QPushButton*>> cards_buttons_ = { { } };

    //matrix for card objects
    std::vector<std::vector<Card*>> card_matrix_ = { { } };

    //Vector for name labels
    std::vector <QLabel*> name_labels_ = { };

    //Map for card stack labels/images
    std::map <std::string, std::vector<QLabel*> > stack_labels = { };

    //Default values for card button positions, X_MARGIN isnt changed
    const int X_MARGIN = 8;
    int Y_MARGIN = 0;
    unsigned int BUTTON_WIDTH;
    unsigned int BUTTON_HEIGTH;

    //Size and position for geaphicsview in which buttons/cards will be shown
    const int gboard_width_ = 600;
    const int gboard_height_ = 440;
    const int gboard_x_coord_ = 10;
    unsigned int gboard_y_coord_ = 160;

    //Default sizes and positions for card stacks
    unsigned int stack_x_coords_ = 640;
    unsigned int stack_y_coords_ = 160;
    unsigned int stack_view_width_ = 400;
    unsigned int stack_view_height_ = 200;

    //Default rgb values for painting cards to stack
    //Each new card on one stack will be slightly lighter shade of blue
    unsigned int red_ = 50;
    unsigned int green_ = 30;
    unsigned int blue_ = 255;

    //One players card stack sizes and positions
    unsigned int stack_width_;
    unsigned int stack_height_;
    unsigned int dst_from_x_side_;
    unsigned int dst_from_y_side_;


};
#endif // MAINWINDOW_HH
