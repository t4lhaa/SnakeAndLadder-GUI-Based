#include "winpop.h"

WinPop::WinPop(QWidget *parent) : QWidget(parent) {
    setFixedSize(1000,1000);

    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("background-color: rgba(0, 0, 0, 150);");
    move(0, 0);


    int w = width();
    int h = height();

    double pw = w * 0.533;
    double ph = h * 0.333;

    popupBox = new QWidget(this);
    popupBox->setFixedSize(pw , ph);
    popupBox->setStyleSheet("border: 5px solid #804113;background-color: #FFFDD0; border-radius: 20px;");

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(15);
    shadow->setOffset(0);
    popupBox->setGraphicsEffect(shadow);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(popupBox, 0, Qt::AlignCenter);

    QVBoxLayout *boxLayout = new QVBoxLayout(popupBox);
    boxLayout->setAlignment(Qt::AlignCenter);

    int fontSize = h * 0.026;
    winnerLabel = new QLabel("PLAYER 1 WINSSSS!!!!!", popupBox);
    winnerLabel->setStyleSheet(QString("border: none; font-size: %1px; font-weight: bold; color: black;").arg(fontSize));
    winnerLabel->setAlignment(Qt::AlignCenter);
    boxLayout->addWidget(winnerLabel);

    int exitSize = w * 0.0733;
    exitButton = new QPushButton(popupBox);
    exitButton->setFixedSize(exitSize, exitSize);
    exitButton->setStyleSheet(
        "QPushButton {"
        "border: none;"
        "border-image: url(:/assets/exitButton.png);"
        "}"
        );
    exitButton->setCursor(Qt::PointingHandCursor);

    connect(exitButton, &QPushButton::clicked, this, &WinPop::exitToHome);

    int spacing = w * 0.0533;
    boxLayout->addSpacing(spacing);
    boxLayout->addWidget(exitButton, 0, Qt::AlignCenter);
}

void WinPop::setWinnerName(const QString &name) {
    winnerLabel->setText(name + " WINSSSS!!!!!");
}
