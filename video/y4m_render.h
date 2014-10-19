//
// y4m_render.h
// ~~~~~~~~~~~~
//
// Copyright (c) 2011 Jack (jack.wgm@gmail.com)
//

#ifndef __Y4M_RENDER_H__
#define __Y4M_RENDER_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "video_render.h"


// ���ڵ��Բ��������Ƶ�ļ�.
class y4m_render
	: public video_render
{
public:
	y4m_render(void);
	~y4m_render(void);

public:
	/* ��ʼrender.	*/
	virtual bool init_render(void* ctx, int w, int h, int pix_fmt);
	virtual bool init_render(void* ctx, int w, int h, int pix_fmt, float fps);

	/* ��Ⱦһ֡.	*/
	virtual bool render_one_frame(AVFrame* data, int pix_fmt);

	/* ������С.	*/
	virtual void re_size(int width, int height);

	/* ���ÿ�߱�.	*/
	virtual void aspect_ratio(int srcw, int srch, bool enable_aspect);

	/* ����render.		*/
	virtual void destory_render();

private:
	FILE *m_yuv_out;
	char *m_image;
	int m_image_width;
	int m_image_height;
};

#endif // __Y4M_RENDER_H__

