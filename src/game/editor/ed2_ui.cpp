#include "ed2_ui.h"
#include <stdio.h> // sscanf
#include <engine/textrender.h>
#include <engine/keys.h>
#include <game/client/gameclient.h> // Localize

void CEditor2Ui::DrawRect(const CUIRect& Rect, const vec4& Color)
{
	Graphics()->TextureClear();
	Graphics()->QuadsBegin();
	IGraphics::CQuadItem Quad(Rect.x, Rect.y, Rect.w, Rect.h);
	Graphics()->SetColor(Color.r*Color.a, Color.g*Color.a, Color.b*Color.a, Color.a);
	Graphics()->QuadsDrawTL(&Quad, 1);
	Graphics()->QuadsEnd();
}

void CEditor2Ui::DrawRectBorder(const CUIRect& Rect, const vec4& Color, float Border, const vec4 BorderColor)
{
	float ScreenX0, ScreenY0, ScreenX1, ScreenY1;
	Graphics()->GetScreen(&ScreenX0, &ScreenY0, &ScreenX1, &ScreenY1);
	const float FakeToScreenX = Graphics()->ScreenWidth()/(ScreenX1-ScreenX0);
	const float FakeToScreenY = Graphics()->ScreenHeight()/(ScreenY1-ScreenY0);
	const float BorderW = Border/FakeToScreenX;
	const float BorderH = Border/FakeToScreenY;

	Graphics()->TextureClear();
	Graphics()->QuadsBegin();

	// border pass
	if(Color.a == 1)
	{
		IGraphics::CQuadItem Quad(Rect.x, Rect.y, Rect.w, Rect.h);
		Graphics()->SetColor(BorderColor.r*BorderColor.a, BorderColor.g*BorderColor.a,
							 BorderColor.b*BorderColor.a, BorderColor.a);
		Graphics()->QuadsDrawTL(&Quad, 1);
	}
	else
	{
		// border pass
		IGraphics::CQuadItem Quads[4] = {
			IGraphics::CQuadItem(Rect.x, Rect.y, BorderW, Rect.h),
			IGraphics::CQuadItem(Rect.x+Rect.w-BorderW, Rect.y, BorderW, Rect.h),
			IGraphics::CQuadItem(Rect.x+BorderW, Rect.y, Rect.w-BorderW, BorderH),
			IGraphics::CQuadItem(Rect.x+BorderW, Rect.y+Rect.h-BorderH, Rect.w-BorderW, BorderH)
		};
		Graphics()->SetColor(BorderColor.r*BorderColor.a, BorderColor.g*BorderColor.a,
							 BorderColor.b*BorderColor.a, BorderColor.a);
		Graphics()->QuadsDrawTL(Quads, 4);
	}

	// front pass
	if(Color.a > 0.001)
	{
		IGraphics::CQuadItem QuadCenter(Rect.x + BorderW, Rect.y + BorderH,
										Rect.w - BorderW*2, Rect.h - BorderH*2);
		Graphics()->SetColor(Color.r*Color.a, Color.g*Color.a,
							 Color.b*Color.a, Color.a);
		Graphics()->QuadsDrawTL(&QuadCenter, 1);
	}

	Graphics()->QuadsEnd();
}

