#ifndef INFO_H
#define INFO_H
#include <string>

typedef std::string Key;

int getHash(const Key& key);
bool isKeysEquals(const Key& key1, const Key& key2);

#endif // INFO_H
