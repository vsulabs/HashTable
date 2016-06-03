#ifndef INFO_H
#define INFO_H
#include <string>

typedef std::string valueType;

int getHash(const valueType& key);
bool isKeysEquals(const valueType& key1, const valueType& key2);

#endif // INFO_H
