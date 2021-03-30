#pragma once
#include "../Math/Math.h"
#include "../Common.h"

namespace Egg { namespace Cam {

	/// Basic camera interface, to be implemented by camera type classes.
	GG_CLASS(Base)
	public:

		/// Returns eye position.
		virtual const Egg::Math::Float3& GetEyePosition()=0;
		/// Returns the ahead vector.
		virtual const Egg::Math::Float3& GetAhead()=0;
		/// Returns the ndc-to-world-view-direction matrix to be used in shaders.
		virtual const Egg::Math::Float4x4& GetRayDirMatrix()=0;
		/// Returns view matrix to be used in shaders.
		virtual const Egg::Math::Float4x4& GetViewMatrix()=0;
		/// Returns projection matrix to be used in shaders.
		virtual const Egg::Math::Float4x4& GetProjMatrix()=0;

		/// Moves camera. To be implemented if the camera has its own animation mechanism.
		virtual void Animate(double dt){}

		virtual void ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){}

		virtual void SetAspect(float aspect)=0;
	GG_ENDCLASS

}}