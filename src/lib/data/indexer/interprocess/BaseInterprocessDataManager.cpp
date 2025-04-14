#include "BaseInterprocessDataManager.h"

using namespace std;

string to_string(ProcessId processId) 
{
	return to_string(static_cast<underlying_type_t<ProcessId>>(processId));
}

wstring to_wstring(ProcessId processId) 
{
	return to_wstring(static_cast<underlying_type_t<ProcessId>>(processId));
}

ostream &operator << (ostream &stream, ProcessId processId) 
{
	return stream << static_cast<underlying_type_t<ProcessId>>(processId);
}

BaseInterprocessDataManager::BaseInterprocessDataManager(
	const std::string& sharedMemoryName,
	size_t initialSharedMemorySize,
	const std::string& instanceUuid,
	ProcessId processId,
	bool isOwner)
	: m_sharedMemory(
		  sharedMemoryName,
		  initialSharedMemorySize,
		  isOwner ? SharedMemory::CREATE_AND_DELETE : SharedMemory::OPEN_ONLY)
	, m_instanceUuid(instanceUuid)
	, m_processId(processId)
{
}

ProcessId BaseInterprocessDataManager::getProcessId() const
{
	return m_processId;
}
