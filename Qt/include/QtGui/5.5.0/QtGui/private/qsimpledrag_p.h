/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSIMPLEDRAG_P_H
#define QSIMPLEDRAG_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qpa/qplatformdrag.h>

#include <QtCore/QObject>

QT_BEGIN_NAMESPACE

#ifndef QT_NO_DRAGANDDROP

class QMouseEvent;
class QWindow;
class QEventLoop;
class QDropData;
class QShapedPixmapWindow;

class Q_GUI_EXPORT QBasicDrag : public QPlatformDrag, public QObject
{
public:
    virtual ~QBasicDrag();

    virtual Qt::DropAction drag(QDrag *drag) Q_DECL_OVERRIDE;

    virtual bool eventFilter(QObject *o, QEvent *e) Q_DECL_OVERRIDE;

protected:
    QBasicDrag();

    virtual void startDrag();
    virtual void cancel();
    virtual void move(const QMouseEvent *me);
    virtual void drop(const QMouseEvent *me);
    virtual void endDrag();

    QShapedPixmapWindow *shapedPixmapWindow() const { return m_drag_icon_window; }
    void updateCursor(Qt::DropAction action);

    bool canDrop() const { return m_can_drop; }
    void setCanDrop(bool c) { m_can_drop = c; }

    Qt::DropAction executedDropAction() const { return m_executed_drop_action; }
    void  setExecutedDropAction(Qt::DropAction da) { m_executed_drop_action = da; }

    QDrag *drag() const { return m_drag; }

private:
    void enableEventFilter();
    void disableEventFilter();
    void restoreCursor();
    void exitDndEventLoop();

    bool m_restoreCursor;
    QEventLoop *m_eventLoop;
    Qt::DropAction m_executed_drop_action;
    bool m_can_drop;
    QDrag *m_drag;
    QShapedPixmapWindow *m_drag_icon_window;
};

class Q_GUI_EXPORT QSimpleDrag : public QBasicDrag
{
public:
    QSimpleDrag();
    virtual QMimeData *platformDropData() Q_DECL_OVERRIDE;

protected:
    virtual void startDrag() Q_DECL_OVERRIDE;
    virtual void cancel() Q_DECL_OVERRIDE;
    virtual void move(const QMouseEvent *me) Q_DECL_OVERRIDE;
    virtual void drop(const QMouseEvent *me) Q_DECL_OVERRIDE;

private:
    QWindow *m_current_window;
};

#endif // QT_NO_DRAGANDDROP

QT_END_NAMESPACE

#endif
