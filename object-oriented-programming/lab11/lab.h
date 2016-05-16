#ifndef UICONTROL_H__
#define UICONTROL_H__

#include "stdafx.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class UIControl
{

   protected:
      int X, Y, Width, Height; // coordonatele controlului
      UIControl *Parent; // Parintele controlului (NULL inseamna ca nu are parinte)
   public:

		virtual int GetX() const = 0;
		virtual int GetY() const = 0;
		virtual void Draw() = 0; // functie care deseneaza controlul
};

class UIPanel : public UIControl
{
	private:
		vector<UIControl*> Controls;
	public:
		UIPanel(UIControl* parent, int x, int y);
		void AddControl(UIControl* control);
		virtual void Draw();
		virtual int GetX() const;
		virtual int GetY() const;
		UIControl* GetParent() const;
};

class UIButton : public UIControl
{
	private:
		const static int activeBackground   = 1;
		const static int activeForeground   = 2;
		const static int inactiveBackground = 3;
		const static int inactiveForeground = 4;

		bool State;
		string Text;
	public:
		UIButton(UIControl* parent, bool state, string text);
		void SetAttributes(int x, int y, int width_, int height_);		
		UIControl* GetParent() const;
		virtual void Draw();
		virtual int GetX() const;
		virtual int GetY() const;
		void SetState(bool value);
		bool GetState() const;
};


class UILabel : public UIControl
{
	private:
		const static int background = 5;
		const static int foreground = 6;

		string Text;
	public:
		UILabel(UIControl* parent, string text, int x, int y);
		UIControl* GetParent() const;
		virtual void Draw();
		virtual int GetX() const;
		virtual int GetY() const;
};


#endif