void CEditor2Ui::DrawRectBorderOutside(const CUIRect& Rect, const vec4& Color, float Border, const vec4 BorderColor)
{
	float ScreenX0, ScreenY0, ScreenX1, ScreenY1;
	Graphics()->GetScreen(&ScreenX0, &ScreenY0, &ScreenX1, &ScreenY1);
	const float FakeToScreenX = Graphics()->ScreenWidth()/(ScreenX1-ScreenX0);
	const float FakeToScreenY = Graphics()->ScreenHeight()/(ScreenY1-ScreenY0);
	const float BorderW = Border/FakeToScreenX;
	const float BorderH = Border/FakeToScreenY;

	Graphics()->TextureClear();
	Graphics()->QuadsBegin();

	// border pass
	if(Color.a == 1)
	{
		IGraphics::CQuadItem Quad(Rect.x-BorderW, Rect.y-BorderH, Rect.w+BorderW*2, Rect.h+BorderH*2);
		Graphics()->SetColor(BorderColor.r*BorderColor.a, BorderColor.g*BorderColor.a,
							 BorderColor.b*BorderColor.a, BorderColor.a);
		Graphics()->QuadsDrawTL(&Quad, 1);
	}
	else
	{
		// border pass
		IGraphics::CQuadItem Quads[4] = {
			IGraphics::CQuadItem(Rect.x-BorderW, Rect.y-BorderH, BorderW, Rect.h+BorderH*2),
			IGraphics::CQuadItem(Rect.x+Rect.w, Rect.y-BorderH, BorderW, Rect.h+BorderH*2),
			IGraphics::CQuadItem(Rect.x, Rect.y-BorderH, Rect.w, BorderH),
			IGraphics::CQuadItem(Rect.x, Rect.y+Rect.h, Rect.w, BorderH)
		};
		Graphics()->SetColor(BorderColor.r*BorderColor.a, BorderColor.g*BorderColor.a,
							 BorderColor.b*BorderColor.a, BorderColor.a);
		Graphics()->QuadsDrawTL(Quads, 4);
	}

	// front pass
	if(Color.a > 0.001)
	{
		IGraphics::CQuadItem QuadCenter(Rect.x, Rect.y, Rect.w, Rect.h);
		Graphics()->SetColor(Color.r*Color.a, Color.g*Color.a,
							 Color.b*Color.a, Color.a);
		Graphics()->QuadsDrawTL(&QuadCenter, 1);
	}

	Graphics()->QuadsEnd();
}

void CEditor2Ui::DrawRectBorderMiddle(const CUIRect& Rect, const vec4& Color, float Border, const vec4 BorderColor)
{
	float ScreenX0, ScreenY0, ScreenX1, ScreenY1;
	Graphics()->GetScreen(&ScreenX0, &ScreenY0, &ScreenX1, &ScreenY1);
	const float FakeToScreenX = Graphics()->ScreenWidth()/(ScreenX1-ScreenX0);
	const float FakeToScreenY = Graphics()->ScreenHeight()/(ScreenY1-ScreenY0);
	const float BorderW = Border/FakeToScreenX;
	const float BorderH = Border/FakeToScreenY;
	const float BorderWhalf = BorderW/2.f;
	const float BorderHhalf = BorderH/2.f;

	Graphics()->TextureClear();
	Graphics()->QuadsBegin();

	// border pass
	if(Color.a == 1)
	{
		IGraphics::CQuadItem Quad(Rect.x-BorderWhalf, Rect.y-BorderHhalf, Rect.w+BorderW, Rect.h+BorderH);
		Graphics()->SetColor(BorderColor.r*BorderColor.a, BorderColor.g*BorderColor.a,
							 BorderColor.b*BorderColor.a, BorderColor.a);
		Graphics()->QuadsDrawTL(&Quad, 1);
	}
	else
	{
		// border pass
		IGraphics::CQuadItem Quads[4] = {
			IGraphics::CQuadItem(Rect.x-BorderWhalf, Rect.y-BorderHhalf, BorderW, Rect.h+BorderH),
			IGraphics::CQuadItem(Rect.x+Rect.w-BorderHhalf, Rect.y-BorderHhalf, BorderW, Rect.h+BorderH),
			IGraphics::CQuadItem(Rect.x, Rect.y-BorderHhalf, Rect.w, BorderH),
			IGraphics::CQuadItem(Rect.x, Rect.y+Rect.h-BorderHhalf, Rect.w, BorderH)
		};
		Graphics()->SetColor(BorderColor.r*BorderColor.a, BorderColor.g*BorderColor.a,
							 BorderColor.b*BorderColor.a, BorderColor.a);
		Graphics()->QuadsDrawTL(Quads, 4);
	}

	// front pass
	if(Color.a > 0.001)
	{
		IGraphics::CQuadItem QuadCenter(Rect.x+BorderWhalf, Rect.y+BorderHhalf,
			Rect.w-BorderW, Rect.h-BorderH);
		Graphics()->SetColor(Color.r*Color.a, Color.g*Color.a,
							 Color.b*Color.a, Color.a);
		Graphics()->QuadsDrawTL(&QuadCenter, 1);
	}

	Graphics()->QuadsEnd();
}

