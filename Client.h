#pragma once
#include "Defines.h"
#include "LazyImporter.hpp"

namespace Client {

	uintptr_t ImageBase;
	uintptr_t StaticFindObjectOriginal;
	uintptr_t GetBoneMatrixOriginal;
	uintptr_t ProcessEventOriginal;
	uintptr_t LineOfSightToOriginal;

	static uintptr_t GetImageBase() {
		return (uintptr_t)safe_call(GetModuleHandleA)(0);
	}

	static void CreatConsole() {
		AllocConsole();
		static_cast<VOID>(freopen(("CONIN$"), ("r"), stdin));
		static_cast<VOID>(freopen(("CONOUT$"), ("w"), stdout));
		static_cast<VOID>(freopen(("CONOUT$"), ("w"), stderr));
	}

	namespace Settings
	{
		namespace Aimbot
		{
			bool MemoryAimbot = 0;
			bool StickySilent = 0;
			bool SilentAimbot = 0;

			bool AimbotSmooth = 0;
			bool FovCircle = 1;
			float FovCircleRadius = 120;
		};

		namespace Visuals
		{
			bool Box = 0;
			bool CornerBox = 1;
			bool Skeleton = 1;
			bool Distance = 1;
			bool Name = 0;
			bool Weapon = 0;
			bool Ammo = 0;
			bool AimLine = 1;
			bool VisibleCheck = 0;
			bool DevTest = 0;
		};

		namespace Exploits
		{
			bool ProjectileTeleport = 1;
			bool Spinbot = 0;
			bool VehicleFly = 0;
			bool InstantReload = 0;
			bool AimWhileReloading = 0;
		};
	};
};

void __forceinline AnsiToWide(char* inAnsi, wchar_t* outWide)
{
	int i = 0;
	for (; inAnsi[i] != '\0'; i++)
		outWide[i] = (wchar_t)(inAnsi)[i];
	outWide[i] = L'\0';
}

class sdk {
public:

	inline uintptr_t GetGameBase() {
		return *(uintptr_t*)(__readgsqword(0x60) + 0x10);
	}
	inline bool isValidPointer(uintptr_t address)
	{

		if (!(safe_call(IsBadWritePtr))((LPVOID)address, (UINT_PTR)8))
			return true;
		else
			return false;
	}

	inline uintptr_t PatternScan(uintptr_t pModuleBaseAddress, const char* sSignature, int pIndex, bool sRelativeAdr = false)
	{
		static auto patternToByte = [](const char* pattern) { auto bytes = std::vector<int>{}; const auto start = const_cast<char*>(pattern); const auto end = const_cast<char*>(pattern) + strlen(pattern); for (auto current = start; current < end; ++current) { if (*current == '?') { ++current; if (*current == '?') ++current; bytes.push_back(-1); } else bytes.push_back(strtoul((const char*)current, &current, 16)); } return bytes; };

		const auto dosHeader = (PIMAGE_DOS_HEADER)pModuleBaseAddress;
		const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)pModuleBaseAddress + dosHeader->e_lfanew);

		const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
		auto patternBytes = patternToByte(sSignature);
		const auto scanBytes = reinterpret_cast<std::uint8_t*>(pModuleBaseAddress);

		const auto s = patternBytes.size();
		const auto d = patternBytes.data();

		for (auto i = 0ul; i < sizeOfImage - s; ++i) {
			bool found = true; for (auto j = 0ul; j < s; ++j) { if (scanBytes[i + j] != d[j] && d[j] != -1) { found = false; break; } }
			if (found)
			{
				if (sRelativeAdr)
				{
					return ((uintptr_t)((UINT_PTR)(reinterpret_cast<uintptr_t>(&scanBytes[i])) + *(PINT)((UINT_PTR)(reinterpret_cast<uintptr_t>(&scanBytes[i])) + ((pIndex)-sizeof(INT))) + (pIndex)));
				}
				else
				{
					return reinterpret_cast<uintptr_t>(&scanBytes[i]);
				}
			}
		}

		return NULL;
	}
	inline bool ProcessEvent(uintptr_t address, void* fnobject, void* parms)
	{
		if (!isValidPointer(address)) return false;
		auto index = *reinterpret_cast<void***>(address); if (!index) return false;
		auto fProcessEvent = static_cast<void(*)(void* address, void* fnobject, void* parms)>(index[0x4D]); if (!fProcessEvent) return false; //changes sometimes (needs to be found in ida)
		fProcessEvent((void*)address, (void*)fnobject, (void*)parms);
		return true;
	}

};
sdk* sdkUssage = new sdk();

class UObject
{
public:
	char padding_01[0x18];
	int32_t ComparisonIndex;
	void** Vtable;
	int32_t                                            ObjectFlags;
	int32_t                                            InternalIndex;
	class UClass* Class;
	class UObject* Outer;

