#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QObject>
#include <QList>
#include <QPair>
#include <QMap>
#include <QPointF>

class Datum;
class Node;

class SceneSerializer : public QObject
{
    Q_OBJECT
public:
    explicit SceneSerializer(
            QObject* node_root,
            QMap<Node*, QPointF> inspectors=QMap<Node*, QPointF>());

    enum SerializerMode { SERIALIZE_ALL, SERIALIZE_NODES };

    void run(QDataStream* out, SerializerMode mode=SERIALIZE_ALL);
    QByteArray run(SerializerMode mode=SERIALIZE_ALL);

protected:
    void serializeNodes(QDataStream* out, QObject* p);
    void serializeNode(QDataStream* out, Node* node);
    void serializeDatum(QDataStream* out, Datum* datum);
    void serializeConnections(QDataStream* out);

    QObject* node_root;
    QMap<Node*, QPointF> inspectors;

    QList<Datum*> datums;
    QList<QPair<Datum*, Datum*>> connections;

    static int PROTOCOL_VERSION;
};

#endif // SERIALIZER_H
