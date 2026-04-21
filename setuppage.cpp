#include "setuppage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

SetupPage::SetupPage(QWidget *parent) : QWidget(parent), totalPlayers(4), currentBoardIndex(0) {
    setFixedSize(1000, 1000);

    int w = width();
    int h = height();\

    int boardW = w * 0.23;
    int boardH = boardW;
    int boardX = (w - boardW) / 2;
    int boardY = h * 0.16;
    int arrowSize = w * 0.06;

    leftButton = new QPushButton(this);
    leftButton->setFixedSize(arrowSize, arrowSize);
    leftButton->setStyleSheet("border-image: url(:/assets/backward.png);");
    leftButton->move(boardX - arrowSize - 10, boardY + boardH / 2 - arrowSize / 2);

    rightButton = new QPushButton(this);
    rightButton->setFixedSize(arrowSize, arrowSize);
    rightButton->setStyleSheet("border-image: url(:/assets/forward.png);");
    rightButton->move(boardX + boardW + 10, boardY + boardH / 2 - arrowSize / 2);

    boardImage = new QLabel(this);
    boardImage->setFixedSize(boardW, boardH);
    boardImage->setScaledContents(true);
    boardImage->setStyleSheet("border: 5px solid #804113;");
    boardImage->setAlignment(Qt::AlignCenter);
    boardImage->move(boardX, boardY);

    connect(leftButton, &QPushButton::clicked, this, &SetupPage::moveLeft);
    connect(rightButton, &QPushButton::clicked, this, &SetupPage::moveRight);

    boardPaths = {
        ":/assets/board1.png",
        ":/assets/board2.png",
        ":/assets/board3.png"
    };
    updateBoardImage();

    QStringList tokenImages = {
        ":/assets/red.png", ":/assets/blue.png",
        ":/assets/green.png", ":/assets/purple.png"
    };

    int iconSize = w * 0.033;
    int inputW = w * 0.4;
    int inputH = h * 0.053;
    int startX = w * 0.3;
    int startY = h * 0.44;
    int spacingY = h * 0.065;

    for (int i = 0; i < 4; ++i) {
        QLabel *token = new QLabel(this);
        token->setPixmap(QPixmap(tokenImages[i]).scaled(iconSize, iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        token->setFixedSize(iconSize, iconSize);
        token->move(startX - iconSize - 10, startY + i * spacingY + 10);

        QLineEdit *edit = new QLineEdit(this);
        edit->setPlaceholderText(QString("Player %1 Name").arg(i + 1));
        edit->setFixedSize(inputW, inputH);
        edit->move(startX, startY + i * spacingY);
        QString backgroundPath = ":/assets/textbox" + QString::number(i + 1) + ".png";

        int fontSize = h * 0.017;
        edit->setStyleSheet(
            QString("QLineEdit {"
                    "border-image: url(%1);"
                    "border: 2px solid #804113;"
                    "border-radius: 10px;"
                    "font-size: %2px;"
                    "font-weight: bold;"
                    "color: white;"
                    "padding-bottom: 5px;"
                    "}").arg(backgroundPath).arg(fontSize));
        edit->setAlignment(Qt::AlignCenter);

        tokenIcons.append(token);
        nameEdits.append(edit);
    }

    int btnW = w * 0.23;
    int btnH = h * 0.07;
    int btnX = (w - btnW) / 2;
    int btnY = startY + 4 * spacingY + h * 0.01;

    continueButton = new QPushButton(this);
    continueButton->setFixedSize(btnW, btnH);
    continueButton->setStyleSheet(
        "QPushButton { border: none; border-image: url(:/assets/start.png); }"
        "QPushButton:hover { border-image: url(:/assets/start_hover.png); }"
        );
    continueButton->move(btnX, btnY);
    connect(continueButton, &QPushButton::clicked, this, &SetupPage::continueClicked);

    int backBtnW = w * 0.23;
    int backBtnH = h * 0.08;
    backToHomeButton = new QPushButton(this);
    backToHomeButton->setFixedSize(backBtnW, backBtnH);
    backToHomeButton->setStyleSheet(
        "QPushButton { border: none; border-image: url(:/assets/back.png); }"
        "QPushButton:hover { border-image: url(:/assets/back_hover.png); }"
        );
    backToHomeButton->move((w - backBtnW) / 2, btnY + btnH + h * 0.015);

    connect(backToHomeButton, &QPushButton::clicked, this, [=]() {
        emit goToHomePage();
    });
}

void SetupPage::setTotalPlayers(int count) {
    totalPlayers = count;
    for (int i = 0; i < tokenIcons.size(); ++i) {
        if (i < totalPlayers) {
            tokenIcons[i]->show();
            nameEdits[i]->show();
        } else {
            tokenIcons[i]->hide();
            nameEdits[i]->hide();
        }
    }
}

void SetupPage::moveLeft() {
    currentBoardIndex = (currentBoardIndex - 1 + boardPaths.size()) % boardPaths.size();
    updateBoardImage();
}

void SetupPage::moveRight() {
    currentBoardIndex = (currentBoardIndex + 1) % boardPaths.size();
    updateBoardImage();
}

void SetupPage::updateBoardImage() {
    boardImage->setPixmap(QPixmap(boardPaths[currentBoardIndex]).scaled(boardImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void SetupPage::continueClicked() {
    emit setupComplete();
}

QVector<QString> SetupPage::getPlayerNames() const {
    QVector<QString> names;
    for (auto edit : nameEdits) {
        names.append(edit->text());
    }
    return names;
}

QString SetupPage::getSelectedBoardPath() const {
    return boardPaths[currentBoardIndex];
}

int SetupPage::getSelectedBoardIndex() const {
    return currentBoardIndex;
}

void SetupPage::reset() {
    for (int i = 0; i < 4; ++i) {
        nameEdits[i]->clear();
    }
}
