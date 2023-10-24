#pragma once
#include "Defines.h"
#include "Client.h"
#include "Cheatloop.h"
#include "zgui.h"

float Width, Height = 0;

using DrawTransitionOrg = void(*)(uintptr_t _this, UCanvas* canvas);
DrawTransitionOrg PostRenderOriginal = 0;

UCanvas* static_canvas;
Vector3 headtarget;

static UObject* FortProjectileBase = 0;
static UGameplayStatics* GameplayStatics = 0;

static BOOL IsNotInScreen(int SizeX, int SizeY, Vector2 Pos) {
	if (((Pos.x <= 0 or Pos.x > SizeX) and (Pos.y <= 0 or Pos.y > SizeY)) or ((Pos.x <= 0 or Pos.x > SizeX) or (Pos.y <= 0 or Pos.y > SizeY))) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}


namespace Colors
{
	ue::FLinearColor AliceBlue = { 0.941176534f, 0.972549081f, 1.000000000f, 1.000000000f };
	ue::FLinearColor AntiqueWhite = { 0.980392218f, 0.921568692f, 0.843137324f, 1.000000000f };
	ue::FLinearColor Aqua = { 0.000000000f, 1.000000000f, 1.000000000f, 1.000000000f };
	ue::FLinearColor Aquamarine = { 0.498039246f, 1.000000000f, 0.831372619f, 1.000000000f };
	ue::FLinearColor Azure = { 0.941176534f, 1.000000000f, 1.000000000f, 1.000000000f };
	ue::FLinearColor Beige = { 0.960784376f, 0.960784376f, 0.862745166f, 1.000000000f };
	ue::FLinearColor Bisque = { 1.000000000f, 0.894117713f, 0.768627524f, 1.000000000f };
	ue::FLinearColor Black = { 0.000000000f, 0.000000000f, 0.000000000f, 1.000000000f };
	ue::FLinearColor BlanchedAlmond = { 1.000000000f, 0.921568692f, 0.803921640f, 1.000000000f };
	ue::FLinearColor Blue = { 0.000000000f, 0.000000000f, 1.000000000f, 1.000000000f };
	ue::FLinearColor BlueViolet = { 0.541176498f, 0.168627456f, 0.886274576f, 1.000000000f };
	ue::FLinearColor Brown = { 0.647058845f, 0.164705887f, 0.164705887f, 1.000000000f };
	ue::FLinearColor BurlyWood = { 0.870588303f, 0.721568644f, 0.529411793f, 1.000000000f };
	ue::FLinearColor CadetBlue = { 0.372549027f, 0.619607866f, 0.627451003f, 1.000000000f };
	ue::FLinearColor Chartreuse = { 0.498039246f, 1.000000000f, 0.000000000f, 1.000000000f };
	ue::FLinearColor Chocolate = { 0.823529482f, 0.411764741f, 0.117647067f, 1.000000000f };
	ue::FLinearColor Coral = { 1.000000000f, 0.498039246f, 0.313725501f, 1.000000000f };
	ue::FLinearColor CornflowerBlue = { 0.392156899f, 0.584313750f, 0.929411829f, 1.000000000f };
	ue::FLinearColor Cornsilk = { 1.000000000f, 0.972549081f, 0.862745166f, 1.000000000f };
	ue::FLinearColor Crimson = { 0.862745166f, 0.078431375f, 0.235294133f, 1.000000000f };
	ue::FLinearColor Cyan = { 0.000000000f, 1.000000000f, 1.000000000f, 1.000000000f };
	ue::FLinearColor DarkBlue = { 0.000000000f, 0.000000000f, 0.545098066f, 1.000000000f };
	ue::FLinearColor DarkCyan = { 0.000000000f, 0.545098066f, 0.545098066f, 1.000000000f };
	ue::FLinearColor DarkGoldenrod = { 0.721568644f, 0.525490224f, 0.043137256f, 1.000000000f };
	ue::FLinearColor DarkGray = { 0.662745118f, 0.662745118f, 0.662745118f, 1.000000000f };
	ue::FLinearColor DarkGreen = { 0.000000000f, 0.392156899f, 0.000000000f, 1.000000000f };
	ue::FLinearColor DarkKhaki = { 0.741176486f, 0.717647076f, 0.419607878f, 1.000000000f };
	ue::FLinearColor DarkMagenta = { 0.545098066f, 0.000000000f, 0.545098066f, 1.000000000f };
	ue::FLinearColor DarkOliveGreen = { 0.333333343f, 0.419607878f, 0.184313729f, 1.000000000f };
	ue::FLinearColor DarkOrange = { 1.000000000f, 0.549019635f, 0.000000000f, 1.000000000f };
	ue::FLinearColor DarkOrchid = { 0.600000024f, 0.196078449f, 0.800000072f, 1.000000000f };
	ue::FLinearColor DarkRed = { 0.545098066f, 0.000000000f, 0.000000000f, 1.000000000f };
	ue::FLinearColor DarkSalmon = { 0.913725555f, 0.588235319f, 0.478431404f, 1.000000000f };
	ue::FLinearColor DarkSeaGreen = { 0.560784340f, 0.737254918f, 0.545098066f, 1.000000000f };
	ue::FLinearColor DarkSlateBlue = { 0.282352954f, 0.239215702f, 0.545098066f, 1.000000000f };
	ue::FLinearColor DarkSlateGray = { 0.184313729f, 0.309803933f, 0.309803933f, 1.000000000f };
	ue::FLinearColor DarkTurquoise = { 0.000000000f, 0.807843208f, 0.819607913f, 1.000000000f };
	ue::FLinearColor DarkViolet = { 0.580392182f, 0.000000000f, 0.827451050f, 1.000000000f };
	ue::FLinearColor DeepPink = { 1.000000000f, 0.078431375f, 0.576470613f, 1.000000000f };
	ue::FLinearColor DeepSkyBlue = { 0.000000000f, 0.749019623f, 1.000000000f, 1.000000000f };
	ue::FLinearColor DimGray = { 0.411764741f, 0.411764741f, 0.411764741f, 1.000000000f };
	ue::FLinearColor DodgerBlue = { 0.117647067f, 0.564705908f, 1.000000000f, 1.000000000f };
	ue::FLinearColor Firebrick = { 0.698039234f, 0.133333340f, 0.133333340f, 1.000000000f };
	ue::FLinearColor FloralWhite = { 1.000000000f, 0.980392218f, 0.941176534f, 1.000000000f };
	ue::FLinearColor ForestGreen = { 0.133333340f, 0.545098066f, 0.133333340f, 1.000000000f };
	ue::FLinearColor Fuchsia = { 1.000000000f, 0.000000000f, 1.000000000f, 1.000000000f };
	ue::FLinearColor Gainsboro = { 0.862745166f, 0.862745166f, 0.862745166f, 1.000000000f };
	ue::FLinearColor GhostWhite = { 0.972549081f, 0.972549081f, 1.000000000f, 1.000000000f };
	ue::FLinearColor Gold = { 1.000000000f, 0.843137324f, 0.000000000f, 1.000000000f };
	ue::FLinearColor Goldenrod = { 0.854902029f, 0.647058845f, 0.125490203f, 1.000000000f };
	ue::FLinearColor Gray = { 0.501960814f, 0.501960814f, 0.501960814f, 1.000000000f };
	ue::FLinearColor Green = { 0.000000000f, 0.501960814f, 0.000000000f, 1.000000000f };
	ue::FLinearColor GreenYellow = { 0.678431392f, 1.000000000f, 0.184313729f, 1.000000000f };
	ue::FLinearColor Honeydew = { 0.941176534f, 1.000000000f, 0.941176534f, 1.000000000f };
	ue::FLinearColor HotPink = { 1.000000000f, 0.411764741f, 0.705882370f, 1.000000000f };
	ue::FLinearColor IndianRed = { 0.803921640f, 0.360784322f, 0.360784322f, 1.000000000f };
	ue::FLinearColor Indigo = { 0.294117659f, 0.000000000f, 0.509803951f, 1.000000000f };
	ue::FLinearColor Ivory = { 1.000000000f, 1.000000000f, 0.941176534f, 1.000000000f };
	ue::FLinearColor Khaki = { 0.941176534f, 0.901960850f, 0.549019635f, 1.000000000f };
	ue::FLinearColor Lavender = { 0.901960850f, 0.901960850f, 0.980392218f, 1.000000000f };
	ue::FLinearColor LavenderBlush = { 1.000000000f, 0.941176534f, 0.960784376f, 1.000000000f };
	ue::FLinearColor LawnGreen = { 0.486274540f, 0.988235354f, 0.000000000f, 1.000000000f };
	ue::FLinearColor LemonChiffon = { 1.000000000f, 0.980392218f, 0.803921640f, 1.000000000f };
	ue::FLinearColor LightBlue = { 0.678431392f, 0.847058892f, 0.901960850f, 1.000000000f };
	ue::FLinearColor LightCoral = { 0.941176534f, 0.501960814f, 0.501960814f, 1.000000000f };
	ue::FLinearColor LightCyan = { 0.878431439f, 1.000000000f, 1.000000000f, 1.000000000f };
	ue::FLinearColor LightGoldenrodYellow = { 0.980392218f, 0.980392218f, 0.823529482f, 1.000000000f };
	ue::FLinearColor LightGreen = { 0.564705908f, 0.933333397f, 0.564705908f, 1.000000000f };
	ue::FLinearColor LightGray = { 0.827451050f, 0.827451050f, 0.827451050f, 1.000000000f };
	ue::FLinearColor LightPink = { 1.000000000f, 0.713725507f, 0.756862819f, 1.000000000f };
	ue::FLinearColor LightSalmon = { 1.000000000f, 0.627451003f, 0.478431404f, 1.000000000f };
	ue::FLinearColor LightSeaGreen = { 0.125490203f, 0.698039234f, 0.666666687f, 1.000000000f };
	ue::FLinearColor LightSkyBlue = { 0.529411793f, 0.807843208f, 0.980392218f, 1.000000000f };
	ue::FLinearColor LightSlateGray = { 0.466666698f, 0.533333361f, 0.600000024f, 1.000000000f };
	ue::FLinearColor LightSteelBlue = { 0.690196097f, 0.768627524f, 0.870588303f, 1.000000000f };
	ue::FLinearColor LightYellow = { 1.000000000f, 1.000000000f, 0.878431439f, 1.000000000f };
	ue::FLinearColor Lime = { 0.000000000f, 1.000000000f, 0.000000000f, 1.000000000f };
	ue::FLinearColor LimeGreen = { 0.196078449f, 0.803921640f, 0.196078449f, 1.000000000f };
	ue::FLinearColor Linen = { 0.980392218f, 0.941176534f, 0.901960850f, 1.000000000f };
	ue::FLinearColor Magenta = { 1.000000000f, 0.000000000f, 1.000000000f, 1.000000000f };
	ue::FLinearColor Maroon = { 0.501960814f, 0.000000000f, 0.000000000f, 1.000000000f };
	ue::FLinearColor MediumAquamarine = { 0.400000036f, 0.803921640f, 0.666666687f, 1.000000000f };
	ue::FLinearColor MediumBlue = { 0.000000000f, 0.000000000f, 0.803921640f, 1.000000000f };
	ue::FLinearColor MediumOrchid = { 0.729411781f, 0.333333343f, 0.827451050f, 1.000000000f };
	ue::FLinearColor MediumPurple = { 0.576470613f, 0.439215720f, 0.858823597f, 1.000000000f };
	ue::FLinearColor MediumSeaGreen = { 0.235294133f, 0.701960802f, 0.443137288f, 1.000000000f };
	ue::FLinearColor MediumSlateBlue = { 0.482352972f, 0.407843173f, 0.933333397f, 1.000000000f };
	ue::FLinearColor MediumSpringGreen = { 0.000000000f, 0.980392218f, 0.603921592f, 1.000000000f };
	ue::FLinearColor MediumTurquoise = { 0.282352954f, 0.819607913f, 0.800000072f, 1.000000000f };
	ue::FLinearColor MediumVioletRed = { 0.780392230f, 0.082352944f, 0.521568656f, 1.000000000f };
	ue::FLinearColor MidnightBlue = { 0.098039225f, 0.098039225f, 0.439215720f, 1.000000000f };
	ue::FLinearColor MintCream = { 0.960784376f, 1.000000000f, 0.980392218f, 1.000000000f };
	ue::FLinearColor MistyRose = { 1.000000000f, 0.894117713f, 0.882353008f, 1.000000000f };
	ue::FLinearColor Moccasin = { 1.000000000f, 0.894117713f, 0.709803939f, 1.000000000f };
	ue::FLinearColor NavajoWhite = { 1.000000000f, 0.870588303f, 0.678431392f, 1.000000000f };
	ue::FLinearColor Navy = { 0.000000000f, 0.000000000f, 0.501960814f, 1.000000000f };
	ue::FLinearColor OldLace = { 0.992156923f, 0.960784376f, 0.901960850f, 1.000000000f };
	ue::FLinearColor Olive = { 0.501960814f, 0.501960814f, 0.000000000f, 1.000000000f };
	ue::FLinearColor OliveDrab = { 0.419607878f, 0.556862772f, 0.137254909f, 1.000000000f };
	ue::FLinearColor Orange = { 1.000000000f, 0.647058845f, 0.000000000f, 1.000000000f };
	ue::FLinearColor OrangeRed = { 1.000000000f, 0.270588249f, 0.000000000f, 1.000000000f };
	ue::FLinearColor Orchid = { 0.854902029f, 0.439215720f, 0.839215755f, 1.000000000f };
	ue::FLinearColor PaleGoldenrod = { 0.933333397f, 0.909803987f, 0.666666687f, 1.000000000f };
	ue::FLinearColor PaleGreen = { 0.596078455f, 0.984313786f, 0.596078455f, 1.000000000f };
	ue::FLinearColor PaleTurquoise = { 0.686274529f, 0.933333397f, 0.933333397f, 1.000000000f };
	ue::FLinearColor PaleVioletRed = { 0.858823597f, 0.439215720f, 0.576470613f, 1.000000000f };
	ue::FLinearColor PapayaWhip = { 1.000000000f, 0.937254965f, 0.835294187f, 1.000000000f };
	ue::FLinearColor PeachPuff = { 1.000000000f, 0.854902029f, 0.725490212f, 1.000000000f };
	ue::FLinearColor Peru = { 0.803921640f, 0.521568656f, 0.247058839f, 1.000000000f };
	ue::FLinearColor Pink = { 1.000000000f, 0.752941251f, 0.796078503f, 1.000000000f };
	ue::FLinearColor Plum = { 0.866666734f, 0.627451003f, 0.866666734f, 1.000000000f };
	ue::FLinearColor PowderBlue = { 0.690196097f, 0.878431439f, 0.901960850f, 1.000000000f };
	ue::FLinearColor Purple = { 0.501960814f, 0.000000000f, 0.501960814f, 1.000000000f };
	ue::FLinearColor Red = { 1.000000000f, 0.000000000f, 0.000000000f, 1.000000000f };
	ue::FLinearColor RosyBrown = { 0.737254918f, 0.560784340f, 0.560784340f, 1.000000000f };
	ue::FLinearColor RoyalBlue = { 0.254901975f, 0.411764741f, 0.882353008f, 1.000000000f };
	ue::FLinearColor SaddleBrown = { 0.545098066f, 0.270588249f, 0.074509807f, 1.000000000f };
	ue::FLinearColor Salmon = { 0.980392218f, 0.501960814f, 0.447058856f, 1.000000000f };
	ue::FLinearColor SandyBrown = { 0.956862807f, 0.643137276f, 0.376470625f, 1.000000000f };
	ue::FLinearColor SeaGreen = { 0.180392161f, 0.545098066f, 0.341176480f, 1.000000000f };
	ue::FLinearColor SeaShell = { 1.000000000f, 0.960784376f, 0.933333397f, 1.000000000f };
	ue::FLinearColor Sienna = { 0.627451003f, 0.321568638f, 0.176470593f, 1.000000000f };
	ue::FLinearColor Silver = { 0.752941251f, 0.752941251f, 0.752941251f, 1.000000000f };
	ue::FLinearColor SkyBlue = { 0.529411793f, 0.807843208f, 0.921568692f, 1.000000000f };
	ue::FLinearColor SlateBlue = { 0.415686309f, 0.352941185f, 0.803921640f, 1.000000000f };
	ue::FLinearColor SlateGray = { 0.439215720f, 0.501960814f, 0.564705908f, 1.000000000f };
	ue::FLinearColor Snow = { 1.000000000f, 0.980392218f, 0.980392218f, 1.000000000f };
	ue::FLinearColor SpringGreen = { 0.000000000f, 1.000000000f, 0.498039246f, 1.000000000f };
	ue::FLinearColor SteelBlue = { 0.274509817f, 0.509803951f, 0.705882370f, 1.000000000f };
	ue::FLinearColor Tan = { 0.823529482f, 0.705882370f, 0.549019635f, 1.000000000f };
	ue::FLinearColor Teal = { 0.000000000f, 0.501960814f, 0.501960814f, 1.000000000f };
	ue::FLinearColor Thistle = { 0.847058892f, 0.749019623f, 0.847058892f, 1.000000000f };
	ue::FLinearColor Tomato = { 1.000000000f, 0.388235331f, 0.278431386f, 1.000000000f };
	ue::FLinearColor Transparent = { 0.000000000f, 0.000000000f, 0.000000000f, 0.000000000f };
	ue::FLinearColor Turquoise = { 0.250980407f, 0.878431439f, 0.815686345f, 1.000000000f };
	ue::FLinearColor Violet = { 0.933333397f, 0.509803951f, 0.933333397f, 1.000000000f };
	ue::FLinearColor Wheat = { 0.960784376f, 0.870588303f, 0.701960802f, 1.000000000f };
	ue::FLinearColor White = { 1.000000000f, 1.000000000f, 1.0f, 1.000000000f };
	ue::FLinearColor WhiteSmoke = { 0.960784376f, 0.960784376f, 0.960784376f, 1.000000000f };
	ue::FLinearColor Yellow = { 1.000000000f, 1.000000000f, 0.000000000f, 1.000000000f };
	ue::FLinearColor YellowGreen = { 0.603921592f, 0.803921640f, 0.196078449f, 1.000000000f };
};


