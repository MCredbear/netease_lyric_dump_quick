#include "readfile.h"
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonArray>
#include <QDebug>

QFileInfoList getlist::fileinfolist;

getlist::getlist(QObject *parent)
{

}

readlyric::readlyric(QObject *parent)
{

}

void getlist::run()
{
    QDir cache("/storage/emulated/0/netease/cloudmusic/Cache/Lyric/");
    QDir download("/storage/emulated/0/netease/cloudmusic/Download/Lyric/");
    cache.setFilter(QDir::Files);
    cache.setSorting(QDir::Time);
    download.setFilter(QDir::Files);
    download.setSorting(QDir::Time);
    cachefileinfolist=cache.entryInfoList();
    downloadfileinfolist=download.entryInfoList();


}

void readlyric::run(){
    QFile file(getlist::fileinfolist[readlyric::index].filePath());

    file.open(QIODevice::ReadOnly);
    QByteArray buff=file.readAll();
    file.close();
    QJsonParseError parseError;
    QJsonDocument json=QJsonDocument::fromJson(buff.data(),&parseError);
    readlyric::lyric=QJsonDocument::fromJson(buff.data(),&parseError).object().value("lyric").toString()+"\n";
    readlyric::lyric+=QJsonDocument::fromJson(buff.data(),&parseError).object().value("romeLrc").toString()+"\n";
    readlyric::lyric+=QJsonDocument::fromJson(buff.data(),&parseError).object().value("translateLyric").toString()+"\n";
    if (readlyric::lyric=="\n\n\n") readlyric::lyric="无歌词";
    emit readlyric::setlyriccompleted();


}

