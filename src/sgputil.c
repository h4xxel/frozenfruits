#include "sgputil.h"

#define MAGIC_1         0x0DF0EFBE
#define MAGIC_2         0x22FF005A

#define COMPRESSION_GZIP 0x1
#define	COMPRESSION_LZMA 0x2
#define	COMPRESSION_BZIP 0x4
#define COMPRESSION_NEW	0x80000000

typedef struct {
        unsigned int    magic_1;
        unsigned int    magic_2;
        unsigned int    headersz;
        unsigned int    datapos;
} SNSBBFZ_MH;

typedef struct {
        unsigned int    dataHeaders;
        unsigned int    headerpadding;
} SNSBBFZ_HEADINFO;

typedef struct {
        unsigned int    zlen;
        unsigned int    len;
        unsigned int    dataindex;
} SNSBBFZ_HEADER;


typedef struct {
        FILE            *fp;
        FILE            *head;
        unsigned int    len;
        unsigned int    headlen;
} SNSBBFZ_SFILES;


typedef struct {
        unsigned int    dataheaders;
        FILE            *fp;
        unsigned int    headerpadding;
        unsigned int    datapos;
        void            *headerdata;
        SNSBBFZ_SFILES  *sfiles;
} SNSBBFZ_FILE;


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
void sgputilError(const char *msg) {
	fprintf(stderr, msg);
	
	return;
}

#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif

/*
void *xzCompress(void *indata, unsigned int len, unsigned int *outlen) {
	void *zdata;
	lzma_stream stream = LZMA_STREAM_INIT;
	unsigned int settings = 0x9 | LZMA_PRESET_EXTREME;
	lzma_check check = LZMA_CHECK_CRC64;
	lzma_ret ret;
	
	ret = lzma_easy_encoder(&stream, settings, check);
	
	if ((zdata = malloc(len)) == NULL) {
		fprintf(stderr, "SGPUTIL: Error: malloc has failed us\n");
		return NULL;
	}
	
	stream.next_in = (Bytef *) indata;
	stream.avail_in = len;
	stream.next_out = (Bytef *) zdata;
	stream.avail_out = len;
	
	ret = lzma_code(&stream, LZMA_RUN);
	ret = lzma_code(&stream, LZMA_FINISH);
	if (stream.avail_out == 0) {
		free(zdata);
		zdata = NULL;
		*outlen = 0;
		*outlen = ~*outlen;
	} else
		*outlen = stream.total_out;
	
	lzma_end(&stream);
	
	return zdata;
}


unsigned int xzDecompress(void *indata, void **out, unsigned int inlen, unsigned int outlen) {
	lzma_stream stream = LZMA_STREAM_INIT;
	const uint32_t flags = LZMA_TELL_UNSUPPORTED_CHECK | LZMA_CONCATENATED;
	const uint64_t memory_limit = UINT64_MAX;
	lzma_ret ret;
	
	if ((*out = malloc(outlen)) == NULL) {
		fprintf(stderr, "SGPUTIL: Error: malloc() has failed us\n");
		return 0;
	}
	
	ret = lzma_stream_decoder(&stream, memory_limit, flags);
	
	stream.next_in = (Bytef *) indata;
	stream.avail_in = inlen;
	stream.next_out = (Bytef *) *out;
	stream.avail_out = outlen;
	
	ret = lzma_code(&stream, LZMA_RUN);
	lzma_end(&stream);
	
	return outlen;
}


void *bz2Compress(void *indata, unsigned int len, unsigned int *outlen) {
	void *zdata;
	bz_stream stream;
	
	if ((zdata = malloc(len)) == NULL) {
		fprintf(stderr, "SGPUTIL: Error: malloc() has failed us\n");
		return NULL;
	}
	
	stream.bzalloc = NULL;
	stream.bzfree = NULL;
	stream.opaque  = NULL;
	BZ2_bzCompressInit(&stream, 9, 0, 30);
	
	stream.next_in = (char *) indata;
	stream.avail_in = len;
	stream.next_out = (char *) zdata;
	stream.avail_out = len;
	
	BZ2_bzCompress(&stream, BZ_RUN);
	BZ2_bzCompress(&stream, BZ_FINISH);
	
	if (stream.avail_out == 0) {
		*outlen = 0;
		*outlen = ~*outlen;
		free(zdata);
		zdata = NULL;
	} else
		*outlen = stream.total_out_lo32;
	
	BZ2_bzCompressEnd(&stream);
	
	return zdata;
}


unsigned int asdfDecompress(void *indata, void **out, unsigned int inlen, unsigned int outlen) {
	bz_stream stream;
	
	if ((*out = malloc(outlen)) == NULL) {
		fprintf(stderr, "SGPUTIL: Error: malloc() has failed us\n");
		return -1;
	}
	
	BZ2_bzDecompressInit(&stream, 0, 0);
	stream.next_in = (char *) indata;
	stream.avail_in = inlen;
	stream.next_out = (char *) *out;
	stream.avail_out = outlen;
	BZ2_bzDecompress(&stream);
	BZ2_bzDecompressEnd(&stream);
	
	return outlen;
}
*/
void *zCompress(void *indata, unsigned int len, unsigned int *outlen) {
	void *zdata;
	z_stream zstruct;
	
	if ((zdata = malloc(len)) == NULL) {
		fprintf(stderr, "SGPUTIL: Error: malloc() failed\n");
		return NULL;
	}
	
	zstruct.zalloc = Z_NULL;
	zstruct.zfree = Z_NULL;
	zstruct.opaque = Z_NULL;
	
	if (deflateInit(&zstruct, 9) != Z_OK) {
		fprintf(stderr, "SGPUTIL: Error: deflateInit() failed\n");
                return NULL;
        }
	
	zstruct.avail_in = len;
	zstruct.next_in = (Bytef *) indata;
	zstruct.avail_out = len;
	zstruct.next_out = (Bytef *) zdata;
	
	if (deflate(&zstruct, 1) == Z_STREAM_ERROR) {
		fprintf(stderr, "SGPUTIL: Error: deflate() failed\n");
		return NULL;
	}
	
	*outlen = len - zstruct.avail_out;
	
	zdata = realloc(zdata, len);
	
	return zdata;
}



