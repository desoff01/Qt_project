#ifndef HASH_H
#define HASH_H

#include <QByteArray>
#include <array>


class Hash
{
    static constexpr std::array<int, 3> xorArr {0x10, 0x20, 0x30};
    QByteArray savedLogin;
public:
    QByteArray getLoginHash(std::string login);
    QByteArray getPasswordHash(std::string password);
    QByteArray getSavedLogin();
};

#endif // HASH_H