void CEditor2Ui::DrawText(const CUIRect& Rect, const char* pText, float FontSize, vec4 Color)
{
	const float OffY = (Rect.h - FontSize - 3.0f) * 0.5f;
	CTextCursor Cursor;
	TextRender()->SetCursor(&Cursor, Rect.x + OffY, Rect.y + OffY, FontSize, TEXTFLAG_RENDER);
	TextRender()->TextShadowed(&Cursor, pText, -1, vec2(0,0), vec4(0,0,0,0), Color);
}

void CEditor2Ui::UiDoButtonBehavior(const void* pID, const CUIRect& Rect, CUIButton* pButState)
{
	pButState->m_Clicked = false;

	if(UI()->CheckActiveItem(pID))
	{
		if(!UI()->MouseButton(0))
		{
			pButState->m_Clicked = true;
			UI()->SetActiveItem(0);
		}
	}

	pButState->m_Hovered = false;
	pButState->m_Pressed = false;

	if(UI()->MouseInside(&Rect) && UI()->MouseInsideClip())
	{
		pButState->m_Hovered = true;
		if(pID)
			UI()->SetHotItem(pID);

		if(UI()->MouseButton(0))
		{
			pButState->m_Pressed = true;
			if(pID && UI()->MouseButtonClicked(0))
				UI()->SetActiveItem(pID);
		}
	}
	else if(pID && UI()->HotItem() == pID)
	{
		UI()->SetHotItem(0);
	}

}

bool CEditor2Ui::UiDoMouseDragging(const void* pID, const CUIRect& Rect, CUIMouseDrag* pDragState)
{
	bool Return = false;
	CUIButton ButState;
	UiDoButtonBehavior(pID, Rect, &ButState);

	if((!pID || UI()->CheckActiveItem(pID)) && UI()->MouseButton(0))
	{
		if(!pDragState->m_IsDragging && UI()->MouseButtonClicked(0) && ButState.m_Pressed)
		{
			pDragState->m_StartDragPos = vec2(UI()->MouseX(), UI()->MouseY());
			pDragState->m_IsDragging = true;
		}
	}
	else
	{
		if(pDragState->m_IsDragging)
		{
			pDragState->m_EndDragPos = vec2(UI()->MouseX(), UI()->MouseY());
			Return = true; // finished dragging
		}
		pDragState->m_IsDragging = false;
	}

	return Return;
}

bool CEditor2Ui::UiButton(const CUIRect& Rect, const char* pText, CUIButton* pButState, float FontSize)
{
	return UiButtonEx(Rect, pText, pButState, StyleColorButton, StyleColorButtonHover,
		StyleColorButtonPressed, StyleColorButtonBorder, FontSize);
}

bool CEditor2Ui::UiButtonEx(const CUIRect& Rect, const char* pText, CUIButton* pButState, vec4 ColNormal,
	vec4 ColHover, vec4 ColPress, vec4 ColBorder, float FontSize)
{
	UiDoButtonBehavior(pButState, Rect, pButState);

	vec4 ShowButColor = ColNormal;
	if(pButState->m_Hovered)
		ShowButColor = ColHover;
	if(pButState->m_Pressed)
		ShowButColor = ColPress;

	DrawRectBorder(Rect, ShowButColor, 1, ColBorder);
	DrawText(Rect, pText, FontSize);
	return pButState->m_Clicked;
}

