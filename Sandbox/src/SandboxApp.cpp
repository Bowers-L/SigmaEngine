#include <sigma.h>

class SandboxApp : public SigmaEngine::Application
{
};

SigmaEngine::Application* SigmaEngine::CreateApplication() {
	return new Application();
}