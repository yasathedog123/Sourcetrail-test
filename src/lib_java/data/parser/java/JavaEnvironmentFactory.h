#ifndef JAVA_ENVIRONMENT_FACTORY_H
#define JAVA_ENVIRONMENT_FACTORY_H

#include <boost/dll/shared_library.hpp>
#include <jni.h>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

class JavaEnvironment;

class JavaEnvironmentFactory
{
public:
	static void createInstance(const std::string &classPath, std::string *errorString);
	static std::shared_ptr<JavaEnvironmentFactory> getInstance();

	~JavaEnvironmentFactory();

	std::shared_ptr<JavaEnvironment> createEnvironment();

private:
	friend class JavaEnvironment;

	static boost::dll::shared_library s_jvmLibrary;
	static std::shared_ptr<JavaEnvironmentFactory> s_instance;
	static std::string s_classPath;

	JavaEnvironmentFactory(JavaVM* jvm);

	void registerEnvironment();
	void unregisterEnvironment();

	JavaVM* m_jvm;
	std::map<std::thread::id, std::pair<JNIEnv*, int>> m_threadIdToEnvAndUserCount;
	std::mutex m_threadIdToEnvAndUserCountMutex;
};

#endif	  // JAVA_ENVIRONMENT_FACTORY_H
