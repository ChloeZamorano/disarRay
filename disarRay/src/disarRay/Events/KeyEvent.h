#pragma once

#include "Event.h"

namespace Dray
{
	class DRAY_API KeyEvent : public Event
	{
	public:
		inline i32 GetKeyCode() const { return m_KeyCode; }

		DRAY_EVENT_CATEGORY(KeyboardEventCategory | InputEventCategory)

	protected:
		KeyEvent(i32 code) :
			m_KeyCode(code) {}

		i32 m_KeyCode;
	};

	class DRAY_API KeyDownEvent : public KeyEvent
	{
	public:
		KeyDownEvent(i32 code, i32 repeat) :
			KeyEvent(code), m_RepeatCount(repeat) {}

		inline i32 GetRepeatCount() const { return m_RepeatCount; }

		str8 ToString() const override
		{
			std::stringstream ss;
			ss << "KeyDownEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		DRAY_EVENT_TYPE(KeyDown)

	private:
		i32 m_RepeatCount;
	};

	class DRAY_API KeyUpEvent : public KeyEvent
	{
	public:
		KeyUpEvent(i32 code) :
			KeyEvent(code) {}

		str8 ToString() const override
		{
			std::stringstream ss;
			ss << "KeyUpEvent: " << m_KeyCode;
			return ss.str();
		}

		DRAY_EVENT_TYPE(KeyUp)
	};

	class DRAY_API KeyTypedEvent: public KeyEvent
	{
	public:
		KeyTypedEvent(i32 code) :
			KeyEvent(code) {}

		str8 ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		DRAY_EVENT_TYPE(KeyTyped)
	};
}
