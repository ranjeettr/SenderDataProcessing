#ifndef SENDER_H
#define SENDER_H

#include <iostream>
#include <condition_variable>
#include "Buffer.h"

class Sender
{
	private:
		Sender() : m_buffer( Buffer::getInstance() ),
				m_senderMtx(),
				m_senderCv(),
				numberOfSenders(0)
		{
		}

		Buffer *m_buffer;
		mutex m_senderMtx;
		condition_variable m_senderCv;

		int numberOfSenders;

	public:
		~Sender(){}
		static Sender *m_sender;
		static Sender *getInstance()
		{
			if( !m_sender )
				m_sender = new( Sender );
			return m_sender;
		}

		void SetNumberOfSenders( int no );
		void SendData( int sender_id );
		void StartAllSenders();
};


#endif
