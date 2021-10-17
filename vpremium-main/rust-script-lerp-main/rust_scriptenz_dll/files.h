#pragma once

class Files
{
public:
	/*[junk_enable 2 5 /]
	[junk_enable_declares /]
	[swap_lines]*/
	void OnSetup();
	int	ReadInt(const char* element, const char* item);
	float ReadFloat(const char* element, const  char* item);
	bool ReadBool(const char* element, const char* item);
	void WriteInt(const char* element, const char* item, int value);
	void WriteFloat(const char* element, const char* item, float value);
	void WriteBool(const char* element, const char* item, bool value);
	/*[/ swap_lines]
	[junk_disable /]*/
private:
	char m_fileName[255];
};

extern Files* files;