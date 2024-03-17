#include "headers/hash.h"
#include <QCryptographicHash>

QByteArray Hash::getLoginHash(std::string login) {
    for (size_t i {0}; i < login.length(); i++) {
        login[i] ^= xorArr[i % 3] + 1;
    }

    QCryptographicHash hash(QCryptographicHash::Sha1);
    QByteArray byteArr(login.c_str());
    hash.addData(byteArr);
    hash.addData("th1s-i5_S01t");

    savedLogin = hash.result();
    return savedLogin;
}

QByteArray Hash::getPasswordHash(std::string password) {
    for (size_t i {0}; i < password.length(); i++) {
        password[i] ^= xorArr[i % 3] + 3;
    }
    QCryptographicHash hash(QCryptographicHash::Sha1);
    QByteArray byteArr(password.c_str());
    byteArr = password.c_str();
    hash.addData(byteArr);
    hash.addData("PT_h4ckDa9s");

    return hash.result();
}

QByteArray Hash::getSavedLogin() {
    return savedLogin;
}
