#include "cbox_allwidget_move_filter.h"
#include "qapplication.h"
#include "qevent.h"
#include "qwidget.h"
#include "windows.h"

#include <QMouseEvent>

const int BORDER_MAIGINS = 5;

CBoxAllWidgetMoveFilter::CBoxAllWidgetMoveFilter(QObject *parent) : QObject(parent)
{
}

bool CBoxAllWidgetMoveFilter::eventFilter(QObject *obj, QEvent *evt)
{
    QWidget *w = (QWidget *)obj;
	if (!w->property("CanMove").toBool() && !w->property("CanResize").toBool())
	{
		return QObject::eventFilter(obj, evt);
	}

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {

			if (w->property("CanMove").toBool())
			{
				if (ReleaseCapture())
					manageMovePolicy(w,event->x(), event->y());
				event->ignore();
			}

			if (w->property("CanResize").toBool())
			{
				if (ReleaseCapture())
					manageResizePolicy(w,event->x(), event->y());
				event->ignore();
			}
			return true;
        }
	}
	else if (event->type() == QEvent::MouseMove) {
		if (w->property("CanResize").toBool()){
			w->setMouseTracking(true);
			manageMouseCursor(w,event->x(), event->y());
			return true;
	    }
    }

    return QObject::eventFilter(obj, evt);
}

void CBoxAllWidgetMoveFilter::startMonitoring()
{
    qApp->installEventFilter(this);
}


void CBoxAllWidgetMoveFilter::manageResizePolicy(QWidget* w, int mouseX, int mouseY)
{
	int wh = w->height();
	int ww = w->width();

	if (mouseX <= BORDER_MAIGINS && mouseX >= 0 && mouseY <= BORDER_MAIGINS && mouseY >= 0)  //左上
	{
		w->setCursor(Qt::SizeFDiagCursor);
		SendMessage(HWND(w->winId()), WM_SYSCOMMAND, SC_SIZE + WMSZ_TOPLEFT, 0);
	}
	else if (mouseX >= ww - BORDER_MAIGINS  && mouseX <= ww &&  mouseY <= BORDER_MAIGINS && mouseY >= 0) //右上
	{
		w->setCursor(Qt::SizeBDiagCursor);
		SendMessage(HWND(w->winId()), WM_SYSCOMMAND, SC_SIZE + WMSZ_TOPRIGHT, 0);
	}
	else if (mouseX > BORDER_MAIGINS && mouseX < ww - BORDER_MAIGINS &&  mouseY <= BORDER_MAIGINS && mouseY >= 0) //上
	{
		w->setCursor(Qt::SizeVerCursor);
		SendMessage(HWND(w->winId()), WM_SYSCOMMAND, SC_SIZE + WMSZ_TOP, 0);
	}
	else if (mouseX <= BORDER_MAIGINS && mouseX >= 0 && mouseY < wh - BORDER_MAIGINS &&  mouseY > BORDER_MAIGINS)//左
	{
		w->setCursor(Qt::SizeHorCursor);
		SendMessage(HWND(w->winId()), WM_SYSCOMMAND, SC_SIZE + WMSZ_LEFT, 0);
	}
	else if (mouseX >= ww - BORDER_MAIGINS && mouseX <= ww && mouseY < wh - BORDER_MAIGINS &&  mouseY > BORDER_MAIGINS)//右
	{
		w->setCursor(Qt::SizeHorCursor);
		SendMessage(HWND(w->winId()), WM_SYSCOMMAND, SC_SIZE + WMSZ_RIGHT, 0);
	}
	else if (mouseX <= BORDER_MAIGINS && mouseX >= 0 && mouseY >= wh - BORDER_MAIGINS && mouseY <= wh)//左下
	{
		w->setCursor(Qt::SizeBDiagCursor);
		SendMessage(HWND(w->winId()), WM_SYSCOMMAND, SC_SIZE + WMSZ_BOTTOMLEFT, 0);
	}
	else if (mouseX >= ww - BORDER_MAIGINS && mouseX <= ww &&  mouseY >= wh - BORDER_MAIGINS && mouseY <= wh)//右下
	{
		w->setCursor(Qt::SizeFDiagCursor);
		SendMessage(HWND(w->winId()), WM_SYSCOMMAND, SC_SIZE + WMSZ_BOTTOMRIGHT, 0);
	}
	else if (mouseX > BORDER_MAIGINS && mouseX < ww - BORDER_MAIGINS &&  mouseY >= wh - BORDER_MAIGINS && mouseY <= wh)//下
	{
		w->setCursor(Qt::SizeVerCursor);
		SendMessage(HWND(w->winId()), WM_SYSCOMMAND, SC_SIZE + WMSZ_BOTTOM, 0);
	}
}

void CBoxAllWidgetMoveFilter::manageMovePolicy(QWidget* w, int mouseX, int mouseY)
{
	int wh = w->height();
	int ww = w->width();

	if (mouseX > BORDER_MAIGINS && mouseX < ww - BORDER_MAIGINS && mouseY > BORDER_MAIGINS && mouseY < wh - BORDER_MAIGINS)
	{
		w->setCursor(Qt::ArrowCursor);
		SendMessage(HWND(w->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
	}
}

void CBoxAllWidgetMoveFilter::manageMouseCursor(QWidget* w, int mouseX, int mouseY)
{
	int wh = w->height();
	int ww = w->width();

	if (mouseX <= BORDER_MAIGINS && mouseX >= 0 && mouseY <= BORDER_MAIGINS && mouseY >= 0)  //左上
	{
		w->setCursor(Qt::SizeFDiagCursor);
	}
	else if (mouseX >= ww - BORDER_MAIGINS  && mouseX <= ww &&  mouseY <= BORDER_MAIGINS && mouseY >= 0) //右上
	{
		w->setCursor(Qt::SizeBDiagCursor);
	}
	else if (mouseX > BORDER_MAIGINS && mouseX < ww - BORDER_MAIGINS &&  mouseY <= BORDER_MAIGINS && mouseY >= 0) //上
	{
		w->setCursor(Qt::SizeVerCursor);
	}
	else if (mouseX <= BORDER_MAIGINS && mouseX >= 0 && mouseY < wh - BORDER_MAIGINS &&  mouseY > BORDER_MAIGINS)//左
	{
		w->setCursor(Qt::SizeHorCursor);
	}
	else if (mouseX >= ww - BORDER_MAIGINS && mouseX <= ww && mouseY < wh - BORDER_MAIGINS &&  mouseY > BORDER_MAIGINS)//右
	{
		w->setCursor(Qt::SizeHorCursor);
	}
	else if (mouseX <= BORDER_MAIGINS && mouseX >= 0 && mouseY >= wh - BORDER_MAIGINS && mouseY <= wh)//左下
	{
		w->setCursor(Qt::SizeBDiagCursor);
	}
	else if (mouseX >= ww - BORDER_MAIGINS && mouseX <= ww &&  mouseY >= wh - BORDER_MAIGINS && mouseY <= wh)//右下
	{
		w->setCursor(Qt::SizeFDiagCursor);
	}
	else if (mouseX > BORDER_MAIGINS && mouseX < ww - BORDER_MAIGINS &&  mouseY >= wh - BORDER_MAIGINS && mouseY <= wh)//下
	{
		w->setCursor(Qt::SizeVerCursor);
	}
	else
	{
		w->setCursor(Qt::ArrowCursor);
	}
}

