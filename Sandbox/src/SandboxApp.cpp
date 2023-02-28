#include <sigma.h>

class SandboxApp : public SigmaEngine::Application
{
public:
	SandboxApp() {
		
	}

	~SandboxApp() {

	}
};

SigmaEngine::Application* SigmaEngine::CreateApplication() {
	return new SandboxApp();
}