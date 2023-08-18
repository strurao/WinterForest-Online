#pragma once
class ResourceBase
{
public:
	ResourceBase();
	virtual ~ResourceBase();

	virtual void LoadFile(const wstring& path);
	virtual void SaveFile(const wstring& path);
};