bool CEditor2Ui::UiTextInput(const CUIRect& Rect, char* pText, int TextMaxLength, CUITextInput* pInputState)
{
	UiDoButtonBehavior(pInputState, Rect, &pInputState->m_Button);
	if(pInputState->m_Button.m_Clicked)
	{
		UI()->SetActiveItem(pInputState);
	}
	else if(UI()->CheckActiveItem(pInputState) && !pInputState->m_Button.m_Hovered &&
		UI()->MouseButtonClicked(0))
	{
		UI()->SetActiveItem(0);
	}

	const bool PrevSelected = pInputState->m_Selected;
	pInputState->m_Selected = UI()->CheckActiveItem(pInputState);

	// just got selected
	if(!PrevSelected && pInputState->m_Selected)
	{
		pInputState->m_CursorPos = str_length(pText);
	}

	static float s_StartBlinkTime = 0;
	const int OldCursorPos = pInputState->m_CursorPos;

	bool Changed = false;
	if(pInputState->m_Selected)
	{
		for(int i = 0; i < Input()->NumEvents(); i++)
		{
			int Len = str_length(pText);
			int NumChars = Len;
			Changed |= CLineInput::Manipulate(Input()->GetEvent(i), pText, TextMaxLength, TextMaxLength,
				&Len, &pInputState->m_CursorPos, &NumChars, Input());
		}
	}

	const float FontSize = 8.0f;

	vec4 BorderColor;
	if(pInputState->m_Selected)
		BorderColor = StyleColorInputSelected;
	else if(pInputState->m_Button.m_Hovered)
		BorderColor = StyleColorButtonHover;
	else
		BorderColor = StyleColorButtonBorder;

	DrawRectBorder(Rect, vec4(0, 0, 0, 1), 1, BorderColor);
	DrawText(Rect, pText, FontSize);

	// cursor
	if(OldCursorPos != pInputState->m_CursorPos)
		s_StartBlinkTime = m_LocalTime;

	if(pInputState->m_Selected && fmod(m_LocalTime - s_StartBlinkTime, 1.0f) < 0.5f)
	{
		const float OffY = (Rect.h - FontSize - 3.0f) * 0.5f; // see DrawText
		float w = TextRender()->TextWidth(0, FontSize, pText, pInputState->m_CursorPos, -1);
		CUIRect CursorRect = Rect;
		CursorRect.x += w + OffY;
		CursorRect.y += 2;
		CursorRect.w = UI()->Screen()->w / Graphics()->ScreenWidth(); // 1px
		CursorRect.h -= 4;
		DrawRect(CursorRect, vec4(1,1,1,1));
	}

	return Changed;
}

bool CEditor2Ui::UiIntegerInput(const CUIRect& Rect, int* pInteger, CUIIntegerInput* pInputState)
{
	const int OldInteger = *pInteger;
	const u8 OldSelected = pInputState->m_TextInput.m_Selected;

	// string format, when value differ, empty or on select/deselect
	if((pInputState->m_Value != *pInteger && !OldSelected) ||
		(pInputState->m_aIntBuff[0] == 0 && !OldSelected) ||
		(OldSelected != pInputState->m_TextInput.m_Selected))
	{
		pInputState->m_Value = *pInteger;
		str_format(pInputState->m_aIntBuff, sizeof(pInputState->m_aIntBuff), "%d", *pInteger);
		pInputState->m_TextInput.m_CursorPos = str_length(pInputState->m_aIntBuff);
	}

	UiTextInput(Rect, pInputState->m_aIntBuff, sizeof(pInputState->m_aIntBuff), &pInputState->m_TextInput);

	// string parse
	if(sscanf(pInputState->m_aIntBuff, "%d", pInteger) < 1)
		*pInteger = 0;

	char aBuff[sizeof(pInputState->m_aIntBuff)];
	str_format(aBuff, sizeof(aBuff), "%d", *pInteger);
	const bool IsEmpty = pInputState->m_aIntBuff[0] == 0;
	const bool IsMinusOnly = pInputState->m_aIntBuff[0] == '-' && pInputState->m_aIntBuff[1] == 0;
	if(!IsEmpty && !IsMinusOnly && str_comp(aBuff, pInputState->m_aIntBuff) != 0)
	{
		pInputState->m_Value = *pInteger;
		str_copy(pInputState->m_aIntBuff, aBuff, sizeof(pInputState->m_aIntBuff));
		pInputState->m_TextInput.m_CursorPos = str_length(pInputState->m_aIntBuff);
	}

	return OldInteger != *pInteger;
}

