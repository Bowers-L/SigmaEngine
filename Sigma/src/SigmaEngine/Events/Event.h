#pragma once

#include "SigmaEngine/Util/BaseUtil.h"

#include "SigmaEngine//Core/Core.h"
#include <string>

namespace SigmaEngine {
	namespace Events {
		enum class EventType 
		{
			None = 0,
			WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
			AppTick, AppUpdate, AppRender,
			KeyPressed, KeyReleased, KeyTyped,
			MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
		};

		enum EventCategory
		{
			None = 0,
			EventCategoryApplication = BIT(0),
			EventCategoryInput = BIT(1),
			EventCategoryKeyboard = BIT(2),
			EventCategoryMouse = BIT(3),
			EventCategoryMouseButton = BIT(4)
		};

		//Event Macros: Automatically defines functions in derived classes based on type and category.
		#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::type; }\
										virtual EventType GetEventType() const override { return GetStaticType(); }\
										virtual const char* GetName() const override { return #type; }

		#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

		class SIGMA_API Event
		{
		public:
			virtual EventType GetEventType() const = 0;
			virtual const char* GetName() const = 0;
			virtual int GetCategoryFlags() const = 0;
			virtual std::string ToString() const { return GetName(); }

			inline bool IsInCategory(EventCategory category) {
				return GetCategoryFlags() & category;	//Bitwise AND
			}
		protected:
			bool m_Handled = false;
		};


	}
}