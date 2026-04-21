#include "homepage.h"
#include "clickablelabel.h"

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    setFixedSize(1000, 1000);

    int w = width();
    int h = height();

    int logoW = w * 0.37;
    int logoH = h * 0.37;
    logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap(":/assets/logo.png").scaled(275, 275, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setFixedSize(logoW, logoH);
    logoLabel->move((w - logoW) / 2, h * 0.08);
    logoLabel->setAlignment(Qt::AlignCenter);


    int iconSize = w * 0.13;
    int spacing = w * 0.055;
    int iconY = h * 0.43;

    twoPlayersLabel = new ClickableLabel(this);
    threePlayersLabel = new ClickableLabel(this);
    fourPlayersLabel = new ClickableLabel(this);

    twoPlayersLabel->setFixedSize(iconSize, iconSize);
    threePlayersLabel->setFixedSize(iconSize, iconSize);
    fourPlayersLabel->setFixedSize(iconSize, iconSize);

    twoPlayersLabel->setPixmap(QPixmap(":/assets/2playericon.png").scaled(iconSize * 0.9, iconSize * 0.9, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    threePlayersLabel->setPixmap(QPixmap(":/assets/3playericon.png").scaled(iconSize * 0.9, iconSize * 0.9, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    fourPlayersLabel->setPixmap(QPixmap(":/assets/4playericon.png").scaled(iconSize * 0.9, iconSize * 0.9, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    int totalWidth = (3 * iconSize) + (2 * spacing);
    int startX = (w - totalWidth) / 2;

    twoPlayersLabel->move(startX, iconY);
    threePlayersLabel->move(startX + iconSize + spacing, iconY);
    fourPlayersLabel->move(startX + 2 * (iconSize + spacing), iconY);

    twoPlayersLabel->setCursor(Qt::PointingHandCursor);
    threePlayersLabel->setCursor(Qt::PointingHandCursor);
    fourPlayersLabel->setCursor(Qt::PointingHandCursor);

    playerCountLabel = new QLabel("Select Number of Players",this);
    playerCountLabel->setStyleSheet("color: black; font-size: 15px;font-weight:bold");
    playerCountLabel->setFixedWidth(w * 0.6);
    playerCountLabel->setWordWrap(true);
    playerCountLabel->setAlignment(Qt::AlignCenter);
    playerCountLabel->adjustSize();  // Resize to fit text
    playerCountLabel->move((w - playerCountLabel->width()) / 2, iconY + iconSize + h * 0.03);


    selectedPlayerCount = 0;

    auto highlightSelection = [=](ClickableLabel* selected) {
        twoPlayersLabel->setStyleSheet("");
        threePlayersLabel->setStyleSheet("");
        fourPlayersLabel->setStyleSheet("");
        selected->setStyleSheet(
            "border: 3px solid black;"
            "border-radius: 10px;"
            "padding-left:3px"
            );
    };

    connect(twoPlayersLabel, &ClickableLabel::clicked, this, [=]() {
        selectedPlayerCount = 2;
        playerCountLabel->setText("2 Players");
        highlightSelection(twoPlayersLabel);
    });

    connect(threePlayersLabel, &ClickableLabel::clicked, this, [=]() {
        selectedPlayerCount = 3;
        playerCountLabel->setText("3 Players");
        highlightSelection(threePlayersLabel);
    });

    connect(fourPlayersLabel, &ClickableLabel::clicked, this, [=]() {
        selectedPlayerCount = 4;
        playerCountLabel->setText("4 Players");
        highlightSelection(fourPlayersLabel);
    });


    int btnW = w * 0.24;
    int btnH = h * 0.08;

    nextButton = new QPushButton(this);
    nextButton->setFixedSize(btnW, btnH);
    nextButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "border-image: url(:/assets/next.png);"
        "}"
        "QPushButton:hover {"
        "border-image: url(:/assets/next_hover.png);"
        "}"
        );
    nextButton->move((w - btnW) / 2, iconY + iconSize + h * 0.15);
    nextButton->setCursor(Qt::PointingHandCursor);

    int exitW = w * 0.23;
    int exitH = h * 0.075;
    exitButton = new QPushButton(this);
    exitButton->setFixedSize(exitW, exitH);
    exitButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "border-image: url(:/assets/exit.png);"
        "}"
        "QPushButton:hover {"
        "border-image: url(:/assets/exit_hover.png);"
        "}"
        );
    exitButton->move((w - exitW) / 2, iconY + iconSize + h * 0.24);
    exitButton->setCursor(Qt::PointingHandCursor);

}

QPushButton* HomePage::getNextButton() const {
    return nextButton;
}

QPushButton* HomePage::getExitButton() const {
    return exitButton;
}

QLabel* HomePage::getPlayerCountLabel() const {
    return playerCountLabel;
}

int HomePage::getSelectedPlayerCount() const {
    return selectedPlayerCount;
}
