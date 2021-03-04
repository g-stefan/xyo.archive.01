//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_NETWORKING_SOCKET_HPP
#define XYO_NETWORKING_SOCKET_HPP

#ifndef XYO_NETWORKING_NETWORK_HPP
#include "xyo-networking-network.hpp"
#endif

#ifndef XYO_STREAM_IREAD_HPP
#include "xyo-stream-iread.hpp"
#endif

#ifndef XYO_STREAM_IWRITE_HPP
#include "xyo-stream-iwrite.hpp"
#endif

#ifndef XYO_NETWORKING_IPADRESS4_HPP
#include "xyo-networking-ipaddress4.hpp"
#endif

#ifndef XYO_NETWORKING_IPADRESS6_HPP
#include "xyo-networking-ipaddress6.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace Networking {
		using namespace XYO::DataStructures;
		using namespace XYO::Stream;
		using namespace XYO::Encoding;

		class IPAddress_;
		class Socket_;

		class Socket:
			public virtual IRead,
			public virtual IWrite {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(Socket);

			protected:

				Socket_ *this_;
				Socket *linkOwner_;
				IPAddress_ *ipAddress;
				bool ipAddressIs6;

			public:

				XYO_EXPORT Socket();
				XYO_EXPORT ~Socket();
				XYO_EXPORT operator bool() const;

				XYO_EXPORT bool openClient(IPAddress4 &adr_);
				XYO_EXPORT bool openServer(IPAddress4 &adr_);
				XYO_EXPORT bool openClient(IPAddress6 &adr_);
				XYO_EXPORT bool openServer(IPAddress6 &adr_);
				XYO_EXPORT bool listen(uint16_t queue_);
				XYO_EXPORT bool accept(Socket &socket_);
				XYO_EXPORT void close();

				XYO_EXPORT size_t read(void *output, size_t ln);
				XYO_EXPORT size_t write(const void *input, size_t ln);
				XYO_EXPORT int waitToWrite(uint32_t microSeconds);
				XYO_EXPORT int waitToRead(uint32_t microSeconds);

				XYO_EXPORT bool openClientX(const String &adr_);
				XYO_EXPORT bool openServerX(const String &adr_);

				XYO_EXPORT bool isIPAddress4();
				XYO_EXPORT bool isIPAddress6();
				XYO_EXPORT bool getIPAddress4(IPAddress4 &);
				XYO_EXPORT bool getIPAddress6(IPAddress6 &);

				XYO_EXPORT void becomeOwner(Socket &socket_);
				XYO_EXPORT void linkOwner(Socket &socket_);
				XYO_EXPORT void unLinkOwner();
				XYO_EXPORT void transferOwner(Socket &socket_);
		};

	};
};

#endif

