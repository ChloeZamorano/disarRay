#pragma once

#include "Event.h"

namespace Dray
{
	class DRAY_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(f32 x, f32 y) :
			m_MouseX(x), m_MouseY(y) {}

		inline f32 GetX() const { return m_MouseX; }
		inline f32 GetY() const { return m_MouseY; }

		str8 ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		DRAY_EVENT_TYPE(MouseMoved)
		DRAY_EVENT_CATEGORY(Mouse | Input)

	private:
		f32 m_MouseX, m_MouseY;
	};

	class DRAY_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(f32 xOff, f32 yOff) :
			m_XOffset(xOff), m_YOffset(yOff) {}

		str8 ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << "(" << m_XOffset << ", " << m_YOffset << ")";
			return ss.str();
		}

		inline f32 GetXOffset() const { return m_XOffset; }
		inline f32 GetYOffset() const { return m_YOffset; }

		DRAY_EVENT_TYPE(MouseScrolled)
		DRAY_EVENT_CATEGORY(Mouse | Input)

	private:
		f32 m_XOffset, m_YOffset;
	};

	class DRAY_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		DRAY_EVENT_CATEGORY(Mouse | Input)

	protected:
		MouseButtonEvent(i32 btn) :
			m_Button(btn) {}

		i32 m_Button;
	};

	class DRAY_API MouseButtonDownEvent : public MouseButtonEvent
	{
	public:
		MouseButtonDownEvent(i32 btn) :
			MouseButtonEvent(btn) {}

		str8 ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonDownEvent: " << m_Button;
			return ss.str();
		}

		DRAY_EVENT_TYPE(MouseButtonDown)
	};

	class DRAY_API MouseButtonUpEvent : public MouseButtonEvent
	{
	public:
		MouseButtonUpEvent(i32 btn) :
			MouseButtonEvent(btn) {}

		str8 ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonUpEvent: " << m_Button;
			return ss.str();
		}

		DRAY_EVENT_TYPE(MouseButtonUp)
	};
}
