#pragma once
#include <functional>

namespace r3
{
	class RigidBody;

	/**
	 * \brief Callback, which gets executed, when two rigid bodies
	 * collide.
	 */
	class CollisionCallback
	{
	public:
		using Callback = std::function<void(RigidBody*, RigidBody*)>;

		explicit CollisionCallback(Callback callback = nullptr);
		~CollisionCallback();

		/** \brief Set the currently used callback function. */
		void setCallback(const Callback& callback);
		/** \brief Execute the underlying callback. */
		void execute(RigidBody* rb1, RigidBody* rb2);

	private:
		Callback m_callback{};
	};
}
