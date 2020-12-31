#include "pdflistview.h"
#include <QScrollBar>
#include "pdflistmodel.h"
PdfListView::PdfListView(QWidget *parent) : QListView(parent)
{
    setSizeAdjustPolicy(AdjustToContents);
    setVerticalScrollMode(ScrollPerPixel);
    verticalScrollBar()->setSingleStep(20);
    setStyleSheet("background-color:gray;");
    verticalScrollBar()->setStyleSheet("QScrollBar:vertical{background:rgba(0, 0, 0, 0);}");
    setSpacing(5);
	m_isDelta = false;
}

void PdfListView::wheelEvent(QWheelEvent *e)
{
	if (e->delta() > 0)
	{
		m_isDelta = false;
	}
	else
	{
		m_isDelta = true;
	}
	QListView::wheelEvent(e);
}

void PdfListView::verticalScrollbarValueChanged(int value)
{
    QListView::verticalScrollbarValueChanged(value);
    int maxVal = verticalScrollBar()->maximum();
	int min = verticalScrollBar()->minimum();
    if(value >= maxVal && m_isDelta)
    {
        if(PdfListModel *m = dynamic_cast<PdfListModel*>(this->model()))
        {
            if(m->beginPage() + currentIndex().row() == m->pageCount())
                return;
            int next = m->nextBeginPage();
            if(next > m->beginPage())
            {
                m->resetBeginPage(next);
                setCurrentIndex(m->index(0));
            }
            else
            {
                return;
            }
        }
    }
	else if (value == 0 && !m_isDelta)
	{
		PdfListModel *m = dynamic_cast<PdfListModel*>(this->model());
		int pre = m->preBeginPage();
		if (pre < 0)
		{
			return;
		}
		m->resetBeginPage(pre);
		verticalScrollBar()->setValue(maxVal);
	}

	
}
