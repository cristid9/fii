#include "stdafx.h"
#include "lab.h"
#include <windows.h>
#include <stdio.h>

static void Print(int x, int y, int foreground, int background, const char* Text)
{

	COORD c;

	c.X = x;

	c.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (foreground & 0x0F)+((background & 0x0F)<<4));

	printf("%s", Text);

}

UIButton::UIButton(UIControl* parent, bool state, string text)
{
	Parent = parent;
	State  = state;
	Text   = text;
}

UIControl* UIButton::GetParent() const
{
	return Parent;
}

void UIButton::Draw()
{	
	int background, foreground;

	if (GetState())
	{
		background = activeBackground;
		foreground = activeForeground;
	}
	else
	{
		foreground = inactiveForeground;
		background = inactiveBackground;
	}

	if (GetParent() != NULL)
	{
		X += GetParent()->GetX();
		Y += GetParent()->GetY();
	}

	int skips     = (Width - Text.size()) / 2;
	int remainder = (Width - Text.size()) % 2 == 0 ? skips : skips + 1;

	string filler = "";
	for (int i = 0; i < Height; i++)
		filler += " ";

	bool executed = false;
	for (int i = 0; i < Width; i++)
	{
		if (i == Width / 2 && !executed)
		{
			string tmp = "";
		
			for (int k = 0; k < skips; k++)
				tmp += " ";

			tmp += Text;

			for (int k = 0; k < remainder; k++)
				tmp += " ";
			
			Print(X, Y + i, background, foreground, tmp.c_str());
	   		executed = true;
		}
		else
		{
			Print(X, Y + i, background, foreground, filler.c_str());
		}
	}
}

void UIButton::SetAttributes(int x, int y, int width_, int height_)
{
	X      = x;
	Y      = y;
	Width  = width_;
	Height = height_;
}

int UIButton::GetX() const
{
	return X;
}

int UIButton::GetY() const 
{
	return Y;
}

void UIButton::SetState(bool value)
{
	State = value;
}

bool UIButton::GetState() const
{
	return State;
}


UILabel::UILabel(UIControl* parent, string text, int x, int y)
{
	Parent = parent;
	Text   = text;
	X      = x;
	Y      = y;
}

UIControl* UILabel::GetParent() const
{
	return Parent;
}

void UILabel::Draw() 
{
	if (GetParent() != NULL)
	{
		X += GetParent()->GetX();
		Y += GetParent()->GetY();
	}

	Print(X, Y, foreground, background, Text.c_str());
}

int UILabel::GetX() const
{
	return X;
}

int UILabel::GetY() const
{
	return Y;
}

UIPanel::UIPanel(UIControl* parent, int x, int y)
{
	Parent = parent;
	X      = x;
	Y      = y;
}

void UIPanel::AddControl(UIControl* control)
{
	Controls.push_back(control);
}

void UIPanel::Draw()
{
	for (auto it = Controls.begin(); it != Controls.end(); it++)
	{
		(*it)->Draw();
	}
}

int UIPanel::GetX() const
{
	return X;
}

int UIPanel::GetY() const
{
	return Y;
}

UIControl* UIPanel::GetParent() const
{
	return Parent;
}
