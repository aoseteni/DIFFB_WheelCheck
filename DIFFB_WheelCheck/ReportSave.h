#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "DIUtils.h"


public struct Report {
public:
	static std::string FolderName() { return "Reports"; }
	static std::string FileExtension() { return  ".txt"; }
};

struct FFBCheckList
{
	std::string device_product_name = "";
	std::string device_instance_name = "";
	bool stop = false;
	bool center = false;
	bool initial_power_check = false;
	LONG initial_power = 0;
	bool lock_to_lock_check = false;
	LONG lock_to_lock_max_move = 0;
	LONG lock_to_lock_max_pos = 0;
	LONG lock_to_lock_min_pos = 0;
	bool damper = false;
	LONG damper_max_move = 0;
	bool friction = false;
	LONG friction_max_move = 0;
	bool initial_power2_check = false;
	LONG initial_power2 = 0;
	std::vector<std::string> lXEffects;

	void Reset() {
		device_product_name = "";
		device_instance_name = "";
		stop = false;
		center = false;
		initial_power_check = false;
		initial_power = 0;
		lock_to_lock_check = false;
		lock_to_lock_max_move = 0;
		lock_to_lock_max_pos = 0;
		lock_to_lock_min_pos = 0;
		damper = false;
		damper_max_move = 0;
		friction = false;
		friction_max_move = 0;
		initial_power2_check = false;
		initial_power2 = 0;
		lXEffects.clear();
	}
};



bool SaveReport(FFBCheckList ffbCheckList, std::string name);
bool FindReport(std::string name);

LONG ToLONG(const std::string &str);
std::string BoolToString(bool b);