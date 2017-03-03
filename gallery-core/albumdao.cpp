#include "albumdao.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "databasemanager.h"
#include <QVariant>
using namespace std;
AlbumDao::AlbumDao(QSqlDatabase &database):mDatabase(database)
{

}
void AlbumDao::init() const
{
    if (!mDatabase.tables().contains("albums"))
    {
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE albums(id INTEGER PRIMARY KEY AUTOINCREMENT ,name TEXT)");
    }
}
void AlbumDao::addAlbum(Album &album) const
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO albums(name) VALUES(:name)");
    query.bindValue(":name",album.name());
    query.exec();
    album.setId(query.lastInsertId().toInt());
}
void AlbumDao::updateAlbum(const Album &album) const
{
    QSqlQuery query(mDatabase);
    query.prepare("update albums set name=:name where id=:id");
    query.bindValue(":id",album.id());
    query.bindValue(":name",album.name());
    query.exec();

}
void AlbumDao::removeAlbum(int id) const
{
    QSqlQuery query(mDatabase);
    query.prepare("delete from albums where id=:id");
    query.bindValue(":id",id);
    query.exec();

}
std::unique_ptr<std::vector<std::unique_ptr<Album>>> AlbumDao::albums() const
{
    QSqlQuery query("SELECT * FROM albums",mDatabase);
    unique_ptr<vector<unique_ptr<Album>>> list(new vector<unique_ptr<Album>>);

    while (query.next()) {

        unique_ptr<Album> album(new Album());
        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());
        list->push_back(move(album));
    }
    return move(list);
}
