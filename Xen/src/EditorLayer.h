#pragma once

#include <Xenode.h>
#include "panel/SceneHierarchyPanel.h"
#include "panel/PropertiesPanel.h"

#include "core/scene/SceneSerializer.h"
#include "core/scene/EditorCameraController.h"

class EditorLayer : public Xen::Layer
{
public:
	enum class GizmoOperation {
		Translate,
		Rotate2D, Rotate3D,
		Scale
	};


	EditorLayer();
	virtual ~EditorLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(double timestep) override;
	void OnImGuiUpdate() override;
	void OnFixedUpdate() override;

	void OnWindowResizeEvent(Xen::WindowResizeEvent& event) override;

	void OnMouseScrollEvent(Xen::MouseScrollEvent& event) override;
	void OnMouseMoveEvent(Xen::MouseMoveEvent& event) override;
	void OnMouseButtonPressEvent(Xen::MouseButtonPressEvent& event) override;
	void OnMouseButtonReleaseEvent(Xen::MouseButtonReleaseEvent& event) override;
	
	void OnKeyPressEvent(Xen::KeyPressEvent& event) override;

private:
	double m_Timestep;

	uint32_t viewport_framebuffer_width = 1, viewport_framebuffer_height = 1;

	Xen::Ref<Xen::FrameBuffer> m_ViewportFrameBuffer;
	Xen::Ref<Xen::Scene> m_ActiveScene;

	SceneHierarchyPanel hier_panel;
	PropertiesPanel prop_panel; 

	GizmoOperation m_GizmoOperation;

	bool m_IsMouseHoveredOnViewport;

	// Editor Camera Stuff------------------------------------
	Xen::Ref<Xen::Camera> m_EditorCamera;
	Xen::EditorCameraController m_EditorCameraController;

private:
	Xen::Vec3 GetCameraFrontDir();
};