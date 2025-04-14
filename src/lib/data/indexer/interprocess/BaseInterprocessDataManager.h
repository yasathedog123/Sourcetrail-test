#ifndef BASE_INTERPROCESS_DATA_MANAGER_H
#define BASE_INTERPROCESS_DATA_MANAGER_H

#include <string>
#include <limits>
#include <type_traits>

#include "SharedMemory.h"

enum class ProcessId : std::size_t 
{
	NONE,
	INVALID = std::numeric_limits<std::underlying_type_t<ProcessId>>::max()
};

std::string to_string(ProcessId processId);
std::wstring to_wstring(ProcessId processId);
std::ostream &operator << (std::ostream &stream, ProcessId processId);

class BaseInterprocessDataManager
{
public:
	BaseInterprocessDataManager(
		const std::string& sharedMemoryName,
		size_t initialSharedMemorySize,
		const std::string& instanceUuid,
		ProcessId processId,
		bool isOwner);

	virtual ~BaseInterprocessDataManager() = default;

	ProcessId getProcessId() const;

protected:
	SharedMemory m_sharedMemory;

	const std::string m_instanceUuid;
	const ProcessId m_processId;
};

#endif	  // BASE_INTERPROCESS_DATA_MANAGER_H
