// contens.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "lab.h"

int _tmain(int argc, _TCHAR* argv[])
{
	UIButton *b = new UIButton(NULL, true, "Foo bar");
	b->SetAttributes(0, 1, 10, 10);
	b->SetState(false);
	b->Draw();

	UILabel *l = new UILabel(NULL, "Baz", 2, 3);
	l->Draw();
	 
	// Now, draw a panel
	UIPanel *p   = new UIPanel(NULL, 5, 5);
	
	UIButton *b2 = new UIButton(p, true, "BP 1");
	b2->SetAttributes(2, 2, 4, 4);
	
	UILabel *l2  = new UILabel(p, "BL 1", 3, 3);
	
	// Nested panel
	UIPanel *p2  = new UIPanel(p, 4, 4);
	UILabel *l3  = new UILabel(p2, "BL 2", 3, 3);
	p2->AddControl(l3);

	p->AddControl(b2);
	p->AddControl(l2);
	p->AddControl(p2);
	p->Draw();

	// A little dirty hack in order to keep the window open...
	getchar();

	return 0;
}

