// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2021 The ESBC Core developers
// Copyright (c) 2021 The VKC Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_GUIUTIL_H
#define BITCOIN_QT_GUIUTIL_H

#include "amount.h"
#include "fs.h"

#include <QEvent>
#include <QHeaderView>
#include <QMessageBox>
#include <QObject>
#include <QProgressBar>
#include <QString>
#include <QTableView>
#include <QTableWidget>

#include <QLayout>
#include <QRect>
#include <QStyle>

//#include <boost/filesystem.hpp>

class QValidatedLineEdit;
class SendCoinsRecipient;

QT_BEGIN_NAMESPACE
class QAbstractItemView;
class QDateTime;
class QFont;
class QLineEdit;
class QUrl;
class QWidget;
QT_END_NAMESPACE

/** Utility functions used by the vkcoin Qt UI.
 */
namespace GUIUtil
{
// Create human-readable string from date
QString dateTimeStr(const QDateTime& datetime);
QString dateTimeStr(qint64 nTime);

// Render vkcoin addresses in monospace font
QFont bitcoinAddressFont();

// Set up widgets for address and amounts
void setupAddressWidget(QValidatedLineEdit* widget, QWidget* parent);
void setupAmountWidget(QLineEdit* widget, QWidget* parent);

// Parse "vkcoin:" URI into recipient object, return true on successful parsing
bool parseBitcoinURI(const QUrl& uri, SendCoinsRecipient* out);
bool parseBitcoinURI(QString uri, SendCoinsRecipient* out);
QString formatBitcoinURI(const SendCoinsRecipient& info);

// Returns true if given address+amount meets "dust" definition
bool isDust(const QString& address, const CAmount& amount);

// HTML escaping for rich text controls
QString HtmlEscape(const QString& str, bool fMultiLine = false);
QString HtmlEscape(const std::string& str, bool fMultiLine = false);

/** Copy a field of the currently selected entry of a view to the clipboard. Does nothing if nothing
        is selected.
       @param[in] column  Data column to extract from the model
       @param[in] role    Data role to extract from the model
       @see  TransactionView::copyLabel, TransactionView::copyAmount, TransactionView::copyAddress
     */
void copyEntryData(QAbstractItemView* view, int column, int role = Qt::EditRole);

void setClipboard(const QString& str);

/** Get save filename, mimics QFileDialog::getSaveFileName, except that it appends a default suffix
        when no suffix is provided by the user.

      @param[in] parent  Parent window (or 0)
      @param[in] caption Window caption (or empty, for default)
      @param[in] dir     Starting directory (or empty, to default to documents directory)
      @param[in] filter  Filter specification such as "Comma Separated Files (*.csv)"
      @param[out] selectedSuffixOut  Pointer to return the suffix (file type) that was selected (or 0).
                  Can be useful when choosing the save file format based on suffix.
     */
QString getSaveFileName(QWidget* parent, const QString& caption, const QString& dir, const QString& filter, QString* selectedSuffixOut);

/** Get open filename, convenience wrapper for QFileDialog::getOpenFileName.

      @param[in] parent  Parent window (or 0)
      @param[in] caption Window caption (or empty, for default)
      @param[in] dir     Starting directory (or empty, to default to documents directory)
      @param[in] filter  Filter specification such as "Comma Separated Files (*.csv)"
      @param[out] selectedSuffixOut  Pointer to return the suffix (file type) that was selected (or 0).
                  Can be useful when choosing the save file format based on suffix.
     */
QString getOpenFileName(QWidget* parent, const QString& caption, const QString& dir, const QString& filter, QString* selectedSuffixOut);

/** Get connection type to call object slot in GUI thread with invokeMethod. The call will be blocking.

       @returns If called from the GUI thread, return a Qt::DirectConnection.
                If called from another thread, return a Qt::BlockingQueuedConnection.
    */
Qt::ConnectionType blockingGUIThreadConnection();

// Activate, show and raise the widget
void bringToFront(QWidget* w);

// Determine whether a widget is hidden behind other windows
bool isObscured(QWidget* w);

// Open debug.log
bool openDebugLogfile();

// Open vkcoin.conf
bool openConfigfile();

// Open masternode.conf
bool openMNConfigfile();

// Browse backup folder
bool showBackups();

// Replace invalid default fonts with known good ones
void SubstituteFonts(const QString& language);

/** Qt event filter that intercepts ToolTipChange events, and replaces the tooltip with a rich text
      representation if needed. This assures that Qt can word-wrap long tooltip messages.
      Tooltips longer than the provided size threshold (in characters) are wrapped.
     */
class ToolTipToRichTextFilter : public QObject
{
    Q_OBJECT

public:
    explicit ToolTipToRichTextFilter(int size_threshold, QObject* parent = 0);

protected:
    bool eventFilter(QObject* obj, QEvent* evt);

private:
    int size_threshold;
};

/**
     * Makes a QTableView last column feel as if it was being resized from its left border.
     * Also makes sure the column widths are never larger than the table's viewport.
     * In Qt, all columns are resizable from the right, but it's not intuitive resizing the last column from the right.
     * Usually our second to last columns behave as if stretched, and when on strech mode, columns aren't resizable
     * interactively or programatically.
     *
     * This helper object takes care of this issue.
     *
     */
class TableViewLastColumnResizingFixer : public QObject
{
    Q_OBJECT

public:
    TableViewLastColumnResizingFixer(QTableView* table, int lastColMinimumWidth, int allColsMinimumWidth);
    void stretchColumnWidth(int column);

private:
    QTableView* tableView;
    int lastColumnMinimumWidth;
    int allColumnsMinimumWidth;
    int lastColumnIndex;
    int columnCount;
    int secondToLastColumnIndex;

