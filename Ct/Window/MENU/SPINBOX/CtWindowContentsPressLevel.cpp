#include "CtWindowContentsPressLevel.h"

CtWindowContentsPressLevel::CtWindowContentsPressLevel(const CtWindowID WindowID) :
	CtWindowContents(WindowID),
	m_Level(Level1)
{
}
CtWindowContentsPressLevel::CtWindowContentsPressLevel(const CtWindowID WindowID, ContentsPressLevel level) :
	CtWindowContents(WindowID),
	m_Level(level)
{
}
CtWindowContentsPressLevel::CtWindowContentsPressLevel(CtWindowContentsPressLevel& contents) :
	CtWindowContents(contents.getType())
{
	m_Level = contents.getLabel();
}

CtWindowContentsPressLevel::~CtWindowContentsPressLevel()
{
}

void CtWindowContentsPressLevel::setLabel(ContentsPressLevel label)
{
	m_Level = label;
}
CtWindowContentsPressLevel::ContentsPressLevel CtWindowContentsPressLevel::getLabel()
{
	return m_Level;
}
void CtWindowContentsPressLevel::setLevel(ContentsPressLevel level)
{
	m_Level = level;
}
CtWindowContentsPressLevel::ContentsPressLevel CtWindowContentsPressLevel::getLevel()
{
	return m_Level;
}
