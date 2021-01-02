//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo.hpp"
#include "xyo-copyright.cpp"
#include "xyo-license.cpp"
#ifndef XYO_NO_VERSION
#       include "xyo-version.cpp"
#endif

// -

#include "xyo-managedmemory-object.cpp"
#include "xyo-managedmemory-registrydata.cpp"
#include "xyo-managedmemory-registrykey.cpp"
#include "xyo-managedmemory-registrythread.cpp"
#include "xyo-managedmemory-registryprocess.cpp"
#include "xyo-managedmemory-registry.cpp"
#include "xyo-multithreading-criticalsection--os-windows.cpp"
#include "xyo-multithreading-criticalsection--os-unix.cpp"
#include "xyo-multithreading-thread--os-windows.cpp"
#include "xyo-multithreading-thread--os-unix.cpp"
#include "xyo-multithreading-thread.cpp"

// --

#include "xyo-datastructures-buffer.cpp"
#include "xyo-stream-memoryread.cpp"
#include "xyo-stream-memorywrite.cpp"
#include "xyo-stream-streamx.cpp"
#include "xyo-encoding-utf.cpp"
#include "xyo-system-console--os-windows.cpp"
#include "xyo-system-console--os-unix.cpp"
#include "xyo-system-datetime--os-windows.cpp"
#include "xyo-system-datetime--os-unix.cpp"
#include "xyo-system-file.cpp"
#include "xyo-system-shellfind--os-windows.cpp"
#include "xyo-system-shellfind--os-unix.cpp"
#include "xyo-system-shell--os-windows.cpp"
#include "xyo-system-shell--os-unix.cpp"
#include "xyo-system-shell.cpp"
#include "xyo-system-processinteractive--os-windows.cpp"
#include "xyo-system-processinteractive--os-unix.cpp"
#include "xyo-encoding-utfstream.cpp"
#include "xyo-encoding-base16.cpp"
#include "xyo-encoding-base32.cpp"
#include "xyo-encoding-base64.cpp"
#include "xyo-multithreading-semaphore.cpp"
#include "xyo-multithreading-transfer.cpp"
#include "xyo-multithreading-worker.cpp"
#include "xyo-multithreading-workerqueue.cpp"
#include "xyo-algorithm-buffer8core.cpp"
#include "xyo-algorithm-randommt.cpp"
#include "xyo-cryptography-md5.cpp"
#include "xyo-cryptography-sha256.cpp"
#include "xyo-cryptography-sha512.cpp"
#include "xyo-cryptography-crypt.cpp"
#include "xyo-datastructures-ini.cpp"
#include "xyo-application-version.cpp"
#include "xyo-system-util.cpp"
#include "xyo-system-compiler.cpp"
#include "xyo-system-compiler--compiler-gcc.cpp"
#include "xyo-system-compiler--compiler-msvc.cpp"

// ---

#include "xyo-networking-ip4.cpp"
#include "xyo-networking-ip6.cpp"
#include "xyo-networking-ipaddress4.cpp"
#include "xyo-networking-ipaddress6.cpp"
#include "xyo-networking-network--os-windows.cpp"
#include "xyo-networking-network--os-unix.cpp"
#include "xyo-networking-url.cpp"
#include "xyo-networking-socket--os-windows.cpp"
#include "xyo-networking-socket--os-unix.cpp"

// ---

#include "xyo-parser-input.cpp"
#include "xyo-parser-token.cpp"
#include "xyo-datastructures-csv.cpp"
#include "xyo-datastructures-xml.cpp"
#include "xyo-datastructures-xmlparser.cpp"

// ---

#include "xyo-datastructures-dynamicobject.cpp"
#include "xyo-datastructures-json-value.cpp"
#include "xyo-datastructures-json-vnull.cpp"
#include "xyo-datastructures-json-vboolean.cpp"
#include "xyo-datastructures-json-vnumber.cpp"
#include "xyo-datastructures-json-vstring.cpp"
#include "xyo-datastructures-json-varray.cpp"
#include "xyo-datastructures-json-vassociativearray.cpp"
#include "xyo-datastructures-json.cpp"

// ---

#ifdef XYO_OS_WINDOWS
#       pragma comment(lib, "user32.lib")
#       pragma comment(lib, "ws2_32.lib")
#endif
