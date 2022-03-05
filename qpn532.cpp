#include "qpn532.h"
#include <QtConcurrent/QtConcurrent>

QPN532::QPN532(QObject *parent) : QObject(parent)
{
    PN532_I2C_Init(&_pn532);
    if (PN532_GetFirmwareVersion(&_pn532, _buff) == PN532_STATUS_OK) {
        printf("Found PN532 with firmware version: %d.%d\r\n", _buff[1], _buff[2]);
        _ready = true;
        Q_EMIT readyChanged();
        PN532_SamConfiguration(&_pn532);
        QtConcurrent::run(this, &QPN532::loop);
    }
    else
    {
        qDebug()<<"Failed to init reader";
    }
}

bool QPN532::isReady() const
{
    return _ready;
}

void QPN532::loop()
{
    while (1)
    {
        // Check if a card is available to read
        _uid_len = PN532_ReadPassiveTarget(&_pn532, _uid, PN532_MIFARE_ISO14443A, 1000);
        if (_uid_len == PN532_STATUS_ERROR) {
            printf(".");
            fflush(stdout);
        } else {

            printf("Found card with UID: ");
            for (uint8_t i = 0; i <_uid_len; i++) {
                _uidArr.append(_uid[i]);
                printf("%02x ", _uid[i]);
            }
            printf("\r\n");
            Q_EMIT cardRead(QString::fromUtf8(_uidArr.toHex()).toUpper());
            _uidArr.clear();
            QThread::sleep(1);
        }
    }
}

