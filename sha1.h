#pragma once
#define SHA1HASHLENGTHBYTES 20
#define SHA1HASHLENGTHUINTS 5

typedef unsigned int uint;

uint* sha1(char* message, uint msize_bytes);