#include "FirstPerson.h"

using namespace Egg;
using namespace Egg::Math;

#include <iostream>
#include <Xinput.h>
#define INPUT_DEADZONE 5000

Cam::FirstPerson::FirstPerson()
{
	position = Float3::UnitZ * -10.0;
	ahead = Float3::UnitZ;
	right = Float3::UnitX;
	yaw = 0.0;
	pitch = 0.0;

	fov = 1.15f;
	nearPlane = 0.5f;
	farPlane = 100.0f;
	SetAspect(1.33f);

	viewMatrix = Float4x4::View(position, ahead, Float3::UnitY);
	rayDirMatrix = (Float4x4::View(Float3::Zero, ahead, Float3::UnitY) * projMatrix).Invert();

	speed = 5.0f;

	lastMousePos = Int2::Zero;
	mouseDelta = Float2::Zero;

	wPressed = false;
	aPressed = false;
	sPressed = false;
	dPressed = false;
	qPressed = false;
	ePressed = false;
}

Cam::FirstPerson::P Cam::FirstPerson::SetView(Egg::Math::Float3 position, Egg::Math::Float3 ahead)
{
	this->position = position;
	this->ahead =    ahead;
	UpdateView();
	return GetShared();
}

Cam::FirstPerson::P Cam::FirstPerson::SetProj(float fov, float aspect, float nearPlane, float farPlane)
{
	this->fov = fov;
	this->aspect = aspect;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	return GetShared();
}

Cam::FirstPerson::P Cam::FirstPerson::SetSpeed(float speed)
{
	this->speed = speed;
	return GetShared();
}

const Float3& Cam::FirstPerson::GetEyePosition()
{
	return position;
}

const Float3& Cam::FirstPerson::GetAhead()
{
	return ahead;
}

const Float4x4& Cam::FirstPerson::GetRayDirMatrix()
{
	return rayDirMatrix;
}

const Float4x4& Cam::FirstPerson::GetViewMatrix()
{
	return viewMatrix;
}

const Float4x4& Cam::FirstPerson::GetProjMatrix()
{
	return projMatrix;
}

void Cam::FirstPerson::UpdateView()
{
	viewMatrix = Float4x4::View(position, ahead, Float3::UnitY);
	rayDirMatrix = (Float4x4::View(Float3::Zero, ahead, Float3::UnitY) * projMatrix).Invert();

	right = Float3::UnitY.Cross(ahead).Normalize();
	yaw = atan2f( ahead.x, ahead.z );
	pitch = -atan2f( ahead.y, ahead.xz.Length() );
}

void Cam::FirstPerson::UpdateProj()
{
	projMatrix = Float4x4::Proj(fov, aspect, nearPlane, farPlane);
}

