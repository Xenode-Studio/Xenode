#pragma once

#include <core/renderer/Structs.h>
#include <core/renderer/Texture.h>
#include <core/renderer/Camera.h>
#include "ScriptableEntity.h"
#include <pch/pch>

namespace Xen {
	namespace Component {

		struct Tag
		{
			std::string tag;

			Tag() : tag("Unnamed") {}
			Tag(const std::string& string) : tag(string) {}
			Tag(const Tag& tag) = default;
		};

		struct Transform
		{
			Vec3 position;
			Vec3 rotation = 0.0f;
			Vec3 scale = 1.0f;

			Transform() = default;
			Transform(const Transform& transform) = default;

			Transform(const Vec3& position, const Vec3& rotation, const Vec3& scale) : position(position), rotation(rotation), scale(scale) {}
		};

		struct SpriteRenderer
		{
			Color color;
			Ref<Texture2D> texture;

			SpriteRenderer() = default;
			SpriteRenderer(const SpriteRenderer& transform) = default;

			SpriteRenderer(const Color& color) : color(color), texture(nullptr) {}
			SpriteRenderer(const Color& color, Ref<Texture2D> texture) : color(color), texture(texture) {}
		};

		struct CameraComp
		{
			Ref<Camera> camera;
			bool is_primary_camera = 1;
			bool is_resizable = 1;

			CameraComp() = default;
			CameraComp(const CameraComp& transform) = default;

			CameraComp(Xen::CameraType type, float viewport_width, float viewport_height) : camera(std::make_shared<Camera>(type, viewport_width, viewport_height)) {}

			CameraComp(const Ref<Camera>& camera) : camera(camera) {}
		};

		struct NativeScript
		{
			ScriptableEntity* scriptable_entity_instance = nullptr;

			ScriptableEntity* (*InstantiateScript)();
			void (*DestroyScript)(NativeScript*);

			Entity entity;

			template<typename T>
			void Bind(Entity e)
			{
				entity = e;
				InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
				DestroyScript = [](NativeScript* script) { delete script->scriptable_entity_instance; script->scriptable_entity_instance = nullptr; };
			}
		};
	}
}