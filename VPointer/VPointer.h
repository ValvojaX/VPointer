#pragma once
#include <Windows.h>

namespace mem
{
	HANDLE m_hProcess;
	
	template <typename T> class VPointer {
	private:
		T* m_address;
	public:
		VPointer() {
			m_address = 0;
		}

		VPointer(T* address) {
			m_address = address;
		}

		VPointer(uint64_t address) {
			m_address = (T*)address;
		}

		// Overload arrow operator
		T* operator -> () {
			T tmp;
			ReadProcessMemory(m_hProcess, m_address, &tmp, sizeof(tmp), NULL);
			return &tmp;
		}

		// Overload dereference operator
		T operator * () {
			T tmp;
			ReadProcessMemory(m_hProcess, m_address, &tmp, sizeof(tmp), NULL);
			return tmp;
		}

		// Overload address-of operator
		T* operator & () {
			return m_address;
		}

		// Overload equality operator
		bool operator == (T* address) {
			return m_address == address;
		}

		// Overload equality operator
		bool operator == (VPointer& other) {
			return m_address == other.m_address;
		}
	};
}