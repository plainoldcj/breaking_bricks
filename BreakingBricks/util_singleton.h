/*
file: util_singleton.h
*/

#pragma once

namespace UTIL {

	template<typename TYPE>
	class Singleton {
	private:
		Singleton(const Singleton& other);
		Singleton& operator=(const Singleton& other);
	protected:
		Singleton(void) { }
	public:
		virtual ~Singleton(void) { }

		static TYPE& Instance(void) {
			static TYPE instance;
			return instance;
		}
	};

} // namespace UTIL