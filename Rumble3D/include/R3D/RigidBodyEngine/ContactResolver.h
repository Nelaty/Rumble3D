#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace rum
{
	class Contact;

	class R3D_DECLSPEC ContactResolver
	{
	public:
		/**
		* Creates a new contact resolver with the given number of iterations
		* per resolution call, and optional epsilon values.
		*/
		explicit ContactResolver(unsigned iterations,
								 real velocityEpsilon = real(0.01f),
								 real positionEpsilon = real(0.01f));

		/**
		* Creates a new contact resolver with the given number of iterations
		* for each kind of resolution, and optional epsilon values.
		*/
		ContactResolver(unsigned velocityIterations,
						unsigned positionIterations,
						real velocityEpsilon = real(0.01f),
						real positionEpsilon = real(0.01f));

		void setIterations(unsigned iterations);
		void setIterations(unsigned velocityIterations,
						   unsigned positionIterations);

		void setEpsilon(real velocityEpsilon,
						real positionEpsilon);

		void resolveContacts(Contact *contacts,
							 unsigned numContacts,
							 real timeDelta);

		void prepareContacts(Contact* contacts,
							 unsigned numContacts,
							 real timeDelta);

		void adjustVelocities(Contact *c,
							  unsigned numContacts,
							  real timeDelta);
		void adjustPositions(Contact *c,
							 unsigned numContacts,
							 real timeDelta);
		bool isValid() const;

	protected:
		/**
		* Holds the number of iterations to perform when resolving
		* velocity.
		*/
		unsigned m_velocityIterations;

		/**
		* Holds the number of iterations to perform when resolving
		* position.
		*/
		unsigned m_positionIterations;

		/**
		* To avoid instability velocities smaller
		* than this value are considered to be zero. Too small and the
		* simulation may be unstable, too large and the bodies may
		* interpenetrate visually. A good starting point is the default
		* of 0.01.
		*/
		real m_velocityEpsilon;

		/**
		* To avoid instability penetrations
		* smaller than this value are considered to be not interpenetrating.
		* Too small and the simulation may be unstable, too large and the
		* bodies may interpenetrate visually. A good starting point is
		* the default of0.01.
		*/
		real m_positionEpsilon;
		/**
		* Stores the number of velocity iterations used in the
		* last call to resolve contacts.
		*/
		unsigned m_velocityIterationsUsed;

		/**
		* Stores the number of position iterations used in the
		* last call to resolve contacts.
		*/
		unsigned m_positionIterationsUsed;

		/**
		* Keeps track of whether the internal settings are valid.
		*/
		bool m_validSettings;
		unsigned m_iterations;
	};

}