ue::FLinearColor getColorFromTier(BYTE Tier) {
	ue::FLinearColor color = { 255.f, 255.f, 255.f, 1 };

	if (Tier == 1)
		color = { 255.f, 255.f, 255.f, 1 };
	else if (Tier == 2)
		color = { Colors::LightGreen };
	else if (Tier == 3)
		color = { 0.f, 1.f, 1.f, 1 };
	else if (Tier == 4)
		color = { Colors::DarkCyan };
	else if (Tier == 5)
		color = { 1.f, 1.f, 0.f, 1 };

	return color;
}

void DrawTriangle(UCanvas* pCanvas, const ue::FVector2D& point1, const ue::FVector2D& point2, const ue::FVector2D& point3, const ue::FLinearColor& color, bool isFilled)
{
	/*static float devParam = 0;
	if (GetAsyncKeyState(VK_F1) & 1) {
		devParam += 1;
	}
	if (GetAsyncKeyState(VK_F2) & 1) {
		devParam -= 1;
	}*/
	//pCanvas->K2_DrawLine(FVector2D(224, 74), FVector2D(299, 74), 1.0f, color);
	pCanvas->K2_DrawLine(point1, point2, 1.0f, color);
	//float halfPositionX = point1.X + (DistanceBetween2Points(point1.X, point1.Y, point2.X, point2.Y) / 2);
	//pCanvas->K2_DrawLine(point1, FVector2D(halfPositionX, 150), 1.0f, color);
	pCanvas->K2_DrawLine(point1, point3, 1.0f, color);
	pCanvas->K2_DrawLine(point2, point3, 1.0f, color);
	// Fill it
	if (isFilled) {
		float addX = 0.5f;
		float addY = 1;
		for (int i = point1.Y; i < point3.Y; i++) {
			// draw line
			pCanvas->K2_DrawLine(ue::FVector2D(point1.X + addX, point1.Y + addY), ue::FVector2D(point2.X - addX, point2.Y + addY), 1.0f, color);
			addY++;
			addX += 0.5f;
		}
	}
}

