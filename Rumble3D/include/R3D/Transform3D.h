#pragma once
#include <R3D/Common/Precision.h>
#include <R3D/Common/Common.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace r3
{
	/**
	 * \brief Encapsulates translation and rotation and manipulation
	 * functions on them.
	 */
	class R3D_DECLSPEC Transform3D
	{
	public:
		/**
		 * \brief Transform3D constructor.
		 * \param position Initial position.
		 * \param rotation Initial rotation.
		 */
		explicit Transform3D(const glm::vec3& position = glm::vec3(0.0),
		                     const glm::mat3& rotation = glm::mat3(1));
		~Transform3D() = default;

		/** 
		 * \brief Set the current position. 
		 * \param position The new position.
		 */
		void setPosition(const glm::vec3& position);
		/** 
		 * \brief Set the current position. 
		 * \param x The x-component of the new position.
		 * \param y The y-component of the new position.
		 * \param z The z-component of the new position.
		 */
		void setPosition(real x, real y, real z);
		/** 
		 * \brief Get the current position. 
		 * \return The position.
		 */
		const glm::vec3& getPosition() const;

		/** 
		 * \brief Additively change the current position. 
		 * \param delta The summand.
		 */
		void translate(const glm::vec3& delta);
		/** 
		 * \brief Additively change the current position.
		 * \param x The x-component of the summand.
		 * \param y The y-component of the summand.
		 * \param z The z-component of the summand.
		 */
		void translate(real x, real y, real z);

		/**
		 * \brief Multiplicative change of the current rotation.
		 * \param rot The factor.
		 */
		void rotate(const glm::quat& rot);
		/** 
		 * \brief Multiplicative change of the current rotation.
		 * \param rot The factor.
		 */
		void rotate(const glm::mat3& rot);

		/** 
		 * \brief Set the current rotation. 
		 * \param w Rotation in radians.
		 * \param x The x-component of the axis.
		 * \param y The y-component of the axis.
		 * \param z The z-component of the axis.
		 */
		void setRotation(float w, float x, float y, float z);
		/** s
		 * \brief Set the current rotation. 
		 * \param orientation The new orientation.
		 */
		void setRotation(const glm::quat& orientation);
		/**
		 * \brief Set the current rotation.
		 * \param rot The new rotation.
		 */
		void setRotation(const glm::mat3& rot);
		/** 
		 * \brief Get the current rotation. 
		 * \return The rotation.
		 */
		glm::mat3 getRotationMat() const;

		/**
		 * \brief Get the current rotation.
		 * \return The rotation.
		 */
		const glm::quat& getRotation() const;

		/**
		 * Approximate rotation around a given axis for a specified duration. This function will
		 * produce wrong values for long durations.
		 * @param rotation
		 * @param duration The duration
		 */
		void updateOrientationByAngularVelocity(const glm::vec3& rotation, 
												real duration);

		/**
		 * \brief Convert a point into local body space.
		 * \param point The point to convert.
		 * \return The point in local body space.
		 */
		glm::vec3 getPointInLocalSpace(const glm::vec3& point) const;
		/**
		 * \brief Convert a point from local body space into world
		 * space.
		 * \param point A point in local body space.
		 * \return The converted point in world space.
		 */
		glm::vec3 getPointInWorldSpace(const glm::vec3& point) const;
		/**
		 * \brief Convert a direction from world space into local
		 * space.
		 * \param direction The direction in world space.
		 * \return The direction in local space.
		 */
		glm::vec3 getDirectionInLocalSpace(const glm::vec3& direction) const;
		/**
		 * \brief Convert a direction from local body space into
		 * world space.
		 * \param direction The direction in local body space.
		 * \return The direction in world space.
		 */
		glm::vec3 getDirectionInWorldSpace(const glm::vec3& direction) const;

		/**
		 * \brief Reset the transform to a given position and rotation.
		 */
		void reset(const glm::vec3& position = glm::vec3(0),
				   const glm::vec3& rotation = glm::vec3(0));

	private:
		glm::quat m_rotation;
		glm::vec3 m_position;
	};
}
