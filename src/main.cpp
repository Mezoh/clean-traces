#include <Windows.h>
#include <iostream>
#include <filesystem>

std::string get_steam_directory( )
{
	LONG   lResult;
	HKEY   hKey;
	LPBYTE folder = new BYTE[MAX_PATH];
	DWORD  dwSize = sizeof(folder);
	char   value[64];
	DWORD  value_length = 64;
	DWORD  dwType = REG_SZ;

	lResult = RegOpenKey(HKEY_LOCAL_MACHINE,
		TEXT("SOFTWARE\\WOW6432Node\\Valve\\Steam"),
		&hKey);


	RegQueryValueExA(hKey, "InstallPath", NULL, &dwType,
		(LPBYTE)&value, &value_length);

	RegCloseKey(hKey);

	return std::string(value);
}

bool delete_file( const std::string file_path )
{
	if (DeleteFileA(file_path.c_str()) != 0)
	{
		std::cout << "Deleted: " << file_path << std::endl;
		return true;
	}
	else {
		std::cout << "Could not delete file: " << file_path << std::endl;
		return false;
	}
}

bool delete_folder( const std::string folder_path )
{
	if (std::filesystem::remove_all(folder_path))
	{
		std::cout << "Deleted folder: " << folder_path << std::endl;
		return true;
	}
	else
	{
		std::cout << "Could not delete folder: " << folder_path << std::endl;
		return false;
	}
}

int main( )
{

	std::string steam_dir = get_steam_directory();

	if (steam_dir != "")
	{
		std::cout << "Found steam directory: " << steam_dir << std::endl;
	}

	std::string steam_config_folder = steam_dir + "\\config";

	// deletables
	std::string user_data = steam_dir + "\\userdata";
	std::string config = steam_config_folder + "\\config.vdf";
	std::string login_users = steam_config_folder + "\\loginusers.vdf";

	delete_file(config);
	delete_file(login_users);
	delete_folder(user_data);

	system("pause");

	return 0;
}