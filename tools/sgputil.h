#ifndef _SGPUTIL_H_
#define _SGPUTIL_H_

#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
//#include <lzma.h>
//#include <bzlib.h>

#ifdef TARGET_IS_RETARDED
#include <windows.h>
#endif

void sgputilError(const char *msg);
int zDecompress(void *in, void **out, unsigned int inlen, unsigned int outlen);
void *zCompress(void *indata, unsigned int len, unsigned int *outlen);
void *xzCompress(void *indata, unsigned int len, unsigned int *outlen);
unsigned int xzDecompress(void *indata, void **out, unsigned int len, unsigned int outlen);
void *bz2Compress(void *indata, unsigned int len, unsigned int *outlen);
unsigned int asdfDecompress(void *indata, void **out, unsigned int inlen, unsigned int outlen);
int isPow2(unsigned int var);
unsigned int findClosestPow2(unsigned int var);
unsigned int getPowOf2(unsigned int var);
unsigned int getLowestBit(unsigned int var);
int sgputilMemCmp(const char *arg1, const char *arg2, int len);
unsigned int *sgputilCompress4(unsigned int *data, unsigned int len, unsigned int *compl);
unsigned int *sgputilDecompress4(unsigned int *data, unsigned int len, unsigned int *ulen);
void *snsbbfzOpen(const char *fname);
unsigned int snsbbfzGetFilesInFile(void *handle);
unsigned int snsbbfzGetHeaderLen(void *handle);
void *snsbbfzGetHeaderData(void *handle, unsigned int n);
void *snsbbfzGetData(void *handle, unsigned int n, unsigned int *len);
void *snsbbfzClose(void *handle);
void *snsbbfzPrepareNew();
int snsbbfzAddFile(void *handle, const char *fname, const char *headdata);
int snsbbfzWriteOut(void *handle, const char *fname);
void spgutilMakeNativePath(char *path);
unsigned int spglutilMakeNativeEndianess(unsigned int i);


#endif
