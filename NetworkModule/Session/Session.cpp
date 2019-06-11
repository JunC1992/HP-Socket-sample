#include "Session.h"
#include <iostream>
#include <sstream>
#include <locale.h> 
#include <string>
#include "stringhelperDef.h"
#include "WSServerApi.h"

#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "c:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "ManagerCenterImp");

Session::Session(boost::asio::ip::tcp::socket socket)
	: m_ws(std::move(socket))
	, m_strand(m_ws.get_io_service())
	, m_isOnline(false)
	, m_userType(-1)
	, m_source(0)
	, m_level(-1)
	, m_isStart(false)
{
	
}

Session::~Session()
{
	if(m_isStart)
		m_pMsgQueue->stop();
}

void Session::Read()
{
	m_ws.async_read(m_buffer, m_strand.wrap(std::bind(&Session::onRead, 
		shared_from_this(), std::placeholders::_1, std::placeholders::_2)));
}

void Session::onRead(boost::system::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if (ec == boost::beast::websocket::error::closed)
	{
		m_pSpi->onDisConnect(this, m_source, ec);
		return;
	}
		
	if (ec)
	{
		m_pSpi->onDisConnect(this, m_source, ec);
		return;
	}

	// 读取缓存数据并清空缓存
	std::stringstream sstr;
	sstr << boost::beast::buffers(m_buffer.data());
	std::wstring content = m_converter.from_bytes(sstr.str().c_str());
	
	// 判断是否是ping
	if (L"ping" == content)
	{
		scoped_lock lock(m_mutex);
		try
		{
			m_ws.write(boost::asio::buffer(string_To_UTF8("pong")));
		}
		catch (const std::exception&)
		{
		}	
		//CMsgQueueDispathcher::instance()->postDispMsg(CommonTools::GeneralTaskCmd1::create(shared_from_this(), &Session::Send, "pong"));
	}
	else
	{
		m_pSpi->onRead(this,m_sessionID, WStringToAChar(content));
	}	
	m_buffer.consume(m_buffer.size());
	Read();
}

void Session::onAccept(boost::system::error_code ec)
{
	if (ec)
		return;
	Read();
}

void Session::Run()
{
	m_ws.async_accept(m_strand.wrap(std::bind(&Session::onAccept,
		shared_from_this(),std::placeholders::_1)));
}

void Session::Register(IWSServerSpi* pSpi)
{
	m_pSpi = pSpi;
}

void Session::Write(const std::string& content, bool isAdd/* = true*/)
{
	if (m_isStart)
	{
		m_pMsgQueue->postDispMsg(CommonTools::GeneralTaskCmd2::create(shared_from_this(),
			&Session::WriteHandle, content, isAdd));
	}
	else
	{
		WriteHandle(content, isAdd);
	}
} 

void Session::WriteHandle(const std::string& content, bool isAdd /*= true*/)
{
	try
	{
		scoped_lock lock(m_mutex);
		if (isAdd)
		{
			//m_ws.async_write(boost::asio::buffer(string_To_UTF8("<HX>" + content + "<END>"))
			//	, m_strand.wrap(std::bind(&Session::onWrite
			//		, this
			//		, std::placeholders::_1
			//		, std::placeholders::_2)));
			//if(m_ws.is_open())
				m_ws.write(boost::asio::buffer(string_To_UTF8("<HX>" + content + "<END>")));
		}
		else
		{
			//m_ws.async_write(boost::asio::buffer(content.c_str(), content.size())
			//	, m_strand.wrap(std::bind(&Session::onWrite
			//		, this
			//		, std::placeholders::_1
			//		, std::placeholders::_2)));
			//if (m_ws.is_open())
				m_ws.write(boost::asio::buffer(content.c_str(), content.size()));
		}
		//CMsgQueueDispathcher::instance()->postDispMsg(CommonTools::GeneralTaskCmd1::create(shared_from_this(), &Session::Send, "<HX>" + content + "<END>"));
		LOG4CXX_DEBUG(logger, "send msg " + content);
	}
	catch (const std::exception& e)
	{

	}
}

int Session::Send(const std::string & content)
{
	try
	{
		Write(string_To_UTF8(content), false);
// 		m_ws.write(boost::asio::buffer(string_To_UTF8(content)));
	}
	catch (const std::exception& )
	{
		return -1;
	}
	return 0;
}

void Session::onWrite(boost::system::error_code ec, std::size_t bytes_transferred)
{
	if (ec)
	{
		m_pSpi->onDisConnect(this, m_source, ec);
		return;
	}

// 	m_buffer.consume(m_buffer.size());

// 	Read();
}

int Session::Init(const std::string& ip, unsigned short port)
{
	m_ip = ip;
	m_sessionID = ip + "_" + std::to_string(port);
	return 0;
}

std::string Session::string_To_UTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴  
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

void Session::SetMsgQueue()
{
	m_isStart = true;
	m_pMsgQueue = std::make_shared<CNMMsgQueueDispathcher>();
}

