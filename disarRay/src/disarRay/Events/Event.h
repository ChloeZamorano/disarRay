#pragma once

#include "drpch.h"

#include "DrayIntern.h"

namespace Dray
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyDown, KeyUp, KeyTyped,
		MouseButtonDown, MouseButtonUp, MouseMoved, MouseScrolled,
	};

	enum EventCategory
	{
		None		= 0,
		App			= BIT(0),
		Cycle		= BIT(1),
		Input		= BIT(2),
		Keyboard	= BIT(3),
		Mouse		= BIT(4),
		MouseButton = BIT(5),
	};

#define DRAY_EVENT_TYPE(type) \
	static EventType GetStaticType() { return EventType::##type; } \
	virtual EventType GetEventType() const override { return GetStaticType(); } \
	virtual const char* GetName() const override { return #type; }

#define DRAY_EVENT_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class DRAY_API Event
	{
		friend class EventDispatcher;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual str8 ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		bool Handled() const { return m_Handled; }

	private:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;
		
	public:
		EventDispatcher(Event& e) : m_Event(e) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator <<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
