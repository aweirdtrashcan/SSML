#pragma once

// https://learn.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=msvc-170
// InstructionSet.cpp
// Compile by using: cl /EHsc /W4 InstructionSet.cpp
// processor: x86, x64
// Uses the __cpuid intrinsic to get information about
// CPU extended instruction set support.

#include <intrin.h>
#include <memory.h>

class InstructionSet {
	enum CPUIDRegister {
		EAX = 0,
		EBX = 1,
		ECX = 2,
		EDX = 3
	};

	class CPUID {
	public:
		CPUID()
			:
			m_CpuId(new int[4])
		{
			memset(m_CpuId, 0, 4 * sizeof(int));
		}
		
		CPUID(const CPUID& other)
			:
			m_CpuId(new int[4]) 
		{
			memcpy(m_CpuId, other.m_CpuId, 4 * sizeof(int));
		}

		CPUID& operator=(const CPUID& other) {
			memcpy(m_CpuId, other.m_CpuId, 4 * sizeof(int));
			return *this;
		}

		~CPUID() {
			delete[] m_CpuId;
		}

		int* id() { return m_CpuId; }

	private:
		int* m_CpuId;
	};

public:
	InstructionSet() 
		:
		m_NumIds(0)
	{
		CPUID cpui;

		// Calling __cpuid with 0x0 as the function_id argument
		// gets the number of the highest valid function ID.
		__cpuid(cpui.id(), 0);

		m_NumIds = cpui.id()[0];
		m_CpuIdsArray = new CPUID[m_NumIds];

		for (int i = 0; i < m_NumIds; i++) {
			__cpuidex(cpui.id(), i, 0);
			m_CpuIdsArray[i] = cpui;
		}

		m_ProcessorName = new char[0x20];
		memset(m_ProcessorName, 0, 20);
		// processor name is in leaf 0 in EBX, EDX, ECX
		*reinterpret_cast<int*>(&m_ProcessorName[0]) = m_CpuIdsArray[0].id()[EBX];
		*reinterpret_cast<int*>(&m_ProcessorName[4]) = m_CpuIdsArray[0].id()[EDX];
		*reinterpret_cast<int*>(&m_ProcessorName[8]) = m_CpuIdsArray[0].id()[ECX];

		m_Leaf1ECX = m_CpuIdsArray[1].id()[ECX];
		m_Leaf1EDX = m_CpuIdsArray[1].id()[EDX];
	}
	
	~InstructionSet() {
		delete[] m_CpuIdsArray;
		delete[] m_ProcessorName;
	}

	bool SSE41() const { return m_Leaf1ECX & 0x00080000; }
	bool SSE42() const { return m_Leaf1ECX & 0x00100000; }

private:
	int m_NumIds;

	int m_Leaf1ECX;
	int m_Leaf1EDX;

	CPUID* m_CpuIdsArray;

	char* m_ProcessorName;
};