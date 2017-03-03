#include "picture.h"

Picture::Picture(const QString &filePath):Picture(QUrl::fromLocalFile(filePath))
{

}
Picture::Picture(const QUrl &fileUrl):mId(-1),mAlbumId(-1),mFileUrl(fileUrl)
{

}
QUrl Picture::fileUrl()const
{
    return mFileUrl;
}
void Picture::setFileUrl(const QUrl &fileUrl)
{
    mFileUrl = fileUrl;
}
