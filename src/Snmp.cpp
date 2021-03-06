#include "include/Snmp.h"
#include <core/Global.h>
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>

extern "C" ModuleInterface* create()
{
    return new Snmp;
}

extern "C" void destroy(ModuleInterface* x)
{
    delete x;
}

Snmp::Snmp()
{
}

Snmp::~Snmp()
{
    stop();
	Global::Instance().get_IrcData().DelConsumer(mpDataInterface);
    delete mpDataInterface;
}

void Snmp::Init(DataInterface* pData)
{
	mpDataInterface = pData;
	mpDataInterface->Init(true, false, false, true);
    Global::Instance().get_IrcData().AddConsumer(mpDataInterface);

    timerlong();
}


void Snmp::stop()
{
    run = false;
    mpDataInterface->stop();
    std::cout << "Snmp::stop" << std::endl;
    raw_parse_thread->join();
    std::cout << "raw_parse_thread stopped" << std::endl;
    privmsg_parse_thread->join();
    std::cout << "privmsg_parse_thread stopped" << std::endl;
}

void Snmp::read()
{
    run = true;
    assert(!raw_parse_thread);
    raw_parse_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&Snmp::parse_raw, this)));
    assert(!privmsg_parse_thread);
    privmsg_parse_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&Snmp::parse_privmsg, this)));
}

void Snmp::parse_raw()
{
    std::vector< std::string > data;
    while(run)
    {
        data = mpDataInterface->GetRawQueue();
        ParseData(data);
    }
}

void Snmp::parse_privmsg()
{
    std::vector< std::string > data;
    while(run)
    {
        data = mpDataInterface->GetPrivmsgQueue();
        PRIVMSG(data, "!");
    }
}


void Snmp::ParseData(std::vector< std::string > data)
{
    if (data.size() >= 1)
    {
		std::string returnstr = "PRIVMSG #blubs :" + data[0];
		if (data.size() >= 2)
		{
			for (unsigned int i = 1; i < data.size(); i++)
			{
				returnstr = returnstr + " " + data[i];
			}
		}
		returnstr = returnstr + "\r\n";
		//SendLowPriority(returnstr);
    }
}


void Snmp::ParsePrivmsg(std::string nick, std::string command, std::string chan, std::vector< std::string > args, int chantrigger)
{
    UsersInterface& U = Global::Instance().get_Users();
    std::string auth = U.GetAuth(nick);
	if (args.size() == 1)
    {
		if (boost::iequals(command, "Snmp"))
		{
			get_snmp(args[0]);
			overwatch(command, command, chan, nick, auth, args);
		}
    }
}

void Snmp::get_snmp(std::string _objid)
{
	/*std::cout << _objid << std::endl;
	std::string result;
	snmp_session* temp_ss;
	temp_ss = open_snmp("10.0.10.252", "ro");
	if (temp_ss)
	{
		result = snmp(temp_ss, _objid);
		if (!boost::iequals(result, ""))
		{
			std::string returnstr = "PRIVMSG #blubs :" + result + "\r\n";
			Send(returnstr);
			std::cout << result << std::endl;
		}
	}
	close_snmp(temp_ss);*/
	poller();
}

void Snmp::poller()
{
	std::string result;
	snmp_session* temp_ss;
	temp_ss = open_snmp("10.0.10.252", "ro");
	if (temp_ss)
	{
		result = snmp(temp_ss, "iso.3.6.1.2.1.2.2.1.16.101");
		if (!boost::iequals(result, ""))
		{
			std::string returnstr = "PRIVMSG #blubs :" + result + "\r\n";
			Send(returnstr);
			std::cout << result << std::endl;
		}
		result = snmp(temp_ss, "iso.3.6.1.2.1.2.2.1.16.102");
		if (!boost::iequals(result, ""))
		{
			std::string returnstr = "PRIVMSG #blubs :" + result + "\r\n";
			Send(returnstr);
			std::cout << result << std::endl;
		}
		result = snmp(temp_ss, "iso.3.6.1.2.1.2.2.1.16.103");
		if (!boost::iequals(result, ""))
		{
			std::string returnstr = "PRIVMSG #blubs :" + result + "\r\n";
			Send(returnstr);
			std::cout << result << std::endl;
		}
		result = snmp(temp_ss, "iso.3.6.1.2.1.2.2.1.16.104");
		if (!boost::iequals(result, ""))
		{
			std::string returnstr = "PRIVMSG #blubs :" + result + "\r\n";
			Send(returnstr);
			std::cout << result << std::endl;
		}
		result = snmp(temp_ss, "iso.3.6.1.2.1.2.2.1.16.105");
		if (!boost::iequals(result, ""))
		{
			std::string returnstr = "PRIVMSG #blubs :" + result + "\r\n";
			Send(returnstr);
			std::cout << result << std::endl;
		}
		result = snmp(temp_ss, "iso.3.6.1.2.1.2.2.1.16.106");
		if (!boost::iequals(result, ""))
		{
			std::string returnstr = "PRIVMSG #blubs :" + result + "\r\n";
			Send(returnstr);
			std::cout << result << std::endl;
		}
		result = snmp(temp_ss, "iso.3.6.1.2.1.2.2.1.16.107");
		if (!boost::iequals(result, ""))
		{
			std::string returnstr = "PRIVMSG #blubs :" + result + "\r\n";
			Send(returnstr);
			std::cout << result << std::endl;
		}
		result = snmp(temp_ss, "iso.3.6.1.2.1.2.2.1.16.108");
		if (!boost::iequals(result, ""))
		{
			std::string returnstr = "PRIVMSG #blubs :" + result + "\r\n";
			Send(returnstr);
			std::cout << result << std::endl;
		}
	}
	close_snmp(temp_ss);
	temp_ss = open_snmp("10.0.10.253", "ro");
	if (temp_ss)
	{
		result = snmp(temp_ss, "iso.3.6.1.2.1.2.2.1.16.103");
		if (!boost::iequals(result, ""))
		{
			std::string returnstr = "PRIVMSG #blubs :" + result + "\r\n";
			Send(returnstr);
			std::cout << result << std::endl;
		}
		result = snmp(temp_ss, "iso.3.6.1.2.1.2.2.1.16.104");
		if (!boost::iequals(result, ""))
		{
			std::string returnstr = "PRIVMSG #blubs :" + result + "\r\n";
			Send(returnstr);
			std::cout << result << std::endl;
		}
		result = snmp(temp_ss, "iso.3.6.1.2.1.2.2.1.16.105");
		if (!boost::iequals(result, ""))
		{
			std::string returnstr = "PRIVMSG #blubs :" + result + "\r\n";
			Send(returnstr);
			std::cout << result << std::endl;
		}
	}
	close_snmp(temp_ss);
}

