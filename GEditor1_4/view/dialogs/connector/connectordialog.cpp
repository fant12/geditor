#include "connectordialog.h"

#include <QCheckBox>
#include <QDir>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>

ConnectorDialog::ConnectorDialog(QWidget *parent) : QDialog(parent){

    screenshotLabel = new QLabel;
    screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    screenshotLabel->setAlignment(Qt::AlignCenter);
    screenshotLabel->setMinimumSize(300, 200);

    createOptionsGroupBox();
    createButtonsLayout();

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(screenshotLabel);
    mainLayout->addWidget(optionsGroupBox);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    shootScreen();

    setWindowTitle(tr("Connector"));
    resize(300, 200);
}

void ConnectorDialog::resizeEvent(QResizeEvent *){

    QSize scaledSize = _originalPixmap.size();
    scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);

    if(!screenshotLabel->pixmap() || scaledSize != screenshotLabel->pixmap()->size())
        updateScreenshotLabel();
}

void ConnectorDialog::shootScreen(){

    _originalPixmap = QPixmap();

    QScreen *screen = QGuiApplication::primaryScreen();
    if(screen)
        _originalPixmap = screen->grabWindow(0);
    updateScreenshotLabel();
    show();
}

void ConnectorDialog::createOptionsGroupBox(){

    optionsGroupBox = new QGroupBox(tr("Options"));




    optionsGroupBoxLayout = new QGridLayout;
    optionsGroupBox->setLayout(optionsGroupBoxLayout);
}

void ConnectorDialog::createButtonsLayout(){

    quitScreenshotButton = createButton(tr("Quit"), this, SLOT(close()));

    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(quitScreenshotButton);
}

QPushButton *ConnectorDialog::createButton(const QString &text, QWidget *receiver,
                                      const char *member){
    QPushButton *button = new QPushButton(text);
    button->connect(button, SIGNAL(clicked()), receiver, member);
    return button;
}

void ConnectorDialog::updateScreenshotLabel(){

    screenshotLabel->setPixmap(_originalPixmap.scaled(screenshotLabel->size(),
                                                     Qt::KeepAspectRatio,
                                                     Qt::SmoothTransformation));
}