bool CEditor2Ui::UiSliderInt(const CUIRect& Rect, int* pInt, int Min, int Max, CUIButton* pInputState)
{
	dbg_assert(false, "implement, see UiSliderFloat");

	const int OldInt = *pInt;
	UiDoButtonBehavior(pInputState, Rect, pInputState);
	DrawRect(Rect, StyleColorBg);

	*pInt = clamp(*pInt, Min, Max);
	float Progress = (float)*pInt/(Max-Min);
	CUIRect ProgressRect = Rect;
	ProgressRect.w = Rect.w * Progress;
	DrawRect(ProgressRect, StyleColorButtonHover);

	char aIntBuff[32];
	str_format(aIntBuff, sizeof(aIntBuff), "%d", *pInt);
	DrawText(Rect, aIntBuff, 8.0f, vec4(1,1,1,1));

	return OldInt != *pInt;
}

bool CEditor2Ui::UiSliderFloat(const CUIRect& Rect, float* pVal, float Min, float Max, CUIButton* pInputState,
	const vec4* pColor)
{
	const float OldInt = *pVal;
	UiDoButtonBehavior(pInputState, Rect, pInputState);

	// start grabbing
	if(!UI()->CheckActiveItem(pInputState) && pInputState->m_Pressed && UI()->MouseButtonClicked(0))
	{
		UI()->SetActiveItem(pInputState);
	}

	// stop grabbing
	if(UI()->CheckActiveItem(pInputState) && !UI()->MouseButton(0))
	{
		UI()->SetActiveItem(0);
	}

	if(UI()->CheckActiveItem(pInputState))
	{
		const float Precision = 200.0f; // TODO: precision should perhaps depend on exact rect pixel width
		float ClickedX = UI()->MouseX() - Rect.x;
		float Cx01 = clamp(ClickedX, 0.0f, Rect.w) / Rect.w;
		*pVal  = (int)(roundf(Cx01 * Precision)) * (Max-Min) / Precision + Min;
	}

	DrawRect(Rect, StyleColorBg);

	*pVal = clamp(*pVal, Min, Max);
	float Progress = *pVal/(Max-Min);
	CUIRect ProgressRect = Rect;
	ProgressRect.w = Rect.w * Progress;

	vec4 Color = StyleColorButtonHover;
	if(pColor)
		Color = *pColor;

	if(pInputState->m_Hovered)
		Color += vec4(0.1f, 0.1f, 0.1f, 0.0f);

	DrawRect(ProgressRect, Color);

	char aIntBuff[32];
	str_format(aIntBuff, sizeof(aIntBuff), "%.3f", *pVal);
	DrawText(Rect, aIntBuff, 8.0f, vec4(1,1,1,1));

	return OldInt != *pVal;
}

bool CEditor2Ui::UiCheckboxYesNo(const CUIRect& Rect, bool* pVal, CUICheckboxYesNo* pCbyn)
{
	const bool OldVal = *pVal;
	CUIRect YesRect, NoRect;
	Rect.VSplitMid(&NoRect, &YesRect);
	UiDoButtonBehavior(&pCbyn->m_NoBut, NoRect, &pCbyn->m_NoBut);
	UiDoButtonBehavior(&pCbyn->m_YesBut, YesRect, &pCbyn->m_YesBut);

	if(pCbyn->m_NoBut.m_Clicked)
		*pVal = false;
	if(pCbyn->m_YesBut.m_Clicked)
		*pVal = true;

	vec4 ColorYes = StyleColorButton;
	vec4 ColorNo = StyleColorButton;
	if(!*pVal)
	{
		ColorNo = StyleColorInputSelected;
		if(pCbyn->m_YesBut.m_Pressed)
			ColorYes = StyleColorButtonPressed;
		else if(pCbyn->m_YesBut.m_Hovered)
			ColorYes = StyleColorButtonPressed;
	}
	else
	{
		ColorYes = StyleColorInputSelected;
		if(pCbyn->m_NoBut.m_Pressed)
			ColorNo = StyleColorButtonPressed;
		else if(pCbyn->m_NoBut.m_Hovered)
			ColorNo = StyleColorButtonPressed;
	}

	DrawRect(NoRect, ColorNo);
	DrawRect(YesRect, ColorYes);
	DrawText(NoRect, Localize("No"), 8);
	DrawText(YesRect, Localize("Yes"), 8);

	return OldVal != *pVal;
}

