#ifndef PDFLISTVIEW_H
#define PDFLISTVIEW_H
#include "stdafx.h"
#include <QListView>
class PdfListView : public QListView
{
    Q_OBJECT
public:
    explicit PdfListView(QWidget *parent = nullptr);

signals:

public slots:

private:

	bool m_isDelta;
    // QAbstractItemView interface
protected slots:
    virtual void verticalScrollbarValueChanged(int value) override;

	void wheelEvent(QWheelEvent *e);
};

#endif // PDFLISTVIEW_H