	static UObject* StaticFindObject(UObject* Class, UObject* InOuter, const wchar_t* Name, bool ExactClass)
	{
		auto StaticFindObjectFN = reinterpret_cast<UObject * (__fastcall*)(UObject*, UObject*, const wchar_t*, bool)>(Client::ImageBase + 0xCB23EC); // old 0x522297C + 1148C70

		return StaticFindObjectFN(Class, InOuter, Name, ExactClass);
	}

	static bool ProcessEvent(uintptr_t address, void* fnobject, void* parms)
	{
		if (!address) return false;
		auto index = *reinterpret_cast<void***>(address); if (!index) return false;
		auto fProcessEvent = static_cast<void(*)(void* address, void* fnobject, void* parms)>(index[0x4D]); if (!fProcessEvent) return false;
		fProcessEvent((void*)address, (void*)fnobject, (void*)parms);
		return true;
	}
};

constexpr auto M_PI = 3.14159265358979323846264338327950288419716939937510;

class UField : public UObject
{
public:
	class UField* Next;                                                     // 0x0000(0x0000) NOT AUTO-GENERATED PROPERTY
};

class UStruct : public UField
{
public:
	UStruct* SuperField;
	void* Children;
	int32_t PropertySize;
	int32_t MinAlignment;
	char pad_0x0048[64];
};

class UClass : public UStruct
{
public:
	unsigned char                                      UnknownData00[0x170];                                     // 0x0088(0x0170) MISSED OFFSET
};

Vector3 galgan(Vector3& zaz, Vector3& daz) {

	Vector3 dalte = zaz - daz;
	Vector3 ongle;
	float hpm = sqrtf(dalte.x * dalte.x + dalte.y * dalte.y);
	ongle.y = atan(dalte.y / dalte.x) * 57.295779513082f;
	ongle.x = (atan(dalte.z / hpm) * 57.295779513082f) * -1.f;
	if (dalte.x >= 0.f) ongle.y += 180.f;
	return ongle;
}

template<class T>
struct TArray
{
	friend class FString;

public:
	TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	}

	TArray(T* data, int32_t count, int32_t max)
		: Data(data),
		Count(count),
		Max(max)
	{
	}

	int Num() const
	{
		return Count;
	}

	T& operator[](int i)
	{
		return Data[i];
	}

	const T& operator[](int i) const
	{
		return Data[i];
	}

	bool IsValidIndex(int i) const
	{
		return i < Num();
	}



private:
	T* Data;
	int32_t Count;
	int32_t Max;
};

