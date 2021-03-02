//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_HPP
#define XYO_HPP

#include "xyo--dependency.hpp"

#include "xyo-copyright.hpp"
#include "xyo-license.hpp"
#ifndef XYO_NO_VERSION
#       include "xyo-version.hpp"
#endif

// -

#include "xyo-managedmemory-deletememory.hpp"
#include "xyo-managedmemory-finalizememory.hpp"
#include "xyo-datastructures-tgetclassofmember.hpp"
#include "xyo-datastructures-tcomparator.hpp"
#include "xyo-managedmemory-tifhasinitmemory.hpp"
#include "xyo-managedmemory-tifhasincreferencecount.hpp"
#include "xyo-managedmemory-tifhasdecreferencecount.hpp"
#include "xyo-managedmemory-tifhassetdeletememory.hpp"
#include "xyo-managedmemory-tifhaspointerlink.hpp"
#include "xyo-managedmemory-tifhasactiveconstructor.hpp"
#include "xyo-managedmemory-tifhasactivedestructor.hpp"
#include "xyo-managedmemory-tifhasactivefinalizer.hpp"
#include "xyo-managedmemory-registry.hpp"
#include "xyo-managedmemory-pointerx.hpp"
#include "xyo-managedmemory-object.hpp"
#include "xyo-datastructures-ttransfer.hpp"
#include "xyo-managedmemory-tpointer.hpp"
#include "xyo-managedmemory-tpointerx.hpp"
#include "xyo-managedmemory-tmemorysystem.hpp"

// --

#include "xyo-datastructures-tmemorycore.hpp"
#include "xyo-datastructures-txlist1.hpp"
#include "xyo-datastructures-txlist2.hpp"
#include "xyo-datastructures-txlist3.hpp"
#include "xyo-datastructures-txlist5.hpp"
#include "xyo-datastructures-txredblacktree.hpp"
#include "xyo-datastructures-txarray.hpp"

// ---

#include "xyo-managedmemory-registrydata.hpp"
#include "xyo-multithreading-tatomic.hpp"
#include "xyo-managedmemory-registrykey.hpp"
#include "xyo-managedmemory-registrylevel.hpp"
#include "xyo-managedmemory-registryprocess.hpp"
#include "xyo-managedmemory-registrythread.hpp"
#include "xyo-multithreading-criticalsection.hpp"
#include "xyo-multithreading-thread.hpp"
#include "xyo-managedmemory-tsingletonprocess.hpp"
#include "xyo-managedmemory-tsingletonthread.hpp"
#include "xyo-managedmemory-tsingleton.hpp"
#include "xyo-managedmemory-tmemorypoolunifiedprocess.hpp"
#include "xyo-managedmemory-tmemorypoolunifiedthread.hpp"
#include "xyo-managedmemory-tmemorypoolunified.hpp"
#include "xyo-managedmemory-tmemorypoolprocess.hpp"
#include "xyo-managedmemory-tmemorypoolthread.hpp"
#include "xyo-managedmemory-tmemorypool.hpp"
#include "xyo-managedmemory-tmemorypoolactiveprocess.hpp"
#include "xyo-managedmemory-tmemorypoolactivethread.hpp"
#include "xyo-managedmemory-tmemorypoolactive.hpp"
#include "xyo-managedmemory-tmemoryprocess.hpp"
#include "xyo-managedmemory-tmemorythread.hpp"
#include "xyo-managedmemory-tmemory.hpp"

// ---

#include "xyo-datastructures-tstringcore.hpp"
#include "xyo-datastructures-tstringreference.hpp"
#include "xyo-datastructures-tdynamicarray.hpp"
#include "xyo-encoding-thex.hpp"
#include "xyo-datastructures-tstring.hpp"
#include "xyo-encoding-string.hpp"

// ----

