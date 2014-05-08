#ifndef FILEINSPECTOR_H
#define FILEINSPECTOR_H

#include <QFileSystemModel>
#include <QTableWidget>

//! FileInspector class
/*!
 * \brief The FileInspector class shows the project directory tree.
 */
class FileInspector : public QTableWidget {

        Q_OBJECT

    public:

        /*!
         * \brief The default constructor.
         * \param root the root path
         * \param parent the parent widget
         */
        explicit FileInspector(QString root, QWidget *parent = 0);

    public:

        void setRoot(QString root);

    private:

        QFileSystemModel _model;

};

#endif // FILEINSPECTOR_H
