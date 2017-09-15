#ifndef MUSICSONGSEARCHONLINEWIDGET_H
#define MUSICSONGSEARCHONLINEWIDGET_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicquerytablewidget.h"
#include "musicdownloadquerythreadabstract.h"

#define AUDITION_PLAY MStatic_cast(int, Qt::yellow)
#define AUDITION_STOP MStatic_cast(int, Qt::transparent)

/*! @brief The class of the data download item.
 * @author Greedysky <greedysky@163.com>
 */
typedef struct MUSIC_WIDGET_EXPORT MusicDownloadData
{
    QString m_songName;
    QString m_time;
    QString m_format;

    void clear()
    {
        m_songName.clear();
        m_time.clear();
        m_format.clear();
    }

    bool isValid() const
    {
        return !(m_songName.isEmpty() && m_time.isEmpty() && m_format.isEmpty());
    }

}MusicDownloadData;
MUSIC_DECLARE_LISTS(MusicDownloadData)

class QLabel;
class QPushButton;
class MusicCoreMPlayer;

/*! @brief The class of the song search online table widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicSongSearchOnlineTableWidget : public MusicQueryItemTableWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicSongSearchOnlineTableWidget(QWidget *parent = 0);

    virtual ~MusicSongSearchOnlineTableWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Set wheather query all quality of records.
     */
    inline void setQueryAllRecords(bool state) { m_queryAllRecords = state;}
    /*!
     * Start search query by text.
     */
    virtual void startSearchQuery(const QString &text) override;
    /*!
     * Data download to local file.
     */
    virtual void musicDownloadLocal(int row) override;

    /*!
     * Stop current audtion.
     */
    void auditionStop();
    /*!
     * Start play audition to music by row.
     */
    void auditionToMusic(int row);
    /*!
     * Stop play audition to music by row.
     */
    void auditionToMusicStop(int row);
    /*!
     * Set search data quality.
     */
    void setSearchQuality(const QString &quality);

    /*!
     * Resize window bound by widgte resize called.
     */
    void resizeWindow();

Q_SIGNALS:
    /*!
     * Check current audtion is playing or not.
     */
    void auditionIsPlaying(bool play);

public Q_SLOTS:
    /*!
     * Table widget list cell enter.
     */
    virtual void listCellEntered(int row, int column) override;
    /*!
     * Table widget list cell click.
     */
    virtual void listCellClicked(int row, int column) override;
    /*!
     * Clear All Items.
     */
    virtual void clearAllItems() override;
    /*!
     * Create searched items.
     */
    virtual void createSearchedItems(const MusicSearchedItem &songItem) override;
    /*!
     * Item has double clicked.
     */
    virtual void itemDoubleClicked(int row, int column) override;
    /*!
     * Left context menu action group click by action.
     */
    virtual void actionGroupClick(QAction *action) override;
    /*!
     * Search data dwonload finished.
     */
    void searchDataDwonloadFinished();
    /*!
     * Open music song download widget.
     */
    void musicSongDownload(int row);

protected:
    /*!
     * Override the widget event.
     */
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    /*!
     * Add search music to play list by index.
     */
    void addSearchMusicToPlayList(int row);

    bool m_queryAllRecords;
    int m_previousAuditionRow;
    MusicCoreMPlayer *m_audition;
    MusicDownloadData m_downloadData;

};



/*! @brief The class of the song search online widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicSongSearchOnlineWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicSongSearchOnlineWidget(QWidget *parent = 0);

    ~MusicSongSearchOnlineWidget();

    /*!
    * Get class object name.
    */
    static QString getClassName();
    /*!
     * Start search query by text.
     */
    void startSearchQuery(const QString &name);
    /*!
     * Start search query by text.
     */
    void startSearchQuery(const QString &name, bool all);
    /*!
     * Research query by quality it changed.
     */
    void researchQueryByQuality(const QString &name, const QString &quality);
    /*!
     * Resize window bound by widgte resize called.
     */
    void resizeWindow();
    /*!
     * Stop current audtion.
     */
    void auditionStop();

public Q_SLOTS:
    /*!
     * Set diff button clicked by index.
     */
    void buttonClicked(int index);
    /*!
     * Check current audtion is playing or not.
     */
    void auditionIsPlaying(bool play);

protected:
    /*!
     * Override the widget event.
     */
    virtual void resizeEvent(QResizeEvent *event) override;
    /*!
     * Create tool widget.
     */
    void createToolWidget(QWidget *widget);
    /*!
     * Set resize labelt ext.
     */
    void setResizeLabelText(const QString &name);

    QLabel *m_textLabel;
    QPushButton *m_playButton;
    QList<QLabel*> m_resizeLabels;
    MusicSongSearchOnlineTableWidget *m_searchTableWidget;

};

#endif // MUSICSONGSEARCHONLINEWIDGET_H
