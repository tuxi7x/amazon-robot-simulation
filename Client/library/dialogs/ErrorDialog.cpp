#include "ErrorDialog.h"


ErrorDialog::ErrorDialog(QString errorMsg)
{
    setFixedSize(300,150);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet(QStringLiteral(
                "QDialog { "
                    "border-radius: 12px; "
                    "border: 1.5px solid; "
                    "color: #003200; "
                    "background-color: #ff6f69; "
                "}"
            ));

    _mainLayout = new QVBoxLayout();

    _errorLabel = new QLabel(errorMsg);
    _errorLabel->setStyleSheet("font-size: 15px;");
    _errorLabel->setWordWrap(true);

    _okButton = new QPushButton("OK");
    _okButton->setFixedHeight(30);
    _okButton->setCursor(QCursor(Qt::PointingHandCursor));
    _okButton->setStyleSheet("border-radius: 10px; background-color: #83c5be;");

    _mainLayout->addWidget(_errorLabel);
    _mainLayout->addWidget(_okButton);

    connect(_okButton,SIGNAL(clicked()),this,SLOT(accept()));

    setLayout(_mainLayout);


}

ErrorDialog::~ErrorDialog()
{
    for (int i = 0;i < _mainLayout->count() ; i++ ) {
        delete _mainLayout->itemAt(i);
    }
    delete _mainLayout;
}

void ErrorDialog::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QStyleOption opt;
    opt.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    p.end();

}
