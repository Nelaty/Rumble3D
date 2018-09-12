#pragma once
#include "R3D/Common/Common.h"

namespace r3
{
	class ContactOld;

	class R3D_DECLSPEC ContactGenerator
	{
	public:
		virtual ~ContactGenerator();
		
		virtual unsigned addContact(ContactOld *contact, unsigned limit) const;

	protected:
		explicit ContactGenerator();
	};
}

