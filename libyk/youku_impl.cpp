#include <cstddef>
#include "utf8.h"
#include "youku_impl.h"

namespace libyk {

youku_impl::youku_impl(void)
	: m_http_stream(m_io_service)
{
	// ����Ϊssl����֤ģʽ.
	m_http_stream.check_certificate(false);
}

youku_impl::~youku_impl(void)
{
}

bool youku_impl::parse_url(const std::string& url)
{
	std::string prefix_youku_url = "http://v.youku.com/v_show/id_";
	const int vid_length = 13;

	// ���url�Ƿ���youku����Ƶ����.
	std::string::size_type pos = url.find(prefix_youku_url);
	if (pos == std::string::npos)
		return false;

	// �õ���Ƶid.
    std::string vid = url.substr(pos + prefix_youku_url.length());
	if (vid.length() >= vid_length)
		vid = vid.substr(0, vid_length);
	else
		return false;

	// �õ���Ƶid.
    m_vid = vid;

    return true;
}

bool youku_impl::parse_video_files(std::vector<std::string> &videos, const std::string &password)
{
    if (m_vid.empty())
        return -1;

	std::string prefix_query_url =
		"https://openapi.youku.com/v2/videos/files.json?"
		"client_id=e57bc82b1a9dcd2f&"
		"client_secret=a361608273b857415ee91a8285a16b4a&video_id=";

	// ���id.
    std::string query = prefix_query_url + m_vid;

	// ���passwd.
    query += password.empty() ? "" : "&watch_password=" + password;

	// �����ӿ�ʼ����.
	boost::system::error_code ec;
	m_http_stream.open(query, ec);
	if (ec && ec != boost::asio::error::eof)
	{
		std::cerr << ec.message().c_str() << std::endl;
		// ��ѯurlʧ��.
		return false;
	}

	// ����json�ַ���, Ȼ�����.
	boost::asio::streambuf response;
	std::ostringstream oss;

	while (boost::asio::read(m_http_stream,
		response, boost::asio::transfer_at_least(1), ec))
	{
		oss << &response;
	}

	// תΪ���ַ���.
	std::wstring utf = utf8_wide(oss.str());
	std::wstringstream stream;
	stream << utf;

	// ����json�ַ���.
	boost::property_tree::wptree root;
	try {
		boost::property_tree::read_json<boost::property_tree::wptree>(stream, root);
		try {
			boost::property_tree::wptree errinfo = root.get_child(L"error");
			int err = errinfo.get<int>(L"code");
			// ���json�а����Ĵ������.
			std::cerr << "error code: " << err << std::endl;
			return false;
		}
		catch (std::exception &)
		{}

		// �õ��ļ���.
		boost::property_tree::wptree files = root.get_child(L"files");
		boost::property_tree::wptree type;

		// ˵��: �ڵõ���Ӧ����Ƶ�ļ����, Ȼ�����segs��, ���������, ��������Ƶ�ֶ���Ϣ.
		// ע��m3u8��û����Ƶ�ֶ���Ϣ��, ��ֻ��һ��m3u8�ĵ�ַurl+duration��Ϣ. ok, ��
		// �õ�����Щ��Ϣ��, ���ǾͿ��԰������������ṩ������������, so, ����Ҫ�����ǽ���
		// ����.

		// �õ�hd2�ļ���.

		// �õ�mp4�ļ���.

		// �õ�3gp�ļ���.

		// �õ�3gphd�ļ���.

		// �õ�flv�ļ���.

		// �õ�m3u8�ļ���.

	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

	// boost::property_tree::parse_json();

	// Ϊ�˱���ͨ��!!
	return false;

	// ��ѯ.

//     curl p;
//     boost::property_tree::wptree root;
//     if (!parse_json(p.curl_send_request(query), root))
//         return -1;

//     boost::property_tree::wptree files=root.get_child(L"files");
// 
//     boost::property_tree::wptree type;

    // ��ʱ�����Ÿ���ͳ�����Ƶ
    /*
    try
    {
        type=files.get_child(L"hd2");
        BOOST_FOREACH(boost::property_tree::wptree::value_type& v,type.get_child(L"segs"))
        {
            boost::property_tree::wptree value=v.second;
            p.detail[index-1]->hd2.push_back(codepage::w2utf(value.get<std::wstring>(L"url")));
        }
        ret++;
    }
    catch(...)
    {

    }

    try
    {
        type=files.get_child(L"mp4");
        BOOST_FOREACH(boost::property_tree::wptree::value_type& v,type.get_child(L"segs"))
        {
            boost::property_tree::wptree value=v.second;
            p.detail[index-1]->mp4.push_back(codepage::w2utf(value.get<std::wstring>(L"url")));
        }
        ret++;
    }
    catch(...)
    {

    }
    */
//     try
//     {
//         type=files.get_child(L"flv");
//         BOOST_FOREACH(boost::property_tree::wptree::value_type& v,type.get_child(L"segs"))
//         {
//             boost::property_tree::wptree value=v.second;
//             std::string relocation=location(codepage::w2utf(value.get<std::wstring>(L"url")));
//             if (!relocation.empty())
//                 videos.push_back(relocation);
//             else
//                 return -1;
//         }
//         return 0;
//     }
//     catch(...)
//     {
//         return -1;
//     }

}

/*
bool libykvideo::parse_json(const std::string& data,boost::property_tree::wptree &root)
{
    if (data.empty())
        return false;

    std::wstringstream stream;

    std::wstring utf=codepage::utf2w(data);

    stream<<utf;

    try
    {
        boost::property_tree::read_json<boost::property_tree::wptree>(stream,root);
    }
    catch(...)
    {
        return false;
    }

    try
    {
        boost::property_tree::wptree errinfo=root.get_child(L"error");
        int err=errinfo.get<int>(L"code");
        return false;
    }
    catch(...)
    {
        return true;
    }
}

std::string libykvideo::location(const std::string& url)
{
    curl p(true);
    std::string header=p.curl_send_request(url);
    boost::to_lower<std::string>(header);
    size_t pos=header.find("location: ")+1;
    if (!pos)
        return false;
    
    header=header.substr((pos-1)+strlen("location: "));
    pos=header.find("\r\n")+1;
    if (!pos)
        return false;
    return header.substr(0,pos-1);    
}

*/

}