class FString : public TArray<wchar_t>
{
public:
	inline FString()
	{
	};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? static_cast<int>(std::wcslen(other)) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};
	FString(const wchar_t* other, int count)
	{
		Data = const_cast<wchar_t*>(other);;
		Max = Count = count;
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* wide() const
	{
		return Data;
	}

	int multi(char* name, int size) const
	{
		return WideCharToMultiByte(CP_UTF8, 0, Data, Count, name, size, nullptr, nullptr) - 1;
	}

	std::string ToString() const
	{
		auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

class KismetSystemLibrary;

namespace ue
{
	namespace cached {
		inline uintptr_t Base = 0;
		inline UObject* kismetobjectname = 0;
		inline KismetSystemLibrary* KismetSystemLibraryA = 0;
		namespace keys
		{
			inline ue::FKey LButton;
			inline ue::FKey Insert;
		}
		namespace offsets {
			inline uintptr_t OwningGameInstance;
			inline uintptr_t Levels;
			inline uintptr_t AcknowledgedPawn;
			inline uintptr_t PlayerCameraManager;
			inline uintptr_t PlayerState;
			inline uintptr_t bADSWhileNotOnGround;
			inline uintptr_t CurrentWeapon;
			inline uintptr_t TeamIndex;
			inline uintptr_t WeaponData;
			inline uintptr_t DisplayName;
			inline uintptr_t Mesh;
			inline uintptr_t RootComponent;
			inline uintptr_t LastFireTime;
			inline uintptr_t AmmoCount;
			inline uintptr_t LastFireTimeVerified;
			inline uintptr_t RelativeLocation;
			inline uintptr_t Tier;
		}
		namespace signatures
		{
			inline uintptr_t GWorld = 0;
			inline uintptr_t FreeFn = 0;

			inline uintptr_t GetNameByIndex = 0;
			inline uintptr_t LineSightOfTo = 0;
			inline uintptr_t GetBoneMatrix = 0;
			inline uintptr_t ProjectWorldToScreen = 0;

		}


		namespace objects {
			inline UObject* FortProjectileBase = 0;
			inline UObject* AFortAthenaZipline = 0;
			inline UObject* K2_SetActorLocation = 0;
			inline UObject* K2_TeleportTo = 0;
			inline UObject* FortRangedWeaponStats = 0;
			inline UObject* K2_GetActorRotation = 0;
			inline UObject* IsReloading = 0;

			namespace actor {
				inline  UObject* FortPlayerPawnAthena = 0;
				inline  UObject* ClientSetRotation = 0;
				inline  UObject* GetPlayerName = 0;
				inline  UObject* ApplyPawnHighlight = 0;
				inline  UObject* ScalePlayerUp = 0;
				inline  UObject* ScalePlayerDown = 0;
				inline  UObject* isHiddingInProp = 0;
				inline  UObject* Fov = 0;
				inline  UObject* SetMouseLocation = 0;
				inline  UObject* SetCharacterBodyVisibilityForPossession = 0;
				inline  UObject* K2_PayBuildingResourceCost = 0;
				inline  UObject* GetVehicle = 0;
				inline  UObject* FortPickup = 0;
			}
			namespace camera {
				inline UObject* GetCameraLocation = 0;
				inline UObject* GetCameraRotation = 0;
				inline UObject* GetFOVAngle = 0;
			}


			namespace render {
				inline UObject* Font = 0;
				inline UObject* K2_DrawLine = 0;
				inline UObject* K2_DrawBox = 0;
				inline UObject* K2_DrawText = 0;
				inline UObject* K2_TextSize = 0;

			}

		}

	}
}

class KismetSystemLibrary
{
public:
	FString GetObjectNamePool(UObject* obj)
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;

		struct
		{
			UObject* obj;
			FString out;
		}Args;
		Args.obj = obj;
		sdkUssage->ProcessEvent((uintptr_t)this, ue::cached::kismetobjectname, &Args);
		return Args.out;
	}
};

struct FMath {
	static __forceinline void SinCos(float* ScalarSin, float* ScalarCos, float  Value);
	static __forceinline float Fmod(float X, float Y);
	template<class T>
	static __forceinline T Clamp(const T X, const T Min, const T Max) { return X < Min ? Min : X < Max ? X : Max; }
};



class UCanvas {
public:

	int32_t SizeX() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return *(int32_t*)((uintptr_t)this + 0x40); //wont change
	}

	int32_t SizeY() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return *(int32_t*)((uintptr_t)this + 0x44); //wont change
	}

	void K2_DrawLine(ue::FVector2D ScreenPositionA, ue::FVector2D ScreenPositionB, float Thickness, ue::FLinearColor RenderColor)
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return;

		struct
		{
			ue::FVector2D                                   ScreenPositionA;                                          // (Parm, ZeroConstructor, IsPlainOldData)
			ue::FVector2D                                  ScreenPositionB;                                          // (Parm, ZeroConstructor, IsPlainOldData)
			float                                              Thickness;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			ue::FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
		} params;

		params.ScreenPositionA = { ScreenPositionA.X, ScreenPositionA.Y };
		params.ScreenPositionB = { ScreenPositionB.X, ScreenPositionB.Y };
		params.Thickness = Thickness;
		params.RenderColor = { (float)RenderColor.R, (float)RenderColor.G, (float)RenderColor.B, (float)RenderColor.A };

		sdkUssage->ProcessEvent(uintptr_t(this), ue::cached::objects::render::K2_DrawLine, &params);
	}

	void K2_DrawBox(ue::FVector2D ScreenPosition, ue::FVector2D ScreenSize, float Thickness, ue::FLinearColor RenderColor)
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return;

		struct
		{
			ue::FVector2D                                  ScreenPosition;                                           // (Parm, ZeroConstructor, IsPlainOldData)
			ue::FVector2D                                   ScreenSize;                                               // (Parm, ZeroConstructor, IsPlainOldData)
			float                                              Thickness;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			ue::FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
		} params;

		params.ScreenPosition = { ScreenPosition.X, ScreenPosition.Y };
		params.ScreenSize = { ScreenSize.X, ScreenSize.Y };
		params.Thickness = Thickness;
		params.RenderColor = { (float)RenderColor.R, (float)RenderColor.G, (float)RenderColor.B, (float)RenderColor.A };

		sdkUssage->ProcessEvent(uintptr_t(this), ue::cached::objects::render::K2_DrawBox, &params);
	}

	struct UCanvas_K2_DrawText_Params
	{
		class UObject* RenderFont;                                               // (Parm, ZeroConstructor)
		struct FString                                     RenderText;                                               // (Parm, ZeroConstructor)
		struct ue::FVector2D                                   ScreenPosition;                                           // (Parm, ZeroConstructor, IsPlainOldData)
		struct ue::FVector2D                                   Scale;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
		struct ue::FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
		float                                              Kerning;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
		struct ue::FLinearColor                                ShadowColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
		struct ue::FVector2D                                   ShadowOffset;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		bool                                               bCentreX;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
		bool                                               bCentreY;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
		bool                                               bOutlined;                                                // (Parm, ZeroConstructor, IsPlainOldData)
		struct ue::FLinearColor                                OutlineColor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	};

	void K2_DrawText(ue::FVector2D ScreenPosition, ue::FLinearColor RenderColor, FString RenderText, bool bCentered = true, bool bOutlined = false)
	{
		UCanvas_K2_DrawText_Params params;
		params.RenderFont = ue::cached::objects::render::Font;
		params.RenderText = RenderText;
		params.ScreenPosition = ScreenPosition;
		params.Scale = ue::FVector2D{ 1, 1 };
		params.RenderColor = RenderColor;
		params.Kerning = false;
		params.ShadowColor = { 0.0f, 0.0f, 0.0f, 1.f };
		params.ShadowOffset = ue::FVector2D{ -1, -1 };
		if (bCentered) {
			params.bCentreX = true;
			params.bCentreY = true;
		}
		else {
			params.bCentreX = false;
			params.bCentreY = false;
		}
		params.bOutlined = bOutlined;
		params.OutlineColor = { 0.0f, 0.0f, 0.0f, 1.f };

		sdkUssage->ProcessEvent(uintptr_t(this), ue::cached::objects::render::K2_DrawText, &params);
	}

	void K3_DrawText(float x, float y, ue::FLinearColor RenderColor, ue::FString RenderText, bool bCentered = true, bool bOutlined = false)
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return;

		struct
		{
			uintptr_t RenderFont;                                               // (Parm, ZeroConstructor, IsPlainOldData)
			ue::FString                                     RenderText;                                               // (Parm, ZeroConstructor)
			Vector2                                   ScreenPosition;                                           // (Parm, ZeroConstructor, IsPlainOldData)
			Vector2                                   Scale;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
			ue::FLinearColor                                RenderColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
			float                                              Kerning;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
			ue::FLinearColor                                ShadowColor;                                              // (Parm, ZeroConstructor, IsPlainOldData)
			Vector2                                   ShadowOffset;                                             // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bCentreX;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bCentreY;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bOutlined;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			ue::FLinearColor                                OutlineColor;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		} params;

		params.RenderFont = uintptr_t(ue::cached::objects::render::Font);
		params.RenderText = RenderText;
		params.ScreenPosition = { x, y };
		params.Scale = { 1.f, 1.f };
		params.RenderColor = { (float)RenderColor.R, (float)RenderColor.G, (float)RenderColor.B, (float)RenderColor.A };
		params.Kerning = false;
		params.ShadowColor = { 0.f, 0.f, 0.f, 0.f };
		params.ShadowOffset = { x + 1.5f, y + 1.5f };

		if (bCentered)
		{
			params.bCentreX = true;
			params.bCentreY = true;
		}
		else
		{
			params.bCentreX = false;
			params.bCentreY = false;
		}

		params.bOutlined = bOutlined;
		params.OutlineColor = { 0.0f, 0.0f, 0.0f, 1.f };

		sdkUssage->ProcessEvent(uintptr_t(this), ue::cached::objects::render::K2_DrawText, &params);
	}

	ue::FVector2D K2_TextSize(FString RenderText)
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return { 0, 0 };

		struct
		{
			uintptr_t RenderFont;                                               // (Parm, ZeroConstructor, IsPlainOldData)
			FString                                     RenderText;                                               // (Parm, ZeroConstructor)
			ue::FVector2D                                   Scale;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
			ue::FVector2D                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;

		params.RenderFont = uintptr_t(ue::cached::objects::render::Font);
		params.RenderText = RenderText;
		params.Scale = { 0.4f, 0.4f };

		sdkUssage->ProcessEvent(uintptr_t(this), ue::cached::objects::render::K2_TextSize, &params);

		return { params.ReturnValue.X, params.ReturnValue.Y };
	}



