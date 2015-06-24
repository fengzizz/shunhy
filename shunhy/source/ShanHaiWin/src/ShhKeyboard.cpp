#include <vector>
#include <algorithm>
#include "ShhKeyboard.h"

namespace Shh{
	ShhKeys::ShhKeys()
	{
		mKeyList.reserve(Shh_DEFAULT_KEY_BUFFER_LENGTH);
	}
	ShhKeys::ShhKeys(int buff_size)
	{
		mKeyList.reserve(buff_size);
	}
	ShhKeys::ShhKeys(const KeyList& key_list)
	{
		mKeyList = key_list;
	}
	inline bool ShhKeys::FindKey(EShhKeys key)
	{
		auto last = mKeyList.end();
		auto o = std::find(mKeyList.begin(), last, key);
		return o < last;
	}
	ShhKeys::~ShhKeys()
	{

	}
	EShhKeys ShhKeys::operator [] (int index)
	{
		return mKeyList[index];
	}
	int ShhKeys::GetCount()
	{
		return mKeyList.size();
	}


// ================================= ShhKeyboard =======================================================
	ShhKeyboard::ShhKeyboard()
	{
		Reset();
	}
	void ShhKeyboard::Present()
	{
		memcpy(mKeyInfoBuff, mKeyInfo, sizeof(mKeyInfo));
		mKeysComplete = false;
	}
	EShhKeyState ShhKeyboard::GetKeyState(EShhKeys key)
	{
		size_t x = (unsigned int)key;
		const KeyInfo& state = getKeyInfoBuff(x);

		size_t move = x & 0x1f;
		KeyInfo mark = 1 << move;
		KeyInfo temp = state & mark;

		return (EShhKeyState)(temp >> move);
	}
	Keys ShhKeyboard::GetPressKeys()
	{
		if (!mKeysComplete)
		{
			for (int i = 0; i < KeyInfoCount; ++i)
			{			
				const KeyInfo& state = mKeyInfoBuff[i];
				if (state)
				{
					size_t head = (size_t)(i << KeyInfo_Move);
					for (int j = 0; j < KeyInfoInBit; ++j)
					{
						size_t mark = 1 << j;
						size_t temp = state & mark;
						if (temp)
						{
							EShhKeys key = (EShhKeys)(head | (size_t)j);
							mPressKeys.AddKey(key);
						}
					}
				}
			}	
			mKeysComplete = true;
		}
		return  Keys(new ShhKeys(mPressKeys));
	}

	void ShhKeyboard::Reset()
	{
		n_memset(mKeyInfo, 0, sizeof(mKeyInfo));
		n_memset(mKeyInfoBuff, 0, sizeof(mKeyInfoBuff));
		mPressKeys.Clear();
		mKeysComplete = false;
	}
	bool ShhKeyboard::IsKeyPress(EShhKeys key)
	{
		return (EShhKS_Press == GetKeyState(key));
	}
	bool ShhKeyboard::IsKeyUp(EShhKeys key)
	{
		return (EShhKS_Release == GetKeyState(key));
	}

	void ShhKeyboard::SetKeyPress(EShhKeys key)
	{
		size_t x = (size_t)key;
		KeyInfo& state = getKeyInfo(x);

		unsigned int move = x & KeyInfo_Mark;
		KeyInfo mark = 1 << move;
		state |= mark;
	}
	void ShhKeyboard::SetKeyUp(EShhKeys key)
	{
		size_t x = (size_t)key;
		KeyInfo& state = getKeyInfo(x);

		size_t move = x & KeyInfo_Mark;
		KeyInfo mark = 1 << move;
		state &= (~mark);
	}
}