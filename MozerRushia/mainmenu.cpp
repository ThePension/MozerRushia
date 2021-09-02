#include "mainmenu.h"

MainMenu::MainMenu(QObject * parent, QSize * screenSize) : QGraphicsScene(parent)
{
    this->setSceneRect(0, 0, screenSize->width(), screenSize->height());

    // Creating play arcade button
    playArcadeButton = new MenuButton();
    playArcadeButton->setText("Arcade");
    playArcadeButton->setGeometry(QRect(width() / 2 - 200, height() / 2 - 60, 400, 100));
    this->addWidget(playArcadeButton);
    playArcadeButton->show();
    playArcadeButton->setDefault(true);

    // Creation history button
    playHistoryButton = new MenuButton();
    playHistoryButton->setText("Histoire");
    playHistoryButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 60, 400, 100));
    this->addWidget(playHistoryButton);
    playHistoryButton->show();
    playHistoryButton->setDefault(true);

    // Creating Quit button
    quitButton = new MenuButton();
    quitButton->setText("Quitter le jeu");
    quitButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 200, 400, 100));
    this->addWidget(quitButton);
    quitButton->show();

    // Creation score text item
    scoreText = new QGraphicsTextItem("Score : ", nullptr);
    QFont scoreFont("", 50, QFont::Bold);
    scoreText->setDefaultTextColor(Qt::white);
    scoreText->setPos(width() / 2 - 200, 100);
    this->addItem(scoreText);
    scoreText->hide();

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
    this->setBackgroundBrush(QPixmap(":/Fond_Menu.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

MainMenu::~MainMenu()
{
    // Delete buttons
    delete quitButton;
    quitButton = nullptr;
    delete playArcadeButton;
    playArcadeButton = nullptr;
    delete playHistoryButton;
    playHistoryButton = nullptr;
    delete scoreText;
    scoreText = nullptr;
    delete scoreTextDocument;
    scoreTextDocument = nullptr;
}
