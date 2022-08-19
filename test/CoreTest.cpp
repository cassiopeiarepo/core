#include "core/test/CoreTest.h"
#include "core/utils/Buffer.h"

CoreTest::CoreTest() {

}

void CoreTest::run() {
	String out;
	Buffer buffer;

	buffer.writeInt(1234);

	buffer.seekSet(0);

	int result_int = buffer.readInt();

	if (result_int == 1234) {
		out += String::format("Test buffor OK");
	}
	else {
		out += String::format("Test buffor FAIL");
	}

	result_category.append(String("Buffer test"));
	result.append(out);
}

