#pragma once

//#include "global.h"


namespace NSPrime
{
	template <class TKey, class TVal>
	class CLSimpleMapEqualHelper
	{
	public:
		static bool IsEqualKey(const TKey& k1, const TKey& k2)
		{
			return (k1 == k2);
		}

		static bool IsEqualValue(const TVal& v1, const TVal& v2)
		{
			return (v1 == v2);
		}
	};

	// intended for small number of simple types or pointers
	template <class TKey, class TVal, class TEqual = CLSimpleMapEqualHelper< TKey, TVal > >
	class CLSimpleMap
	{
	public:
		TKey* m_aKey;
		TVal* m_aVal;
		int m_nSize;

		typedef TKey _ArrayKeyType;
		typedef TVal _ArrayElementType;

	// Construction/destruction
		CLSimpleMap() : m_aKey(NULL), m_aVal(NULL), m_nSize(0)
		{ }

		~CLSimpleMap()
		{
			RemoveAll();
		}

	// Operations
		int GetSize() const
		{
			return m_nSize;
		}
		bool Add(const TKey& key, const TVal& val)
		{
			TKey* pKey;
			pKey = (TKey*)realloc(m_aKey, (m_nSize + 1) * sizeof(TKey));
			if(pKey == NULL)
				return false;
			m_aKey = pKey;
			TVal* pVal;
			pVal = (TVal*)realloc(m_aVal, (m_nSize + 1) * sizeof(TVal));
			if(pVal == NULL)
				return false;
			m_aVal = pVal;
			InternalSetAtIndex(m_nSize, key, val);
			m_nSize++;
			return true;
		}
		bool Remove(const TKey& key)
		{
			int nIndex = FindKey(key);
			if(nIndex == -1)
				return false;
			return RemoveAt(nIndex);
		}
		bool RemoveAt(int nIndex)
		{
			if (nIndex < 0 || nIndex >= m_nSize)
			{
				return false;
			}
			m_aKey[nIndex].~TKey();
			m_aVal[nIndex].~TVal();
			if(nIndex != (m_nSize - 1))
			{
				memmove((void*)(m_aKey + nIndex), (void*)(m_aKey + nIndex + 1), (m_nSize - (nIndex + 1)) * sizeof(TKey));
				memmove((void*)(m_aVal + nIndex), (void*)(m_aVal + nIndex + 1), (m_nSize - (nIndex + 1)) * sizeof(TVal));
			}
			TKey* pKey;
			pKey = (TKey*)realloc(m_aKey, (m_nSize - 1) * sizeof(TKey));
			if(pKey != NULL || m_nSize == 1)
				m_aKey = pKey;
			TVal* pVal;
			pVal = (TVal*)realloc(m_aVal, (m_nSize - 1) * sizeof(TVal));
			if(pVal != NULL || m_nSize == 1)
				m_aVal = pVal;
			m_nSize--;
			return true;
		}
		void RemoveAll()
		{
			if(m_aKey != NULL)
			{
				for(int i = 0; i < m_nSize; i++)
				{
					m_aKey[i].~TKey();
					m_aVal[i].~TVal();
				}
				free(m_aKey);
				m_aKey = NULL;
			}
			if(m_aVal != NULL)
			{
				free(m_aVal);
				m_aVal = NULL;
			}

			m_nSize = 0;
		}
		bool SetAt(const TKey& key, const TVal& val)
		{
			int nIndex = FindKey(key);
			if(nIndex == -1)
				return false;
			if((nIndex < 0) || (nIndex >= m_nSize))
			{
				return false;
			}
			m_aKey[nIndex].~TKey();
			m_aVal[nIndex].~TVal();
			InternalSetAtIndex(nIndex, key, val);
			return true;
		}
		TVal Lookup(const TKey& key) const
		{
			int nIndex = FindKey(key);
			if(nIndex == -1)
				return NULL;    // must be able to convert
			return GetValueAt(nIndex);
		}
		TKey ReverseLookup(const TVal& val) const
		{
			int nIndex = FindVal(val);
			if(nIndex == -1)
				return NULL;    // must be able to convert
			return GetKeyAt(nIndex);
		}
		TKey* GetKeyAt(int nIndex) const
		{
			if(nIndex < 0 || nIndex >= m_nSize)
			{
				return NULL;
			}
				
			return &(m_aKey[nIndex]);
		}
		TVal* GetValueAt(int nIndex) const
		{
			if(nIndex < 0 || nIndex >= m_nSize)
			{
				return NULL;
			}
				
			return &(m_aVal[nIndex]);
		}

		int FindKey(const TKey& key) const
		{
			for(int i = 0; i < m_nSize; i++)
			{
				if(TEqual::IsEqualKey(m_aKey[i], key))
					return i;
			}
			return -1;  // not found
		}
		int FindVal(const TVal& val) const
		{
			for(int i = 0; i < m_nSize; i++)
			{
				if(TEqual::IsEqualValue(m_aVal[i], val))
					return i;
			}
			return -1;  // not found
		}

		bool SetAtIndex(int nIndex, const TKey& key, const TVal& val)
		{
			if (nIndex < 0 || nIndex >= m_nSize)
				return false;
			InternalSetAtIndex(nIndex, key, val);
			return true;
		}


	// Implementation

		template <typename T>
		class Wrapper
		{
		public:
			Wrapper(const T& _t) : t(_t)
			{
			}
			template <class _Ty>
			void *operator new(size_t, _Ty* p)
			{
				return p;
			}
			template <class _Ty>
			void operator delete(void* /* pv */, _Ty* /* p */)
			{
			}
			T t;
		};
		void InternalSetAtIndex(int nIndex, const TKey& key, const TVal& val)
		{
			new(m_aKey + nIndex) Wrapper<TKey>(key);
			new(m_aVal + nIndex) Wrapper<TVal>(val);
		}
	};
}
