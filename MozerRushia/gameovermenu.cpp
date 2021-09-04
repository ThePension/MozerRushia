#include "gameovermenu.h"

GameOverMenu::GameOverMenu(QObject * parent, QSize * screenSize) : QGraphicsScene(parent)
{
    this->setSceneRect(0, 0, screenSize->width(), screenSize->height());

    // Creating play arcade button
    replayButton = new MenuButton();
    replayButton->setText("&Rejouer");
    replayButton->setGeometry(QRect(width() / 2 - 200, height() / 2 - 60, 400, 100));
    this->addWidget(replayButton);
    replayButton->show();
    replayButton->setDefault(true);

    // Creating Quit button
    quitButton = new MenuButton();
    quitButton->setText("&Quitter le jeu");
    quitButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 200, 400, 100));
    this->addWidget(quitButton);
    quitButton->show();

    // Creating back to menu button
    backToMenuButton = new MenuButton();
    backToMenuButton->setText("Menu &principal");
    backToMenuButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 60, 400, 100));
    this->addWidget(backToMenuButton);
    backToMenuButton->show();

    // Creation score text item
    scoreText = new QGraphicsTextItem("Score : ", nullptr);
    QFont scoreFont("", 50, QFont::Bold);
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setPos(width() / 2 - 200, 100);
    this->addItem(scoreText);
    scoreText->show();

    // For the outlined text
    scoreTextDocument = new QTextDocument();
    QTextCharFormat charFormat;
    charFormat.setFont(scoreFont);
    QPen outlinePen = QPen(Qt::black, 2, Qt::SolidLine);
    charFormat.setTextOutline(outlinePen);
    QTextCursor cursor = QTextCursor(scoreTextDocument);
    cursor.insertText("Score : ", charFormat);
    scoreText->setDocument(scoreTextDocument);

    // Menu background image
    this->setBackgroundBrush(QPixmap(":/GameOver.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

GameOverMenu::~GameOverMenu()
{
    // Delete buttons
    delete replayButton;
    replayButton = nullptr;
    delete scoreText;
    scoreText = nullptr;
    delete quitButton;
    quitButton = nullptr;
    delete scoreTextDocument;
    scoreTextDocument = nullptr;
}

void GameOverMenu::disconnectReplayButtonConnection(){
    delete replayButton;
    replayButton = nullptr;
    // Creating play arcade button
    replayButton = new MenuButton();
    replayButton->setText("&Rejouer");
    replayButton->setGeometry(QRect(width() / 2 - 200, height() / 2 - 60, 400, 100));
    this->addWidget(replayButton);
    replayButton->show();
}
