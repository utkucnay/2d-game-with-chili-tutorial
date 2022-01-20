#pragma once

#include <vector>
#include "resource.h"
#include "EngineUtil.h"
#include <algorithm>
#include <string>

template<class T>
class Codex
{
private:
	class Entry
	{
	public:
		Entry(const std::wstring& key, const T* pResource)
			:
			key(key),
			pResource(pResource)
		{}
		std::wstring key;
		const T* pResource;
	};
public:
	static const T* Retrieve(const std::wstring& key)
	{
		return Get()._Retrieve(key);
	}
	static void Purge()
	{
		Get()._Purge();
	}
private:
	Codex() = default;
	~Codex()
	{
		for (auto& e : entries)
		{
			delete e.pResource;
		}
	}
	const T* _Retrieve(const std::wstring& key)
	{
		auto i = std::lower_bound(entries.begin(), entries.end(), key,
			[](const Entry& e, const std::wstring& key)
			{
				return e.key < key;
			}
		);
		if (i == entries.end() || i->key != key)
		{
			i = entries.emplace(i, key, new T(key));
		}
		return i->pResource;
	}
	void _Purge()
	{
		for (auto& e : entries)
		{
			delete e.pResource;
		}
		entries.clear();
	}
	static Codex& Get()
	{
		static Codex codex;
		return codex;
	}
private:
	std::vector<Entry> entries;
};