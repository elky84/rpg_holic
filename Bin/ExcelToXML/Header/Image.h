#pragma once

namespace ExcelData
{

class Image
{
public:
	Image()
	{
		memset(&m_Name, 0, sizeof(m_Name));

		memset(&m_Index, 0, sizeof(m_Index));

	}

	std::wstring& NameReference()
	{
		return m_Name;
	}

	std::wstring Name() const
	{
		return m_Name;
	}

	void Name(const std::wstring& _Name)
	{
		m_Name = _Name;
	}

	int& IndexReference()
	{
		return m_Index;
	}

	int Index() const
	{
		return m_Index;
	}

	void Index(const int& _Index)
	{
		m_Index = _Index;
	}

private:
	std::wstring m_Name;
	int m_Index;
};

class ImageData : public light::Excel::Data
{
public:
	virtual bool Load()
	{
		Image Instance;
		light::XMLParser parser;
		light::ScopeProfiler profiler(__FUNCTIONW__, 10, _T("./XML/Image.XML"));
		if( false == parser.File(_T("./XML/Image.XML")))
		{
			LOG_ERROR(_T("%s, Open() Failed. Path(./XML/Image.XML"), __FUNCTIONW__);
			return false;
		}

		if ( false == parser.Execute(_T("/ImageList")))
		{
			LOG_ERROR(_T("%s, Execute() Failed. /ImageList"), __FUNCTIONW__);
			return false;
		}

		if ( false == parser.BindElem(_T("Data")))
		{
			LOG_ERROR(_T("%s, Execute() Failed. Data"), __FUNCTIONW__);
			return false;
		}

		if ( false == parser.BindAttrib(_T("Index"), Instance.IndexReference()))
		{
			LOG_ERROR(_T("%s, BindAttrib() Failed. Instance.IndexReference()"), __FUNCTIONW__);
			return false;
		}

		if ( false == parser.BindAttrib(_T("Name"), Instance.NameReference()))
		{
			LOG_ERROR(_T("%s, BindAttrib() Failed. Instance.NameReference()"), __FUNCTIONW__);
			return false;
		}

		while (parser.Next())
		{
			m_Map.insert(std::map<int, Image>::value_type(Instance.Index(), Instance));
		}

		return true;
	}

	bool Get(int& key, Image& Instance)
	{
		std::map<int, Image>::iterator it = m_Map.find(key);
		{
			return false;
		}
		Instance = it->second;
		return true;
	}

	std::map<int, Image>& Map()
	{
		return m_Map;
	}

private:
	std::map<int, Image> m_Map;
};

__declspec(selectany) ImageData ImageDataInstance;

} // ExcelData
