#include "include.h"

void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR col)
{
	D3DRECT rect = { x, y, x + w, y + h };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, col, 0, 0);
}
void DrawLine(int x1, int y1, int x2, int y2, int thickness, bool antialias, D3DCOLOR col)
{
	ID3DXLine* lineL;
	D3DXCreateLine(pDevice, &lineL);

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(x1, y1);
	Line[1] = D3DXVECTOR2(x2, y2);
	
	lineL->SetWidth(thickness);
	lineL->SetAntialias(antialias);
	lineL->Draw(Line, 2, col);
	lineL->Release();
}
void DrawMessage(LPD3DXFONT font, unsigned int x, unsigned int y, int alptha, unsigned char r, unsigned char g, unsigned char b, LPCSTR Message) {
	D3DCOLOR fontColor = D3DCOLOR_ARGB(alptha, r, g, b);
	RECT rct;
	rct.left = x;
	rct.right = 1680;
	rct.top = y;
	rct.bottom = rct.top + 200;
	font ->DrawTextA(NULL, Message, -1, &rct, 0, fontColor);
}
void DrawHealthText(LPD3DXFONT font, unsigned int x, unsigned int y, int health, int armor) {
	D3DCOLOR whiteColor = D3DCOLOR_ARGB(255, 230, 230, 230);
	D3DCOLOR healthColor = D3DCOLOR_ARGB(255, 0, 230, 0);
	D3DCOLOR armorColor = D3DCOLOR_ARGB(255, 0, 0, 230);
	RECT rct;
	rct.left = x;
	rct.right = 1920;
	rct.top = y;
	rct.bottom = rct.top + 200;

	LPCSTR convertedHealth = std::to_string(health).c_str();
	LPCSTR convertedArmor = std::to_string(armor).c_str();

	LPCSTR htext = "HP: ";
	LPCSTR atext = "ARMOR: ";

	font->DrawTextA(NULL, htext, -1, &rct, 0, whiteColor);
	RECT rctu;
	rctu.left = x + 20;
	rctu.right = 1920;
	rctu.top = y;
	rctu.bottom = rct.top + 200;
	font->DrawTextA(NULL, convertedHealth, -1, &rctu, 0, healthColor);
	
	RECT rctx;
	rctx.left = x;
	rctx.right = 1680;
	rctx.top = y + 12;
	rctx.bottom = rct.top + 200;
	font->DrawTextA(NULL, atext, -1, &rctx, 0, armorColor);
}

void DrawBoundingBox(int baseX, int baseY, int width, int height, int thickness, bool antialias, D3DCOLOR color) {
	//Btn
	DrawLine(baseX - width / 2, baseY, baseX + width / 2, baseY, thickness, antialias, color);
	//Sides left
	DrawLine(baseX - width / 2, baseY - height, baseX - width / 2, baseY, thickness, antialias, color);
	//sides right
	DrawLine(baseX + width / 2, baseY - height, baseX + width / 2, baseY, thickness, antialias, color);
	//Line cross top
	DrawLine(baseX - width / 2, baseY - height, baseX + width / 2, baseY - height, thickness, antialias, color);
}

void DrawCorneredBox(int baseX, int baseY, int width, int height, int thickness, float coverage, bool antialias, D3DCOLOR color) {

	//Left Top
	DrawLine(baseX - width / 2, baseY - height, (baseX - width / 2) + (width * coverage), baseY - height, thickness, antialias, color); //top -> right
	DrawLine(baseX - width / 2, baseY - height, (baseX - width / 2), (baseY - height) + (height * coverage), thickness, antialias, color); // top -> down

	//Left Bottom
	DrawLine(baseX - width / 2, baseY, (baseX - width / 2) + (width * coverage), baseY, thickness, antialias, color); //btm -> right
	DrawLine(baseX - width / 2, baseY, baseX - width / 2, baseY - (height *  coverage), thickness, antialias, color); // btm -> up

	//Right Top
	DrawLine(baseX + width / 2, baseY - height, (baseX + width / 2) - (width * coverage), baseY - height, thickness, antialias, color); // top -> left
	DrawLine(baseX + width / 2, baseY - height, baseX + width / 2, (baseY - height) + (height * coverage), thickness, antialias, color); // top -> down

	//Right bottom
	DrawLine(baseX + width / 2, baseY, (baseX + width / 2) - (width * coverage), baseY, thickness, antialias, color); //btm -> right
	DrawLine(baseX + width / 2, baseY, baseX + width / 2, baseY - (height * coverage), thickness, antialias, color); // btm -> up
}

void DrawHealthBar(int baseX, int baseY, int width, int height, int thickness, bool antialias, int EntityHealth, int EntityArmor){

	ImColor HealthColor = { 0.0f, 0.8f, 0.0f, 1.0f };
	ImColor ArmorColor = { 0.0f, 0.0f, 0.8f, 1.0f };

	if (EntityHealth > 85){
		HealthColor = { 0.0f, 0.8f, 0.0f, 1.0f };
	}
	else if (EntityHealth > 50) {
		HealthColor = { 0.8f, 0.8f, 0.0f, 1.0f };
	}
	else {
		HealthColor = { 0.8f, 0.2f, 0.0f, 1.0f };
	}
	//- ((EntityHealth * baseY)/100) - (baseY / 100)*EntityHealth) - baseY + ((height / 100)*EntityHealth)
	//basY - height = bund punkt
	//basey = top
	int headPosY = baseY - height;
	int lengthButtomToHeadH= (height / 100) * EntityHealth;
	int lengthButtomToHeadA= (height / 100) * EntityArmor;

	//From top to buttom
	//First point - 
	//Secound point - baseY (buttom)
	DrawLine((baseX + width / 2) + 5, baseY - lengthButtomToHeadH, (baseX + width / 2) + 5, baseY, 3, antialias, ImColor_D3D(HealthColor));

	//DrawLine((baseX + width / 2) + 8, baseY - lengthButtomToHeadA, (baseX + width / 2) + 8, baseY, 3, antialias, ImColor_D3D(ArmorColor));
}

void DrawHealthbar2(int baseX, int baseY, int width, int headPosY, bool antialias, int EntityHealth) {

	int size = baseY + headPosY;

	ImColor HealthColor = { 0.0f, 0.8f, 0.0f, 1.0f };
	DrawLine(
		//point1
		(baseX + width / 2) + 5, 
		baseY, 
		
		//point2
		(baseX + width / 2) + 5,
		baseY - headPosY,

		3,
		antialias,
		ImColor_D3D(HealthColor));
}