bool CEditor2Ui::UiButtonSelect(const CUIRect& Rect, const char* pText, CUIButton* pButState, bool Selected,
	float FontSize)
{
	return UiButtonEx(Rect, pText, pButState, StyleColorButton, StyleColorButtonHover, StyleColorButtonPressed,
					  Selected ? vec4(1, 0, 0, 1):StyleColorButtonBorder, FontSize);
}

bool CEditor2Ui::UiGrabHandle(const CUIRect& Rect, CUIGrabHandle* pGrabHandle, const vec4& ColorNormal, const vec4& ColorActive)
{
	UiDoMouseDragging(pGrabHandle, Rect, pGrabHandle);
	const bool Active = IsInsideRect(vec2(UI()->MouseX(), UI()->MouseY()), Rect) || pGrabHandle->m_IsDragging;
	DrawRect(Rect, Active ? ColorActive : ColorNormal);
	pGrabHandle->m_IsGrabbed = UI()->CheckActiveItem(pGrabHandle);
	return pGrabHandle->m_IsDragging;
}


void CEditor2Ui::UiBeginScrollRegion(CScrollRegion* pSr, CUIRect* pClipRect, vec2* pOutOffset, const CScrollRegionParams* pParams)
{
	if(pParams)
		pSr->m_Params = *pParams;

	// only show scrollbar if content overflows
	const bool ShowScrollbar = pSr->m_ContentH > pClipRect->h;

	CUIRect ScrollBarBg;
	CUIRect* pModifyRect = ShowScrollbar ? pClipRect : 0;
	pClipRect->VSplitRight(pSr->m_Params.m_ScrollbarWidth, pModifyRect, &ScrollBarBg);
	ScrollBarBg.Margin(pSr->m_Params.m_ScrollbarMargin, &pSr->m_RailRect);

	if(ShowScrollbar)
	{
		if(pSr->m_Params.m_ScrollbarBgColor.a > 0)
			RenderTools()->DrawRoundRect(&ScrollBarBg, pSr->m_Params.m_ScrollbarBgColor, 4.0f);
		if(pSr->m_Params.m_RailBgColor.a > 0)
			RenderTools()->DrawRoundRect(&pSr->m_RailRect, pSr->m_Params.m_RailBgColor, 0);
	}
	else
		pSr->m_ContentScrollOff.y = 0;

	if(pSr->m_Params.m_ClipBgColor.a > 0)
		RenderTools()->DrawRoundRect(pClipRect, pSr->m_Params.m_ClipBgColor, 4.0f);

	UI()->ClipEnable(pClipRect);

	pSr->m_ClipRect = *pClipRect;
	pSr->m_ContentH = 0;
	*pOutOffset = pSr->m_ContentScrollOff;
}