    void adjustTableColumnsWidth();
    int getAvailableWidthForColumn(int column);
    int getColumnsWidth();
    void connectViewHeadersSignals();
    void disconnectViewHeadersSignals();
    void setViewHeaderResizeMode(int logicalIndex, QHeaderView::ResizeMode resizeMode);
    void resizeColumn(int nColumnIndex, int width);

private slots:
    void on_sectionResized(int logicalIndex, int oldSize, int newSize);
    void on_geometriesChanged();
};

/**
     * Extension to QTableWidgetItem that facilitates proper ordering for "DHMS"
     * strings (primarily used in the masternode's "active" listing).
     */
class DHMSTableWidgetItem : public QTableWidgetItem
{
public:
    DHMSTableWidgetItem(const int64_t seconds);
    virtual bool operator<(QTableWidgetItem const& item) const;

private:
    // Private backing value for DHMS string, used for sorting.
    int64_t value;
};

bool GetStartOnSystemStartup();
bool SetStartOnSystemStartup(bool fAutoStart);

/** Save window size and position */
void saveWindowGeometry(const QString& strSetting, QWidget* parent);
/** Restore window size and position */
void restoreWindowGeometry(const QString& strSetting, const QSize& defaultSizeIn, QWidget* parent);

/** Load global CSS theme */
QString loadStyleSheet();

/** Check whether a theme is not build-in */
bool isExternal(QString theme);

QString getThemeImage(QString image);

/* Convert QString to OS specific boost path through UTF-8 */
fs::path qstringToBoostPath(const QString& path);

/* Convert OS specific boost path to QString through UTF-8 */
QString boostPathToQString(const fs::path& path);

/* Convert seconds into a QString with days, hours, mins, secs */
QString formatDurationStr(int secs);

/* Format CNodeStats.nServices bitmask into a user-readable string */
QString formatServicesStr(quint64 mask);

/* Format a CNodeCombinedStats.dPingTime into a user-readable string or display N/A, if 0*/
QString formatPingTime(double dPingTime);

#if defined(Q_OS_MAC) && QT_VERSION >= 0x050000
// workaround for Qt OSX Bug:
// https://bugreports.qt-project.org/browse/QTBUG-15631
// QProgressBar uses around 10% CPU even when app is in background
class ProgressBar : public QProgressBar
{
    bool event(QEvent* e)
    {
        return (e->type() != QEvent::StyleAnimationUpdate) ? QProgressBar::event(e) : false;
    }
};
#else
typedef QProgressBar ProgressBar;
#endif

} // namespace GUIUtil

#ifndef FLOWLAYOUT_H
#define FLOWLAYOUT_H

class FlowLayout : public QLayout
{
public:
    explicit FlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
    explicit FlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
    ~FlowLayout();

    void addItem(QLayoutItem *item) override;
    int horizontalSpacing() const;
    int verticalSpacing() const;
    Qt::Orientations expandingDirections() const override;
    bool hasHeightForWidth() const override;
    int heightForWidth(int) const override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;
    QSize sizeHint() const override;
    QLayoutItem *takeAt(int index) override;

private:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem *> itemList;
    int m_hSpace;
    int m_vSpace;
};
#endif // FLOWLAYOUT_H

#endif // BITCOIN_QT_GUIUTIL_H