#define D2R(d) (d / 180.f) * M_PI
#define MAX_SEGMENTS 180

	void K2_DrawFOV(Vector2 pos, int r, ue::FLinearColor color)
	{
		float Step = M_PI * 2.0 / 60;
		int Count = 0;
		Vector2 V[128];
		for (float a = 0; a < M_PI * 2.0; a += Step)
		{
			float X1 = Client::Settings::Aimbot::FovCircleRadius * cosf(a) + pos.x;
			float Y1 = Client::Settings::Aimbot::FovCircleRadius * sinf(a) + pos.y;
			float X2 = Client::Settings::Aimbot::FovCircleRadius * cosf(a + Step) + pos.x;
			float Y2 = Client::Settings::Aimbot::FovCircleRadius * sinf(a + Step) + pos.y;
			V[Count].x = X1;
			V[Count].y = Y1;
			V[Count + 1].x = X2;
			V[Count + 1].y = Y2;
			K2_DrawLine(ue::FVector2D({ V[Count].x, V[Count].y }), ue::FVector2D({ X2, Y2 }), 1.0f, color);
		}
	}

	void DrawCorneredBox(double X, double Y, double W, double H, ue::FLinearColor color, int thickness) {
		float lineW = (W / 3);
		float lineH = (H / 3);
		this->K2_DrawLine({ X, Y }, { X, Y + lineH }, thickness, color);

		this->K2_DrawLine({ X, Y }, { X + lineW, Y }, thickness, color);

		this->K2_DrawLine({ X + W - lineW, Y }, { X + W, Y }, thickness, color);

		this->K2_DrawLine({ X + W, Y }, { X + W, Y + lineH }, thickness, color);

		this->K2_DrawLine({ X, Y + H - lineH }, { X, Y + H }, thickness, color);

		this->K2_DrawLine({ X, Y + H }, { X + lineW, Y + H }, thickness, color);

		this->K2_DrawLine({ X + W - lineW, Y + H }, { X + W, Y + H }, thickness, color);

		this->K2_DrawLine({ X + W, Y + H - lineH }, { X + W, Y + H }, thickness, color);

	}
};




