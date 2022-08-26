#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <QPainter>


class Game: public QWidget
{
public:
    Game(QWidget* parent);

protected:
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void paintEvent(QPaintEvent*) override;

private:
    static const int DOT_WIDTH = 15;
    static const int DOT_HEIGHT = 15;
    static const int FIELD_WIDTH = 15;
    static const int FIELD_HEIGHT = 15;
    static const int DELAY = 150;

    bool _inGame;
    int timer;

    enum Direction {
        left, right, up, down
    };

    Direction _dir;

    QVector<QPoint> _snake;
    QPoint _apple;

    void initGame();
    void draw();
    void move();
    void checkField();
    void setApple();
    void checkApple();
    void gameOver();
};

#endif // GAME_H
