/* this file is part of easyMule
 * Copyright (C)2002-2008 VeryCD Dev Team ( strEmail.Format("%s@%s", "emuledev", "verycd.com") / http: * www.easymule.org )
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
/*
 author: h7ing (hqing87@gmail.com)
 */

#include "MatchString.h"
#include "stdafx.h"


bool StringMatcher::MatchString(CString& strMatchDestination, vec_cstr& vecMatchDestinationPinyin, vec_cstr& vec_strSearchKey)
{
	vec_cstr::size_type total_match_count = 0;
	vec_cstr::size_type total_search_key = vec_strSearchKey.size();

	// 匹配每个关键词(key string)
	for (vec_cstr::iterator ix_key = vec_strSearchKey.begin(); ix_key != vec_strSearchKey.end(); ++ix_key)
	{
		CString& string_one_search_key = *ix_key;

		// 原始字符串匹配
		if (strMatchDestination.MakeLower().Find(string_one_search_key.MakeLower()) != -1)
		{
			total_match_count++;
			continue;
		}

		int match_count = 0; // 记录当前关键词中被成功匹配的字符数
		int match_count_temp = 0; // 临时变量
		int match_count_same_char = 0; // 记录当前关键词中与首字母相连的相同字符被匹配的次数(eg:dddw)
		int match_count_max_char = 0; // 记录一个多音字中完全匹配字符数的最大值
		int match_count_full = 0; // 记录同一个字中多种发音完全匹配成功的次数
		int last_match_index = -1; // 上一个匹配到关键词字符的拼音索引
		int current_index = -1; // 当前进行匹配的拼音索引
		const int search_key_str_count = string_one_search_key.GetLength(); // 当前关键词的字符数

		// 原始字符串中没有找到关键词,再用拼音向量匹配
		for (vec_cstr::iterator ix_pinyin = vecMatchDestinationPinyin.begin(); ix_pinyin != vecMatchDestinationPinyin.end(); ++ix_pinyin)
		{
			current_index++;

			CString& string_one_pinyin = *ix_pinyin; // 一个字的拼音(可能有多种读音)

			vec_cstr vec_one_pinyin_spilt;
			SplitString(string_one_pinyin, vec_one_pinyin_spilt); // 将得到的拼音存入容器(默认将所有字是多音字)

			// 按多音字的每个读音进行匹配
			for (vec_cstr::iterator ix_pinyin_spilt = vec_one_pinyin_spilt.begin(); ix_pinyin_spilt != vec_one_pinyin_spilt.end(); ++ix_pinyin_spilt)
			{
				CString& string_temp = *ix_pinyin_spilt; // 一个读音
				int pinyin_index = 0;

				// 当前发音的首字母与关键词的第一个待匹配字符比较
				if (string_temp[0] != string_one_search_key[match_count])
				{
					// 前一个匹配成功的字为多音字,
					// 且该多音字中存在如下规律的发音:(x)_(x)(y)
					// eg:劲->jin_jing, 拎->lin_ling
					// 且当前字的首字母与前一个多音字中的(y)相同:
					// eg:拎个->lin_ling|ge
					// 则输入:linge
					// 匹配到"ge"时,当前匹配索引应回退到前一个字符"g"
					if (last_match_index == current_index - 1
						&& match_count_full > 1
						&& string_temp[0] == string_one_search_key[match_count - 1])
					{
						match_count--;
						match_count_full = 0;
						match_count_temp = -1; // 置为-1, 防止关键词索引在下面的判断中回退到0
					}
					else if (string_temp[0] != string_one_search_key[0])
						continue;

					// 关键词需要重新匹配:
					// eg:单词->下行线
					// 拼音->xia,hang_heng_xing,xian
					// 关键词->xingxian
					// 匹配到"xing"时将关键词成功匹配字符数清零(重新匹配)
					// eg2:单词->当当当当网
					// 拼音->dang,dang,dang,dang,wang
					// 关键词->dddw
					// 匹配到'w'时,若之前字符完全相同且匹配成功,则待匹配字符索引回退到前一个字符
					if (match_count_same_char > 0)
					{
						match_count--;
						match_count_same_char--;
					}
					else if (!match_count_temp)
					{
						match_count = 0;
					}
				}

				// 当前读音(从下标0开始)与关键词(从第一个待匹配字符开始)逐个字符比较
				while (string_temp[pinyin_index] != '\0' && 
					string_temp[pinyin_index] == string_one_search_key[match_count])
				{
					match_count++;
					pinyin_index++;
				}

				last_match_index = current_index;

				// 完全匹配输入关键词
				if (match_count == search_key_str_count)
				{
					match_count_temp = 0;
					match_count_max_char = 0;
					break;
				}

				// 完全匹配一个发音
				if (pinyin_index == string_temp.GetLength())
				{
					// 记录完全匹配发音的次数
					match_count_full++;

					// 记录被完全匹配的最大值(最长的发音)
					if (match_count_max_char < pinyin_index)
						match_count_max_char = pinyin_index;
				}

				// 关键词中的字符被匹配到时,用临时变量记录
				if (pinyin_index > 0)
				{
					match_count_temp = pinyin_index;
				}

				// 恢复关键词待匹配字符的索引
				match_count -= pinyin_index;
			} // END foreach in vecMatchDestinationPinyin

			// 是否完全匹配到某个发音
			if (match_count_max_char > 0)
			{
				match_count += match_count_max_char;
				match_count_temp = 0;
				match_count_max_char = 0;

				// 仅记录输入关键词完全匹配不少于2种发音的情况
				if (match_count_full < 2)
					match_count_full = 0;
			}

			// 没有完全匹配时,不管实际匹配到多少个字符,均默认为只匹配到首字母
			if (match_count_temp > 0)
			{
				match_count++;
				match_count_temp = 0;

				// 当关键词为连续字符(与首字母相同,中间无间隔,如:ddddw)且匹配成功,记录后续相同字符出现的次数
				if (match_count > 1
					&& string_one_search_key[0] == string_one_search_key[match_count - 1]
				&& string_one_search_key[match_count - 1] == string_one_search_key[match_count - 2])
				{
					match_count_same_char++;
				}
				else
				{
					match_count_same_char = 0;
				}
			}

			// 当前关键词完全匹配成功
			if (current_index == last_match_index && match_count == search_key_str_count)
			{
				total_match_count++;
				break;
			}

			// 若当前拼音没有匹配到,则下一次匹配从关键词的第一个字符开始匹配
			if (current_index != last_match_index)
			{
				match_count = 0;
				match_count_full = 0;
			}
		}

		if (total_match_count == total_search_key)
			return true;
	}

	return (total_match_count == total_search_key);
}

