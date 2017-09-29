
#include <unistd.h>

#include<iostream>
#include<sstream>
#include<string>

#include <zmq_wrap.hpp>

#include <rapidjson/document.h>
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace std;

string genejson(int cnt)
{
	string sret;

	rapidjson::Document jdoc;
	jdoc.SetObject();

	stringstream is;
	is<< cnt;
	rapidjson::Value strValue(rapidjson::kStringType);
	strValue.SetString(is.str().c_str(),jdoc.GetAllocator());
	if(cnt % 1000){
		jdoc.AddMember("ins",strValue,jdoc.GetAllocator());
	}else{
		jdoc.AddMember("print",strValue,jdoc.GetAllocator());
	}

	rapidjson::StringBuffer buffer;
	rapidjson::Writer< rapidjson::StringBuffer> writer(buffer);
	jdoc.Accept(writer);
	sret = buffer.GetString();

	return sret;
}

void f()
{
	cout << "wrap req"<<endl;
	wz_socket wz_sct(ZMQ_REQ,"ipc://hello.ipc",1000,1);
	int idx = 0;

	while(1){
		string str;
		str = genejson(idx++);

		try{
			wz_sct.send(str.c_str(),str.size()+1);
		}catch (zmq::error_t & e)
		{
			cout << "req send except " << " errno "<<e.num ()<< " str "<< e.what()<<endl;
			break;
		}

		zmq::message_t msg;
		try{
			wz_sct.recv(&msg);
		}catch(zmq::error_t & e)
		{
			cout << "req rcv except " << " errno "<<e.num ()<< " str "<< e.what()<<endl;
			break;
		}

		if(idx %1000 == 0){
			cout << "zmq.hpp rcv " << (char *)msg.data()<<" sec "<<time(NULL)<<endl;
		}
	}
}

int main (void)
{
	while(1){
		f();
	}
}

