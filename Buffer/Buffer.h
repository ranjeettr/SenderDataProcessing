#ifndef BUFFER_H
#define BUFFER_H

#include <mutex>
#include <map>
#include <vector>


using namespace std;

class Buffer
{
	private:
		map<int, vector<string>> m_buffer;
		mutex dataMtx;
		
		Buffer()
		{}

	public:
		static Buffer *m_bufferInstance;
		static Buffer *getInstance()
		{
	                if( !m_bufferInstance )
                        {
                                m_bufferInstance = new Buffer();
                        }
                        return m_bufferInstance;
		}

		bool writeData( string &message, int sender_id );
		bool readData( string &message);
};

#endif
