#include "ReportSave.h"


bool SaveReport(FFBCheckList ffbCheckList, std::string name) {
	// フォルダを作成
	std::filesystem::create_directory(Report::FolderName());

	// ファイル名として使用する文字列
	std::string filePath;
	
	filePath = Report::FolderName() + "/" + name + "_Report" + Report::FileExtension();

	// ファイルを開く
	std::ofstream file(filePath);

	// ファイルが正しく開けたかを確認
	if (file.is_open()) {
		// 変数の値をファイルに書き込む
		file << "ProductName : " << ffbCheckList.device_product_name << std::endl;
		file << "InstanceName : " << ffbCheckList.device_instance_name << std::endl;
		file << std::endl;
		file << "Stop = " + BoolToString(ffbCheckList.stop) << std::endl;
		file << std::endl;
		file << "Center = " + BoolToString(ffbCheckList.center) << std::endl;
		file << std::endl;
		file << "InitialPowerCheck = " + BoolToString(ffbCheckList.initial_power_check) << std::endl;
		file << "InitialPower = " << ffbCheckList.initial_power << std::endl;
		file << std::endl;
		file << "LockToLock = " + BoolToString(ffbCheckList.lock_to_lock_check) << std::endl;
		file << "LockToLock_MaxMove = " << ffbCheckList.lock_to_lock_max_move << std::endl;
		file << "LockToLock_MaxPos = " << ffbCheckList.lock_to_lock_max_pos << std::endl;
		file << "LockToLock_MinPos = " << ffbCheckList.lock_to_lock_min_pos << std::endl;
		file << std::endl;
		file << "Damper = " + BoolToString(ffbCheckList.damper) << std::endl;
		file << "Damper_MaxMove = " << ffbCheckList.damper_max_move << std::endl;
		file << std::endl;
		file << "Friction = " + BoolToString(ffbCheckList.friction) << std::endl;
		file << "Friction_MaxMove = " << ffbCheckList.friction_max_move << std::endl;
		file << std::endl;
		file << "InitialPower2Check = " + BoolToString(ffbCheckList.initial_power2_check) << std::endl;
		file << "InitialPower2 = " << ffbCheckList.initial_power2 << std::endl;
		file << std::endl;
		file << "lXEffects :" << std::endl;
		for (auto s : ffbCheckList.lXEffects)
		{
			file << "	" << s << std::endl;
		}

		// ファイルを閉じる
		file.close();

		return true;
	}
	else {
		return false;
	}

	return false;
}


bool FindReport(std::string name) {
	// ファイル名として使用する文字列
	std::string filePath_ = Report::FolderName() + "/" + name + Report::FileExtension();

	try {
		std::filesystem::path filePath(filePath_);

		// ファイルが存在するか確認
		return (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath));
	}
	catch (const std::filesystem::filesystem_error& e) {
		printf_s("*** Error - レポート確認失敗(ファイルの検索中にエラーが発生しました(");
		printf_s(name.c_str());
		printf_s(")");
		return false;
	}
}



LONG ToLONG(const std::string &str) {
	try {
		return std::stoi(str);
	}
	catch (...) {
		return 0;
	}
}

std::string BoolToString(bool b) {
	return (b) ? "true" : "false";
}