#pragma once
#include "Common/Common.h"
#include "Common/Precision.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace rum
{
	class R3D_DECLSPEC Transform3D
	{
	public:
		explicit Transform3D(const glm::vec3& position = glm::vec3(0.0),
							 const glm::mat3& rotation = glm::mat3(1));
		~Transform3D();

		/** Set the current position. */
		void setPosition(const glm::vec3& position);
		/** Set the current position. */
		void setPosition(real x, real y, real z);
		/** Get the current position. */
		const glm::vec3& getPosition() const;

		/** Set the current rotation. */
		void setRotation(const glm::quat& orientation);
		/** Get the current rotation. */
		const glm::mat3& getRotation() const;


		glm::vec3 getPointInLocalSpace(const glm::vec3 &point) const;
		glm::vec3 getPointInWorldSpace(const glm::vec3 &point) const;
		glm::vec3 getDirectionInLocalSpace(const glm::vec3 &direction) const;
		glm::vec3 getDirectionInWorldSpace(const glm::vec3 &direction) const;

	private:
		glm::mat3 m_rotation;
		glm::vec3 m_position;
	};
}
