#pragma once

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#include <string.h>
#include <cstdlib>

#include <Windows.h>
#include <WinUser.h>

#include <msclr/marshal_cppstd.h>

#define DIRECTINPUT_VERSION     0x0800          // DirectInput�̃o�[�W�����w��
#include <dinput.h>

#include "DIUtils.h"

#include "ReportSave.h"
#include "FFBMonitorForm.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "ws2_32.lib")

#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define GetHInstance() ((HINSTANCE)GetModuleHandle(0))
#define GetHWND() (reinterpret_cast<HWND>(this->Handle.ToPointer()))


//DirectInput�p//
BYTE byKeyState[256];		//�L�[�{�[�h
DIMOUSESTATE diMouseState;	//�}�E�X
DIJOYSTATE diJoyState;		//�Q�[���p�b�h
DIJOYSTATE preDiJoyState;	//1tick�O�̃Q�[���p�b�h
bool initialized = false;

//FFB�e�X�g���̃X�e�[�g�ϐ�
enum STATE {
	WAIT,
	START,
	STOP,
	CENTER,
	INITIAL_POWER,
	LOCK_TO_LOCK,
	DAMPER,
	FRICTION,
	INITIAL_POWER2,
	END,
	DIALOG,
};
STATE state = STATE::WAIT;
int state_tick = 0;
int wait_tick = 0;

void SetState(STATE state_) {
	state = state_;
	state_tick = 0;
	wait_tick = 0;
}

FFBCheckList ffbCheckList;

struct StateStop
{
	LONG start_axis_pos = 0;
};
StateStop stateStop;

struct StateCenter
{
	LONG power = 0;
	int stop_tick = 0;
};
StateCenter stateCenter;

struct StateInitial_Power
{
	LONG start_axis_pos = 0;
	LONG power = 0;
	int stop_tick = 0;
};
StateInitial_Power stateInitial_Power;

struct StateLock_To_Lock
{
	LONG power = 0;
	int stop_tick = 0;
	int static_tick = 0;//�ُ�ȐÎ~����
};
StateLock_To_Lock stateLock_To_Lock;

struct StateDamper
{
	LONG power = 0;
	int damper_tick = 0;//�_���p�[�������Ă���Ɛ������ꂽ����
};
StateDamper stateDamper;

struct StateFriction
{
	LONG power = 0;
	int friction_tick = 0;//�t���N�V�����������Ă���Ɛ������ꂽ����
};
StateFriction stateFriction;

struct StateInitial_Power2
{
	LONG start_axis_pos = 0;
	LONG power = 0;
	int stop_tick = 0;
};
StateInitial_Power2 stateInitial_Power2;

//FFB���j�^�[�p�ϐ�
LONG FFBMonitor_Total_Spring = 0;
LONG FFBMonitor_Total_Constant = 0;
LONG FFBMonitor_Total_Dumper = 0;
LONG FFBMonitor_Total_Friction = 0;
LONG FFBMonitor_MaxPower = 0;

//�f�o�b�O�p�ϐ�
float f1 = 0;
float f2 = 0;
float f3 = 0;

