#include "menubutton.h"

MenuButton::MenuButton(QWidget * parent) : QPushButton(parent)
{
    setStyleSheet( "QPushButton {"
                        "border: 2px solid black;"
                        "font-size: 30px;"
                        "font-weight: bold;"
                        "border-radius: 5px;"
                        "color: white;"
                        "background-color: rgba(1, 0, 0, 65%);"
                    "}"
                    "QPushButton:hover {"
                        "background-color: rgba(1, 0, 0, 90%);"
                    "}");
}