void DrawFilledRect(UCanvas* pCanvas, ue::FVector2D initial_pos, float width, float height, ue::FLinearColor color)
{
	for (float i = 0.0f; i < height; i += 1.0f)
		pCanvas->K2_DrawLine(ue::FVector2D(initial_pos.X, initial_pos.Y + i), ue::FVector2D(initial_pos.X + width, initial_pos.Y + i), 1.0f, color);

}


void CheatInit()
{
	float closestTocenter = FLT_MAX;
	AFortPawn* targetpawn = nullptr;

	GWorld* WorldIndex = *(GWorld**)(Client::ImageBase + 0xEA84A78);
	UGameInstance* GameInstanceIndex = WorldIndex->OwningGameInstance();
	ULevel* PersistentLevelIndex = WorldIndex->PersistentLevel();
	ULocalPlayers* LocalPlayersIndex = GameInstanceIndex->LocalPlayers();
	ULocalPlayer* LocalPlayerIndex = LocalPlayersIndex->LocalPlayer();
	APlayerController* PlayerControllerIndex = LocalPlayerIndex->PlayerController();
	APlayerCameraManager* PlayerCameraManagerIndex = PlayerControllerIndex->PlayerCameraManager();
	AFortPawn* AcknowledgedPawnIndex = PlayerControllerIndex->LocalPawn();

	auto ActorArray = PersistentLevelIndex->ActorCount();
	auto ActorPointer = PersistentLevelIndex->Actors();

	for (int i = 0; i < ActorArray; i++)
	{
		AFortPawn* Actor = ActorPointer->GetCurrentActor(i);

		if (!Actor)
			continue;

		auto ActorPawn = ue::cached::KismetSystemLibraryA->GetObjectNamePool((UObject*)Actor); // crash maybe

		if (Actor == AcknowledgedPawnIndex)
			continue;

		if (strstr(ActorPawn.ToString().c_str(), "PlayerPawn")) {
			Vector3 head = Actor->GetBone(68);
			Vector2 head_w2s = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, head);

			if (Client::Settings::Visuals::VisibleCheck)
			{
				if (IsVisible(PlayerControllerIndex, Actor, 0))
				{
					if (Actor != AcknowledgedPawnIndex) {

						auto dx = head_w2s.x - (Width / 2);
						auto dy = head_w2s.y - (Height / 2);
						auto dist = sqrtf(dx * dx + dy * dy);

						if (dist < Client::Settings::Aimbot::FovCircleRadius && dist < closestTocenter) {
							closestTocenter = dist;
							targetpawn = Actor;
							headtarget = targetpawn->GetBone(68);
						}
					}
				}
			}
			else
			{
				if (Actor != AcknowledgedPawnIndex) {

					auto dx = head_w2s.x - (Width / 2);
					auto dy = head_w2s.y - (Height / 2);
					auto dist = sqrtf(dx * dx + dy * dy);

					if (dist < Client::Settings::Aimbot::FovCircleRadius && dist < closestTocenter) {
						closestTocenter = dist;
						targetpawn = Actor;
						headtarget = targetpawn->GetBone(68);
					}
				}
			}

			if (Client::Settings::Aimbot::MemoryAimbot and targetpawn and (safe_call(GetAsyncKeyState)(VK_RBUTTON)))
			{
				Vector2 headtarget_w2s = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, headtarget);

				auto camloc = PlayerCameraManagerIndex->GetCameraLocation();

				auto NewRotation = galgan(camloc, headtarget);

				PlayerControllerIndex->ClientSetRotation(NewRotation, false);
			}

			Vector2 head2_w2s = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, { head.x, head.y, head.z + 20 });

			{
				Vector3 bottom = Actor->GetBone(0);

				Vector2 bottom_w2s = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, { bottom.x, bottom.y, bottom.z });
				ue::FLinearColor col = ue::FLinearColor(255.f, 0.f, 0.f, 255.f);

				if (Client::Settings::Visuals::VisibleCheck)
				{
					if (IsVisible(PlayerControllerIndex, Actor, 0))
					{
						col = ue::FLinearColor(255.f, 0.f, 0.f, 255.f);
					}
					else
					{
						col = ue::FLinearColor(255.f, 255.f, 255.f, 255.f);
					}
				}
				else
				{
					col = ue::FLinearColor(255.f, 0.f, 0.f, 255.f);
				}

				float BoxHeight = (float)(bottom_w2s.y - head2_w2s.y);
				float BoxWidth = BoxHeight * 0.60f;

				float BottomLeftX = (float)head2_w2s.x - BoxWidth / 2;
				float BottomLeftY = (float)bottom_w2s.y;

				float BottomRightX = (float)head2_w2s.x + BoxWidth / 2;
				float BottomRightY = (float)bottom_w2s.y;

				float TopRightX = (float)head2_w2s.x + BoxWidth / 2;
				float TopRightY = (float)head2_w2s.y;

				float TopLeftX = (float)head2_w2s.x - BoxWidth / 2;
				float TopLeftY = (float)head2_w2s.y;

				float TextOffset_Y = head2_w2s.y;
				float TextOffset_X = TopRightX + 5;

				Vector2 calculation;

				if (Client::Settings::Visuals::Box) {
					static_canvas->K2_DrawLine({ BottomLeftX, BottomLeftY }, { BottomRightX, BottomRightY }, 1.f, col);
					static_canvas->K2_DrawLine({ BottomRightX, BottomRightY }, { TopRightX, TopRightY }, 1.f, col);
					static_canvas->K2_DrawLine({ TopRightX, TopRightY }, { TopLeftX, TopLeftY }, 1.f, col);
					static_canvas->K2_DrawLine({ TopLeftX, TopLeftY }, { BottomLeftX, BottomLeftY }, 1.f, col);
				}


				if (Client::Settings::Visuals::CornerBox)
				{
					float BoxHeight = bottom_w2s.y - head2_w2s.y;
					float BoxWidth = BoxHeight / 2.1f;
					static_canvas->DrawCorneredBox(head2_w2s.x - (BoxWidth / 2), head2_w2s.y, BoxWidth, BoxHeight, col, 2.f);
				}

				float heightA = abs(head_w2s.y - bottom_w2s.y);
				float widthA = heightA * 0.65f;
				auto Size = ue::FVector2D(widthA, heightA);
				auto Pos = ue::FVector2D(head_w2s.x - widthA / 2, head_w2s.y);
				auto centerTop = ue::FVector2D(Pos.X + (Size.X / 2), Pos.Y);			

				if (Client::Settings::Visuals::Name) {
					auto name = Actor->PlayerState()->GetPlayerName();
					if (name.wide()) {
						TextOffset_Y += static_canvas->K2_TextSize(FString(name)).Y + 15;
						calculation = Vector2(head2_w2s.x, head2_w2s.y + 25);
						static_canvas->K2_DrawText({ calculation.x,calculation.y }, ue::FLinearColor(255.f, 0.f, 0.f, 1.f), name, true, true);
					}
				}


				if (Client::Settings::Visuals::Distance) {
					int dist = PlayerCameraManagerIndex->GetCameraLocation().Distance(Actor->RootComponent()->RelativeLocation()) / 100;
					static char distanceesp[128];
					static wchar_t wdistanceesp[128];
					sprintf(distanceesp, ("%dm"), dist);
					AnsiToWide(distanceesp, wdistanceesp);
					TextOffset_Y += static_canvas->K2_TextSize(FString(wdistanceesp)).Y;
					calculation = Vector2(head2_w2s.x, head2_w2s.y + 35);
					static_canvas->K2_DrawText({ calculation.x,calculation.y }, ue::FLinearColor(255.f, 255.f, 0.f, 1.f), wdistanceesp, true, true);
				}

				Vector2 ChestAtLeft = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(37));
				Vector2 ChestAtRight = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(8));
				Vector2 Chest = { ChestAtLeft.x + (ChestAtRight.x - ChestAtLeft.x) / 2, ChestAtLeft.y };
				ue::FLinearColor Color = ue::FLinearColor(255.f, 0.f, 0.f, 0.f);
				if (Client::Settings::Visuals::Skeleton) {
					Vector2 Neck = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(66));
					Vector2 LeftShoulder = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(38));
					Vector2 RightShoulder = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(9));
					Vector2 LeftElbow = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(39));
					Vector2 RightElbow = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(10));
					Vector2 LeftHand = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(62));
					Vector2 RightHand = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(33));
					Vector2 LeftLeg = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(78));
					Vector2 RightLeg = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(71));
					Vector2 LeftThigh = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(84));
					Vector2 RightThigh = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(77));
					Vector2 LeftFoot = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(81));
					Vector2 RightFoot = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(73));
					Vector2 LeftFeet = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(82));
					Vector2 RightFeet = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(86));
					Vector2 LeftFeetFinger = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(83));
					Vector2 RightFeetFinger = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(76));
					Vector2 Bottom = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(0));
					Vector2 Pelvis = PlayerCameraManagerIndex->ProjectWorldLocationToScreen(Width, Height, Actor->GetBone(2));

					static_canvas->K2_DrawLine({ Neck.x, Neck.y }, { Chest.x,Chest.y }, 1, Color);
					static_canvas->K2_DrawLine({ Chest.x,Chest.y }, { Pelvis.x,Pelvis.y }, 1, Color);
					static_canvas->K2_DrawLine({ Chest.x,Chest.y }, { LeftShoulder.x,LeftShoulder.y }, 1, Color);
					static_canvas->K2_DrawLine({ Chest.x,Chest.y }, { RightShoulder.x , RightShoulder.y }, 1, Color);
					static_canvas->K2_DrawLine({ LeftShoulder.x,LeftShoulder.y }, { LeftElbow.x,LeftElbow.y }, 1, Color);
					static_canvas->K2_DrawLine({ RightShoulder.x,RightShoulder.y }, { RightElbow.x ,RightElbow.y }, 1, Color);
					static_canvas->K2_DrawLine({ LeftElbow.x, LeftElbow.y }, { LeftHand.x, LeftHand.y }, 1, Color);
					static_canvas->K2_DrawLine({ RightElbow.x,RightElbow.y }, { RightHand.x ,RightHand.y }, 1, Color);
					static_canvas->K2_DrawLine({ Pelvis.x,Pelvis.y }, { LeftLeg.x,LeftLeg.y }, 1, Color);
					static_canvas->K2_DrawLine({ Pelvis.x,Pelvis.y }, { RightLeg.x ,RightLeg.y }, 1, Color);
					static_canvas->K2_DrawLine({ LeftLeg.x,LeftLeg.y }, { LeftThigh.x,LeftThigh.y }, 1, Color);
					static_canvas->K2_DrawLine({ RightLeg.x,RightLeg.y }, { RightThigh.x, RightThigh.y }, 1, Color);
					static_canvas->K2_DrawLine({ LeftThigh.x,LeftThigh.y }, { LeftFoot.x , LeftFoot.y }, 1, Color);
					static_canvas->K2_DrawLine({ RightThigh.x, RightThigh.y }, { RightFoot.x, RightFoot.y }, 1, Color);
					static_canvas->K2_DrawLine({ LeftFoot.x,LeftFoot.y }, { LeftFeet.x ,LeftFeet.y }, 1, Color);
					static_canvas->K2_DrawLine({ RightFoot.x,RightFoot.y }, { RightFeet.x, RightFeet.y }, 1, Color);

				}
			}
		}
	}

}

