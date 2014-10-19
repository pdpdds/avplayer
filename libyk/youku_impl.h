#ifndef __YOUKU_IMPL_H__
#define __YOUKU_IMPL_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "avhttp.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/noncopyable.hpp>

namespace libyk {

class youku_impl : public boost::noncopyable
{
public:
	youku_impl(void);
	virtual ~youku_impl(void);

public:
	// �����ſ���Ƶurl.
	bool parse_url(const std::string &url);
	// ����url�е���Ƶ�ļ�.
	bool parse_video_files(std::vector<std::string> &videos, const std::string &password = "");

private:
	std::string m_vid;
	boost::asio::io_service m_io_service;
	avhttp::http_stream m_http_stream;
};

}

#endif // __YOUKU_IMPL_H__

