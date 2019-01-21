#ifndef DISPLAYTEXT_HPP
#define DISPLAYTEXT_HPP

#include "Widget.hpp"
#include <string>

class DisplayText : public Widget {
public:
	DisplayText() {}
	~DisplayText() {}

	void iterateBehaviors() {
		// Iterate through behaviors
		for (auto & currentBehavior : this->behaviors) {
			currentBehavior(this);
		}
	}
};

#endif 