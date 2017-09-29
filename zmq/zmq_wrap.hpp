
#ifndef __ZMQ_WRAP_HPP__
#define __ZMQ_WRAP_HPP__

#include <zmq.hpp>

class wz_socket
{
public:
	inline wz_socket(int type,std::string const& addr, int tout_ms = -1, int linger_ms = -1)
	{
		mp_ctx = new zmq::context_t();
		mp_sct = new zmq::socket_t(*mp_ctx,type);
		if(type == ZMQ_REQ){
			mp_sct->connect(addr);
		}else if(type == ZMQ_REP){
			mp_sct->bind(addr);
		}
		mp_sct->setsockopt(ZMQ_RCVTIMEO,tout_ms);
		mp_sct->setsockopt(ZMQ_LINGER,linger_ms);
	}

	inline ~wz_socket ()
	{
		close();
	}

	inline void close()
	{
		delete mp_sct;
		delete mp_ctx;
	}

	inline size_t send (const void *buf_, size_t len_, int flags_ = 0)
	{
		return mp_sct->send(buf_, len_, flags_);
	}

	inline bool recv (zmq::message_t *msg_, int flags_ = 0)
	{
		return mp_sct->recv(msg_, flags_);
	}
	
	zmq::context_t *mp_ctx;
	zmq::socket_t *mp_sct;
};

#endif