#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
int zDecompress(void *in, void **out, unsigned int inlen, unsigned int outlen) {
	z_stream zstream;
	
	if (in == NULL || out == NULL)
		return -1;
	if (inlen == 0 || outlen == 0)
		return -1;
	
	zstream.zalloc = NULL;
	zstream.zfree = NULL;
	zstream.opaque = NULL;
	zstream.avail_in = 0;
	zstream.next_in = NULL;
	
	if ((*out = malloc(outlen)) == NULL)
		return -1;
	
	if (inflateInit(&zstream) != Z_OK)
		return -1;
	
	zstream.avail_in = inlen;
	zstream.next_in = (Bytef *) in;
	zstream.avail_out = outlen;
	zstream.next_out = (Bytef *) *out;
	
	inflate(&zstream, Z_NO_FLUSH);
	inflateEnd(&zstream);
	
	return outlen;
}

#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
int isPow2(unsigned int var) {
	unsigned int temp;
	
	for (temp = 1; var ^ temp && var > temp; temp <<= 1);
	
	if (var == temp)
		return 0;

	return -1;
}

#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
unsigned int findClosestPow2(unsigned int var) {
	int i;
	
	for (i = 1; i < var; i <<= 1);
	
	return i;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
unsigned int getPowOf2(unsigned int var) {
	int i;
	
	for (i = 0; var > 0; var >>= 1, i++);
	
	return i;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
unsigned int getLowestBit(unsigned int var) {
	int i, j;
	
	if (var == 0)
		return 2353453;
	
	
	for (j = i = 1; !(i & var); i<<=1, j++);
	
	return j-1;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
int sgputilMemCmp(const char *arg1, const char *arg2, int len) {
	int i;
	
	for (i = 0; i < len; i++)
		if (arg1[i] != arg2[i])
			return -1;
	
	return 0;
}

/*
#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
unsigned int *sgputilCompress4(unsigned int *data, unsigned int len, unsigned int *compl) {
	unsigned int i, *comp, prev, prevnum, clen;
	
	if (data == NULL)
		return NULL;
	
	if ((comp = malloc(len)) == NULL)
		return NULL;
	
	prev = 0;
	for (i = prevnum = clen = 0; i < (len >> 2); i++) {
		if (!(data[i] & 0xFF000000))
			data[i] = 0;
		if (!i) {
			prev = data[i];
			comp[clen] = data[i];
			clen++;
		} else {
			if (data[i] == prev) {
				prevnum++;
				comp[clen] = prevnum;
			} else {
				if (prevnum != 0) {
					clen++;
					prevnum = 0;
				}
				
				prev = data[i];
				comp[clen] = data[i];
				clen++;
			}
		}
	}
	if (prevnum > 0)
		clen++;
	
	comp = realloc(comp, clen << 2);
	*compl = clen << 2;
	return comp;
}

*/
#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
unsigned int *sgputilDecompress4(unsigned int *data, unsigned int len, unsigned int *ulen) {
	unsigned int *udata, udatal, i, j, k, prev;
	
	if (data == NULL)
		return NULL;
	
	// First, we need to know how much RAM we need to alloc
	for (i = udatal = 0; i < (len >> 2); i++) {
		if (data[i] < 0x1000000 && data[i] > 0) 
			udatal += data[i];
		else
			udatal++;
	}
	
	if ((udata = (unsigned int *) malloc(udatal << 2)) == NULL)
		return NULL;
	
	for (i = j = prev = 0; i < (len >> 2); i++) {
		if (data[i] >= 0x1000000 || data[i] == 0) {
			prev = data[i];
			udata[j] = data[i];
			j++;
		} else {
			for (k = 0; k < data[i]; k++, j++)
				udata[j] = prev;
		}
	}
	
	*ulen = udatal << 2;
	return udata;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
void *snsbbfzOpen(const char *fname) {
	SNSBBFZ_FILE *fs;
	SNSBBFZ_MH mh;
	SNSBBFZ_HEADINFO *hf;
	void *raw, *deflated;
	
	if (fname == NULL) {
		fprintf(stderr, "sgputil: Error: Got a NULL-pointer instead of a filename\n");
		return NULL;
	}
	
	if ((fs = (SNSBBFZ_FILE *) malloc(sizeof(SNSBBFZ_FILE))) == NULL) {
		fprintf(stderr, "sgputil: Error: malloc has failed us\n");
		return NULL;
	}
	
	if ((fs->fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "sgputil: Error: Unable to open file %s\n", fname);
		free(fs);
		return NULL;
	}
	
	if (fread(&mh, sizeof(SNSBBFZ_MH), 1, fs->fp) != 1) {
		fprintf(stderr, "sgputil: Error: EOF when reading header in file %s\n", fname);
		fclose(fs->fp);
		free(fs);
		return NULL;
	}
	
	if (spglutilMakeNativeEndianess(mh.magic_1) != MAGIC_1 || mh.magic_2 != MAGIC_2) {
		fprintf(stderr, "sgputil: Error: Bad magic in file %s\n", fname);
		fclose(fs->fp);
		free(fs);
		return NULL;
	}
	
	if ((raw = malloc(spglutilMakeNativeEndianess(mh.headersz & 0xFFFF))) == NULL) {
		fprintf(stderr, "sgputil: Error: malloc has failed us\n");
		fclose(fs->fp);
		free(fs);
		return NULL;
	}
	
	if (fread(raw, spglutilMakeNativeEndianess(mh.headersz & 0xFFFF), 1, fs->fp) != 1) {
		fprintf(stderr, "sgputil: Error: EOF in file %s while reading compressed headers\n", fname);
		fclose(fs->fp);
		free(fs);
		free(raw);
		free(deflated);
		return NULL;
	}
	
/*	if (mh.datapos & COMPRESSION_NEW)
		xzDecompress(raw, &deflated, spglutilMakeNativeEndianess(mh.headersz & 0xFFFF), spglutilMakeNativeEndianess(mh.headersz >> 16));
	else*/
		zDecompress(raw, &deflated, spglutilMakeNativeEndianess(mh.headersz & 0xFFFF), spglutilMakeNativeEndianess(mh.headersz >> 16));
	hf = (SNSBBFZ_HEADINFO *) deflated;
	free(raw);
	
	
	fs->dataheaders = spglutilMakeNativeEndianess(hf->dataHeaders);
	fs->headerpadding = spglutilMakeNativeEndianess(hf->headerpadding);
	fs->headerdata = deflated;
	fs->datapos = spglutilMakeNativeEndianess(mh.datapos);
	
	return fs;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
unsigned int snsbbfzGetFilesInFile(void *handle) {
	SNSBBFZ_FILE *fs = (SNSBBFZ_FILE *) handle;
	
	return fs->dataheaders;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
unsigned int snsbbfzGetHeaderLen(void *handle) {
	SNSBBFZ_FILE *fs = (SNSBBFZ_FILE *) handle;
	
	return fs->headerpadding;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
void *snsbbfzGetHeaderData(void *handle, unsigned int n) {
	SNSBBFZ_FILE *fs = (SNSBBFZ_FILE *) handle;
	
	unsigned int *index = (unsigned int *) fs->headerdata;
	void *payload;
	
	if (n >= fs->dataheaders)
		return NULL;
	
	index = &index[sizeof(SNSBBFZ_HEADINFO) >> 2];
	index = &index[((sizeof(SNSBBFZ_HEADER) + fs->headerpadding) >> 2) * n];
	payload = &index[sizeof(SNSBBFZ_HEADINFO) >> 2];
	
	return payload;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
void *snsbbfzGetData(void *handle, unsigned int n, unsigned int *len) {
	SNSBBFZ_FILE *fs = (SNSBBFZ_FILE *) handle;
	SNSBBFZ_HEADER *fh;
	void *raw, *data;
	unsigned int *index = (unsigned int *) fs->headerdata;
	
	if (n >= fs->dataheaders)
		return NULL;
	
	index = &index[sizeof(SNSBBFZ_HEADINFO) >> 2];
	fh = (SNSBBFZ_HEADER *) &index[((sizeof(SNSBBFZ_HEADER) + fs->headerpadding) >> 2) * n];
	
	if ((raw = malloc(spglutilMakeNativeEndianess(fh->zlen))) == NULL) {
		fprintf(stderr, "sgputil: Error: malloc has failed us\n");
		return NULL;
	}
	
	fseek(fs->fp, (fs->datapos & 0xFFFFF) + spglutilMakeNativeEndianess(fh->dataindex), SEEK_SET);
	if (fread(raw, spglutilMakeNativeEndianess(fh->zlen), 1, fs->fp) != 1) {
		fprintf(stderr, "sgputil: Error: EOF in file while fetching data block %i, size %i\n", n, fh->zlen);
		free(raw);
		return NULL;
	}
	
//	if (fh->flags & COMPRESSION_GZIP)
		zDecompress(raw, &data, spglutilMakeNativeEndianess(fh->zlen), spglutilMakeNativeEndianess(fh->len));
/*	else if (fh->flags & COMPRESSION_BZIP)
		asdfDecompress(raw, &data, spglutilMakeNativeEndianess(fh->zlen), spglutilMakeNativeEndianess(fh->len));
	else if (fh->flags & COMPRESSION_LZMA)
		xzDecompress(raw, &data, spglutilMakeNativeEndianess(fh->zlen), spglutilMakeNativeEndianess(fh->len));*/
	*len = spglutilMakeNativeEndianess(fh->len);
	
	free(raw);
	
	return data;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
void *snsbbfzClose(void *handle) {
	SNSBBFZ_FILE *fs = (SNSBBFZ_FILE *) handle;
	
	fclose(fs->fp);
	free(fs->headerdata);
	free(fs);
	
	return NULL;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
void *snsbbfzPrepareNew() {
	SNSBBFZ_FILE *file;
	if ((file = (SNSBBFZ_FILE *) malloc(sizeof(SNSBBFZ_FILE))) == NULL) {
		fprintf(stderr, "sgputil: Error: Malloc has failed us\n");
		return NULL;
	}
	
	file->fp = NULL;
	file->dataheaders = 0;
	file->headerpadding = 0;
	file->datapos = sizeof(SNSBBFZ_MH) + sizeof(SNSBBFZ_HEADINFO);
	file->headerdata = NULL;
	file->sfiles = NULL;
	
	return file;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
int snsbbfzAddFile(void *handle, const char *fname, const char *headdata) {
	SNSBBFZ_FILE *file = (SNSBBFZ_FILE *) handle;
	void *reallocBuff;
	unsigned int fsize, fid;
	FILE *fp;
	
	if ((fp = fopen(fname, "r")) == NULL) {
		fprintf(stderr, "sgputil: Error: Unable to open file %s\n", fname);
		return -1;
	}
	
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	if (fsize == 0) {
		fprintf(stderr, "sgputil: Error: File %s is empty\n", fname);
		return -1;
	}
	
	fid = file->dataheaders;
	file->dataheaders++;
	
	if ((reallocBuff = realloc(file->sfiles, sizeof(SNSBBFZ_SFILES) * file->dataheaders)) == NULL) {
		fprintf(stderr, "sgputil: Error: realloc has failed us\n");
		file->dataheaders--;
		return -1;
	}
	
	file->sfiles = (SNSBBFZ_SFILES *) reallocBuff;
	file->sfiles[fid].fp = fp;
	file->sfiles[fid].len = fsize;
	
	
	if (headdata != NULL) {
		if ((fp = fopen(headdata, "r")) == NULL) {
			fprintf(stderr, "sgputil: Error: Couldn't open file %s\n", headdata);
			fclose(file->sfiles[fid].fp);
			file->sfiles = (SNSBBFZ_SFILES *) realloc(file->sfiles, sizeof(SNSBBFZ_HEADINFO) * fid);
			file->dataheaders--;
			return -1;
		}
		
		fseek(fp, 0, SEEK_END);
		fsize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		
		if (fsize == 0) {
			fprintf(stderr, "sgputil: Error: File %s is empty\n", headdata);
			fclose(fp);
			fclose(file->sfiles[fid].fp);
			file->dataheaders--;
		}
		
		if (fsize > file->headerpadding)
			file->headerpadding = fsize;
		
	} else {
		file->sfiles[fid].head = NULL;
		file->sfiles[fid].headlen = 0;
	}
	
	return fid;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
int snsbbfzWriteOut(void *handle, const char *fname) {
	SNSBBFZ_FILE *file = (SNSBBFZ_FILE *) handle;
	FILE *out;
	unsigned int headerlen;
	void *headerdata;
	SNSBBFZ_HEADINFO *hf;
	SNSBBFZ_HEADER *hh;
	char *offsetCalc, *headerData;
	void *tempData, *fileData;
	unsigned int datapos, i, gziplen, lzmalen, bziplen;
	SNSBBFZ_MH mh;
	
	mh.magic_1 = MAGIC_1;
	mh.magic_2 = MAGIC_2;
	
	if (fname == NULL) {
		fprintf(stderr, "sgputil: Error: Target filename is NULL\n");
		return -1;
	}
	
	if ((out = fopen(fname, "w")) == NULL) {
		fprintf(stderr, "sgputil: Error: Couldn't create target %s\n", fname);
		return -1;
	}
	
	headerlen = (sizeof(SNSBBFZ_HEADER) + file->headerpadding) * file->dataheaders + sizeof(SNSBBFZ_HEADINFO);
	
	
	if ((headerdata = malloc(headerlen)) == NULL) {
		fprintf(stderr, "sgputil: Error: malloc has failed us\n");
		return -1;
	}
	
	hf = (SNSBBFZ_HEADINFO *) headerdata;
	
	hf->dataHeaders = file->dataheaders;
	hf->headerpadding = file->headerpadding;
	datapos = 0;
	
	offsetCalc = (char *) &hf[1];
	
	for (i = 0; i < hf->dataHeaders; i++) {
		hh = (SNSBBFZ_HEADER *) &offsetCalc[(file->headerpadding+sizeof(SNSBBFZ_HEADER))*i];
		fseek(file->sfiles[i].fp, 0, SEEK_SET);
		
		hh->len = file->sfiles[i].len;
		
		if ((fileData = malloc(file->sfiles[i].len)) == NULL) {
			fprintf(stderr, "sgputil: Error: Malloc has failed us\n");
			return -1;
		}
		
		fread(fileData, file->sfiles[i].len, 1, file->sfiles[i].fp);
		
		tempData = zCompress(fileData, file->sfiles[i].len, &gziplen);//&hh->zlen);
		free(tempData);
//		tempData = bz2Compress(fileData, file->sfiles[i].len, &bziplen);//&hh->zlen);
//		free(tempData);
//		tempData = xzCompress(fileData, file->sfiles[i].len, &lzmalen);//&hh->zlen);
//		free(tempData);
/*		if (lzmalen < gziplen) {
			hh->zlen = lzmalen;
			fprintf(stderr, "LZMA Length: %i\n", lzmalen);
			hh->flags = COMPRESSION_LZMA;
			file->sfiles[i].flags = COMPRESSION_LZMA;
*/ /*		} else if (bziplen < gziplen) {
			hh->zlen = bziplen;
libbz2 seems		fprintf(stderr, "BZIP Length: %i\n", hh->zlen);
broken			hh->flags = COMPRESSION_BZIP;
			file->sfiles[i].flags = COMPRESSION_BZIP;
		} else { */
			hh->zlen = gziplen;
			fprintf(stderr, "GZIP Length: %i\n", gziplen);
			//hh->flags = COMPRESSION_GZIP;
			//file->sfiles[i].flags = COMPRESSION_GZIP;
//		}
		
		free(fileData);
		hh->dataindex = datapos;
		datapos += hh->zlen;
		headerData = (char *) &hh;
		headerData = &headerData[sizeof(SNSBBFZ_HEADER)];
		if (file->sfiles[i].head != NULL) {
			fseek(file->sfiles[i].head, 0, SEEK_SET);
			fread(headerData, file->sfiles[i].headlen, 1, file->sfiles[i].head);
			fclose(file->sfiles[i].head);
		}
//		fprintf(stderr, "End of loop\n");
	}
//	fprintf(stderr, "Loop done\n");
	
	mh.headersz = (headerlen << 16);
	tempData = zCompress(headerdata, headerlen, &datapos);
	mh.headersz += (datapos & 0xFFFF);
	mh.datapos = datapos + sizeof(SNSBBFZ_MH);
	
	
	fwrite(&mh, sizeof(SNSBBFZ_MH), 1, out);
	fwrite(tempData, datapos, 1, out);
	free(tempData);
	free(headerdata);
	
	for (i = 0; i < file->dataheaders; i++) {
		if ((tempData = malloc(file->sfiles[i].len)) == NULL) {
			fprintf(stderr, "sgputil: Error: Malloc has failed us\n");
			return -1;
		}
		fseek(file->sfiles[i].fp, 0, SEEK_SET);
		fread(tempData, file->sfiles[i].len, 1, file->sfiles[i].fp);
		fclose(file->sfiles[i].fp);
/*		if (file->sfiles[i].flags & COMPRESSION_LZMA)
			headerData = (char *) xzCompress(tempData, file->sfiles[i].len, &datapos);
		else if (file->sfiles[i].flags & COMPRESSION_BZIP)
			headerData = (char *) bz2Compress(tempData, file->sfiles[i].len, &datapos);
		else if (file->sfiles[i].flags & COMPRESSION_GZIP)*/
//			headerData = (char *) zCompress(tempData, file->sfiles[i].len, &datapos);
//		else
			headerData = NULL;
		free(tempData);
		fwrite(headerData, datapos, 1, out);
		free(headerData);
	}
	
	return 0;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
void spgutilMakeNativePath(char *path) {
	#ifdef TARGET_IS_RETARDED
		char *tempstr = path;
		while ((tempstr = strstr(path, "/")) != NULL)
			*tempstr = '\\';
	#endif
	return;
}


#ifdef TARGET_IS_RETARDED
	DLLIMPORT
#endif
unsigned int spglutilMakeNativeEndianess(unsigned int i) {
	return i;
/*	unsigned int ret;
	char *temp = (char *) &i;
	
	ret = *temp;
	ret += temp[1] << 8;
	ret += temp[2] << 16;
	ret += temp[3] << 24;*/
	
//	return ret;
}
