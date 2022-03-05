#ifndef QPN532_H
#define QPN532_H

#include <QObject>

extern "C"
{
    #include "pn532.h"
    #include "pn532_rpi.h"
}

class QPN532 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool ready READ isReady NOTIFY readyChanged)

public:
    explicit QPN532(QObject *parent = nullptr);
    bool isReady() const;
    void loop();


private:
    bool _ready = false;
    PN532 _pn532;
    uint8_t _buff[255];
    uint8_t _uid[MIFARE_UID_MAX_LENGTH];
    int32_t _uid_len = 0;
    QByteArray _uidArr;


signals:
    void readyChanged();
    void cardRead(QString uid);
};

#endif // QPN532_H
