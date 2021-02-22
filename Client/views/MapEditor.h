#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QRect>

class MapEditor : public QMainWindow
{
    Q_OBJECT
public:
    explicit MapEditor(QWidget *parent = nullptr);
    ~MapEditor();

protected:
    void closeEvent(QCloseEvent *event) override;


private:
    QWidget* _centralWidget;

public slots:
    void openMapEditor(QRect windowPosition);

signals:
    void editorClosed(QRect windowPosition);


};

#endif // MAPEDITOR_H
