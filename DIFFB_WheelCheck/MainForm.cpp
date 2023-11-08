#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace DIFFB_WheelCheck;

[STAThreadAttribute]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	MainForm ^mainForm = gcnew MainForm();
	System::Timers::Timer^ timer = gcnew System::Timers::Timer();
	{
		timer->Interval = 16;
		timer->AutoReset = true;
		timer->Elapsed += gcnew System::Timers::ElapsedEventHandler(mainForm, &MainForm::OnTick);
		timer->Start();
	}

	Application::Run(mainForm);

	return 0;
}