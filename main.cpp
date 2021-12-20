#include "mainwindow.hh"
#include <QApplication>

/* Memory card game
 *
 * Description:
 * Simple memory card game to be played by multiple people at the same time
 * Rules: User chooses amount of cards(8-52), players(2-6) and
 * player names(1-15letters). Program checks that all inputs are valid.
 *
 * Game is started by pressing <PLAY!>.
 * In each turn one player has to reveal two individual cards, if pairs are
 * found, moves them to players stack of cards. Turn is passed to next player
 * manually by clicking <SWITCH TURN>. Once all the card pairs have been found,
 * the game ends and results are shown to players. New game can be started by
 * clicking <RESTART>, which restores the game back to its default state.
 *
 * Clickable cards are generated as QPushButtons and a picture is set on
 * the button, picture changes based on the state of the card(Open/Hidden).
 * Cards in players stack of cards are QLabels with picture on them.
 * Pictures in buttons and labels are set with QPixmap.
 * The pictures themselves are made by a friend of mine, they cannot be found
 * on the internet.
 * Most of the UI is made with QtDesigner.
 * Cards and players are depicted using classes.
 * After one game has ended, modifies a .txt file with top 20 scores in it.
 * Game disables/enables some UI components based on the state of the game
 * for preventing mistakes/errors caused by user clicking around etc.
 *
 * Programs writer
 * Name: Eetu Kemppi
 * E-Mail: eetu.kemppi@protonmail.com
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
