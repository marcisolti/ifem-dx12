#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include "d3dx12.h"
#include <memory>
#include <vector>
#include <string>

#include <wrl/client.h>
#include <dxgi1_5.h>

template<typename T>
using com_ptr = Microsoft::WRL::ComPtr<T>;

// TODO it doesnt work with templated classes :c
#define GG_CLASS(T) GG_DECL(T) \
class T : public Egg::Shared<T>, public std::enable_shared_from_this<T> {

#define GG_SUBCLASS(T, BASE) GG_DECL(T) \
class T : public BASE, public Egg::Shared<T> {\
public:\
	using Egg::Shared<T>::Create;\
	using Egg::Shared<T>::GetShared;\
	using Egg::Shared<T>::P;\
private:

#define GG_ENDCLASS };

#define GG_DECL(T) class T;\
using T##P = std::shared_ptr<T>;\
using T##W = std::weak_ptr<T>; \
using T##A = Egg::Shared<T>::A;

namespace Egg {

	template<class T>
	class Shared {
	public:
		template<typename... Args>
		inline static std::shared_ptr<T> Create(Args&&... args)
		{
			struct EnableMakeShared : public T {
				EnableMakeShared(Args&&...args) :T(std::forward<Args>(args)...) {}
			};
			return std::make_shared<EnableMakeShared>(std::forward<Args>(args)...);
		}
		std::shared_ptr<T> GetShared() {
			return std::dynamic_pointer_cast<T>(((T*)this)->shared_from_this());
		}

		using P = std::shared_ptr<T>;
		using W = std::weak_ptr<T>;

		class access_ptr {
			T* ptr_;
		public:
			access_ptr(P const& other) :ptr_(other.get()) {}
			/// Dereference the pointer for ptr->m usage
			constexpr T* operator->() const noexcept { return ptr_; }
			/// Allow if(ptr) to test for null
			constexpr explicit operator bool() const noexcept {
				return ptr_ != nullptr;
			}
			/// Convert to a raw pointer where necessary
			constexpr explicit operator T* () const noexcept {
				return ptr_;
			}
			/// !ptr is true iff ptr is null
			constexpr bool operator!() const noexcept {
				return !ptr_;
			}
		};

		using A = access_ptr;
	};

	namespace Internal {

		void Assert(bool trueMeansOk, const char * msgOnFail, ...);

		class HResultTester {
		public:
			const char * message;
			const char * file;
			const int line;
			va_list args;

			HResultTester(const char * msg, const char * file, int line, ...);

			void operator<<(HRESULT hr);
		};

	}

}


// the message is assumed to be a printf format string, the variadic arguments assumed to be the arguments for that format
#define ASSERT(trueMeansOk, msgOnFail, ...) Egg::Internal::Assert(trueMeansOk, msgOnFail, __VA_ARGS__)

#define DX_API(msg, ...) Egg::Internal::HResultTester(msg, __FILE__, __LINE__, __VA_ARGS__) <<