void PostRender(uintptr_t this_, UCanvas* Canvas) {
	if (!Canvas) {
		return PostRenderOriginal(this_, Canvas);
	}

	static_canvas = (UCanvas*)Canvas;
	auto width = static_canvas->SizeX();
	auto height = static_canvas->SizeY();

	if (Client::Settings::Aimbot::FovCircle)
		static_canvas->K2_DrawFOV(Vector2(Width / 2, Height / 2), Client::Settings::Aimbot::FovCircleRadius, { 1.f, 0.f, 0.f, 1.f });

	static_canvas->K2_DrawLine(ue::FVector2D(Width / 2 + 10, Height / 2), ue::FVector2D(Width / 2 - 10, Height / 2), 1.f, { 1.f, 0.f, 0.f, 1.f });
	static_canvas->K2_DrawLine(ue::FVector2D(Width / 2, Height / 2 + 10), ue::FVector2D(Width / 2, Height / 2 - 10), 1.f, { 1.f, 0.f, 0.f, 1.f });

	static int CurrentTab = 1;

	zgui::drawlist::SetCanvas(Canvas);
	zgui::PollInput("Fortnite  ");
	zgui::BeginWindow("Ajdin", ue::FVector2D(400.f, 400.f), VK_F8); {
		if (zgui::Button("Aiming", ue::FVector2D(174.f, 30.f))) CurrentTab = 1;
		zgui::SameLine();
		if (zgui::Button("Visuals", ue::FVector2D(174.f, 30.f))) CurrentTab = 2;
		zgui::SameLine(0.f);

		switch (CurrentTab) {
		case 1:
			zgui::Checkbox("     Enable Aimbot", &Client::Settings::Aimbot::MemoryAimbot);
			zgui::Checkbox("     Fov Circle", &Client::Settings::Aimbot::FovCircle);
			zgui::SliderFloat("", 5.f, 360.f, &Client::Settings::Aimbot::FovCircleRadius);
			break;
		case 2:
			zgui::Checkbox("     Skeleton ESP", &Client::Settings::Visuals::Skeleton);

			zgui::Checkbox("     Normal Box ESP", &Client::Settings::Visuals::Box);
			zgui::Checkbox("     Cornered Box ESP", &Client::Settings::Visuals::CornerBox);

			zgui::Checkbox("     Distance ESP", &Client::Settings::Visuals::Distance);
			zgui::Checkbox("     Name ESP", &Client::Settings::Visuals::Name);
			break;
		}
		zgui::EndWindow();
	}

	CheatInit();

	return PostRenderOriginal(this_, Canvas);
}