#include "xyo-datastructures-treference.hpp"
#include "xyo-datastructures-tstaticcast.hpp"
#include "xyo-datastructures-error.hpp"
#include "xyo-datastructures-tstack.hpp"
#include "xyo-datastructures-tstackpointerunsafe.hpp"
#include "xyo-datastructures-tredblacktreeone.hpp"
#include "xyo-datastructures-txredblacktree.hpp"
#include "xyo-datastructures-tdoubleendedqueue.hpp"
#include "xyo-datastructures-tassociativearray.hpp"
#include "xyo-datastructures-tring.hpp"
#include "xyo-datastructures-buffer.hpp"
#include "xyo-datastructures-uconvert.hpp"
#include "xyo-stream-iread.hpp"
#include "xyo-stream-iwrite.hpp"
#include "xyo-stream-iseek.hpp"
#include "xyo-stream-memoryread.hpp"
#include "xyo-stream-memorywrite.hpp"
#include "xyo-stream-streamx.hpp"
#include "xyo-encoding-utf8core.hpp"
#include "xyo-encoding-utf16core.hpp"
#include "xyo-encoding-utf32core.hpp"
#include "xyo-encoding-utf.hpp"
#include "xyo-encoding-tutfconvert.hpp"
#include "xyo-system-console.hpp"
#include "xyo-system-datetime.hpp"
#include "xyo-system-filetime.hpp"
#include "xyo-system-file.hpp"
#include "xyo-system-shellfind.hpp"
#include "xyo-system-shell.hpp"
#include "xyo-system-processinteractive.hpp"
#include "xyo-system-processor.hpp"
#include "xyo-encoding-utfstream.hpp"
#include "xyo-encoding-hex.hpp"
#include "xyo-encoding-base16.hpp"
#include "xyo-encoding-base32.hpp"
#include "xyo-encoding-base64.hpp"
#include "xyo-application-imain.hpp"
#include "xyo-multithreading-semaphore.hpp"
#include "xyo-multithreading-synchronize.hpp"
#include "xyo-multithreading-transfer.hpp"
#include "xyo-multithreading-worker.hpp"
#include "xyo-multithreading-workerqueue.hpp"
#include "xyo-algorithm-buffer8core.hpp"
#include "xyo-algorithm-randommt.hpp"
#include "xyo-cryptography-md5.hpp"
#include "xyo-cryptography-sha256.hpp"
#include "xyo-cryptography-sha512.hpp"
#include "xyo-cryptography-crypt.hpp"
#include "xyo-datastructures-ini.hpp"
#include "xyo-application-version.hpp"
#include "xyo-system-util.hpp"
#include "xyo-system-compiler.hpp"

// -----

#include "xyo-networking-ip4.hpp"
#include "xyo-networking-ip6.hpp"
#include "xyo-networking-ipaddress4.hpp"
#include "xyo-networking-ipaddress6.hpp"
#include "xyo-networking-network.hpp"
#include "xyo-networking-url.hpp"
#include "xyo-networking-socket.hpp"

// -----

#include "xyo-parser-input.hpp"
#include "xyo-parser-token.hpp"
#include "xyo-datastructures-csv.hpp"
#include "xyo-datastructures-xml.hpp"
#include "xyo-datastructures-xmlparser.hpp"

// -----

#include "xyo-datastructures-dynamicobject.hpp"
#include "xyo-datastructures-json-value.hpp"
#include "xyo-datastructures-json-vnull.hpp"
#include "xyo-datastructures-json-vboolean.hpp"
#include "xyo-datastructures-json-vnumber.hpp"
#include "xyo-datastructures-json-vstring.hpp"
#include "xyo-datastructures-json-varray.hpp"
#include "xyo-datastructures-json-vassociativearray.hpp"
#include "xyo-datastructures-json.hpp"

// -----

namespace XYO {
	using namespace DataStructures;
	using namespace ManagedMemory;
	using namespace Multithreading;
	using namespace Encoding;
	using namespace Algorithm;
	using namespace Stream;
	using namespace System;
	using namespace Cryptography;
	using namespace Application;
	using namespace Networking;
};

#endif

