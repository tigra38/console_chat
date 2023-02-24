#pragma once
#define SHA1HASHLENGTHBYTES 20
#define SHA1HASHLENGTHUINTS 5
unsigned int* sha1(char* message, unsigned int msize_bytes);