#ifndef READFILE_H
#define READFILE_H

#include <QObject>
#include <QThread>
#include <QFileInfoList>
#include <QDebug>

class getlist : public QThread
{
    Q_OBJECT
public:
    explicit getlist(QObject *parent = nullptr);
    QStringList cachelist;
    QStringList downloadlist;
    QFileInfoList cachefileinfolist;
    QFileInfoList downloadfileinfolist;
    static QFileInfoList fileinfolist;
    Q_PROPERTY(QStringList filelist READ tofilelist NOTIFY setfilelistcompleted);
    QStringList filelist;
    QStringList tofilelist(){
        return filelist;
    }
    Q_INVOKABLE void setfilelist(bool b){
        if (b) fileinfolist=downloadfileinfolist;
        else fileinfolist=cachefileinfolist;
        filelist.clear();
        for (int i=0;i<fileinfolist.count();i++) filelist.append(fileinfolist[i].fileName());
        emit setfilelistcompleted();
    }

    void run();
signals:
    void setfilelistcompleted();
};

class readlyric : public QThread
{
    Q_OBJECT
public:
    explicit readlyric(QObject *parent = nullptr);
    Q_PROPERTY(QString lyric READ tolyric  NOTIFY setlyriccompleted);
    QString lyric;
    QString tolyric(){
        return readlyric::lyric;
    }
    Q_INVOKABLE void setlyric(int index){
        readlyric::index=index;
        readlyric::start();
    }
    void run();
    int index;

signals:
    void setlyriccompleted();
};



#endif // READFILE_H
