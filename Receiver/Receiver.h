#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <condition_variable>
#include "Buffer.h"

class Receiver
{
	private:
		Receiver() : m_buffer( Buffer::getInstance() ),
				m_receiverMtx(),
				m_receiverCv()
		{
		}

		Buffer *m_buffer;
		mutex m_receiverMtx;
		condition_variable m_receiverCv;

	public:
		~Receiver(){}
		static Receiver *m_receiver;
		static Receiver *getInstance()
		{
			if( !m_receiver )
				m_receiver = new( Receiver );
			return m_receiver;
		}

		void ProcessData();
		void StartProcessing();
};


#endif
