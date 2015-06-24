#ifndef __DELEGATE_H__
#define __DELEGATE_H__
#include "CoreDef.h"
#include <list>
#include <typeinfo>

namespace Shh
{

	namespace delegates
	{
		class _Shh_Export IDelegateUnlink
		{
		public:
			virtual ~IDelegateUnlink() { }

			IDelegateUnlink()
			{
				m_baseDelegateUnlink = this;
			}
			bool compare(IDelegateUnlink* _unlink) const
			{
				return m_baseDelegateUnlink == _unlink->m_baseDelegateUnlink;
			}

		private:
			IDelegateUnlink* m_baseDelegateUnlink;
		};

		inline IDelegateUnlink* GetDelegateUnlink(void* _base)
		{
			return 0;
		}
		inline IDelegateUnlink* GetDelegateUnlink(IDelegateUnlink* _base)
		{
			return _base;
		}
	};

#define SHH_SUFFIX       0
#define SHH_TEMPLATE
#define SHH_TEMPLATE_PARAMS
#define SHH_TEMPLATE_ARGS
#define SHH_T_TEMPLATE_PARAMS  <typename T>
#define SHH_T_TEMPLATE_ARGS <T>
#define SHH_PARAMS
#define SHH_ARGS
#define SHH_TYPENAME

#include "DelegateImplement.h"

#define SHH_SUFFIX       1
#define SHH_TEMPLATE	template
#define SHH_TEMPLATE_PARAMS  <typename TP1>
#define SHH_TEMPLATE_ARGS    <TP1>
#define SHH_T_TEMPLATE_PARAMS  <typename T, typename TP1>
#define SHH_T_TEMPLATE_ARGS    <T, TP1>
#define SHH_PARAMS       TP1 p1
#define SHH_ARGS         p1
#define SHH_TYPENAME     typename

#include "DelegateImplement.h"

#define SHH_SUFFIX       2
#define SHH_TEMPLATE	template
#define SHH_TEMPLATE_PARAMS  <typename TP1, typename TP2>
#define SHH_TEMPLATE_ARGS    <TP1, TP2>
#define SHH_T_TEMPLATE_PARAMS  <typename T, typename TP1, typename TP2>
#define SHH_T_TEMPLATE_ARGS    <T, TP1, TP2>
#define SHH_PARAMS       TP1 p1, TP2 p2
#define SHH_ARGS         p1, p2
#define SHH_TYPENAME     typename

#include "DelegateImplement.h"

#define SHH_SUFFIX       3
#define SHH_TEMPLATE	template
#define SHH_TEMPLATE_PARAMS  <typename TP1, typename TP2, typename TP3>
#define SHH_TEMPLATE_ARGS    <TP1, TP2, TP3>
#define SHH_T_TEMPLATE_PARAMS  <typename T, typename TP1, typename TP2, typename TP3>
#define SHH_T_TEMPLATE_ARGS    <T, TP1, TP2, TP3>
#define SHH_PARAMS       TP1 p1, TP2 p2, TP3 p3
#define SHH_ARGS         p1, p2, p3
#define SHH_TYPENAME     typename

#include "DelegateImplement.h"

#define SHH_SUFFIX       4
#define SHH_TEMPLATE	template
#define SHH_TEMPLATE_PARAMS  <typename TP1, typename TP2, typename TP3, typename TP4>
#define SHH_TEMPLATE_ARGS    <TP1, TP2, TP3, TP4>
#define SHH_T_TEMPLATE_PARAMS  <typename T, typename TP1, typename TP2, typename TP3, typename TP4>
#define SHH_T_TEMPLATE_ARGS    <T, TP1, TP2, TP3, TP4>
#define SHH_PARAMS       TP1 p1, TP2 p2, TP3 p3, TP4 p4
#define SHH_ARGS         p1, p2, p3, p4
#define SHH_TYPENAME     typename

#include "DelegateImplement.h"

#define SHH_SUFFIX       5
#define SHH_TEMPLATE	template
#define SHH_TEMPLATE_PARAMS  <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
#define SHH_TEMPLATE_ARGS    <TP1, TP2, TP3, TP4, TP5>
#define SHH_T_TEMPLATE_PARAMS  <typename T, typename TP1, typename TP2, typename TP3, typename TP4, typename TP5>
#define SHH_T_TEMPLATE_ARGS    <T, TP1, TP2, TP3, TP4, TP5>
#define SHH_PARAMS       TP1 p1, TP2 p2, TP3 p3, TP4 p4, TP5 p5
#define SHH_ARGS         p1, p2, p3, p4, p5
#define SHH_TYPENAME     typename

#include "DelegateImplement.h"

#define SHH_SUFFIX       6
#define SHH_TEMPLATE	template
#define SHH_TEMPLATE_PARAMS  <typename TP1, typename TP2, typename TP3, typename TP4, typename TP5, typename TP6>
#define SHH_TEMPLATE_ARGS    <TP1, TP2, TP3, TP4, TP5, TP6>
#define SHH_T_TEMPLATE_PARAMS  <typename T, typename TP1, typename TP2, typename TP3, typename TP4, typename TP5, typename TP6>
#define SHH_T_TEMPLATE_ARGS    <T, TP1, TP2, TP3, TP4, TP5, TP6>
#define SHH_PARAMS       TP1 p1, TP2 p2, TP3 p3, TP4 p4, TP5 p5, TP6 p6
#define SHH_ARGS         p1, p2, p3, p4, p5, p6
#define SHH_TYPENAME     typename

#include "DelegateImplement.h"


}

#endif // __DELEGATE_H__
