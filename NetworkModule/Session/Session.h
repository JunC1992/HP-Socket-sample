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
	
	// ��ʼ��
	int Init(const std::string& ip, unsigned short port);

	// ����
	void Run();

	// ������Ϣ���з���
	void SetMsgQueue();

	// ע��ص�
	void Register(IWSServerSpi* pSpi);

	// 
	void onAccept(boost::system::error_code ec);

	// ��ȡ�׽��ֻ�����
	void Read();

	void onRead(boost::system::error_code ec, std::size_t bytes_transferred);

	// д���׽��ֻ�����
	void Write(const std::string& content,	bool isAdd = true);

	void onWrite(boost::system::error_code ec, std::size_t bytes_transferred);

	void WriteHandle(const std::string& content, bool isAdd = true);

	// �����Ƿ�����
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

	// i/o������
	boost::beast::multi_buffer m_buffer;

	// �������
	//boost::lockfree::spsc_queue<std::string, boost::lockfree::capacity<QUEUE_MAX_SIZE>> m_writeTexts;

	// �ص���ָ��
	IWSServerSpi* m_pSpi;

	// ip
	std::string m_ip;

	// �˻���
	std::string m_accountName;

	// ��¼��
	std::string m_loginName;

	// �ػ�id : ip+port
	std::string m_sessionID;

	// ע��ʱ��
	std::string m_registerTime;

	// ��¼ʱ��
	std::string m_loginTime;

	// �Ƿ�����
	bool m_isOnline;

	// �˻�id
	std::string m_userID;

	// ���˻�id
	std::string m_parentID;

	// �˻�����
	int m_userType;

	// �˻��ȼ�
	int m_level;

	// ��Դ
	int m_source;

	// mac��ַ
	std::string  m_mac;

	// ��ʽת��
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> m_converter;

	// ��
	Mutex m_mutex;

	CNMMsgQueueDispathcherPtr m_pMsgQueue;

	// �Ƿ���Ϣ���д�������Ϣ
	bool m_isStart;

};

typedef std::shared_ptr<Session> SessionPtr;
typedef std::vector<SessionPtr> SessionPtrVec;
