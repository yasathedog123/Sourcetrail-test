#include "Controller.h"

Controller::Controller() = default;

Controller::~Controller() = default;

void Controller::setComponent(Component* component)
{
	m_component = component;
}

Id Controller::getTabId() const
{
	if (m_component)
	{
		return m_component->getTabId();
	}

	return 0;
}
