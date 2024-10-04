#include <iostream>
#include <windows.h>
#include <map>
#include <sstream>
#include <iomanip>
#include <ctime>

struct ScreenData {
	std::string processName;
	int currentLine;
	int totalLines;
	std::string timestamp;
};

std::map<std::string, ScreenData> screens;
bool inScreen = false;

void setColor( unsigned char color )
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
}

std::string truncateText(const std::string& text, std::size_t width) {
    if (text.length() > width) {
        return "..." + text.substr(text.length() - (width - 3));
    }
    return text;
}

std::string formatPID(const std::string& pid, std::size_t totalWidth) {
    std::string truncatedPID = truncateText(pid, totalWidth);
    std::size_t padding = totalWidth - truncatedPID.length();
    std::string formattedPID = std::string(padding, ' ') + truncatedPID;

    return formattedPID;
}

void header() {
	setColor(0x07);
	std::cout << "  ____ ____  ____  _____ _____ ____ __   __     \n";
	std::cout << " / __/  ___|/ __ `|  _  ` ____/ ___`  ` / /     \n";
	std::cout << "| |   `___ ` |  | | |_| |  __|`___ ` `   /      \n";
	std::cout << "| |__ ___) | |__| | ___/| |___ ___) | | |       \n";
	std::cout << " `___` ____/`____/|_|   |_____|___ /  |_|       \n";
	std::cout << " -----------------------------------------------\n";
	
	setColor(0x02);
	std::cout << "Hello, Welcome to CSOPESY commandline!\n";
	setColor(0x0E);
	std::cout << "Type 'exit' to quit, 'clear' to clear the screen, '?' to view command list\n";
	setColor(0x07);
}

std::string getCurrentTimestamp() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%m/%d/%Y, %I:%M:%S %p", &tstruct);
    return buf;
}

void initialize() {
	std::cout << "'initialize' command recognized. Doing something.\n";
}

void screen_r(const std::string& name) {
	if (inScreen == false && (screens.find(name) != screens.end())) {
		system("cls");
		ScreenData& screen = screens[name];
		screen.currentLine++;
		std::cout << "Process Name: " << screen.processName << "\n";
		std::cout << "Current line: " << screen.currentLine << "/" << screen.totalLines << "\n";
		std::cout << "Timestamp: " << screen.timestamp << "\n\n";
		setColor(0x0E);
		std::cout << "Type 'exit' to go back to the main menu, '?' to view command list\n";
		setColor(0x07);
		inScreen = true;
	} else if(inScreen == true){
		std::cout << "Command not recognized.\n";
	} else {
		std::cout << "Screen '" << name << "' not found.\n";
	}
}

void screen_s(const std::string& name) {
	if (inScreen == false) {
		system("cls");
		ScreenData newScreen;
		newScreen.processName = name;
		newScreen.currentLine = 0;
		newScreen.totalLines = 100;
		newScreen.timestamp = getCurrentTimestamp();

		screens[name] = newScreen;
		std::cout << "Process Name: " << newScreen.processName << "\n";
		std::cout << "Current line: " << newScreen.currentLine << "/" << newScreen.totalLines << "\n";
		std::cout << "Timestamp: " << newScreen.timestamp << "\n\n";
		setColor(0x0E);
		std::cout << "Type 'exit' to go back to the main menu, '?' to view command list\n";
		setColor(0x07);
		inScreen = true;
	} else {
		std::cout << "Command not recognized.\n";
	}

}

void scheduler_test() {
	std::cout << "'scheduler-test' command recognized. Doing something.\n";
}

void scheduler_stop() {
	std::cout << "'scheduler-stop' command recognized. Doing something.\n";
}

void report_util() {
	std::cout << "'report-util' command recognized. Doing something.\n";
}

void clear() {
	std::cout << "'clear' command recognized. Clearing screen.\n";
	#ifdef _WIN32
	system("cls"); // Windows-specific clear command
	#else
	system("clear"); // Unix/Linux/Mac-specific clear command
	#endif
	header();
}

void exit_screen() {
	inScreen = false;
	system("cls");
	header();
}

void exit() {
	if (inScreen) {
        exit_screen();
    } else {
        std::cout << "'exit' command recognized. Exiting program.\n";
        exit(0);
    }
}

