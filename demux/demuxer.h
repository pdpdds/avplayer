//
// demuxer.h
// ~~~~~~~~~
//
// Copyright (c) 2011 Jack (jack.wgm@gmail.com)
//

#ifndef __DEMUXER_H__
#define __DEMUXER_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif


class demuxer
{
public:
	demuxer() {}
	virtual ~demuxer() {}

public:
	// ��demuxer, ����Ϊany, �Դ����������.
	virtual bool open(boost::any ctx) = 0;

	// ��ȡһ��packet��pkt��.
	// ����true��ʾ�ɹ�.
	virtual bool read_packet(AVPacket *pkt) = 0;

	// seek_packet ������seek��ָ����timestampλ��.
	// timestamp ʱ���.
	virtual bool seek_packet(int64_t timestamp) = 0;

	// stream_index �õ�ָ��AVMediaType���͵�index.
	// index �Ƿ��ص�ָ��AVMediaType���͵�index.
	// ����true��ʾ�ɹ�.
	virtual bool stream_index(enum AVMediaType type, int &index) = 0;

	// query_avcodec_id ��ѯָ��index��codec��idֵ.
	// ָ����index.
	// ָ����index��codec_id.
	// �ɹ�����true.
	virtual bool query_avcodec_id(int index, enum AVCodecID &codec_id) = 0;

	// ��ȡ��ͣ, ��ҪΪRTSP��������ý��Э��.
	virtual int read_pause() { return -1; }

	// ͬ��, �ָ�����.
	virtual int read_play() { return -1; }

	// �ر�.
	virtual void close() = 0;
};

#endif // __DEMUXER_H__
