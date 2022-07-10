#include <Sigma.h>

class SandboxApp : public Sigma::Application 
{
public:
	SandboxApp() {
		
	}

	~SandboxApp() {

	}
};

Sigma::Application* Sigma::CreateApplication() {
	return new SandboxApp();
}