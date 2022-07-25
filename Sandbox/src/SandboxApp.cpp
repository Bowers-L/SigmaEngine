#include <sigma.h>

class sandboxapp : public SigmaEngine::Application
{
public:
	sandboxapp() {
		
	}

	~sandboxapp() {

	}
};

SigmaEngine::Application* SigmaEngine::CreateApplication() {
	return new sandboxapp();
}