// Enum FortniteGame.EFortItemTier
enum class EFortItemTier : uint8_t
{
	No_Tier = 0,
	I = 1,
	II = 2,
	III = 3,
	IV = 4,
	V = 5,
	VI = 6,
	VII = 7,
	VIII = 8,
	IX = 9,
	X = 10,
	NumItemTierValues = 11,
	EFortItemTier_MAX = 12
};
class AFortItemDefinition {
public:

	ue::FText DisplayName() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return {};
		return *(ue::FText*)((uintptr_t)this + 0x90); //FortItemDefinition::DisplayName 0x90
	}
	BYTE Tier() {
		return *(BYTE*)((uintptr_t)this + 0x73); //FortItemDefinition::Tier 0x74
	}
};
class AWeapon {
public:

	AFortItemDefinition* WeaponData() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (AFortItemDefinition*)(*(uintptr_t*)(this + 0x3F0)); //FortWeapon::WeaponData 0x3F0
	}
	void RapidFire() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return;

		float a = 0;
		float b = 0;
		a = *(float*)((uintptr_t)this + 0xAB0); //FortWeapon::LastFireTime 0xAB0
		b = *(float*)((uintptr_t)this + 0xAB4); //FortWeapon::LastFireTimeVerified 0xAB4
		*(float*)((uintptr_t)this + 0xAB0) = a + b - 0.3333; //FortWeapon::LastFireTime 0xAB0
	}
	// Enum FortniteGame.EFortItemTier

	bool IsReloadingCheckTest()
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (bool*)(*(uintptr_t*)(this + 0x348)); 
	}

	bool IsReloadingCheck()
	{
		struct {
			bool isreloading;
		} gay;

		sdkUssage->ProcessEvent((uintptr_t)this, ue::cached::objects::IsReloading, &gay);
		return gay.isreloading;
	}

	int GetBulletsPerClip()
	{
		static UObject* fn = NULL;
		if (!fn)
			fn = UObject::StaticFindObject(nullptr, nullptr, L"FortWeapon.GetBulletsPerClip", false);

		struct
		{
			int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;


		sdkUssage->ProcessEvent((uintptr_t)this, fn, &params);
		return params.ReturnValue;
	}
	int GetMagazineAmmoCount()
	{
		static UObject* fn = NULL;
		if (!fn)
			fn = UObject::StaticFindObject(nullptr, nullptr, L"FortWeapon.GetMagazineAmmoCount", false);

		struct
		{
			int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;


		sdkUssage->ProcessEvent((uintptr_t)this, fn, &params);
		return params.ReturnValue;
	}

};
class APlayerState {
public:

	uintptr_t TeamIndex() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return *(uintptr_t*)(this + 0x1100); // FortPlayerStateAthena::TeamIndex 0x1098
	}
	int32_t SeasonLevelUIDisplay() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return *(int32_t*)(this + 0x1118); //FortPlayerStateAthena::SeasonLevelUIDisplay 0x10B0
	}	FString GetPlayerName() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return L"";
		FString PlayerName;
		sdkUssage->ProcessEvent((uintptr_t)this, ue::cached::objects::actor::GetPlayerName, &PlayerName);
		if (!PlayerName.IsValid()) return L"";
		return PlayerName;
	}



};
class ARootComponent {
public:

	Vector3 RelativeLocation()
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return { 0, 0, 0 };
		return *(Vector3*)((uintptr_t)this + 0x128); //SceneComponent::RelativeLocation 0x128
	}
	// ItemDefinition
	/*Vector3 RelativeRotation() {
		if (!Memory::IsValidPointer((uintptr_t)this)) return { 0, 0, 0 };
		return *(Vector3*)((uintptr_t)this + 0x128);
	}

	Vector3 GetComponentVelocity()
	{
		if (!Memory::IsValidPointer((uintptr_t)this)) return { 0, 0, 0 };
		StructsParams::USceneComponent_GetComponentVelocity_Params params;

		FN::ProcessEvent(uintptr_t(this), ObjectsAddresses::GetComponentVelocity, &params);

		return params.ReturnValue;
	}*/
};
class UFortVehicleFuelComponent {
public:

};
class APlayerController;
class AFortAthenaVehicle {
public:
	UFortVehicleFuelComponent* CachedFuelComponent()
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (UFortVehicleFuelComponent*)(*(uintptr_t*)((uintptr_t)this + 0x10a8)); //FortAthenaVehicle::CachedFuelComponent 0x10A0
	}
};

