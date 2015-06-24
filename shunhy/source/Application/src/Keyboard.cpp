#include <vector>
#include <algorithm>
#include "Keyboard.h"
#include "Memory.h"
namespace Shh{

// ================================= Keyboard =======================================================
	const size_t Keyboard::KeyStateMove = 5;
	const KeyStates Keyboard::KeyStateMark = 0x1f;
	Keyboard::Keyboard()
	{
	}
	Keyboard::~Keyboard()
	{

	}
	EKeyState Keyboard::GetKeyState(EKeys key) const
	{
		size_t x = (unsigned int)key;
		const KeyStates& state = getKeyStates(x);

		size_t move = x & 0x1f;
		KeyStates mark = 1 << move;
		KeyStates temp = state & mark;

		return (EKeyState)(temp >> move);
	}
	//Keys Keyboard::GetPressKeys()
	//{
	//	if (!mKeysComplete)
	//	{
	//		for (int i = 0; i < KeyInfoCount; ++i)
	//		{			
	//			const KeyInfo& state = mKeyInfoBuff[i];
	//			if (state)
	//			{
	//				size_t head = (size_t)(i << KeyInfo_Move);
	//				for (int j = 0; j < KeyInfoInBit; ++j)
	//				{
	//					size_t mark = 1 << j;
	//					size_t temp = state & mark;
	//					if (temp)
	//					{
	//						EKeys key = (EKeys)(head | (size_t)j);
	//						mPressKeys.AddKey(key);
	//					}
	//				}
	//			}
	//		}	
	//		mKeysComplete = true;
	//	}
	//	return  Keys(new Keys(mPressKeys));
	//}

	bool Keyboard::IsKeyPress(EKeys key) const
	{
		return (EKS_Pressed == GetKeyState(key));
	}
	bool Keyboard::IsKeyRelease(EKeys key) const
	{
		return (EKS_Released == GetKeyState(key));
	}

	KeyStates& Keyboard::getKeyStates(size_t key)
	{
		int index = key >> KeyStateMove;//除以32
		shh_assert(index < 8);
		return mKeyInfo[index];
	}
	const KeyStates& Keyboard::getKeyStates(size_t key) const
	{
		int index = key >> KeyStateMove;//除以32
		shh_assert(index < 8);
		return mKeyInfo[index];
	}
}