BOOL InitiliazeMain()
{
	Client::CreatConsole();
	Client::ImageBase = Client::GetImageBase();

	Width = safe_call(GetSystemMetrics)(0);
	Height = safe_call(GetSystemMetrics)(1);
	ue::cached::objects::render::Font = UObject::StaticFindObject(nullptr, nullptr, L"/Engine/EngineFonts/Roboto.Roboto", false);
	std::cout << "Font " << ue::cached::objects::render::Font << std::endl;

	ue::cached::objects::render::K2_DrawLine = UObject::StaticFindObject(nullptr, nullptr, L"Canvas.K2_DrawLine", false);
	std::cout << "K2_DrawLine " << ue::cached::objects::render::K2_DrawLine << std::endl;
	ue::cached::objects::render::K2_DrawBox = UObject::StaticFindObject(nullptr, nullptr, L"Canvas.K2_DrawBox", false);
	std::cout << "K2_DrawBox " << ue::cached::objects::render::K2_DrawBox << std::endl;
	ue::cached::objects::render::K2_DrawText = UObject::StaticFindObject(nullptr, nullptr, L"Canvas.K2_DrawText", false);
	std::cout << "K2_DrawText " << ue::cached::objects::render::K2_DrawText << std::endl;
	ue::cached::objects::render::K2_TextSize = UObject::StaticFindObject(nullptr, nullptr, L"Canvas.K2_TextSize", false);
	std::cout << "K2_TextSize " << ue::cached::objects::render::K2_TextSize << std::endl;
	ue::cached::objects::camera::GetCameraLocation = UObject::StaticFindObject(nullptr, nullptr, L"PlayerCameraManager.GetCameraLocation", false);
	ue::cached::objects::camera::GetCameraRotation = UObject::StaticFindObject(nullptr, nullptr, L"PlayerCameraManager.GetCameraRotation", false);
	ue::cached::objects::camera::GetFOVAngle = UObject::StaticFindObject(nullptr, nullptr, L"PlayerCameraManager.GetFOVAngle", false);
	ue::cached::objects::actor::ClientSetRotation = UObject::StaticFindObject(nullptr, nullptr, L"Controller.ClientSetRotation", false);
	ue::cached::objects::actor::GetPlayerName = UObject::StaticFindObject(nullptr, nullptr, L"PlayerState.GetPlayerName", false);
	ue::cached::objects::render::K2_TextSize = UObject::StaticFindObject(nullptr, nullptr, L"Canvas.K2_TextSize", false);
	ue::cached::kismetobjectname = UObject::StaticFindObject(nullptr, nullptr, L"Engine.KismetSystemLibrary.GetObjectName", false);

	ue::cached::KismetSystemLibraryA = (KismetSystemLibrary*)UObject::StaticFindObject(nullptr, nullptr, L"Engine.KismetSystemLibrary", false);
	FortProjectileBase = UObject::StaticFindObject(nullptr, nullptr, L"FortniteGame.FortProjectileBase", false);

	ue::cached::objects::IsReloading = UObject::StaticFindObject(nullptr, nullptr, L"FortWeapon.IsReloading", false);

	std::cout << "Projectile Class: " << FortProjectileBase << std::endl;

	GameplayStatics = UGameplayStatics::StaticClass();
	Sleep(200);

	GWorld* WorldIndex = *(GWorld**)(Client::ImageBase + 0xEA84A78); //old 0x102f69d8 + 1 1180
	std::cout << "WorldIndex " << WorldIndex << std::endl;
	UGameInstance* GameInstanceIndex = WorldIndex->OwningGameInstance();
	std::cout << "GameInstanceIndex " << GameInstanceIndex << std::endl;
	ULocalPlayers* LocalPlayersIndex = GameInstanceIndex->LocalPlayers();
	std::cout << "LocalPlayersIndex " << LocalPlayersIndex << std::endl;
	ULocalPlayer* LocalPlayerIndex = LocalPlayersIndex->LocalPlayer();
	std::cout << "LocalPlayerIndex " << LocalPlayerIndex << std::endl;
	UViewportClient* ViewportClientIndex = LocalPlayerIndex->ViewportClient();
	std::cout << "ViewportClientIndex " << ViewportClientIndex << std::endl;

	void** PostRender_Hj = *(void***)(ViewportClientIndex);
	unsigned long Window_Protection;
	safe_call(VirtualProtect)(&PostRender_Hj[110], 8, 0x40, &Window_Protection);
	PostRenderOriginal = decltype(PostRenderOriginal)(PostRender_Hj[110]);
	PostRender_Hj[110] = &PostRender;
	safe_call(VirtualProtect)(&PostRender_Hj[110], 8, Window_Protection, &Window_Protection);

	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		InitiliazeMain();
	}
	return TRUE;
}