class kek {
public:
	ue::FText* DisplayName() {
		if (!sdkUssage->isValidPointer(uintptr_t(this))) return 0;
		return reinterpret_cast<ue::FText*>(*(uintptr_t*)((uintptr_t)this + 0x90)); //UFortItemDefinition	DisplayName
	}

	BYTE Tier() {
		if (!sdkUssage->isValidPointer(uintptr_t(this))) return false;
		return *(BYTE*)((uintptr_t)this + 0x73); //UFortItemDefinition	Tier
	}
};
class USceneComponent {
public:
	BOOL K2_SetRelativeRotation(const Vector3 NewRotation, bool bSweep, bool bTeleport)
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;

		static UObject* fn = NULL;
		if (!fn)
			fn = UObject::StaticFindObject(nullptr, nullptr, L"SceneComponent.K2_SetRelativeRotation", false);

		struct
		{
			Vector3							NewRotation;
			bool							bSweep;
			int								SweepHitResult;
			bool							bTeleport;
			bool							ReturnValue;
		} params;

		params.NewRotation = NewRotation;
		params.bSweep = bSweep;
		params.bTeleport = bTeleport;

		sdkUssage->ProcessEvent((uintptr_t)this, fn, &params);

		return params.ReturnValue;
	}
};

class AFortPawn {
public:
	const wchar_t* ObjectName() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return (L"");
		//return find::GetObjectName((ue::classes::UObject*)this);
	}

	kek* ItemDefinition() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (kek*)(*(uintptr_t*)((uintptr_t)this + (0x318 + 0x18)));
	}

	APlayerState* PlayerState() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (APlayerState*)(*(uintptr_t*)((uintptr_t)this + 0x2A8)); //APawn	PlayerState
	}



	ARootComponent* RootComponent() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (ARootComponent*)(*(uintptr_t*)((uintptr_t)this + 0x190)); //AActor	RootComponent
	}
	APlayerController* PlayerController() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (APlayerController*)(*(uintptr_t*)((uintptr_t)this + 0x30)); //wont change
	}
	void AimWhileJumping(bool action) {
		*(bool*)((uintptr_t)this + 0x4d86) = action; //FortPlayerPawnAthena::bADSWhileNotOnGround 0x4B25
	}
	BOOL IsA(PVOID parentClass) {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return false;
		ue::classes::UObject* object = (ue::classes::UObject*)this;
		for (auto super = object->Class; super; super = super->SuperClass)
		{
			if (super == parentClass) {
				return true;
			}
		}
		return false;
	}

	Vector3 GetBone(int Id)
	{
		if (!sdkUssage->isValidPointer(uintptr_t(this))) return { 0, 0, 0 };

		auto mesh = Mesh();
		if (!mesh) return { 0, 0, 0 };

		auto function = ((ue::FMatrix * (__fastcall*)(uintptr_t, ue::FMatrix*, int))(Client::ImageBase + 0x1A33EE4));
		function(mesh, ue::myMatrix, Id);

		return { ue::myMatrix->M[3][0], ue::myMatrix->M[3][1], ue::myMatrix->M[3][2] };
	}

	uintptr_t Mesh() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return *(uintptr_t*)((uintptr_t)this + 0x310); //Character::Mesh 0x310
	}




	/*Vector3 GetBone(int Id)
	{
		if (!sdkUssage->isValidPointer(uintptr_t(this))) return { 0, 0, 0 };

		auto mesh = Mesh();
		if (!mesh) return { 0, 0, 0 };

		auto function = ((ue::FMatrix * (__fastcall*)(uintptr_t, ue::FMatrix*, int))(ue::cached::signatures::GetBoneMatrix));
		function(mesh, ue::myMatrix, Id);

		return { ue::myMatrix->M[3][0], ue::myMatrix->M[3][1], ue::myMatrix->M[3][2] };
	}*/
	AWeapon* CurrentWeapon() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (AWeapon*)(*(uintptr_t*)((uintptr_t)this + 0x908)); //FortPawn::CurrentWeapon 0x868
	}

	struct AFortPlayerPawn_GetVehicleActor_Params
	{
		class AFortPawn* ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
	};


	class AFortPawn* GetVehicleActor()
	{
		static UObject* fn = NULL;
		if (!fn)
			fn = UObject::StaticFindObject(nullptr, nullptr, L"FortPlayerPawn.GetVehicleActor", false);

		AFortPlayerPawn_GetVehicleActor_Params params;

		sdkUssage->ProcessEvent((uintptr_t)this, fn, &params);

		return params.ReturnValue;
	}



	struct AActor_K2_TeleportTo_Params
	{
		Vector3										DestLocation;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		Vector3										DestRotation;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		bool										ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
	};


	BOOL K2_TeleportTo(const Vector3& DestLocation, const Vector3& DestRotation)
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;

		AActor_K2_TeleportTo_Params params;

		params.DestLocation = DestLocation;
		params.DestRotation = DestRotation;

		sdkUssage->ProcessEvent((uintptr_t)this, ue::cached::objects::K2_TeleportTo, &params);

		return params.ReturnValue;
	}

	BOOL K2_SetActorLocation(const Vector3 NewLocation, bool bSweep, bool bTeleport)
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;

		struct
		{
			Vector3							NewLocation;
			bool							bSweep;
			int								SweepHitResult;
			bool							bTeleport;
			bool							ReturnValue;
		} params;

		params.NewLocation = NewLocation;
		params.bSweep = bSweep;
		params.bTeleport = bTeleport;

		sdkUssage->ProcessEvent((uintptr_t)this, ue::cached::objects::K2_SetActorLocation, &params);

		return params.ReturnValue;
	}

};
class APlayerCameraManager {
public:

