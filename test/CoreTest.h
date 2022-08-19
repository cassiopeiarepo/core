#ifndef __CORE_TEST_H__
#define __CORE_TEST_H__

#include <core/types/Vector.h>
#include <core/types/Str.h>

class CoreTest {
public:
	CoreTest();

	void run();

	Vector<String> result;
	Vector<String> result_category;

};

#endif /* __CORE_TEST_H__ */