void CEditor2Ui::UiEndScrollRegion(CScrollRegion* pSr)
{
	UI()->ClipDisable();

	dbg_assert(pSr->m_ContentH > 0, "Add some rects with ScrollRegionAddRect()");

	// only show scrollbar if content overflows
	if(pSr->m_ContentH <= pSr->m_ClipRect.h)
		return;

	// scroll wheel
	CUIRect RegionRect = pSr->m_ClipRect;
	RegionRect.w += pSr->m_Params.m_ScrollbarWidth;
	if(UI()->MouseInside(&RegionRect))
	{
		if(!UI()->NextHotItem())
			UI()->SetHotItem(pSr);

		if(Input()->KeyPress(KEY_MOUSE_WHEEL_UP))
			pSr->m_ScrollY -= pSr->m_Params.m_ScrollSpeed;
		else if(Input()->KeyPress(KEY_MOUSE_WHEEL_DOWN))
			pSr->m_ScrollY += pSr->m_Params.m_ScrollSpeed;
	}

	const float SliderHeight = max(pSr->m_Params.m_SliderMinHeight,
		pSr->m_ClipRect.h/pSr->m_ContentH * pSr->m_RailRect.h);

	CUIRect Slider = pSr->m_RailRect;
	Slider.h = SliderHeight;
	const float MaxScroll = pSr->m_RailRect.h - SliderHeight;

	if(pSr->m_RequestScrollY >= 0)
	{
		pSr->m_ScrollY = pSr->m_RequestScrollY/(pSr->m_ContentH - pSr->m_ClipRect.h) * MaxScroll;
		pSr->m_RequestScrollY = -1;
	}

	pSr->m_ScrollY = clamp(pSr->m_ScrollY, 0.0f, MaxScroll);
	Slider.y += pSr->m_ScrollY;

	bool Hovered = false;
	bool Grabbed = false;
	const void* pID = &pSr->m_ScrollY;
	int Inside = UI()->MouseInside(&Slider);

	if(Inside)
	{
		UI()->SetHotItem(pID);

		if(!UI()->CheckActiveItem(pID) && UI()->MouseButtonClicked(0))
		{
			UI()->SetActiveItem(pID);
			pSr->m_MouseGrabStart.y = UI()->MouseY();
		}

		Hovered = true;
	}

	if(UI()->CheckActiveItem(pID) && !UI()->MouseButton(0))
		UI()->SetActiveItem(0);

	// move slider
	if(UI()->CheckActiveItem(pID) && UI()->MouseButton(0))
	{
		float my = UI()->MouseY();
		pSr->m_ScrollY += my - pSr->m_MouseGrabStart.y;
		pSr->m_MouseGrabStart.y = my;

		Grabbed = true;
	}

	pSr->m_ScrollY = clamp(pSr->m_ScrollY, 0.0f, MaxScroll);
	pSr->m_ContentScrollOff.y = -pSr->m_ScrollY/MaxScroll * (pSr->m_ContentH - pSr->m_ClipRect.h);

	vec4 SliderColor = pSr->m_Params.m_SliderColor;
	if(Grabbed)
		SliderColor = pSr->m_Params.m_SliderColorGrabbed;
	else if(Hovered)
		SliderColor = pSr->m_Params.m_SliderColorHover;

	RenderTools()->DrawRoundRect(&Slider, SliderColor, 0);
}

void CEditor2Ui::UiScrollRegionAddRect(CScrollRegion* pSr, CUIRect Rect)
{
	vec2 ContentPos = vec2(pSr->m_ClipRect.x, pSr->m_ClipRect.y);
	ContentPos.x += pSr->m_ContentScrollOff.x;
	ContentPos.y += pSr->m_ContentScrollOff.y;
	pSr->m_LastAddedRect = Rect;
	pSr->m_ContentH = max(Rect.y + Rect.h - ContentPos.y, pSr->m_ContentH);
}

void CEditor2Ui::UiScrollRegionScrollHere(CScrollRegion* pSr, int Option)
{
	const float MinHeight = min(pSr->m_ClipRect.h, pSr->m_LastAddedRect.h);
	const float TopScroll = pSr->m_LastAddedRect.y -
		(pSr->m_ClipRect.y + pSr->m_ContentScrollOff.y);

	switch(Option)
	{
		case CScrollRegion::SCROLLHERE_TOP:
			pSr->m_RequestScrollY = TopScroll;
			break;

		case CScrollRegion::SCROLLHERE_BOTTOM:
			pSr->m_RequestScrollY = TopScroll - (pSr->m_ClipRect.h - MinHeight);
			break;

		case CScrollRegion::SCROLLHERE_KEEP_IN_VIEW:
		default: {
			const float dy = pSr->m_LastAddedRect.y - pSr->m_ClipRect.y;

			if(dy < 0)
				pSr->m_RequestScrollY = TopScroll;
			else if(dy > (pSr->m_ClipRect.h-MinHeight))
				pSr->m_RequestScrollY = TopScroll - (pSr->m_ClipRect.h - MinHeight);
		} break;
	}
}

bool CEditor2Ui::UiScrollRegionIsRectClipped(CScrollRegion* pSr, const CUIRect& Rect)
{
	return (pSr->m_ClipRect.x > (Rect.x + Rect.w)
		|| (pSr->m_ClipRect.x + pSr->m_ClipRect.w) < Rect.x
		|| pSr->m_ClipRect.y > (Rect.y + Rect.h)
		|| (pSr->m_ClipRect.y + pSr->m_ClipRect.h) < Rect.y);
}