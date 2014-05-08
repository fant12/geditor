#ifndef CONNECTORDIALOG_H
#define CONNECTORDIALOG_H

#include <QDialog>
#include <QPixmap>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QGraphicsView;
class QGridLayout;
class QGroupBox;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QVBoxLayout;
QT_END_NAMESPACE

/*

Hier ist noch die falsche Funktion drin, der Connector soll lediglich Aktion und Akteur
miteinander verbinden

Außerdem für Screenshots bestimmter Widgets:
QPixmap p = QPixmap::grabWidget(widget);
p.save("p.png");

oder QWidget::render

*/
class ConnectorDialog : public QDialog {

        Q_OBJECT

    public:
        explicit ConnectorDialog(QWidget *parent = 0);

    private slots:

        void shootScreen();

    protected:

        void resizeEvent(QResizeEvent *event);

    private:
        void createOptionsGroupBox();
        void createButtonsLayout();
        QPushButton *createButton(const QString &text, QWidget *receiver, const char *member);
        void updateScreenshotLabel();

        QPixmap _originalPixmap;

        QLabel *screenshotLabel;
        QGroupBox *optionsGroupBox;
        QPushButton *quitScreenshotButton;

        QVBoxLayout *mainLayout;
        QGridLayout *optionsGroupBoxLayout;
        QHBoxLayout *buttonsLayout;

        QGraphicsView *_view;
        QGraphicsScene *_scene;

};

#endif // CONNECTOR_H
