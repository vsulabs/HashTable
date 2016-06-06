#include "info.h"

int getHash(const Key& key)
{
    return key.length();
}

bool isKeysEquals(const Key& key1, const Key& key2)
{
    return (key1 == key2);
}
