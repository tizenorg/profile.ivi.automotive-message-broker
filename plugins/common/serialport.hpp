#ifndef _SERIALPORT_H_
#define _SERIALPORT_H_

#include "abstractio.hpp"
#include "debugout.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

class SerialPort: public AbstractIo
{
public:
	SerialPort(std::string _tty)
		:tty(_tty)
	{

	}

	~SerialPort()
	{
		close();
	}

	bool open()
	{
		fd = ::open(tty.c_str(), O_RDWR, O_NOCTTY);

		if(fd == -1)
		{
			DebugOut()<<"Cannot open serial device."<<endl;
			return false;
		}

		struct termios oldtio;
		tcgetattr(fd,&oldtio);

		oldtio.c_cflag |= CS8 | CLOCAL | CREAD;

		oldtio.c_iflag |= IGNPAR;
		oldtio.c_iflag &= ~(ICRNL | IMAXBEL);


		oldtio.c_oflag &= ~OPOST;

		oldtio.c_lflag |= ECHOE | ECHOK | ECHOCTL | ECHOKE;
		oldtio.c_lflag &= ~(ECHO | ICANON | ISIG);

		//oldtio.c_cc[VEOL]     = '\r';

		cfsetispeed(&oldtio, B9600);
		cfsetospeed(&oldtio, B9600);

		tcflush(fd, TCIFLUSH);
		tcsetattr(fd, TCSANOW, &oldtio);

		fcntl(fd,F_SETFL,O_NONBLOCK);

		return true;
	}

	int fileDescriptor() { return fd; }

	bool close()
	{
		::close(fd);
	}

	std::string read()
	{
		char buff;
		std::string result;
		int bytesread = 0;
		while( bytesread = ::read(fd,&buff,1) > 0 )
		{
			result += buff;
		}


		if(bytesread == -1)
			perror("Error while reading: ");

		return result;
	}

	void write(std::string data)
	{
		int written = ::write(fd,data.c_str(),data.length());
		if(written == -1)
		{
			DebugOut()<<"Unable to write"<<endl;
		}
	}

private:
	int fd;
	std::string tty;

};


#endif