// Give a string and a pinyin string container, it will add the new pinyin string
// to the container.
void StringMatcher::GetPinyin(const CString& strSource, vec_cstr& vecPinyinContainer)
{
	int character_count = strSource.GetLength();

	wchar_t one_character;
	unsigned long ul_character;
	char utf8char[8] = {0};

	for (int ix = 0; ix != character_count; ++ix)
	{
		one_character = strSource[ix];
		ul_character = (unsigned long)one_character;

		// if not chinese
		if (ul_character < 0x4E00 || ul_character > 0x9fA5)
			continue;

		WideCharToMultiByte( CP_UTF8, 0, &one_character, -1, utf8char, 8, NULL, NULL );
		CString string_temp( get_pinyin( utf8char ) );

		//strPinyinContainer += string_temp;
		vecPinyinContainer.push_back(string_temp);
	}
} // END GetPinyin

void StringMatcher::SplitString(const CString& strInput, vec_cstr& vec_strOutput)
{
	int nSpaceIndex = strInput.Find(L" ");

	if (nSpaceIndex == -1)
	{
		vec_strOutput.push_back(strInput);
		return;
	}

	CString strOneSearchKey = strInput.Mid(0, nSpaceIndex);
	CString strSubString = strInput.Mid(nSpaceIndex + 1);

	vec_strOutput.push_back(strOneSearchKey);

	while ((nSpaceIndex = strSubString.Find(L" ") ) != -1)
	{
		strOneSearchKey = strSubString.Mid(0, nSpaceIndex);
		vec_strOutput.push_back(strOneSearchKey);

		strSubString = strSubString.Mid(nSpaceIndex + 1);
	}

	if (!strSubString.IsEmpty())
		vec_strOutput.push_back(strSubString);
}

