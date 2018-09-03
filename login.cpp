#include "login.h"
#include "QLabel"
#include "QLineEdit"
#include "QFont"
#include "QPushButton"
#include "switchbutton.h"
/*
 * login widget
 * if not registered, register
 * if login failed, prompt
 * if login succeed, menu
 * already modified:
 * window titile
*/
Login::Login(QWidget *parent) : BaseWidget(parent)
{
    setWindowTitle("Login");   
    functionName->setText("Login");
    QFont labelFont;
    labelFont.setFamily("Microsoft YaHei");
    labelFont.setPixelSize(20);
    QFont lineEditFont = labelFont;
    QFont buttonFont = labelFont;
    QLabel *userName = new QLabel("UserName", this);
    userName->setGeometry(100, 400, 150, 60);
    userName->setFont(labelFont);
    QLineEdit *getUserName = new QLineEdit(this);
    getUserName->setGeometry(userName->x() + userName->width(), userName->y(), 250, userName->height());
    getUserName->setFont(lineEditFont);
    QLabel *password = new QLabel("Password", this);
    password->setGeometry(userName->x(), userName->y() + 2 * userName->height(), userName->width(), userName->height());
    password->setFont(labelFont);
    QLineEdit *getPassword = new QLineEdit(this);
    getPassword->setGeometry(password->x() + password->width(), password->y(), 250, password->height());
    getPassword->setEchoMode(QLineEdit::Password);
    getPassword->setFont(lineEditFont);
    QPushButton *registerButton = new QPushButton("Register",this);
    registerButton->setGeometry(userName->x(), password->y() + 2 * password->height(), 150, 60);
    registerButton->setFont(buttonFont);
    QPushButton *loginButton = new QPushButton("Login", this);
    loginButton->setGeometry(350, registerButton->y(), 150,60);
    loginButton->setFont(buttonFont);
}

Login::~Login()
{

}
