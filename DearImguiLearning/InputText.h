#ifndef INPUTTEXT_HPP
#define INPUTTEXT_HPP

#include "Widget.hpp"

class InputText : public Widget {
private:
	char* title = nullptr;
	char* input = nullptr;

public:
	InputText(char* title, char* input) {
		this->title = title;
		this->input = input;
	}
	~InputText() {
		delete this->title;
		delete this->input;
	}

	char* getInput() { return this->input; }

	void iterateBehaviors() {
		// Check trigger
		if (ImGui::InputText(this->title, this->input, 255)) {
			// Act according to behaviors
			for (auto & currentBehavior : this->behaviors) {
				currentBehavior(this);
			}
		}
	}
};



#endif 
