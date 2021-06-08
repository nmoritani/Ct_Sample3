#ifndef __IMGTYPE_H__
#define __IMGTYPE_H__

/* 読み込んだイメージを格納する構造体 */
/* TODO クラス化 */
typedef union {
	unsigned long n;
	struct {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};
} IMGCOLOR;

typedef struct {
	int			width, height;
	unsigned char *buf;
	int			row_bytes;
	int			stride;
	int			pixel_depth;
	int			pixel_bytes;
	bool		palette_premultiplied;
	int			palette_num;
	IMGCOLOR	*palette;
} IMAGE;

/* ピクセルデータ取得クラス */
class ImgGetPixel {
public:
	virtual IMGCOLOR get() = 0;
	virtual IMGCOLOR getRGBA() = 0;
};

class ImgGetPixel1bpp : public ImgGetPixel {
protected:
	IMAGE *img;
	int pos;
	unsigned char bit;
	unsigned char cnt;
	unsigned char *ptr;
public:
	ImgGetPixel1bpp(IMAGE *image);
	virtual IMGCOLOR get();
	virtual IMGCOLOR getRGBA();
};

class ImgGetPixel2bpp : public ImgGetPixel {
protected:
	IMAGE *img;
	int pos;
	unsigned char cnt;
	unsigned char bit;
	unsigned char *ptr;
public:
	ImgGetPixel2bpp(IMAGE *image);
	virtual IMGCOLOR get();
	virtual IMGCOLOR getRGBA();
};

class ImgGetPixel4bpp : public ImgGetPixel {
protected:
	IMAGE *img;
	int pos;
	unsigned char cnt;
	unsigned char bit;
	unsigned char *ptr;
public:
	ImgGetPixel4bpp(IMAGE *image);
	virtual IMGCOLOR get();
	virtual IMGCOLOR getRGBA();
};

class ImgGetPixel8bpp : public ImgGetPixel {
protected:
	IMAGE *img;
	int pos;
	unsigned char *ptr;
public:
	ImgGetPixel8bpp(IMAGE *image);
	virtual IMGCOLOR get();
	virtual IMGCOLOR getRGBA();
};

class ImgGetPixel16bpp : public ImgGetPixel {
protected:
	IMAGE *img;
	int pos;
	unsigned char *ptr;
public:
	ImgGetPixel16bpp(IMAGE *image);
	virtual IMGCOLOR get();
	virtual IMGCOLOR getRGBA();
};

class ImgGetPixel24bpp : public ImgGetPixel {
protected:
	IMAGE *img;
	int pos;
	unsigned char *ptr;
public:
	ImgGetPixel24bpp(IMAGE *image);
	virtual IMGCOLOR get();
	virtual IMGCOLOR getRGBA();
};


class ImgGetPixel32bpp : public ImgGetPixel {
protected:
	IMAGE *img;
	int pos;
	unsigned char *ptr;
public:
	ImgGetPixel32bpp(IMAGE *image);
	virtual IMGCOLOR get();
	virtual IMGCOLOR getRGBA();
};

void img_init(IMAGE *img);
void img_free(IMAGE *img);
ImgGetPixel* img_get_pixelfunc(IMAGE *img);

#endif
