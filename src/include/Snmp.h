#ifndef Snmp_H
#define Snmp_H
#include <core/ModuleBase.h>
#include <interfaces/DataInterface.h>
#include <string>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

class DataInterface;
class Snmp : public ModuleBase
{
public:
    Snmp();
    ~Snmp();
    void read();
    void stop();
    void Init(DataInterface* pData);
    void timerrun();

private:
    DataInterface* mpDataInterface;

    void parse_raw();
    void parse_privmsg();
    void ParseData(std::vector< std::string > data);
    void ParsePrivmsg(std::string nick, std::string command, std::string chan, std::vector< std::string > args, int chantrigger);
    void get_snmp(std::string _objid);
	void poller();

	snmp_session* open_snmp(std::string _peername, std::string _community);
    void close_snmp(snmp_session *ss);
    std::string snmp(snmp_session *_ss, std::string _objid);

    void timerlong();
    std::vector<int> timer_sec;
    std::vector< std::string > timer_command;
    std::vector<int> timer_long_sec;
    std::vector< std::string > timer_long_command;
    int longtime;

    bool run;
    boost::shared_ptr<boost::thread> raw_parse_thread;
    boost::shared_ptr<boost::thread> privmsg_parse_thread;

};

#endif // Snmp_H

