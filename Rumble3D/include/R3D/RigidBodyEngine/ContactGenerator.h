#pragma once
#include "Contact.h"

namespace rum
{
	class ContactGenerator
	{
	public:
		virtual unsigned addContact(Contact *contact, unsigned limit) const = 0;
	};

}

