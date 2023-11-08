#pragma once

#include <Windows.h>

namespace DIFFB_WheelCheck {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// FFBMonitorForm の概要
	/// </summary>
	public ref class FFBMonitorForm : public System::Windows::Forms::Form
	{
	public:
		FFBMonitorForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~FFBMonitorForm()
		{
			if (components)
			{
				delete components;
			}
		}


	protected:

	protected:


	private: System::Windows::Forms::ProgressBar^  Bar_TotalDumperMinus;
	private: System::Windows::Forms::ProgressBar^  Bar_TotalDumperPlus;
	private: System::Windows::Forms::Label^  Text_Total_Dumper;






	private: System::Windows::Forms::CheckBox^  CheckBox_TopMost;

	private: System::Windows::Forms::Label^  Value_Total_Dumper;



	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Timer^  TickTimer;

	private: System::Windows::Forms::ToolTip^  toolTip1;

	private:
		LONG *FFBMonitor_Total_Spring = nullptr;
		LONG *FFBMonitor_Total_Constant = nullptr;
		LONG *FFBMonitor_Total_Dumper = nullptr;
		LONG *FFBMonitor_Total_Friction = nullptr;
		LONG *FFBMonitor_MaxPower = nullptr;
	private: System::Windows::Forms::Label^  Value_Total_Spring;
	private: System::Windows::Forms::ProgressBar^  Bar_TotalSpringMinus;
	private: System::Windows::Forms::ProgressBar^  Bar_TotalSpringPlus;
	private: System::Windows::Forms::Label^  Value_Total_Constant;

	private: System::Windows::Forms::ProgressBar^  Bar_TotalConstantMinus;
	private: System::Windows::Forms::ProgressBar^  Bar_TotalConstantPlus;
	private: System::Windows::Forms::Label^  Text_Total_Constant;
	private: System::Windows::Forms::Label^  Value_Total_Friction;
	private: System::Windows::Forms::ProgressBar^  Bar_TotalFrictionMinus;
	private: System::Windows::Forms::ProgressBar^  Bar_TotalFrictionPlus;
	private: System::Windows::Forms::Label^  Text_Total_Friction;



	private: System::Windows::Forms::Label^  Text_Total_Spring;









	public: System::Void SetData(LONG *FFBMonitor_Total_Spring_, LONG *FFBMonitor_Total_Constant_, LONG *FFBMonitor_Total_Dumper_, LONG *FFBMonitor_Total_Friction_, LONG *FFBMonitor_MaxPower_) {
		FFBMonitor_Total_Spring = FFBMonitor_Total_Spring_;
		FFBMonitor_Total_Constant = FFBMonitor_Total_Constant_;
		FFBMonitor_Total_Dumper = FFBMonitor_Total_Dumper_;
		FFBMonitor_Total_Friction = FFBMonitor_Total_Friction_;
		FFBMonitor_MaxPower = FFBMonitor_MaxPower_;
	}
	private: System::ComponentModel::IContainer^  components;
	public:
		bool close = false;

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>



#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FFBMonitorForm::typeid));
			this->Bar_TotalDumperMinus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_TotalDumperPlus = (gcnew System::Windows::Forms::ProgressBar());
			this->Text_Total_Dumper = (gcnew System::Windows::Forms::Label());
			this->CheckBox_TopMost = (gcnew System::Windows::Forms::CheckBox());
			this->Value_Total_Dumper = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->TickTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->Value_Total_Spring = (gcnew System::Windows::Forms::Label());
			this->Bar_TotalSpringMinus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_TotalSpringPlus = (gcnew System::Windows::Forms::ProgressBar());
			this->Text_Total_Spring = (gcnew System::Windows::Forms::Label());
			this->Value_Total_Constant = (gcnew System::Windows::Forms::Label());
			this->Bar_TotalConstantMinus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_TotalConstantPlus = (gcnew System::Windows::Forms::ProgressBar());
			this->Text_Total_Constant = (gcnew System::Windows::Forms::Label());
			this->Value_Total_Friction = (gcnew System::Windows::Forms::Label());
			this->Bar_TotalFrictionMinus = (gcnew System::Windows::Forms::ProgressBar());
			this->Bar_TotalFrictionPlus = (gcnew System::Windows::Forms::ProgressBar());
			this->Text_Total_Friction = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// Bar_TotalDumperMinus
			// 
			this->Bar_TotalDumperMinus->Location = System::Drawing::Point(12, 117);
			this->Bar_TotalDumperMinus->Maximum = 10000;
			this->Bar_TotalDumperMinus->Name = L"Bar_TotalDumperMinus";
			this->Bar_TotalDumperMinus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_TotalDumperMinus->RightToLeftLayout = true;
			this->Bar_TotalDumperMinus->Size = System::Drawing::Size(158, 10);
			this->Bar_TotalDumperMinus->Step = 10000;
			this->Bar_TotalDumperMinus->TabIndex = 29;
			// 
			// Bar_TotalDumperPlus
			// 
			this->Bar_TotalDumperPlus->Location = System::Drawing::Point(170, 117);
			this->Bar_TotalDumperPlus->Maximum = 10000;
			this->Bar_TotalDumperPlus->Name = L"Bar_TotalDumperPlus";
			this->Bar_TotalDumperPlus->Size = System::Drawing::Size(158, 10);
			this->Bar_TotalDumperPlus->Step = 10000;
			this->Bar_TotalDumperPlus->TabIndex = 28;
			// 
			// Text_Total_Dumper
			// 
			this->Text_Total_Dumper->AutoSize = true;
			this->Text_Total_Dumper->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Total_Dumper->Location = System::Drawing::Point(12, 92);
			this->Text_Total_Dumper->Name = L"Text_Total_Dumper";
			this->Text_Total_Dumper->Size = System::Drawing::Size(100, 18);
			this->Text_Total_Dumper->TabIndex = 27;
			this->Text_Total_Dumper->Text = L"Total Dumper";
			// 
			// CheckBox_TopMost
			// 
			this->CheckBox_TopMost->AutoSize = true;
			this->CheckBox_TopMost->Font = (gcnew System::Drawing::Font(L"BIZ UDPゴシック", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->CheckBox_TopMost->Location = System::Drawing::Point(223, 189);
			this->CheckBox_TopMost->Name = L"CheckBox_TopMost";
			this->CheckBox_TopMost->Size = System::Drawing::Size(108, 16);
			this->CheckBox_TopMost->TabIndex = 36;
			this->CheckBox_TopMost->Text = L"常に前面に表示";
			this->CheckBox_TopMost->UseVisualStyleBackColor = true;
			this->CheckBox_TopMost->CheckedChanged += gcnew System::EventHandler(this, &FFBMonitorForm::CheckBox_TopMost_CheckedChanged);
			// 
			// Value_Total_Dumper
			// 
			this->Value_Total_Dumper->AutoSize = true;
			this->Value_Total_Dumper->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Value_Total_Dumper->Location = System::Drawing::Point(140, 92);
			this->Value_Total_Dumper->Name = L"Value_Total_Dumper";
			this->Value_Total_Dumper->Size = System::Drawing::Size(58, 18);
			this->Value_Total_Dumper->TabIndex = 38;
			this->Value_Total_Dumper->Text = L"-10000";
			this->Value_Total_Dumper->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::SystemColors::ActiveBorder;
			this->label9->Location = System::Drawing::Point(9, 162);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(323, 18);
			this->label9->TabIndex = 42;
			this->label9->Text = L"___________________________________";
			// 
			// TickTimer
			// 
			this->TickTimer->Enabled = true;
			this->TickTimer->Interval = 16;
			this->TickTimer->Tick += gcnew System::EventHandler(this, &FFBMonitorForm::TickTimer_Tick);
			// 
			// toolTip1
			// 
			this->toolTip1->AutomaticDelay = 0;
			// 
			// Value_Total_Spring
			// 
			this->Value_Total_Spring->AutoSize = true;
			this->Value_Total_Spring->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Value_Total_Spring->Location = System::Drawing::Point(140, 8);
			this->Value_Total_Spring->Name = L"Value_Total_Spring";
			this->Value_Total_Spring->Size = System::Drawing::Size(58, 18);
			this->Value_Total_Spring->TabIndex = 47;
			this->Value_Total_Spring->Text = L"-10000";
			this->Value_Total_Spring->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Bar_TotalSpringMinus
			// 
			this->Bar_TotalSpringMinus->Location = System::Drawing::Point(12, 33);
			this->Bar_TotalSpringMinus->Maximum = 10000;
			this->Bar_TotalSpringMinus->Name = L"Bar_TotalSpringMinus";
			this->Bar_TotalSpringMinus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_TotalSpringMinus->RightToLeftLayout = true;
			this->Bar_TotalSpringMinus->Size = System::Drawing::Size(158, 10);
			this->Bar_TotalSpringMinus->Step = 10000;
			this->Bar_TotalSpringMinus->TabIndex = 46;
			// 
			// Bar_TotalSpringPlus
			// 
			this->Bar_TotalSpringPlus->Location = System::Drawing::Point(170, 33);
			this->Bar_TotalSpringPlus->Maximum = 10000;
			this->Bar_TotalSpringPlus->Name = L"Bar_TotalSpringPlus";
			this->Bar_TotalSpringPlus->Size = System::Drawing::Size(158, 10);
			this->Bar_TotalSpringPlus->Step = 10000;
			this->Bar_TotalSpringPlus->TabIndex = 45;
			// 
			// Text_Total_Spring
			// 
			this->Text_Total_Spring->AutoSize = true;
			this->Text_Total_Spring->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Total_Spring->Location = System::Drawing::Point(12, 8);
			this->Text_Total_Spring->Name = L"Text_Total_Spring";
			this->Text_Total_Spring->Size = System::Drawing::Size(99, 18);
			this->Text_Total_Spring->TabIndex = 44;
			this->Text_Total_Spring->Text = L"Spring Force";
			// 
			// Value_Total_Constant
			// 
			this->Value_Total_Constant->AutoSize = true;
			this->Value_Total_Constant->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Value_Total_Constant->Location = System::Drawing::Point(140, 50);
			this->Value_Total_Constant->Name = L"Value_Total_Constant";
			this->Value_Total_Constant->Size = System::Drawing::Size(58, 18);
			this->Value_Total_Constant->TabIndex = 51;
			this->Value_Total_Constant->Text = L"-10000";
			this->Value_Total_Constant->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Bar_TotalConstantMinus
			// 
			this->Bar_TotalConstantMinus->Location = System::Drawing::Point(12, 75);
			this->Bar_TotalConstantMinus->Maximum = 10000;
			this->Bar_TotalConstantMinus->Name = L"Bar_TotalConstantMinus";
			this->Bar_TotalConstantMinus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_TotalConstantMinus->RightToLeftLayout = true;
			this->Bar_TotalConstantMinus->Size = System::Drawing::Size(158, 10);
			this->Bar_TotalConstantMinus->Step = 10000;
			this->Bar_TotalConstantMinus->TabIndex = 50;
			// 
			// Bar_TotalConstantPlus
			// 
			this->Bar_TotalConstantPlus->Location = System::Drawing::Point(170, 75);
			this->Bar_TotalConstantPlus->Maximum = 10000;
			this->Bar_TotalConstantPlus->Name = L"Bar_TotalConstantPlus";
			this->Bar_TotalConstantPlus->Size = System::Drawing::Size(158, 10);
			this->Bar_TotalConstantPlus->Step = 10000;
			this->Bar_TotalConstantPlus->TabIndex = 49;
			// 
			// Text_Total_Constant
			// 
			this->Text_Total_Constant->AutoSize = true;
			this->Text_Total_Constant->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Total_Constant->Location = System::Drawing::Point(12, 50);
			this->Text_Total_Constant->Name = L"Text_Total_Constant";
			this->Text_Total_Constant->Size = System::Drawing::Size(115, 18);
			this->Text_Total_Constant->TabIndex = 48;
			this->Text_Total_Constant->Text = L"Constant Force";
			// 
			// Value_Total_Friction
			// 
			this->Value_Total_Friction->AutoSize = true;
			this->Value_Total_Friction->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Value_Total_Friction->Location = System::Drawing::Point(140, 135);
			this->Value_Total_Friction->Name = L"Value_Total_Friction";
			this->Value_Total_Friction->Size = System::Drawing::Size(58, 18);
			this->Value_Total_Friction->TabIndex = 55;
			this->Value_Total_Friction->Text = L"-10000";
			this->Value_Total_Friction->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Bar_TotalFrictionMinus
			// 
			this->Bar_TotalFrictionMinus->Location = System::Drawing::Point(12, 160);
			this->Bar_TotalFrictionMinus->Maximum = 10000;
			this->Bar_TotalFrictionMinus->Name = L"Bar_TotalFrictionMinus";
			this->Bar_TotalFrictionMinus->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->Bar_TotalFrictionMinus->RightToLeftLayout = true;
			this->Bar_TotalFrictionMinus->Size = System::Drawing::Size(158, 10);
			this->Bar_TotalFrictionMinus->Step = 10000;
			this->Bar_TotalFrictionMinus->TabIndex = 54;
			// 
			// Bar_TotalFrictionPlus
			// 
			this->Bar_TotalFrictionPlus->Location = System::Drawing::Point(170, 160);
			this->Bar_TotalFrictionPlus->Maximum = 10000;
			this->Bar_TotalFrictionPlus->Name = L"Bar_TotalFrictionPlus";
			this->Bar_TotalFrictionPlus->Size = System::Drawing::Size(158, 10);
			this->Bar_TotalFrictionPlus->Step = 10000;
			this->Bar_TotalFrictionPlus->TabIndex = 53;
			// 
			// Text_Total_Friction
			// 
			this->Text_Total_Friction->AutoSize = true;
			this->Text_Total_Friction->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Total_Friction->Location = System::Drawing::Point(12, 135);
			this->Text_Total_Friction->Name = L"Text_Total_Friction";
			this->Text_Total_Friction->Size = System::Drawing::Size(96, 18);
			this->Text_Total_Friction->TabIndex = 52;
			this->Text_Total_Friction->Text = L"Total Friction";
			// 
			// FFBMonitorForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(341, 213);
			this->Controls->Add(this->Value_Total_Friction);
			this->Controls->Add(this->Bar_TotalFrictionMinus);
			this->Controls->Add(this->Bar_TotalFrictionPlus);
			this->Controls->Add(this->Text_Total_Friction);
			this->Controls->Add(this->Value_Total_Constant);
			this->Controls->Add(this->Bar_TotalConstantMinus);
			this->Controls->Add(this->Bar_TotalConstantPlus);
			this->Controls->Add(this->Text_Total_Constant);
			this->Controls->Add(this->Value_Total_Spring);
			this->Controls->Add(this->Bar_TotalSpringMinus);
			this->Controls->Add(this->Bar_TotalSpringPlus);
			this->Controls->Add(this->Text_Total_Spring);
			this->Controls->Add(this->Value_Total_Dumper);
			this->Controls->Add(this->CheckBox_TopMost);
			this->Controls->Add(this->Bar_TotalDumperMinus);
			this->Controls->Add(this->Bar_TotalDumperPlus);
			this->Controls->Add(this->Text_Total_Dumper);
			this->Controls->Add(this->label9);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(357, 252);
			this->MinimumSize = System::Drawing::Size(357, 252);
			this->Name = L"FFBMonitorForm";
			this->Text = L"FFBMonitor";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void CheckBox_TopMost_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		TopMost = CheckBox_TopMost->CheckState == CheckState::Checked;
	}

	private: System::Void TickTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (close) {
			this->Close();
		}

		if (FFBMonitor_Total_Spring) {
			ProgressBar_AbsoluteGauge(Bar_TotalSpringMinus, Bar_TotalSpringPlus, Value_Total_Spring, *FFBMonitor_Total_Spring);
		}

		if (FFBMonitor_Total_Constant) {
			ProgressBar_RelativeGauge(Bar_TotalConstantMinus, Bar_TotalConstantPlus, Value_Total_Constant, *FFBMonitor_Total_Constant);
		}

		if (FFBMonitor_Total_Dumper) {
			ProgressBar_AbsoluteGauge(Bar_TotalDumperMinus, Bar_TotalDumperPlus, Value_Total_Dumper, *FFBMonitor_Total_Dumper);
		}

		if (FFBMonitor_Total_Friction) {
			ProgressBar_AbsoluteGauge(Bar_TotalFrictionMinus, Bar_TotalFrictionPlus, Value_Total_Friction, *FFBMonitor_Total_Friction);
		}
	}

	private: System::Void ProgressBar_RelativeGauge(ProgressBar^ progressbarMinus, ProgressBar^ progressbarPlus, Label^ value_text, LONG input_) {
		LONG input = min(max(input_, -progressbarMinus->Maximum), progressbarPlus->Maximum);
		progressbarPlus->Maximum += 1;
		progressbarPlus->Value = progressbarPlus->Maximum;
		progressbarPlus->Value = max(input, 0);
		progressbarPlus->Maximum -= 1;
		progressbarMinus->Maximum += 1;
		progressbarMinus->Value = progressbarMinus->Maximum;
		progressbarMinus->Value = max(-input, 0);
		progressbarMinus->Maximum -= 1;

		value_text->Text = input.ToString();
	}

	private: System::Void ProgressBar_AbsoluteGauge(ProgressBar^ progressbarMinus, ProgressBar^ progressbarPlus, Label^ value_text, LONG input_) {
		LONG input = min(input_, progressbarPlus->Maximum);
		progressbarPlus->Maximum += 1;
		progressbarPlus->Value = progressbarPlus->Maximum;
		progressbarPlus->Value = max(input, 0);
		progressbarPlus->Maximum -= 1;
		progressbarMinus->Maximum += 1;
		progressbarMinus->Value = progressbarMinus->Maximum;
		progressbarMinus->Value = max(input, 0);
		progressbarMinus->Maximum -= 1;

		value_text->Text = input.ToString();
	}
};
}
