#include "drpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Dray
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
