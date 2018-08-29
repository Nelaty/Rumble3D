#pragma once
#include "R3D/Common/Common.h"

namespace rum
{
	class Contact;

	class R3D_DECLSPEC ContactGenerator
	{
	public:
		virtual ~ContactGenerator();
		
		virtual unsigned addContact(Contact *contact, unsigned limit) const;

	protected:
		explicit ContactGenerator();
	};
}

