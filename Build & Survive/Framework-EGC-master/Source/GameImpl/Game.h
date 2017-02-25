#pragma once
#include <Component/SimpleScene.h>
#include "LabCamera.h"

class Game : public SimpleScene
{
	public:
		Game();
		~Game();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix,int c) ;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		void SetLifes(float deltaTimeSeconds);
		void SetPlayerAndCamera();
		void SetTowers(float deltaTimeSeconds);
		void SetEnemies(float deltaTimeSeconds);
		void AddNewEnemies();
		void EnemyEscapedDetection();
		void TowerHitDetected();
		void TriggerPlayer(float deltaTimeSeconds);
		void PlayerHitDetected();
		void EnemyDeadAnimation(float deltaTimeSeconds);
		void PlayerDeadAnimation(float deltaTimeSeconds);
		void CreateMiniMap();

	protected:
		Laborator::Camera *camera;
		Laborator::Camera *camera2;
		glm::mat4 projectionMatrix;
		glm::mat4 projectionMatrix2;
		bool renderCameraTarget;
};
