#pragma once
#include "Keyboard.h"
#include "ShhWinCommDef.h"

namespace Shh{


#define Shh_MAX_KEY_BUFFER_COUNT 2
#define Shh_DEFAULT_KEY_BUFFER_LENGTH 16
#define Shh_KEY_COUNT 256
#define Shh_MAX_MOUSE_BUFFER_COUNT 2

#define KeyInfoCount 8
#define KeyInfoInBit 32
#define KeyInfo_Move 5
#define KeyInfo_Mark 0x1f
typedef UInt32 KeyInfo;

	class ShhKeys : public IKeys//SHH_WIN_API
	{
		friend class ShhKeyboard;
	public:		
		~ShhKeys();
		virtual EShhKeys operator [](int index);
		virtual bool FindKey(EShhKeys key);
		virtual int	GetCount();
	private:
		typedef std::vector<EShhKeys> KeyList;
		ShhKeys();
		ShhKeys(const KeyList& key_list);
		ShhKeys(int buff_size);
		void AddKey(EShhKeys key);	
		void Clear();		
		KeyList mKeyList;
	};
	inline void ShhKeys::AddKey(EShhKeys key)
	{
		mKeyList.push_back(key);
	}
	inline void ShhKeys::Clear()
	{
		mKeyList.clear();
	}
	class ShhKeyboard : public IKeyboard //SHH_WIN_API
	{
	public:
		ShhKeyboard();
		virtual EShhKeyState GetKeyState(EShhKeys key);
		virtual Keys GetPressKeys();
		virtual bool IsKeyPress(EShhKeys key);
		virtual bool IsKeyUp(EShhKeys key);		
		void Present();
		void SetKeyPress(EShhKeys key);
		void SetKeyUp(EShhKeys key);
		void Reset();
	private:
		KeyInfo& getKeyInfo(unsigned int key);
		const KeyInfo& getKeyInfo(unsigned int key) const;

		KeyInfo& getKeyInfoBuff(unsigned int key);
		const KeyInfo& getKeyInfoBuff(unsigned int key) const;

		KeyInfo mKeyInfo[KeyInfoCount];
		KeyInfo mKeyInfoBuff[KeyInfoCount];
		ShhKeys mPressKeys;
		bool mKeysComplete;

		//EShhKeyState mKeyStates[Shh_KEY_COUNT];//[Shh_MAX_KEY_BUFFER_COUNT]
		//ShhKeys mKeys[Shh_MAX_KEY_BUFFER_COUNT];
		//int mBackKeysIndex;					//后台缓冲索引

		//EShhKeyState (* mPresentKeyStates)[Shh_KEY_COUNT];		//前台缓冲
		//EShhKeyState (* mBackKeyStates)[Shh_KEY_COUNT];			//后台缓冲

		//ShhKeys* mPresentKeys;	//前台缓冲
		//ShhKeys* mBackKeys;		//后台缓冲
	};
	inline UInt32& ShhKeyboard::getKeyInfo(unsigned int key)
	{
		int index = key >> KeyInfo_Move;
		n_assert(index < 8);
		return mKeyInfo[index];
	}
	inline const UInt32& ShhKeyboard::getKeyInfo(unsigned int key) const
	{
		int index = key >> KeyInfo_Move;
		n_assert(index < 8);
		return mKeyInfo[index];
	}
	inline UInt32& ShhKeyboard::getKeyInfoBuff(unsigned int key)
	{
		int index = key >> KeyInfo_Move;
		n_assert(index < 8);
		return mKeyInfoBuff[index];
	}
	inline const UInt32& ShhKeyboard::getKeyInfoBuff(unsigned int key) const
	{
		int index = key >> KeyInfo_Move;
		n_assert(index < 8);
		return mKeyInfoBuff[index];
	}
}