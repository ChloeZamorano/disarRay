#pragma once

#include "Event.h"

namespace Dray
{
	class DRAY_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(u32 w, u32 h) :
			m_Width(w), m_Height(h) {}

		inline u32 GetWidth() const { return m_Width; }
		inline u32 GetHeight() const { return m_Height; }

		str8 ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		DRAY_EVENT_TYPE(WindowResize)
		DRAY_EVENT_CATEGORY(App)
	private:
		u32 m_Width, m_Height;
	};

	class DRAY_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		DRAY_EVENT_TYPE(WindowClose)
		DRAY_EVENT_CATEGORY(App)
	};

	class DRAY_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		DRAY_EVENT_TYPE(AppTick)
		DRAY_EVENT_CATEGORY(App)
	};

	class DRAY_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		DRAY_EVENT_TYPE(AppUpdate)
		DRAY_EVENT_CATEGORY(App)
	};

	class DRAY_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		DRAY_EVENT_TYPE(AppRender)
		DRAY_EVENT_CATEGORY(App)
	};
}