	Vector3 GetCameraLocation()
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return { 0,0,0 };

		struct APlayerCameraManager_GetCameraLocation_Params
		{
			Vector3                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		};
		APlayerCameraManager_GetCameraLocation_Params params;

		sdkUssage->ProcessEvent((uintptr_t)this, ue::cached::objects::camera::GetCameraLocation, &params);

		return params.ReturnValue;
	}
	Vector3 GetCameraRotation()
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return { 0,0,0 };


		struct APlayerCameraManager_GetCameraRotation_Params
		{
			Vector3                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		};
		APlayerCameraManager_GetCameraRotation_Params params;

		sdkUssage->ProcessEvent((uintptr_t)this, ue::cached::objects::camera::GetCameraRotation, &params);

		return params.ReturnValue;
	}
	float GetFOVAngle()
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;

		struct APlayerCameraManager_GetFOVAngle_Params
		{
			float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		};

		APlayerCameraManager_GetFOVAngle_Params params;

		sdkUssage->ProcessEvent((uintptr_t)this, ue::cached::objects::camera::GetFOVAngle, &params);

		return params.ReturnValue;
	}

	Vector2 ProjectWorldLocationToScreen(int SizeX, int SizeY, Vector3 world_location)
	{
		Vector3 CameraLocation = GetCameraLocation();

		Vector3 CameraRotation = GetCameraRotation();

		float FOVAngle = GetFOVAngle();


		Vector2 output;
		float delta[3];
		float sp = 0, cp = 0, sy = 0, cy = 0, sr = 0, cr = 0;
		float axisx[3];
		float axisy[3];
		float axisz[3];
		float transformed[3];

		delta[0] = world_location.x - CameraLocation.x;
		delta[1] = world_location.y - CameraLocation.y;
		delta[2] = world_location.z - CameraLocation.z;

		sp = sinf(CameraRotation.x * M_PI / 180);
		cp = cosf(CameraRotation.x * M_PI / 180);
		sy = sinf(CameraRotation.y * M_PI / 180);
		cy = cosf(CameraRotation.y * M_PI / 180);
		sr = sinf(CameraRotation.z * M_PI / 180);
		cr = cosf(CameraRotation.z * M_PI / 180);

		axisx[0] = cp * cy;
		axisx[1] = cp * sy;
		axisx[2] = sp;

		axisy[0] = sr * sp * cy - cr * sy;
		axisy[1] = sr * sp * sy + cr * cy;
		axisy[2] = -sr * cp;

		axisz[0] = -(cr * sp * cy + sr * sy);
		axisz[1] = cy * sr - cr * sp * sy;
		axisz[2] = cr * cp;

		transformed[0] = delta[0] * axisy[0] + delta[1] * axisy[1] + delta[2] * axisy[2];
		transformed[1] = delta[0] * axisz[0] + delta[1] * axisz[1] + delta[2] * axisz[2];
		transformed[2] = delta[0] * axisx[0] + delta[1] * axisx[1] + delta[2] * axisx[2];

		if (transformed[2] < 1)
			transformed[2] = 1;

		if (transformed[2] / 100 > 0)
		{
			float tmpx = 0, tmpy = 0;

			tmpx = (float)(SizeX / 2);
			tmpy = (float)(SizeY / 2);

			output.x = tmpx + transformed[0] * tmpx / tanf(FOVAngle * M_PI / 360) / transformed[2];
			output.y = tmpy - transformed[1] * tmpx / tanf(FOVAngle * M_PI / 360) / transformed[2];

			return output;
		}

		return Vector2(0, 0);
	}
};

