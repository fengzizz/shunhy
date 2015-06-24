#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__
#include "InputEvent.h"
//#include <vector>
namespace Shh
{

	#define KeyInfoCount 8
	typedef uint32 KeyStates;


	//template  class _Shh_Export std::allocator<EKeys>;
	//template  class _Shh_Export std::vector<EKeys, std::allocator<EKeys> >;

	class _Shh_Export Keyboard
	{
	public:
		~Keyboard();
		EKeyState GetKeyState(EKeys key) const;
		bool IsKeyPress(EKeys key) const;
		bool IsKeyRelease(EKeys key) const;	
	protected:
		Keyboard();
		KeyStates& getKeyStates(size_t key);
		const KeyStates& getKeyStates(size_t key) const;

		KeyStates mKeyInfo[KeyInfoCount];		
		static const size_t KeyStateMove;
		static const KeyStates KeyStateMark;
	};
}

#endif // __KEYBOARD_H__
