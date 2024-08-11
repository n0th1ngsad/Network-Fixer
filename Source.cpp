#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

void runCommand(const std::string& command) {
    system(command.c_str());
}

void addRegistryValue(const std::string& key, const std::string& valueName, const std::string& valueType, const std::string& valueData) {
    std::string command = "reg add \"" + key + "\" /v \"" + valueName + "\" /t " + valueType + " /d " + valueData + " /f";
    runCommand(command);
}

std::string generateRandomBinary(int length) {
    std::string hexValue;
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < length; ++i) {
        int byteValue = rand() % 256;
        char hexByte[3];
        sprintf_s(hexByte, "%02X", byteValue);
        hexValue += hexByte;
    }
    return hexValue;
}

int main() {
    std::cout << "Network Fix\nMade by dyhis\n";

    runCommand("netsh advfirewall firewall set rule group=\"File and Printer Sharing\" new enable=no");
    runCommand("netsh advfirewall firewall set rule group=\"Network Discovery\" new enable=no");
    runCommand("netsh int tcp set global autotuninglevel=normal");
    runCommand("netsh interface set interface \"Microsoft Network Adapter Multiplexor Protocol\" admin=disabled");
    runCommand("sc config lltdsvc start=disabled");
    addRegistryValue("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\Tcpip6\\Parameters", "DisabledComponents", "REG_DWORD", "0xFFFFFFFF");
    addRegistryValue("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters", "EEE", "REG_DWORD", "0");
    addRegistryValue("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces", "NetworkAddress", "REG_SZ", "\"\"");
    addRegistryValue("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters", "ArpOffload", "REG_DWORD", "0");
    addRegistryValue("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters", "TcpAckFrequency", "REG_DWORD", "1");
    addRegistryValue("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters", "TcpChecksumOffloadIPv4", "REG_DWORD", "0");
    addRegistryValue("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters", "LargeSendOffloadv2IPv6", "REG_DWORD", "0");
    addRegistryValue("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters", "TcpChecksumOffloadIPv6", "REG_DWORD", "0");
    addRegistryValue("HKLM\\SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters", "UdpChecksumOffloadIPv6", "REG_DWORD", "0");

    std::cout << "Network properties have been configured.\n";

    std::string randomDNS = generateRandomBinary(28);
    std::string randomSearchList = generateRandomBinary(28);
    std::string randomDUID = generateRandomBinary(28);

    addRegistryValue("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\Tcpip6\\Parameters", "Dhcpv6DNSServers", "REG_BINARY", randomDNS);
    addRegistryValue("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\Tcpip6\\Parameters", "Dhcpv6DomainSearchList", "REG_BINARY", randomSearchList);
    addRegistryValue("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services\\Tcpip6\\Parameters", "Dhcpv6DUID", "REG_BINARY", randomDUID);

    std::cout << "Random binary values set.\n";

    runCommand("ipconfig /flushdns");
    runCommand("ipconfig /registerdns");
    runCommand("ipconfig /release");
    runCommand("ipconfig /renew");
    runCommand("netsh winsock reset");

    return 0;
}
