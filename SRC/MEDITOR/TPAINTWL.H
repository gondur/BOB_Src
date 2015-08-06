//---------------------------------------------------------------------------
#ifndef TPaintWlH
#define TPaintWlH
//---------------------------------------------------------------------------
#include <vcl\SysUtils.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL (WM_MOUSELAST+1)  // message that will be supported
#endif

class TPaintBoxWithWheel : public TPaintBox
{
private:
	TNotifyEvent FOnMouseWheel;
protected:
  void __fastcall InternalOnMouseWheel(TMessage* Message);
BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(WM_MOUSEWHEEL, TMessage*, InternalOnMouseWheel)
END_MESSAGE_MAP(TPaintBox)

public:
	Cardinal	wheelmsg;
	__fastcall TPaintBoxWithWheel(TComponent* Owner);
void __fastcall TPaintBoxWithWheel::WndProc(TMessage& Message);    
__published:
	__property TNotifyEvent OnMouseWheel = {read=FOnMouseWheel, write=FOnMouseWheel};
};
//---------------------------------------------------------------------------
#endif

