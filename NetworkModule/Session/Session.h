#pragma once
#include <memory>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <codecvt>
#include "cmutex.h"
#include "../NMMsgQueueDispathcher.h"

//#define QUEUE_MAX_SIZE 100000

#pragma warning(disable: 4251)

class IWSServerSpi;
class Session : public std::enable_shared_from_this<Session>
{
public:
	explicit Session(boost::asio::ip::tcp::socket socket);
	~Session();
	
	// 初始化
	int Init(const std::string& ip, unsigned short port);

	// 运行
	void Run();

	// 启动消息队列发送
	void SetMsgQueue();

	// 注册回调
	void Register(IWSServerSpi* pSpi);

	// 
	void onAccept(boost::system::error_code ec);

	// 读取套接字缓冲区
	void Read();

	void onRead(boost::system::error_code ec, std::size_t bytes_transferred);

	// 写入套接字缓冲区
	void Write(const std::string& content,	bool isAdd = true);

	void onWrite(boost::system::error_code ec, std::size_t bytes_transferred);

	void WriteHandle(const std::string& content, bool isAdd = true);

	// 设置是否在线
	inline void SetIsOnline(bool isOnline)
	{
		m_isOnline = isOnline;
	}

	inline bool IsOnline()
	{
		return m_isOnline;
	}

	inline std::string SessionID()
	{
		return m_sessionID;
	}

	inline void SetUserID(const std::string& userID)
	{
		m_userID = userID;
	}

	inline void SetUserType(int userType)
	{
		m_userType = userType;
	}

	inline void SetUserLevel(int level)
	{
		m_level = level;
	}

	inline int GetUserType()
	{
		return m_userType;
	}

	inline int GetUserLevel()
	{
		return m_level;
	}

	inline void SetSource(int source)
	{
		m_source = source;
	}
	inline int GetSource()
	{
		return m_source;
	}
	inline std::string GetUserID()
	{
		return m_userID;
	}

	inline std::string GetParentID()
	{
		return m_parentID;
	}

	inline void SetParentID(const std::string& parentID)
	{
		m_parentID = parentID;
	}

	inline void SetUserName(const std::string& userName)
	{
		m_accountName = userName;
	}

	inline std::string GetUserName()
	{
		return m_accountName;
	}

	inline std::string GetIp()
	{
		return m_ip;
	}

	inline void SetLoginName(const std::string& loginName)
	{
		m_loginName = loginName;
	}

	inline std::string GetLoginName()
	{
		return m_loginName;
	}

	inline void SetLoginTime(const std::string& loginTime)
	{
		m_loginTime = loginTime;
	}

	inline std::string GetLoginTime()
	{
		return m_loginTime;
	}

	inline void SetRegisterTime(const std::string& registerTime)
	{
		m_registerTime = registerTime;
	}

	inline std::string GetRegisterTime()
	{
		return m_registerTime;
	}
	inline void SetMac(const std::string& mac)
	{
		m_mac = mac;
	}

	inline std::string GetMac()
	{
		return m_mac;
	}

	boost::beast::websocket::stream<boost::asio::ip::tcp::socket> m_ws;

private:
	int Send(const std::string & content);

	std::string string_To_UTF8(const std::string & str);

private:
	boost::asio::io_service::strand m_strand;

	// i/o缓存区
	boost::beast::multi_buffer m_buffer;

	// 缓存队列
	//boost::lockfree::spsc_queue<std::string, boost::lockfree::capacity<QUEUE_MAX_SIZE>> m_writeTexts;

	// 回调类指针
	IWSServerSpi* m_pSpi;

	// ip
	std::string m_ip;

	// 账户名
	std::string m_accountName;

	// 登录名
	std::string m_loginName;

	// 回话id : ip+port
	std::string m_sessionID;

	// 注册时间
	std::string m_registerTime;

	// 登录时间
	std::string m_loginTime;

	// 是否在线
	bool m_isOnline;

	// 账户id
	std::string m_userID;

	// 父账户id
	std::string m_parentID;

	// 账户类型
	int m_userType;

	// 账户等级
	int m_level;

	// 来源
	int m_source;

	// mac地址
	std::string  m_mac;

	// 格式转换
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> m_converter;

	// 锁
	Mutex m_mutex;

	CNMMsgQueueDispathcherPtr m_pMsgQueue;

	// 是否消息队列处理发送消息
	bool m_isStart;

};

typedef std::shared_ptr<Session> SessionPtr;
typedef std::vector<SessionPtr> SessionPtrVec;