namespace DIFFB_WheelCheck {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MainForm �̊T�v
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^�[ �R�[�h��ǉ����܂�
			//
		}
	private: System::Windows::Forms::Label^  Text_Input_lX;
	public:

	public:


	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Label^  Text_Device;
	private: System::Windows::Forms::Label^  DeviceName;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::ProgressBar^  progressBar2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  FFBMonitorButton;
	private: System::Windows::Forms::Label^  label1;


	public:
	private: System::Windows::Forms::Button^  ResetButton;
	public:


	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	protected:


	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�[�ϐ��ł��B
		/// </summary>
		FFBMonitorForm ^ffb_monitor = nullptr;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i�[ �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�[�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->ResetButton = (gcnew System::Windows::Forms::Button());
			this->Text_Input_lX = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->Text_Device = (gcnew System::Windows::Forms::Label());
			this->DeviceName = (gcnew System::Windows::Forms::Label());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->progressBar2 = (gcnew System::Windows::Forms::ProgressBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->FFBMonitorButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// ResetButton
			// 
			this->ResetButton->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ResetButton->Location = System::Drawing::Point(14, 179);
			this->ResetButton->Name = L"ResetButton";
			this->ResetButton->Size = System::Drawing::Size(98, 23);
			this->ResetButton->TabIndex = 0;
			this->ResetButton->Text = L"Reset";
			this->ResetButton->UseVisualStyleBackColor = true;
			this->ResetButton->Click += gcnew System::EventHandler(this, &MainForm::ResetButton_Click);
			// 
			// Text_Input_lX
			// 
			this->Text_Input_lX->AutoSize = true;
			this->Text_Input_lX->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Input_lX->Location = System::Drawing::Point(115, 60);
			this->Text_Input_lX->Name = L"Text_Input_lX";
			this->Text_Input_lX->Size = System::Drawing::Size(112, 18);
			this->Text_Input_lX->TabIndex = 3;
			this->Text_Input_lX->Text = L"Input lX -32767";
			this->toolTip1->SetToolTip(this->Text_Input_lX, L"FFB�̑ΏۂƂȂ鎲�̓��͒l��\���܂�");
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->checkBox1->Location = System::Drawing::Point(223, 182);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(108, 16);
			this->checkBox1->TabIndex = 4;
			this->checkBox1->Text = L"��ɑO�ʂɕ\��";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox1_CheckedChanged);
			// 
			// Text_Device
			// 
			this->Text_Device->AutoSize = true;
			this->Text_Device->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Text_Device->Location = System::Drawing::Point(12, 9);
			this->Text_Device->Name = L"Text_Device";
			this->Text_Device->Size = System::Drawing::Size(62, 21);
			this->Text_Device->TabIndex = 5;
			this->Text_Device->Text = L"Device";
			// 
			// DeviceName
			// 
			this->DeviceName->AutoSize = true;
			this->DeviceName->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DeviceName->Location = System::Drawing::Point(12, 30);
			this->DeviceName->Name = L"DeviceName";
			this->DeviceName->Size = System::Drawing::Size(108, 21);
			this->DeviceName->TabIndex = 6;
			this->DeviceName->Text = L"DeviceName";
			// 
			// toolTip1
			// 
			this->toolTip1->AutomaticDelay = 0;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::SystemColors::ActiveBorder;
			this->label5->Location = System::Drawing::Point(11, 88);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(323, 18);
			this->label5->TabIndex = 21;
			this->label5->Text = L"___________________________________";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(172, 85);
			this->progressBar1->Maximum = 32767;
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(158, 10);
			this->progressBar1->Step = 32767;
			this->progressBar1->TabIndex = 22;
			// 
			// progressBar2
			// 
			this->progressBar2->Location = System::Drawing::Point(14, 85);
			this->progressBar2->Maximum = 32767;
			this->progressBar2->Name = L"progressBar2";
			this->progressBar2->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->progressBar2->RightToLeftLayout = true;
			this->progressBar2->Size = System::Drawing::Size(158, 10);
			this->progressBar2->Step = 1;
			this->progressBar2->TabIndex = 23;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::SystemColors::ActiveBorder;
			this->label3->Location = System::Drawing::Point(9, 36);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(323, 18);
			this->label3->TabIndex = 32;
			this->label3->Text = L"___________________________________";
			// 
			// FFBMonitorButton
			// 
			this->FFBMonitorButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->FFBMonitorButton->Font = (gcnew System::Drawing::Font(L"BIZ UDP�S�V�b�N", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->FFBMonitorButton->Location = System::Drawing::Point(21, 113);
			this->FFBMonitorButton->Name = L"FFBMonitorButton";
			this->FFBMonitorButton->Size = System::Drawing::Size(300, 50);
			this->FFBMonitorButton->TabIndex = 48;
			this->FFBMonitorButton->Text = L"�e�X�g�J�n";
			this->FFBMonitorButton->UseVisualStyleBackColor = false;
			this->FFBMonitorButton->Click += gcnew System::EventHandler(this, &MainForm::FFBTestButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ActiveBorder;
			this->label1->Location = System::Drawing::Point(9, 154);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(323, 18);
			this->label1->TabIndex = 49;
			this->label1->Text = L"___________________________________";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(341, 209);
			this->Controls->Add(this->Text_Input_lX);
			this->Controls->Add(this->FFBMonitorButton);
			this->Controls->Add(this->progressBar2);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->DeviceName);
			this->Controls->Add(this->Text_Device);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->ResetButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(357, 248);
			this->MinimumSize = System::Drawing::Size(357, 248);
			this->Name = L"MainForm";
			this->Text = L"DIFFB_WheelCheck";
			this->TopMost = true;
			this->TransparencyKey = System::Drawing::Color::Lime;
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void ResetButton_Click(System::Object^  sender, System::EventArgs^  e) {
		initialized = false;
		initialized = DIInit(GetHInstance(), GetHWND());
	}

	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		this->TopMost = this->checkBox1->CheckState == CheckState::Checked;
	}

	//���C���t�H�[���ǂݍ��ݎ�
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
		initialized = false;
		initialized = DIInit(GetHInstance(), GetHWND());
		//�t�H�[����TopMost�̏����ݒ�Ƀ`�F�b�N�{�b�N�X�̓��e����v������
		TopMost = false;
		checkBox1->CheckState = (TopMost) ? CheckState::Checked : CheckState::Unchecked;

		//���͕\��
		Text_Input_lX->Text = "Input lX " + diJoyState.lX;
	}

	private: System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		initialized = false;
	}

	private: System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
		DIRelease();
	}
			 
	public: System::Void OnTick(System::Object^ obj, System::Timers::ElapsedEventArgs^ args) {
		if (!initialized) {
			return;
		}

		bool isEnableGamePad = DIGetGamePadState(DID_GAMEPAD1, diJoyState);

		//�e�X�g�p��FFB�o��
		FFBUpdate(DID_GAMEPAD1, diJoyState, preDiJoyState);

		//UI�X�V//
		try
		{
			this->Invoke(gcnew Action(this, &MainForm::UIUpdate));
		}
		catch (ObjectDisposedException^ e)
		{
		}
		//UI�X�V//


		preDiJoyState = diJoyState;
	}

	private: System::Void UIUpdate() {
		//label3->Text = "TPS " + (Math::Floor(TPS * 10 + 0.5) / 10).ToString();

		DeviceName->Text = DIGetGamePadProductName(DID_GAMEPAD1);

		//diJoyState.lX;//�n���h��
		//diJoyState.lY;//�A�N�Z��
		//diJoyState.lRz;//�u���[�L
		LONG input = diJoyState.lX;
		if (input != preDiJoyState.lX) {
			Text_Input_lX->Text = "Input lX " +  input;
		}
		//�f�o�b�O�p
		//Text_Input_lX->Text = "coeff_spd=" + f1 + "\ncoeff_per=" + f2 + "\ntireGrip=" + f3;
		//�Q�[�W�̍X�V
		progressBar1->Maximum += 1;
		progressBar1->Value = progressBar1->Maximum;
		progressBar1->Value = max(input, 0);
		progressBar1->Maximum -= 1;
		progressBar2->Maximum += 1;
		progressBar2->Value = progressBar2->Maximum;
		progressBar2->Value = max(-input, 0);
		progressBar2->Maximum -= 1;
	}

	private: System::Void FFBUpdate(DIDEV did, DIJOYSTATE diJoyState, DIJOYSTATE preDiJoyState) {
		LONG constant_coefficient = 0;
		LONG damper_coefficient = 0;
		LONG friction_coefficient = 0;
		LONG spring_coefficient = 0;
		LONG spring_centeroffset = 0;


		if (state != STATE::WAIT && state != STATE::DIALOG) {
			if (!ffb_monitor) {//FFB���j�^�[��������Ă���
				SetState(STATE::END);
			}
			else if (ffb_monitor->IsDisposed) {
				SetState(STATE::END);
			}
		}

		switch (state) {
		case STATE::WAIT:
			break;

		case STATE::START:
			if (0 == state_tick) {
				ffbCheckList.Reset();
				ffbCheckList.device_product_name = DIGetGamePadProductName_std(did);
				ffbCheckList.device_instance_name = DIGetGamePadInstanceName_std(did);
				ffbCheckList.lXEffects = GetlXEffects(did);
			}
			if (30 <= state_tick) {
				SetState(STATE::STOP);
				break;
			}
			state_tick++;
			break;

		case STATE::STOP:
			if (state_tick == 0) {
				//�J�n���̏�Ԃ�ۑ����Ă���
				stateStop.start_axis_pos = diJoyState.lX;
			}
			else if (diJoyState.lX < stateStop.start_axis_pos - 50 || stateStop.start_axis_pos + 50 < diJoyState.lX) {//臒l+-50
				//����ɓ����Ă���̂ŃG���[�ŗ��Ƃ�
				ffbCheckList.stop = false;
				SetState(STATE::END);
			}
			else if (30 <= state_tick) {
				//�Î~�m�FOK
				ffbCheckList.stop = true;
				SetState(STATE::CENTER);
				break;
			}
			state_tick++;
			break;

		case STATE::CENTER:
			if (state_tick == 0) {
				stateCenter.power = 2000;
				stateCenter.stop_tick = 0;
			}
			if (preDiJoyState.lX - 50 <= diJoyState.lX && diJoyState.lX <= preDiJoyState.lX + 50) {
				stateCenter.stop_tick++;
			}
			if (30 <= stateCenter.stop_tick) {
				if (10000 <= stateCenter.power) {//�ő�p���[�œ����Ȃ���Ύ��̃X�e�b�v��
					ffbCheckList.center = true;
					SetState(STATE::INITIAL_POWER);
					break;
				}
				stateCenter.power += 2000;
				stateCenter.stop_tick = 0;
			}
			spring_coefficient = stateCenter.power;
			spring_centeroffset = 0;
			state_tick++;
			break;

		case STATE::INITIAL_POWER:
			if (state_tick == 0) {
				stateInitial_Power.power = 10;
				stateInitial_Power.start_axis_pos = diJoyState.lX;
				stateInitial_Power.stop_tick = 0;
			}
			if (stateInitial_Power.start_axis_pos + 50 < diJoyState.lX) {//臒l+-50
				ffbCheckList.initial_power_check = true;
				ffbCheckList.initial_power = stateInitial_Power.power;
				SetState(STATE::LOCK_TO_LOCK);
				break;
			}
			else {
				stateInitial_Power.stop_tick++;
			}
			if (5 <= stateInitial_Power.stop_tick) {
				if (10000 <= stateInitial_Power.power) {
					//�ő�p���[�ł������Ȃ�
					ffbCheckList.initial_power_check = false;
					SetState(STATE::END);
					break;
				}
				stateInitial_Power.power += 10;
				stateInitial_Power.stop_tick = 0;
			}
			constant_coefficient = stateInitial_Power.power;
			state_tick++;
			break;

		case STATE::LOCK_TO_LOCK:
			if (state_tick == 0) {
				stateLock_To_Lock.power = min(max(stateInitial_Power.power * 10, 500), 10000);
				stateLock_To_Lock.stop_tick = 0;
				stateLock_To_Lock.static_tick = 0;
			}
			ffbCheckList.lock_to_lock_max_move = max(ffbCheckList.lock_to_lock_max_move, abs(preDiJoyState.lX - diJoyState.lX));
			ffbCheckList.lock_to_lock_max_pos = max(ffbCheckList.lock_to_lock_max_pos, diJoyState.lX);
			ffbCheckList.lock_to_lock_min_pos = min(ffbCheckList.lock_to_lock_min_pos, diJoyState.lX);
			if (0 < stateLock_To_Lock.power) {//�E�����̃e�X�g��
				if (DIAXIS_RANGE_MAX - 1000 <= diJoyState.lX) {//���b�N��
					stateLock_To_Lock.stop_tick++;
				}
				if (30 <= stateLock_To_Lock.stop_tick) {
					stateLock_To_Lock.power = -stateLock_To_Lock.power;
					stateLock_To_Lock.stop_tick = 0;
				}
			}
			else {//�������̃e�X�g��
				if (diJoyState.lX <= -DIAXIS_RANGE_MAX + 1000) {//���b�N��
					stateLock_To_Lock.stop_tick++;
				}
				if (30 <= stateLock_To_Lock.stop_tick) {
					ffbCheckList.lock_to_lock_check = true;
					SetState(STATE::DAMPER);
					break;
				}
			}
			if (preDiJoyState.lX == diJoyState.lX) {
				stateLock_To_Lock.static_tick++;
			}
			else {
				stateLock_To_Lock.static_tick = 0;
			}
			if (60 <= stateLock_To_Lock.static_tick) {
				if (10000 <= stateLock_To_Lock.power) {
					//�ُ�ȐÎ~�����m
					ffbCheckList.lock_to_lock_check = false;
					SetState(STATE::END);
				}
				else {
					stateLock_To_Lock.power = min(stateLock_To_Lock.power + 500, 10000);
					stateLock_To_Lock.static_tick = 0;
				}
				break;
			}
			constant_coefficient = stateLock_To_Lock.power;
			state_tick++;
			break;

		case STATE::DAMPER:
			if (state_tick == 0) {
				stateDamper.power = abs(stateLock_To_Lock.power);
				stateDamper.damper_tick = 0;
			}
			ffbCheckList.damper_max_move = max(ffbCheckList.damper_max_move, abs(preDiJoyState.lX - diJoyState.lX));
			if (abs(preDiJoyState.lX - diJoyState.lX) < ffbCheckList.lock_to_lock_max_move) {//�_���p�[�������ē������݂��Ă���
				stateDamper.damper_tick++;
			}
			else {
				stateDamper.damper_tick = 0;
			}
			if (60 <= stateDamper.damper_tick) {
				if (DIAXIS_RANGE_MAX - 1000 <= diJoyState.lX) {//���b�N��
					//���b�N�܂Ői��ł��܂��Ă���
					ffbCheckList.damper = false;
					SetState(STATE::END);
					break;
				}
				else {
					//����Ɋ���
					ffbCheckList.damper = true;
					SetState(STATE::FRICTION);
					break;
				}
			}
			damper_coefficient = 10000;
			constant_coefficient = stateDamper.power;
			state_tick++;
			break;
		case STATE::FRICTION:
			if (state_tick == 0) {
				stateFriction.power = abs(stateLock_To_Lock.power);
				stateFriction.friction_tick = 0;
			}
			ffbCheckList.friction_max_move = max(ffbCheckList.friction_max_move, abs(preDiJoyState.lX - diJoyState.lX));
			if (abs(preDiJoyState.lX - diJoyState.lX) < ffbCheckList.lock_to_lock_max_move) {//�t���N�V�����������ē������݂��Ă���
				stateFriction.friction_tick++;
			}
			else {
				stateFriction.friction_tick = 0;
			}
			if (60 <= stateFriction.friction_tick) {
				if (DIAXIS_RANGE_MAX - 1000 <= diJoyState.lX) {//���b�N��
					//���b�N�܂Ői��ł��܂��Ă���
					ffbCheckList.friction = false;
					SetState(STATE::END);
					break;
				}
				else {
					//����Ɋ���
					ffbCheckList.friction = true;
					SetState(STATE::INITIAL_POWER2);
					break;
				}
			}
			friction_coefficient = 10000;
			constant_coefficient = stateFriction.power;
			state_tick++;
			break;
		case STATE::INITIAL_POWER2://2�x�ڂ�initial power����
			if (state_tick == 20) {
				stateInitial_Power2.power = 10;
				stateInitial_Power2.start_axis_pos = diJoyState.lX;
				stateInitial_Power2.stop_tick = 0;
			}
			if (state_tick < 20) {
				//�����҂��ăn���h����Î~������
				state_tick++;
				break;
			}
			if (stateInitial_Power2.start_axis_pos + 50 < diJoyState.lX) {//臒l+-50
				ffbCheckList.initial_power2_check = true;
				ffbCheckList.initial_power2 = stateInitial_Power2.power;
				SetState(STATE::END);
				break;
			}
			else {
				stateInitial_Power2.stop_tick++;
			}
			if (5 <= stateInitial_Power2.stop_tick) {
				if (10000 <= stateInitial_Power2.power) {
					//�ő�p���[�ł������Ȃ�
					ffbCheckList.initial_power2_check = false;
					SetState(STATE::END);
					break;
				}
				stateInitial_Power2.power += 10;
				stateInitial_Power2.stop_tick = 0;
			}
			constant_coefficient = stateInitial_Power2.power;
			state_tick++;
			break;
		case STATE::END:
		{
			//�I������
			//FFB���j�^�[������
			if (ffb_monitor) {
				if (!ffb_monitor->IsDisposed) {
					ffb_monitor->close = true;
				}
			}
			//�e�X�g�I���̃_�C�A���O�\���Ń��|�[�g�쐬�̗L����I��������
			if (ffbCheckList.stop && ffbCheckList.initial_power_check && ffbCheckList.lock_to_lock_check && ffbCheckList.damper && ffbCheckList.initial_power2_check) {
				// ���b�Z�[�W�{�b�N�X��\������
				System::String^ message = "FFB�̃e�X�g���������܂����B\n���|�[�g���쐬����ꍇ�́u�͂��v�������Ă��������B";
				message += "\n�e�X�g���ʁFDirectInputFFB�ɑΉ����Ă��܂��B";
					
				System::String^ title = "FFB�e�X�g�̊���";
				SetState(STATE::DIALOG);//�_�C�A���O�\�����͉������Ȃ��X�e�[�g�ɂ���FFBUpdate�̌Ăяo���𖳌������Ă���
				System::Windows::Forms::DialogResult dialogResult =
					System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::YesNo, MessageBoxIcon::Information);

				if (dialogResult == System::Windows::Forms::DialogResult::Yes) {
					//���|�[�g�쐬
					SaveReport(ffbCheckList, ffbCheckList.device_product_name);
				}
			}
			else {
				System::String^ message = "FFB�̃e�X�g�����f����܂����B\n���|�[�g���쐬����ꍇ�́u�͂��v�������Ă��������B";
				do//break���g����������
				{
					if (!ffbCheckList.stop) { message += "\n(STATE::STOP �ŃG���[���������A�I�����܂���)\n�e�X�g���̓n���h���ɐG��Ȃ��ł�������"; break; }
					if (!ffbCheckList.initial_power_check) { message += "\n(STATE::INITIAL_POWER �ŃG���[���������A�I�����܂���)"; break; }
					if (!ffbCheckList.lock_to_lock_check) { message += "\n(STATE::LOCK_TO_LOCK �ŃG���[���������A�I�����܂���)"; break; }
					if (!ffbCheckList.damper) { message += "\n(STATE::DAMPER �ŃG���[���������A�I�����܂���)"; break; }
					if (!ffbCheckList.initial_power2_check) { message += "\n(STATE::INITIAL_POWER2 �ŃG���[���������A�I�����܂���)"; break; }
				} while (false);
				message += "\n�e�X�g���ʁFDirectInputFFB�ɑΉ����Ă��܂���B\n���[�X�Q�[������FFB�ɑΉ����Ă��鎖���m�F�o���Ă���n���R���̏ꍇ�A�ēx�e�X�g���邱�Ƃ������߂��܂��B";

				System::String^ title = "FFB�e�X�g�̒��f";
				SetState(STATE::DIALOG);//�_�C�A���O�\�����͉������Ȃ��X�e�[�g�ɂ���FFBUpdate�̌Ăяo���𖳌������Ă���
				System::Windows::Forms::DialogResult dialogResult =
					System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::YesNo, MessageBoxIcon::Information);

				if (dialogResult == System::Windows::Forms::DialogResult::Yes) {
					//���|�[�g�쐬
					SaveReport(ffbCheckList, ffbCheckList.device_product_name);
				}
			}
			SetState(STATE::WAIT);
			break;
		}
		case STATE::DIALOG:
			break;
		}


			
		//Spring
		DISetFFB_Spring(did, spring_centeroffset, spring_coefficient, spring_coefficient);
		//FFB���j�^�[
		FFBMonitor_Total_Spring = spring_coefficient;

		//Constant
		DISetFFB_Constant(did, constant_coefficient);
		//FFB���j�^�[
		FFBMonitor_Total_Constant = constant_coefficient;
	
		//Damper
		DISetFFB_Damper(did, damper_coefficient);
		//FFB���j�^�[
		FFBMonitor_Total_Dumper = damper_coefficient;

		//Friction
		DISetFFB_Friction(did, friction_coefficient);
		//FFB���j�^�[
		FFBMonitor_Total_Friction = friction_coefficient;
	}

