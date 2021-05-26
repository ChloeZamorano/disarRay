#include "drpch.h"
#include "DrayApp.h"

#include "Input.h"
#include "Renderer/Renderer.h"

namespace Dray
{
	DrayApp* DrayApp::s_Instance = nullptr;

	DrayApp::DrayApp()
	{
		DRAY_ENGINE_ASSERT(!s_Instance,
			"DrayApp is a singleton, cannot have more than one per instance!")
			s_Instance = this;



		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(DRAY_BIND_FN(DrayApp::OnEvent));



		Input::MakePoller();



		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);



		m_VAO.reset(VertexArray::Create());


		f32 verts[7 * 4] =
		{
			-0.8f,  0.8f, 0.0f,		0.80f, 0.25f, 0.25f, 1.0f,
			 0.8f,  0.8f, 0.0f,		0.25f, 0.80f, 0.25f, 1.0f,
			 0.8f, -0.8f, 0.0f,		0.25f, 0.25f, 0.80f, 1.0f,
			-0.8f, -0.8f, 0.0f,		0.80f, 0.80f, 0.80f, 1.0f,
		};

		std::shared_ptr<VertexBuffer> VBO;
		VBO.reset(VertexBuffer::Create(verts, sizeof(verts)));

		VBO->SetLayout(VertexLayout{
			{ ShaderDataType::Float3, "a_Pos" },
			{ ShaderDataType::Float4, "a_Col" },
			});

		m_VAO->AddVertexBuffer(VBO);


		u32 quads[4] =
		{
			0, 1, 2, 3
		};

		std::shared_ptr<IndexBuffer> IBO;
		IBO.reset(IndexBuffer::Create(quads, sizeof(quads) / sizeof(u32)));

		m_VAO->SetIndexBuffer(IBO);


		str8 vertSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Pos;
			layout(location = 1) in vec4 a_Col;

			out vec4 v_Col;

			void main()
			{
				gl_Position = vec4(a_Pos, 1);
				v_Col = a_Col;
			}
		)";
		str8 pixelSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 col;

			in vec4 v_Col;

			void main()
			{
				col = vec4(.8, .075, .12, 1);
				col = v_Col;
			}
		)";

		m_SO.reset(new Shader(vertSrc, pixelSrc));
	}

	DrayApp::~DrayApp() {}

	void DrayApp::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void DrayApp::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void DrayApp::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(DRAY_BIND_FN(DrayApp::OnWindowClose));

		for (LayerStack::StackIt it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
	}

	const char* coomer[] =
	{
		"Hello, Gordon!",
		"I've been outside Black Mesa, Dr. Freeman. There's nothing there. But YOU. I know there's a world in your dreams. AND I NEED TO GO THERE!!! ",
		"Gordon? If you woke up one day, and realized everything around you was a lie...was FAKE...What would you do? ",
		"Look Gordon! Ropes! We can use these to help with large pits! ",
		"HELP ME GORDON! ",
		"Gordon...Every time you go to sleep I can feel my body TORN apart...ATOM by ATOM...It's agonizing Gordon...I've SEEN outside Black Mesa, Gordon...There's NOTHING...But I know YOU. There's a world outside here, Gordon. AND I NEED YOU TO TAKE ME THERE...",
		"I did have a wife, but they took her in the divorce. ",
		"You're not a war criminal if there's no more military to judge you. ",
		"Gordon, I'm tired. ",
		"Gordon, titty boob huge fuck. ",
		"He was my best friend...but he owed me seven dollars! "
	};

	void DrayApp::Run()
	{
		while (m_Running)
		{
			DrawStage1();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			DrawStage2();
		}
	}

	void DrayApp::DrawStage1()
	{
		RenderCommand::SetClearColor(.125f, .075f, .125f);
		RenderCommand::Clear();

		m_SO->Bind();
		Renderer::Submit(m_VAO);
	}

	void DrayApp::DrawStage2()
	{
		m_Window->OnUpdate();
	}

	bool DrayApp::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
