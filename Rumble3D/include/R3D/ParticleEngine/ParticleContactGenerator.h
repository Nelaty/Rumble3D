#pragma once

namespace rum 
{
	class ParticleContact;

	class ParticleContactGenerator 
	{
	public:
		virtual ~ParticleContactGenerator();

		// Speichert in contact die Attribute für einen 
		// erkannten Kontakt. Der Zeiger contact zeigt 
		// auf das erste Element eines Arrays von Kontakten.
		// limit ist die Anzahl der beschreibbaren Elemente 
		// im Array.
		// Rückgabewert ist die Anzahl der Kontakte, die in 
		// den Array geschrieben wurden.
		virtual unsigned AddContact(ParticleContact* contact, unsigned int limit) const = 0;

	protected:
		explicit ParticleContactGenerator();
	};
}