void Snmp::timerrun()
{
    //cout << "channelbot::timerrun()" << endl;
    int Tijd;
    time_t t= time(0);
    Tijd = t;
    longtime++;
    if (longtime >= 30)
    {
		poller();
        timerlong();
        longtime = 0;
    }
    for (int i = timer_sec.size() - 1; i >= 0; i--)
    {
        if (timer_sec[i] < Tijd)
        {
            std::cout << timer_command[i] << std::endl;
            timer_sec.erase(timer_sec.begin()+i);
            timer_command.erase(timer_command.begin()+i);
        }
    }
}

void Snmp::timerlong()
{
    int Tijd;
    time_t t= time(0);
    Tijd = t;
    Tijd = Tijd + 100;
    for (int i = timer_long_sec.size() - 1; i >= 0; i--)
    {
        if (timer_long_sec[i] < Tijd)
        {
            std::cout << "timer_long to timer " << timer_long_command[i] << std::endl;
            timer_sec.push_back(timer_long_sec[i]);
            timer_command.push_back(timer_long_command[i]);
            timer_long_sec.erase(timer_long_sec.begin()+i);
            timer_long_command.erase(timer_long_command.begin()+i);
        }
    }
}

snmp_session* Snmp::open_snmp(std::string _peername, std::string _community)
{
	snmp_session session, *ss;
	const char *arg = _community.c_str();
	init_snmp("ircppsnmp");
	snmp_sess_init( &session );
	session.peername = strdup(_peername.c_str());
	session.version = SNMP_VERSION_2c;
	session.community = (unsigned char*)arg;
	session.community_len = strlen(arg);
	/*
	* Open the session
	*/
	SOCK_STARTUP;
	ss = snmp_open(&session);                     /* establish the session */

	if (!ss)
	{
		snmp_sess_perror("ack", &session);
		SOCK_CLEANUP;
	}
	return ss;
}

void Snmp::close_snmp(snmp_session *_ss)
{
	snmp_close(_ss);
	SOCK_CLEANUP;
}

std::string Snmp::snmp(snmp_session *ss, std::string _objid)
{
	snmp_pdu *pdu;
	snmp_pdu *response;
	oid anOID[MAX_OID_LEN];
	size_t anOID_len;
	netsnmp_variable_list *vars;
	int status;
	std::string return_string = "";

	pdu = snmp_pdu_create(SNMP_MSG_GET);
	anOID_len = MAX_OID_LEN;
	if (!read_objid(_objid.c_str(), anOID, &anOID_len))
	{
		snmp_perror(_objid.c_str());
		return "";
	}

	snmp_add_null_var(pdu, anOID, anOID_len);

	status = snmp_synch_response(ss, pdu, &response);
	char buf[1024];

	vars = response->variables;
	if (response->errstat == SNMP_ERR_NOERROR)
	{
		snprint_variable(buf, sizeof(buf), vars->name, vars->name_length, vars);
		fprintf(stdout, "%s: %s\n", ss->peername, buf);
		return_string = std::string(buf);
	}
	else
	{
		/*for (ix = 1; vp && ix != pdu->errindex; vp = vp->next_variable, ix++)
			;
		if (vp)
		{
			snprint_objid(buf, sizeof(buf), vp->name, vp->name_length);
		}
		else
		{
			strcpy(buf, "(none)");
		}
		fprintf(stdout, "%s: %s: %s\n", ss->peername, buf, snmp_errstring(pdu->errstat));*/
	}
	if (response)
	{
		snmp_free_pdu(response);
	}
	return return_string;
}




