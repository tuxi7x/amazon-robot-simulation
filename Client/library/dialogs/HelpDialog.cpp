#include "HelpDialog.h"

HelpDialog::HelpDialog() : DialogBase()
{
    setWindowTitle("Súgó");

    _mainLayout = new QVBoxLayout();

    QLabel* paragraph1 = new QLabel("<b>Ez a szimulációs program egy raktárban dolgozó szállító robotok útvonalát tervezi meg és hajtja végre a tervet.</b>");
    QLabel* paragraph2 = new QLabel("<b>Pálya szerkesztése:</b> \nSzimuláció indítása előtt a szerkesztőben lehet saját pályát készíteni és azt elmenteni. \nAz egyes elemek lehelyezése Drag and drop módszerrel történik.");
    QLabel* paragraph3 = new QLabel("<b>Szimuláció indítása fájlból betöltve:</b> \nEgy előzőleg elkészített pályát felhasználva tudunk új szimulációt indítani egy szerveren. \nEhhez meg kell adni az IP címet és a portot, illetve a felhasználni kívánt pályát.");
    QLabel* paragraph4 = new QLabel("<b>Csatlakozás futó szimulációhoz:</b> \nCsatlakozási lehetőséget biztosít egy már korábban elindított szimulációhoz. \nEhhez szükség van az IP címre, illetve a Portra.");

    _mainLayout->addWidget(paragraph1);
    _mainLayout->addWidget(paragraph2);
    _mainLayout->addWidget(paragraph3);
    _mainLayout->addWidget(paragraph4);
    _mainLayout->setAlignment(Qt::AlignTop);
    _mainLayout->setSpacing(53);

    QString style = this->styleSheet();

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(5);
    effect->setXOffset(5);
    effect->setYOffset(5);
    effect->setColor(Qt::black);

    paragraph1->setWordWrap(true);
    paragraph2->setWordWrap(true);
    paragraph3->setWordWrap(true);
    paragraph4->setWordWrap(true);


    setStyleSheet("color: white; font-size: 20px;" + style);


    setFixedSize(this->size());
    setLayout(_mainLayout);
}

HelpDialog::~HelpDialog()
{
    for (int i = 0;i < _mainLayout->count() ; i++ ) {
        delete _mainLayout->itemAt(i);
    }
    delete _mainLayout;
}
