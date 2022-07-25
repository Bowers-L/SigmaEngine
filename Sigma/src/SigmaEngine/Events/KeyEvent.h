#pragma once

#include "Event.h"
#include "KeyCode.h"

#include <sstream>

namespace SigmaEngine {
	namespace Events {
		class KeyEvent : public Event {
		public:
			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryMouse);

			KeyCode GetKeyCode() const { return m_KeyCode; }
		protected:
			KeyEvent(KeyCode keyCode) : m_KeyCode(keyCode) {}
			KeyCode m_KeyCode;
		};

		class KeyPressedEvent : public KeyEvent {
		public:
			KeyPressedEvent(const KeyCode keyCode, bool isRepeat = false) :
				KeyEvent(keyCode), m_IsRepeat(isRepeat) {}

			EVENT_CLASS_TYPE(KeyPressed)

			bool isRepeat() const { return m_IsRepeat; }

			std::string ToString() const override {
				std::stringstream ss;
				ss << "Key Pressed Event: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
				return ss.str();
			}
		private:
			bool m_IsRepeat;
		};

		class KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(const KeyCode keycode)
				: KeyEvent(keycode) {}

			EVENT_CLASS_TYPE(KeyReleased)

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyReleasedEvent: " << m_KeyCode;
				return ss.str();
			}
		};

		class KeyTypedEvent : public KeyEvent
		{
		public:
			KeyTypedEvent(const KeyCode keycode)
				: KeyEvent(keycode) {}

			EVENT_CLASS_TYPE(KeyTyped)

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyTypedEvent: " << m_KeyCode;
				return ss.str();
			}
		};
	}
}