#include "info.h"

int getHash(const valueType& key)
{
    return key.length();
}

bool isKeysEquals(const valueType& key1, const valueType& key2)
{
    return (key1 == key2);
}
