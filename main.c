#include<stdio.h>
#include<math.h>

#include"ACE/awsscool3dengine.h"

//Big TODO s:
//		* Fix weird warping at high vertical angles.
//		* .obj file loading?

//Current TODO s:
//		* Assimp?

//Trying to figure out the current structure of ace:
//
//	  ACE:|-Window*.					<- ACEInit.
//		|-Camera*.						<- ACEUseCamera.
//			|-Dir, Pos.					<- ACEMoveCam. (TODO)
//		|-Scene*.						<- ACEUseScene.
//			|-DefaultShader.			<- ACEMakeSceneEx();
//			|-Objects**.				<- ACEAddObject.
//				|-Materiel.				<- obj.Materiel = _.
//				|-Vertices.				<- ACEMake___Object();
//				|-Model.				<- Mat4 utils.

int main(int argc, char* argv[]){
	ACEInit(400, 400);
	ACELockMouse();

	ACEScene Scene = ACEMakeScene(0.2, 0.5, 0.9, 5);
	ACEUseScene(&Scene);

	ACEObject b = ACEMakePrimitive(ACECUBE, &Scene);

	b.Materiel = ACEMakeColorMateriel(0.2, 0.6, 0.9, &Scene);

	ACEAddObject(&b, &Scene);

	ACECamera cam = ACEMakeCamera((Vec3){0, 0, 0}, (Vec3){0, 0, 1}, CreateProjMat4(0.1, 100, 0.1, 0.1));
	ACEUseCamera(&cam);

	Mat4Trans(&b.Model, 0, 0,-1);


	//ACERemoveObject(&b, &Scene);

	Vec2 PrevMPos = ACEMousePos();
	const float MSens = 0.01,
				CamSpeed = 0.02;
	float yaw = 0, pitch = 0;
	while(!ACEShouldQuit()){
		ACERender();

		Vec2 CurMPos = ACEMousePos();

		float dx = CurMPos.x - PrevMPos.x;
		float dy = CurMPos.y - PrevMPos.y;

		PrevMPos = CurMPos;
		
		yaw += dx*MSens;
		pitch += dy*MSens;

		pitch = fmax(fmin(pitch, 1.57), -1.57);

		cam.Dir.x = cos(yaw)*cos(pitch);
		cam.Dir.y = sin(pitch);
		cam.Dir.z = sin(yaw)*cos(pitch);


		if(ACEIsKeyDown(GLFW_KEY_W))
			cam.Pos = Vec3AddVec3(cam.Pos, Vec3MultFloat(cam.Dir, CamSpeed));
		if(ACEIsKeyDown(GLFW_KEY_S))
			cam.Pos = Vec3AddVec3(cam.Pos, Vec3MultFloat(cam.Dir,-CamSpeed));
	}
	ACEQuit();
	return 0;
}
