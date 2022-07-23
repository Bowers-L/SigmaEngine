#include <sigma.h>

class sandboxapp : public Sigma::Application 
{
public:
	sandboxapp() {
		
	}

	~sandboxapp() {

	}
};

Sigma::Application* Sigma::CreateApplication() {
	return new sandboxapp();
}