	private: System::Void FFBTestButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (state == STATE::WAIT) {
			// ���b�Z�[�W�{�b�N�X��\������
			System::String^ message = "FFB�̃e�X�g���J�n���܂��B\n�e�X�g����f�o�C�X���K�肳�ꂽ���@�ŌŒ肵�Ă��������B\n�e�X�g�J�n��̓e�X�g�����̃��b�Z�[�W���o��܂ŁA\n�n���h���ɂӂ�Ȃ��ł��������B";
			System::String^ title = "FFB�e�X�g�̊J�n";
			System::Windows::Forms::DialogResult dialogResult =
				System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OKCancel, MessageBoxIcon::Exclamation);

			if (dialogResult != System::Windows::Forms::DialogResult::OK) {
				return;
			}

			if (ffb_monitor) {
				if (!ffb_monitor->IsDisposed) {
					ffb_monitor->close = true;
				}
			}
			ffb_monitor = gcnew FFBMonitorForm();
			ffb_monitor->SetData(&FFBMonitor_Total_Spring, &FFBMonitor_Total_Constant, &FFBMonitor_Total_Dumper, &FFBMonitor_Total_Friction, &FFBMonitor_MaxPower);
			ffb_monitor->Show();

			SetState(STATE::START);
		}
		else {
			// ���b�Z�[�W�{�b�N�X��\������
			System::String^ message = "FFB�̃e�X�g���ł��B\n�e�X�g���I�����Ă��玎�s���Ă��������B";
			System::String^ title = "FFB�e�X�g�̊J�n";
			System::Windows::Forms::DialogResult dialogResult =
				System::Windows::Forms::MessageBox::Show(message, title, MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		}
	}
};
}