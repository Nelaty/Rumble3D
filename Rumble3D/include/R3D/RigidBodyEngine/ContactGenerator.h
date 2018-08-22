#pragma once
#include "Contact.h"

namespace rum
{
	class ContactGenerator
	{
	public:
		virtual ~ContactGenerator();
		
		virtual unsigned addContact(Contact *contact, unsigned limit) const;

	protected:
		explicit ContactGenerator();
	};
}

