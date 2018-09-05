#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	struct R3D_DECLSPEC PhysicsMaterialDef
	{
		static constexpr real s_defaultFriction = 0.0f;
		static constexpr real s_defaultRestitution = 1.0f;

		real m_friction{s_defaultFriction};
		real m_restitution{s_defaultRestitution};
	};

	class R3D_DECLSPEC PhysicsMaterial
	{
	public:
		explicit PhysicsMaterial();
		explicit PhysicsMaterial(const PhysicsMaterialDef& definition);
		PhysicsMaterial& operator=(const PhysicsMaterial&) = default;
		~PhysicsMaterial();

		void init(const PhysicsMaterialDef& definition);

		void setFriction(real friction);
		real getFriction() const;

		void setRestitution(real restitution);
		real getRestitution() const;

		const PhysicsMaterialDef& getMaterialDef() const;

	private:
		PhysicsMaterialDef m_mat;
	};
}