
#include <stdio.h>
#include <unistd.h>

#include<iostream>
#include<sstream>
#include<string>

#include <zmq_wrap.hpp>

#include <rapidjson/document.h>
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace std;

struct scmd
{
	int cmd;
	string str;
};

int parsejson(const char * pstr,struct scmd &ecmd)
{
	rapidjson::Document jdoc;
	jdoc.Parse<0>(pstr);
	if (jdoc.HasParseError())
	{
		printf("GetParseError %d\n",jdoc.GetParseError());
		return -1;
	}
	int iret = 0;
	char *key = (char*)"ins";
	if(jdoc.HasMember(key)){
		ecmd.cmd = 1;
		ecmd.str = jdoc[key].GetString();
		iret = 1;
	}
	key = (char*)"print";
	if(jdoc.HasMember(key)){
		ecmd.cmd = 1;
		ecmd.str = jdoc[key].GetString();
		cout <<pstr<<endl;
		iret = 1;
	}
	return 0;
}

void f()
{
	cout << "wrap rep"<<endl;
	wz_socket wz_sct(ZMQ_REP,"ipc://hello.ipc",-1,1);

	while(1){
		zmq::message_t msg;
		try{
			wz_sct.recv(&msg);
		}catch(zmq::error_t & e)
		{
			cout << "rep recv except " << " errno "<<e.num ()<< " str "<< e.what()<<endl;
			break;
		}

		//cout << "zmq.hpp rcv " << (char *)msg.data()<<endl;
		struct scmd ecmd={0};
		parsejson((char*)msg.data(),ecmd);
		cout << "cmd "<< ecmd.cmd<<" str "<<ecmd.str<<endl;

		try{
			wz_sct.send(msg.data(),msg.size());
		}catch(zmq::error_t & e)
		{
			cout << "rep send except " << " errno "<<e.num ()<< " str "<< e.what()<<endl;
			break;
		}
	}
}

int main (void)
{
	while(1){
		f();
	}
}




