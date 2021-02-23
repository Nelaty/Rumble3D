#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	/**
	 * \brief Construction information for a PhysicsMaterial
	 */
	struct R3D_DECLSPEC PhysicsMaterialDef
	{
		static constexpr real s_defaultFriction = 0.5f;
		static constexpr real s_defaultRestitution = 0.5f;

		real m_friction{s_defaultFriction};
		real m_restitution{s_defaultRestitution};
	};

	/**
	 * \brief Contains physical properties of a material.
	 */
	class R3D_DECLSPEC PhysicsMaterial
	{
	public:
		explicit PhysicsMaterial();
		/**
		 * \brief PhysicsMaterial constructor
		 * \param definition The construction information.
		 */
		explicit PhysicsMaterial(const PhysicsMaterialDef& definition);
		PhysicsMaterial& operator=(const PhysicsMaterial&) = default;
		~PhysicsMaterial() = default;

		/**
		 * \brief Initialize all attributes.
		 * \param definition The construction information.
		 */
		void init(const PhysicsMaterialDef& definition);

		/**
		 * \brief Set the friction coefficient.
		 * \param friction The new friction coefficient.
		 */
		void setFriction(real friction);
		/**
		 * \brief Get the current friction coefficient.
		 * \return The friction coefficient.
		 */
		real getFriction() const;

		/**
		 * \brief Set the current restitution coefficient.
		 * \param restitution The new restitution coefficient.
		 */
		void setRestitution(real restitution);
		/**
		 * \brief Get the current restitution coefficient.
		 * \return The restitution coefficient.
		 */
		real getRestitution() const;

		/**
		 * \brief Get a collection of all attributes.
		 * \return The material definition.
		 */
		const PhysicsMaterialDef& getMaterialDef() const;

	private:
		PhysicsMaterialDef m_mat;
	};
}