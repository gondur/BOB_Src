//---------------------------------------------------------------------------
#ifndef SGSelectH
#define SGSelectH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
//---------------------------------------------------------------------------
class TSuperGroupSelect : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TBitBtn *SuperGroupButton;
	TComboBox *SGList;
	void __fastcall SuperGroupButtonClick(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	
	void __fastcall SGListClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSuperGroupSelect(TComponent* Owner);
    void __fastcall OpenForm();

};
//---------------------------------------------------------------------------
extern TSuperGroupSelect *SuperGroupSelect;
//---------------------------------------------------------------------------
#endif
