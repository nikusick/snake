#include "game.h"

#include <QDebug>
#include <QTime>
#include <QMessageBox>
Game::Game(QWidget* parent) {

    resize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT);
    setWindowTitle("SNAKE");
    initGame();
}

void Game::timerEvent(QTimerEvent* event) {
    if (_inGame) {
        checkApple();
        move();
        checkField();
    }
    repaint();
}

void Game::keyPressEvent(QKeyEvent* event) {
    int key = event->key();
    if (key == Qt::Key_Left && _dir != right) {
        _dir = left;
    }
    if (key == Qt::Key_Right && _dir != left) {
        _dir = right;
    }
    if (key == Qt::Key_Up && _dir != down) {
        _dir = up;
    }
    if (key == Qt::Key_Down && _dir != up) {
        _dir = down;
    }
}

void Game::paintEvent(QPaintEvent* event) {

    draw();
}

void Game::initGame() {
    _inGame = true;
    setApple();
    timer = startTimer(DELAY);
    _dir = right;
    _snake.resize(3);

    for (int i = 0; i < _snake.size(); ++i) {
        _snake[i].setX(_snake.size() - i - 1);
        _snake[i].setY(0);
    }
}

void Game::draw() {
    QPainter qp(this);
    if (_inGame) {
        qp.setBrush(Qt::red);
        qp.drawEllipse(_apple.x() * DOT_WIDTH,
                       _apple.y() * DOT_HEIGHT,
                       DOT_WIDTH, DOT_HEIGHT);
        for (int i = 0; i < _snake.size(); ++i) {
            if (i == 0) {
                qp.setBrush(Qt::black);
            }
            else {
                qp.setBrush(Qt::green);
            }
            qp.drawEllipse(_snake[i].x() * DOT_WIDTH,
                           _snake[i].y() * DOT_HEIGHT,
                           DOT_WIDTH, DOT_HEIGHT);
        }
    }
    else {
        gameOver();
    }
}

void Game::move() {
    for (int i = _snake.size() - 1; i > 0; --i) {
        _snake[i] = _snake[i - 1];
    }
    switch (_dir) {
        case left: { _snake[0].rx() -= 1; break; }
        case right: { _snake[0].rx() += 1; break; }
        case up: { _snake[0].ry() -= 1; break; }
        case down: { _snake[0].ry() += 1; break; }
    }
}

void Game::checkField() {
    if (_snake.count(_snake.front()) != 1) {
        _inGame = false;
    }
    if (_snake.front().x() >= FIELD_WIDTH ||
            _snake.front().y() >= FIELD_HEIGHT ||
            _snake.front().x() < 0 ||
            _snake.front().y() < 0) {
        _inGame = false;
    }
    if (!_inGame) {
        killTimer(timer);
    }
}

void Game::setApple() {
    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    _apple.rx() = rand() % DOT_WIDTH;
    _apple.ry() = rand() % DOT_HEIGHT;
}

void Game::checkApple() {
    if (_apple == _snake.front()) {
        _snake.push_back(QPoint(0, 0));
        setApple();
    }
}

void Game::gameOver() {
    QMessageBox msg;
    msg.setText("Game Over!");
    msg.exec();

    initGame();
}