void StringMatcher::AddItem(void* toadd, const CString& name)
{
	m_ListItemNames.insert(std::make_pair(toadd, name));
	std::vector<CString> myVec;
	GetPinyin(name, myVec);
	m_ListItemPinyin.insert(std::make_pair(toadd, myVec));
	m_ListItemsNeedShowOrig.push_back(toadd);
}

void StringMatcher::RemoveItem(void* toremove)
{
	m_ListItemNames.erase(toremove);
	m_ListItemPinyin.erase(toremove);
	
	for (ListItemsNeedShow::iterator ix = m_ListItemsNeedShowOrig.begin(); ix != m_ListItemsNeedShowOrig.end(); ++ix)
	{
		if (*ix == toremove)
		{
			m_ListItemsNeedShowOrig.erase(ix);
			break;
		}
	}
}

const StringMatcher::ListItemsNeedShow& StringMatcher::GetMatchResult(CString* pSearchKey)
{
	if (!m_ListItemsNeedShow.empty())
		m_ListItemsNeedShow.clear();

	if ( m_ListItemNames.size() <= 0 )
		return m_ListItemsNeedShow;

	if ( pSearchKey == NULL || *pSearchKey == _T(""))
	{
		m_isOriginal = true;
		m_strSearchKey = _T("");
		return m_ListItemsNeedShowOrig;
	}

	std::vector<CString> vecSearchKeys;
	m_strSearchKey = *pSearchKey;

	SplitString(m_strSearchKey, vecSearchKeys);

	for (ListItemNamesOrig::iterator ix_ListItems = m_ListItemNames.begin(); ix_ListItems != m_ListItemNames.end(); ++ix_ListItems)
	{
		void* listKey = ix_ListItems->first;
		CString& strItemName = ix_ListItems->second;
		std::vector<CString>& vecStrPinyin = m_ListItemPinyin[listKey];

		if (MatchString(strItemName, vecStrPinyin, vecSearchKeys))
			m_ListItemsNeedShow.push_back(listKey);
	}

	m_isOriginal = false;

	return m_ListItemsNeedShow;
}

void StringMatcher::RemoveAllItems()
{
	m_ListItemNames.clear();
	m_ListItemPinyin.clear();
	m_ListItemsNeedShow.clear();
	m_ListItemsNeedShowOrig.clear();
}

bool StringMatcher::GetOneItemMatchResult(CString& strItemName)
{
	if (m_strSearchKey.IsEmpty())
		return true;

	std::vector<CString> vecPinyin;
	GetPinyin(strItemName, vecPinyin);

	std::vector<CString> vecSearchKeys;
	SplitString(m_strSearchKey, vecSearchKeys);

	return MatchString(strItemName, vecPinyin, vecSearchKeys);
}

CString StringMatcher::GetItemName(void* toget)
{
	ListItemNamesOrig::iterator it = m_ListItemNames.find(toget);
	if (it != m_ListItemNames.end())
		return it->second;
	else
		return _T("");
}

void StringMatcher::RenameItem(void* torename, const CString& name)
{
	ListItemNamesOrig::iterator it = m_ListItemNames.find(torename);
	if (it == m_ListItemNames.end())
		return;

	m_ListItemNames[torename] = name;
	std::vector<CString>& myVec = m_ListItemPinyin[torename];
	myVec.clear();
	GetPinyin(name, myVec);
}