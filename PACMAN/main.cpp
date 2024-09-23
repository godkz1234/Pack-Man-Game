#include"Util.h"
#include"MainFrame.h"

int main() {
	MainFrame* mainFrame = new MainFrame(100);

	while (mainFrame->isRunning()) {
		mainFrame->Update();
		mainFrame->Render();
	}
	
}