void Cam::FirstPerson::Animate(double dt)
{

	if(wPressed)
		position += ahead * (shiftPressed?speed*5.0:speed) * dt;
	if(sPressed)
		position -= ahead * (shiftPressed?speed*5.0:speed) * dt;
	if(aPressed)
		position -= right * (shiftPressed?speed*5.0:speed) * dt;
	if(dPressed)
		position += right * (shiftPressed?speed*5.0:speed) * dt;
	if(qPressed)
		position -= Float3(0,1,0) * (shiftPressed?speed*5.0:speed) * dt;
	if(ePressed)
		position += Float3(0,1,0) * (shiftPressed?speed*5.0:speed) * dt;

	DWORD dwResult;
	DWORD cindex;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			// Controller is connected
			cindex = i;
		}
		else
		{
			// Controller is not connected
		}
	}
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	dwResult = XInputGetState(cindex, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected

		std::vector<Float2> T
		{
			{ (float)state.Gamepad.sThumbLX, (float)state.Gamepad.sThumbLY },
			{ (float)state.Gamepad.sThumbRX, (float)state.Gamepad.sThumbRY }
		};


		double nmagnitude[] = { 0,0 };
		for (int i = 0; i < T.size(); ++i)
		{
			//determine how far the controller is pushed
			float magnitude = std::sqrt(T[i].x * T[i].x+ T[i].y* T[i].y);
			//std::cout << magnitude << ' ';


			//check if the controller is outside a circular dead zone
			if (magnitude > INPUT_DEADZONE)
			{
				//clip the magnitude at its expected maximum value
				if (magnitude > 32767) magnitude = 32767;

				//adjust magnitude relative to the end of the dead zone
				magnitude -= INPUT_DEADZONE;

				//optionally normalize the magnitude with respect to its expected range
				//giving a magnitude value of 0.0 to 1.0
				nmagnitude[i] = magnitude / (32767 - INPUT_DEADZONE);
			}
			else //if the controller is in the deadzone zero out the magnitude
			{
				magnitude = 0.0;
				nmagnitude[i] = 0.0;
			}
		}
		//std::cout << '\n';

		float RT = (float)state.Gamepad.bRightTrigger / 255;
		float LT = (float)state.Gamepad.bLeftTrigger / 255;
		float eps = 0.15;
		if (RT > eps)
			position += Float3{ 0, 1, 0 } * RT/10;
		if (LT > eps)
			position -= Float3{ 0, 1, 0 } * LT/10;

		//std::cout << T[0].x << ',' << T[0].y << ';' << T[1].x << ',' << T[1].y << '\n';
		
		// man! 
		for (int i = 0; i < T.size(); ++i)
		{
			if (std::abs(T[i].x) > 0.001 && std::abs(T[i].x) > 0.001) 
			{
				T[i] = T[i].Normalize();
			}
			else
			{
				T[i] = { 0,0 };
			}
		}
		
		position += (right * T[0].x + ahead * T[0].y) * nmagnitude[0] / 10;

		yaw += T[1].x   * nmagnitude[1] / 100;
		pitch -= T[1].y * nmagnitude[1] / 100;
	}
	else
	{
		// Controller is not connected
	}

	yaw += mouseDelta.x / 100;
	pitch += mouseDelta.y / 100;

	pitch = Float1(pitch).Clamp(-3.14 / 2, +3.14 / 2).x;
	mouseDelta = Float2::Zero;


	ahead = Float3(sin(yaw)*cos(pitch), -sin(pitch), cos(yaw)*cos(pitch) );

	UpdateView();
}

void Cam::FirstPerson::ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_KEYDOWN)
	{
		if(wParam == 'W')
			wPressed = true;
		else if(wParam == 'A')
			aPressed = true;
		else if(wParam == 'S')
			sPressed = true;
		else if(wParam == 'D')
			dPressed = true;
		else if(wParam == 'Q')
			qPressed = true;
		else if(wParam == 'E')
			ePressed = true;
		else if(wParam == VK_SHIFT)
			shiftPressed = true;
	}
	else if(uMsg == WM_KEYUP)
	{
		if(wParam == 'W')
			wPressed = false;
		else if(wParam == 'A')
			aPressed = false;
		else if(wParam == 'S')
			sPressed = false;
		else if(wParam == 'D')
			dPressed = false;
		else if(wParam == 'Q')
			qPressed = false;
		else if(wParam == 'E')
			ePressed = false;
		else if(wParam == VK_SHIFT)
			shiftPressed = false;
		else if(wParam == VK_ADD)
			speed *= 2;
		else if(wParam == VK_SUBTRACT)
			speed *= 0.5;
	}
	else if(uMsg == WM_KILLFOCUS)
	{
		wPressed = false;
		aPressed = false;
		sPressed = false;
		dPressed = false;
		qPressed = false;
		ePressed = false;
		shiftPressed = false;
	}
	
	else if(uMsg == WM_RBUTTONDOWN)
	{
		lastMousePos = Int2( LOWORD(lParam), HIWORD(lParam));
	}
	else if(uMsg == WM_RBUTTONUP)
	{
		mouseDelta = Float2::Zero;
	}
	else if(uMsg == WM_MOUSEMOVE && (wParam & MK_RBUTTON))
	{
		Int2 mousePos( LOWORD(lParam), HIWORD(lParam));
		mouseDelta = Float2(mousePos.x - lastMousePos.x,
			mousePos.y - lastMousePos.y);

		lastMousePos = mousePos;
	}
	
}

void Cam::FirstPerson::SetAspect(float aspect)
{
	this->aspect = aspect;
	UpdateProj();
}