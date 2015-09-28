/*
file: util_memory.h
*/

#pragma once

#include <list>
#include <cstdlib>

namespace UTIL {

	template<typename TYPE>
	class Memory {
	private:
		static std::list<TYPE*> freeList;
	public:
		virtual ~Memory(void) {
			// TODO
		}

		void* operator new(std::size_t size) {
			if(freeList.empty()) {
				return malloc(sizeof(TYPE));
			}
			void* memory = freeList.back();
			freeList.pop_back();
			return memory;
		}

		void operator delete(void* memory) {
			if(NULL == memory) return;
			freeList.push_back((TYPE*)memory);
		}
	};
	
	template<typename TYPE>
	std::list<TYPE*> Memory<TYPE>::freeList;

} // namespace UTIL