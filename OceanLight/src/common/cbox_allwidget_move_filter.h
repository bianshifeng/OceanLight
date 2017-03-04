#ifndef CBOXALLWIDGETMOVEFILTER_H
#define CBOXALLWIDGETMOVEFILTER_H

#include <QObject>
class QWidget;

class CBoxAllWidgetMoveFilter : public QObject
{
    Q_OBJECT
public:
	explicit CBoxAllWidgetMoveFilter(QObject *parent = 0);
	void startMonitoring();

protected:
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    void manageResizePolicy(QWidget* w,int mouseX, int mouseY);
    void manageMovePolicy(QWidget* w, int mouseX, int mouseY);
    void manageMouseCursor(QWidget* w, int mouseX, int mouseY);

};

#endif // CBOXALLWIDGETMOVEFILTER_H