class APlayerController {
public:
	AFortPawn* LocalPawn() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (AFortPawn*)(*(uintptr_t*)((uintptr_t)this + 0x330)); //PlayerController::AcknowledgedPawn 0x328
	}

	APlayerCameraManager* PlayerCameraManager() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (APlayerCameraManager*)(*(uintptr_t*)(this + 0x340)); //PlayerController::PlayerCameraManager 0x338
	}

	BOOL ClientSetRotation(const Vector3& NewRotation, bool bResetCamera)
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;

		struct AController_ClientSetRotation_Params
		{
			Vector3										NewRotation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
			bool										bResetCamera;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		};

		AController_ClientSetRotation_Params params;
		params.NewRotation = NewRotation;
		params.bResetCamera = bResetCamera;

		sdkUssage->ProcessEvent(uintptr_t(this), ue::cached::objects::actor::ClientSetRotation, &params);
		return TRUE;
	}
};

class UViewportClient {
public:

};
class ULocalPlayer {
public:
	APlayerController* PlayerController() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (APlayerController*)(*(uintptr_t*)((uintptr_t)this + 0x30)); //wont change
	}
	UViewportClient* ViewportClient() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (UViewportClient*)(*(uintptr_t*)((uintptr_t)this + 0x78)); //wont change
	}

};
class ULocalPlayers {
public:
	ULocalPlayer* LocalPlayer() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (ULocalPlayer*)(*(uintptr_t*)((uintptr_t)this));
	}
};
class UGameInstance {
public:
	ULocalPlayers* LocalPlayers() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (ULocalPlayers*)(*(uintptr_t*)((uintptr_t)this + 0x38)); //wont change
	}
};
class AActors {
public:

	AFortPawn* GetCurrentActor(int i) {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (AFortPawn*)(*(uintptr_t*)(this + i * sizeof(uintptr_t)));
	}
	ARootComponent* RootComponent() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (ARootComponent*)(*(uintptr_t*)((uintptr_t)this + 0x190)); //AActor	RootComponent
	}

	struct AActor_K2_TeleportTo_Params
	{
		Vector3										DestLocation;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		Vector3										DestRotation;                                             // (Parm, ZeroConstructor, IsPlainOldData)
		bool										ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
	};


	BOOL K2_TeleportTo(const Vector3& DestLocation, const Vector3& DestRotation)
	{
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;

		AActor_K2_TeleportTo_Params params;

		params.DestLocation = DestLocation;
		params.DestRotation = DestRotation;

		sdkUssage->ProcessEvent((uintptr_t)this, ue::cached::objects::K2_TeleportTo, &params);

		return params.ReturnValue;
	}
};
class ULevel {
public:



	int ActorCount() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (int)(*(uintptr_t*)(this + 0xA0)); //wont change
	}
	ue::TArray<AFortPawn*> ActorArray() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return {};
		return *(ue::TArray<AFortPawn*>*)((uintptr_t)this + 0x98); //wont change
	}
	AActors* Actors() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (AActors*)(*(uintptr_t*)(this + 0x98)); //wont change
	}
};
class GWorld {
public:
	UGameInstance* OwningGameInstance() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (UGameInstance*)(*(uintptr_t*)((uintptr_t)this + 0x1b8)); //World::OwningGameInstance 0x1A8
	}
	ue::TArray<ULevel*> Levels() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return {};
		return *(ue::TArray<ULevel*>*)((uintptr_t)this + 0x170); //ue::cached::offsets::Levels
	}
	ULevel* PersistentLevel() {
		if (!sdkUssage->isValidPointer((uintptr_t)this)) return 0;
		return (ULevel*)(*(uintptr_t*)(this + 0x30)); //wont change
	}
};

class UGameplayStatics
{
public:

	void GetAllActorsOfClass(GWorld* WorldContextObject, UClass* ActorClass, TArray<AFortPawn*>* OutActors)
	{

		static uintptr_t fn = NULL;

		if (!fn)
		{
			fn = (uintptr_t)UObject::StaticFindObject(nullptr, nullptr, L"Engine.GameplayStatics.GetAllActorsOfClass", false);
		}

		struct UGameplayStatics_GetAllActorsOfClass_Params
		{
			GWorld* WorldContextObject;
			UClass* ActorClass;
			TArray<AFortPawn*> OutActors;
		};

		UGameplayStatics_GetAllActorsOfClass_Params params;

		params.WorldContextObject = WorldContextObject;

		params.ActorClass = ActorClass;

		UObject::ProcessEvent((uintptr_t)this, (void*)fn, &params);

		if (OutActors != nullptr) *OutActors = params.OutActors;

	}

	static UGameplayStatics* StaticClass()
	{

		static uintptr_t fn = NULL;

		if (!fn)
		{
			fn = (uintptr_t)UObject::StaticFindObject(nullptr, nullptr, L"Engine.GameplayStatics", false);
		}

		return (UGameplayStatics*)fn;

	}

};

static bool IsVisible(APlayerController* PlayerController, AFortPawn* Pawn, Vector3* ViewPoint)
{
	auto subIsVisible = reinterpret_cast<bool(__fastcall*)(APlayerController * PlayerController, AFortPawn * Pawn, Vector3 * ViewPoint)>(Client::ImageBase + 0x7857C3C);
	return subIsVisible(PlayerController, Pawn, ViewPoint);
}