void nvidia() {
	// GPU
    std::cout << "+-----------------------------------------------------------------------------------------+\n";
    std::cout << "| NVIDIA-SMI 551.86                 Driver Version: 551.86         CUDA Version: 12.4     |\n";
    std::cout << "|-----------------------------------------+------------------------+----------------------+\n";
    std::cout << "| GPU  Name                     TCC/WDDM  | Bus-Id          Disp.A | Volatile Uncorr. ECC |\n";
    std::cout << "| Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |\n";
    std::cout << "|                                         |                        |               MIG M. |\n";
    std::cout << "|=========================================+========================+======================|\n";
    std::cout << "|   0  NVIDIA GeForce GTX 1080      WDDM  |   00000000:26:00.0  On |                  N/A |\n";
    std::cout << "| 28%   37C    P8             11W / 180W  |     701MiB /   8192MiB |      0%      Default |\n";
    std::cout << "|                                         |                        |                  N/A |\n";
    std::cout << "+-----------------------------------------+------------------------+----------------------+\n\n";
    
    // Dummy processes
    std::cout << "+-----------------------------------------------------------------------------------------+\n";
    std::cout << "| Processes:                                                                              |\n";
    std::cout << "|  GPU   GI   CI        PID   Type   Process name                              GPU Memory |\n";
    std::cout << "|        ID   ID                                                               Usage      |\n";
    std::cout << "|=========================================================================================|\n";
    
    // Process 1
    std::cout << "|    " 
              << std::setw(1) << std::left << truncateText("0", 1) << "   "
              << std::setw(3) << truncateText("N/A", 3) << "  "
              << std::setw(3) << truncateText("0", 3) << "     "
              << std::setw(5) << formatPID("123", 5) << "   "
              << std::setw(4) << truncateText("C", 4) << "   "
              << std::setw(35) << truncateText("hello.exe", 35) << "       "
              << std::setw(10) << truncateText("500MiB", 10) << " |\n";
    
    // Process 2
    std::cout << "|    "  
              << std::setw(1) << std::left << truncateText("0", 1) << "   "
              << std::setw(3) << truncateText("1", 3) << "  "
              << std::setw(3) << truncateText("N/A", 3) << "     "
              << std::setw(5) << formatPID("4567", 5) << "   "
              << std::setw(4) << truncateText("G", 4) << "   "
              << std::setw(35) << truncateText("program.exe", 35) << "       "
              << std::setw(10) << truncateText("1200MiB", 10) << " |\n";
    
    // Process 3
    std::cout << "|    "
              << std::setw(1) << std::left << truncateText("0", 1) << "   "
              << std::setw(3) << truncateText("0", 3) << "  "
              << std::setw(3) << truncateText("1", 3) << "     "
              << std::setw(5) << formatPID("8910", 5) << "   "
              << std::setw(4) << truncateText("C", 4) << "   "
              << std::setw(35) << truncateText("C:\\Windows\\Windows32\\very_long_process_name.exe", 35) << "       "
              << std::setw(10) << truncateText("700MiB", 10) << " |\n";
    
    // Process 4
    std::cout << "|    " 
              << std::setw(1) << std::left << truncateText("0", 1) << "   "
              << std::setw(3) << truncateText("1", 3) << "  "
              << std::setw(3) << truncateText("1", 3) << "     "
              << std::setw(5) << formatPID("1112", 5) << "   "
              << std::setw(4) << truncateText("G", 4) << "   "
              << std::setw(35) << truncateText("C:\\Windows\\welcome.exe", 35) << "       "
              << std::setw(10) << truncateText("150MiB", 10) << " |\n";
    
    // Process 5
    std::cout << "|    "
              << std::setw(1) << std::left << truncateText("0", 1) << "   "
              << std::setw(3) << truncateText("0", 3) << "  "
              << std::setw(3) << truncateText("0", 3) << "     "
              << std::setw(5) << formatPID("13", 5) << "   "
              << std::setw(4) << truncateText("C", 4) << "   "
              << std::setw(35) << truncateText("game.exe", 35) << "       "
              << std::setw(10) << truncateText("300MiB", 10) << " |\n";
    std::cout << "+-----------------------------------------------------------------------------------------+\n";
}

void command_list() {
	setColor(0x0E);
	std::cout << "\nAvailable Commands:\n";
	
	if (inScreen) {
		setColor(0x02);
		std::cout << "'exit' - return to the main menu\n";
		setColor(0x07);
	} else {
		setColor(0x02);
		std::cout << "'initialize'\n";
		std::cout << "'screen -r <screen name>' - load a screen\n";
		std::cout << "'screen -s <screen name>' - create/save a screen\n";
		std::cout << "'scheduler-test'\n";
		std::cout << "'scheduler-stop'\n";
		std::cout << "'report-util'\n";
		std::cout << "'nvidia-smi' - view GPU & processes\n";
		std::cout << "'clear' - clear the screen\n";
		std::cout << "'exit' - exit the terminal\n";
		setColor(0x07);
	}
}

std::pair<std::string, std::string> parseCommand(const std::string& input) {
	std::istringstream stream(input);
	std::string cmd, argument;
	stream >> cmd;
	std::getline(stream, argument);
	if (!argument.empty() && argument[0] == ' ') {
	argument = argument.substr(1);
	}
	return {cmd, argument};
}

int main() {
	header();
	std::string input;
	
	while (true) {
		std::cout << "Enter a command: ";
		std::getline(std::cin, input);
		
		std::pair<std::string, std::string> parsedCommand = parseCommand(input);
		std::string cmd = parsedCommand.first;
		std::string argument = parsedCommand.second;
		
		//  initialize , screen, scheduler-test, scheduler-stop , report-util
		if (cmd == "initialize"  && inScreen == false) {
			initialize();
		} else if (cmd == "screen" && argument.substr(0, 2) == "-r") {
			std::string screenName = argument.substr(3);
			screen_r(screenName);
		} else if (cmd == "screen" && argument.substr(0, 2) == "-s") {
			std::string screenName = argument.substr(3);
			screen_s(screenName);
		} else if (cmd == "scheduler-test" && inScreen == false) {
			scheduler_test();
		} else if (cmd == "scheduler-stop" && inScreen == false) {
			scheduler_stop();
		} else if (cmd == "report-util" && inScreen == false) {
			report_util();
		} else if (cmd == "nvidia-smi") {
			nvidia();
		} else if (cmd == "clear" && inScreen == false) {
			clear();
		} else if (cmd == "exit") {
			exit();
		} else if (cmd == "?") {
			command_list();
		} else std::cout << "Command not recognized.\n";
	}
}
